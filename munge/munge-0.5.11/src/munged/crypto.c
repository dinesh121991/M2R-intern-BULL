/*****************************************************************************
 *  Written by Chris Dunlap <cdunlap@llnl.gov>.
 *  Copyright (C) 2007-2013 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2002-2007 The Regents of the University of California.
 *  UCRL-CODE-155910.
 *
 *  This file is part of the MUNGE Uid 'N' Gid Emporium (MUNGE).
 *  For details, see <https://munge.googlecode.com/>.
 *
 *  MUNGE is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.  Additionally for the MUNGE library (libmunge), you
 *  can redistribute it and/or modify it under the terms of the GNU Lesser
 *  General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *
 *  MUNGE is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  and GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  and GNU Lesser General Public License along with MUNGE.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *****************************************************************************/


#if HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <errno.h>
#include <munge.h>
#include <pthread.h>
#include <stdlib.h>
#include "crypto.h"
#include "cipher.h"
#include "md.h"
#include "log.h"


/*****************************************************************************
 *  Libgcrypt Functions
 *****************************************************************************/

#if HAVE_LIBGCRYPT

#include <gcrypt.h>


GCRY_THREAD_OPTION_PTHREAD_IMPL;


void
crypto_init (void)
{
    gcry_error_t e;

    e = gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
    if (e) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to set Libgcrypt thread callbacks: %s", gcry_strerror (e));
    }
    /*  Initialize subsystems, but omit the Libgcrypt version check.
     */
    if (!gcry_check_version (NULL)) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to start Libgcrypt initialization");
    }
    e = gcry_control (GCRYCTL_DISABLE_SECMEM, 0);
    if (e) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to disable Libgcrypt secure memory: %s",
            gcry_strerror (e));
    }
    e = gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
    if (e) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to finish Libgcrypt initialization: %s",
            gcry_strerror (e));
    }
    cipher_init_subsystem ();
    md_init_subsystem ();
    return;
}


void
crypto_fini (void)
{
    return;
}

#endif /* HAVE_LIBGCRYPT */


/*****************************************************************************
 *  OpenSSL Functions
 *****************************************************************************/

#if HAVE_OPENSSL

#include <assert.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <string.h>
#include "str.h"


#define OPENSSL_LOG_MAX_ERR_LEN         1024


static pthread_mutex_t *openssl_mutex_array = NULL;


static unsigned long _openssl_thread_id (void);
static void _openssl_thread_locking (int mode, int n,
    const char *file, int line);


#if HAVE_CRYPTO_DYNLOCK

struct CRYPTO_dynlock_value {
    pthread_mutex_t mutex;
};

static struct CRYPTO_dynlock_value * _openssl_thread_dynlock_create (
    const char *file, int line);
static void _openssl_thread_dynlock_lock (
    int mode, struct CRYPTO_dynlock_value *lock, const char *file, int line);
static void _openssl_thread_dynlock_destroy (
    struct CRYPTO_dynlock_value *lock, const char *file, int line);

#endif /* HAVE_CRYPTO_DYNLOCK */


void
crypto_init (void)
{
    int n;
    int i;

    if (openssl_mutex_array) {
        return;
    }
    if ((n = CRYPTO_num_locks ()) <= 0) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to determine requisite number of OpenSSL locks");
    }
    if (!(openssl_mutex_array = malloc (n * sizeof (pthread_mutex_t)))) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to allocate %d OpenSSL locks", n);
    }
    for (i = 0; i < n; i++) {
        errno = pthread_mutex_init (&openssl_mutex_array[i], NULL);
        if (errno != 0) {
            log_errno (EMUNGE_SNAFU, LOG_ERR,
                "Failed to init OpenSSL mutex %d", i);
        }
    }
    CRYPTO_set_id_callback (_openssl_thread_id);
    CRYPTO_set_locking_callback (_openssl_thread_locking);

#if HAVE_CRYPTO_DYNLOCK
    CRYPTO_set_dynlock_create_callback (_openssl_thread_dynlock_create);
    CRYPTO_set_dynlock_lock_callback (_openssl_thread_dynlock_lock);
    CRYPTO_set_dynlock_destroy_callback (_openssl_thread_dynlock_destroy);
#endif /* HAVE_CRYPTO_DYNLOCK */

    cipher_init_subsystem ();
    md_init_subsystem ();
    return;
}


void
crypto_fini (void)
{
    int n;
    int i;

    if (!openssl_mutex_array) {
        return;
    }
    CRYPTO_set_id_callback (NULL);
    CRYPTO_set_locking_callback (NULL);

#if HAVE_CRYPTO_DYNLOCK
    CRYPTO_set_dynlock_create_callback (NULL);
    CRYPTO_set_dynlock_lock_callback (NULL);
    CRYPTO_set_dynlock_destroy_callback (NULL);
#endif /* HAVE_CRYPTO_DYNLOCK */

    if ((n = CRYPTO_num_locks ()) <= 0) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to determine requisite number of OpenSSL locks");
    }
    for (i = 0; i < n; i++) {
        errno = pthread_mutex_destroy (&openssl_mutex_array[i]);
        if (errno != 0) {
            log_msg (LOG_ERR,
                "Failed to destroy OpenSSL mutex %d: %s", i, strerror (errno));
        }
    }
    free (openssl_mutex_array);
    openssl_mutex_array = NULL;
    return;
}


static unsigned long
_openssl_thread_id (void)
{
    return ((unsigned long) pthread_self ());
}


static void
_openssl_thread_locking (int mode, int n, const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        errno = pthread_mutex_lock (&openssl_mutex_array[n]);
        if (errno != 0) {
            log_errno (EMUNGE_SNAFU, LOG_ERR,
                "Failed to lock OpenSSL mutex %d", n);
        }
    }
    else {
        errno = pthread_mutex_unlock (&openssl_mutex_array[n]);
        if (errno != 0) {
            log_errno (EMUNGE_SNAFU, LOG_ERR,
                "Failed to unlock OpenSSL mutex %d", n);
        }
    }
    return;
}


#if HAVE_CRYPTO_DYNLOCK

static struct CRYPTO_dynlock_value *
_openssl_thread_dynlock_create (const char *file, int line)
{
    struct CRYPTO_dynlock_value *lock;

    if (!(lock = malloc (sizeof (struct CRYPTO_dynlock_value)))) {
        log_err (EMUNGE_SNAFU, LOG_ERR,
            "Failed to allocate OpenSSL dynamic lock");
    }
    errno = pthread_mutex_init (&lock->mutex, NULL);
    if (errno != 0) {
        log_errno (EMUNGE_SNAFU, LOG_ERR,
            "Failed to init OpenSSL dynamic mutex");
    }
    return (lock);
}


static void
_openssl_thread_dynlock_lock (int mode, struct CRYPTO_dynlock_value *lock,
                              const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        errno = pthread_mutex_lock (&lock->mutex);
        if (errno != 0) {
            log_errno (EMUNGE_SNAFU, LOG_ERR,
                "Failed to lock OpenSSL dynamic mutex");
        }
    }
    else {
        errno = pthread_mutex_unlock (&lock->mutex);
        if (errno != 0) {
            log_errno (EMUNGE_SNAFU, LOG_ERR,
                "Failed to unlock OpenSSL dynamic mutex");
        }
    }
    return;
}


static void
_openssl_thread_dynlock_destroy (struct CRYPTO_dynlock_value *lock,
                                 const char *file, int line)
{
    errno = pthread_mutex_destroy (&lock->mutex);
    if (errno != 0) {
        log_msg (LOG_ERR,
            "Failed to destroy OpenSSL dynamic mutex: %s", strerror (errno));
    }
    free (lock);
    return;
}


void
openssl_log_msg (int priority)
{
    int         e;
    const char *data;
    int         flags;
    char        buf [OPENSSL_LOG_MAX_ERR_LEN];

    ERR_load_crypto_strings ();
    while ((e = ERR_get_error_line_data (NULL, NULL, &data, &flags)) != 0) {
#if HAVE_ERR_ERROR_STRING_N
        ERR_error_string_n (e, buf, sizeof (buf));
#else  /* !HAVE_ERR_ERROR_STRING_N */
        assert (sizeof (buf) >= 120);
        ERR_error_string (e, buf);
#endif /* !HAVE_ERR_ERROR_STRING_N */
        if (data && (flags & ERR_TXT_STRING)) {
            (void) strcatf (buf, sizeof (buf), ":%s", data);
        }
        log_msg (priority, "%s", buf);
    }
    ERR_free_strings ();
    return;
}

#endif /* HAVE_CRYPTO_DYNLOCK */


#endif /* HAVE_OPENSSL */


/*****************************************************************************
 *  Common Functions
 *****************************************************************************/

int
crypto_memcmp (const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = s1;
    const unsigned char *b = s2;
    size_t               i;
    unsigned char        x;

    for (i = 0, x = 0; i < n; i++) {
        x |= a[i] ^ b[i];
    }
    return (x != 0);
}
