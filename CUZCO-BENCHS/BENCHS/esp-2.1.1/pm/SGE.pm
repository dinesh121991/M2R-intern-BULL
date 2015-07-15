package SGE;

use FileHandle;

sub new {
  return bless  {};
}

sub AUTOLOAD {

}


sub round
{
        my ($num) = shift;
        return int( ($num + 0.500) );
}


#
# --------------------------------------------------
# SGE specific subroutines
# --------------------------------------------------
#
#  Number of processors busy
#
sub getrunning
{
    my $nrunpe, @fields;
    $nrunpe = 0;
    open( LLS, "qstat -f | grep BIP|");
    while (<LLS>) {
	@fields = split " ", $_;
	@pes = split "/", $fields[2];
	$nrunpe += $pes[0];
    }
    close(LLS);
    return $nrunpe;
}

#
#  Monitor & log batch queues
#
sub monitor_queues
{
    my $nque, $nrun, @fields, $nrunpe;
    my $sleeptime, $txx0, $ty;
    
    sleep($_[0]);
    $nque = 0;
    $nrun = 0;
    open( QSTAT, "qstat -u tdavis 2>/dev/null |");
    while (<QSTAT>) {
	@fields = split " ", $_;
        if  ($fields[4] eq "qw" ) {
  	  ++$nque;
	} elsif ($fields[4] eq "r" && $fields[8] eq "MASTER" ) {
	  ++$nrun;
	}
    }
    close(QSTAT);
    $nrunpe = getrunning();
    $espdone = !($nque || $nrun || $nrunpe);
    printf("%d I nrun: %d, nrunpe: %d, nque: %d, espdone: %d\n", epoch(), $nrun, $nrunpe, $nque, $espdone);
    printf LOG "%d  I  Runjobs: %d %d PEs   Queued: %d\n", epoch(), $nrun, $nrunpe, $nque;
}

$qsub = " qsub";

#
#  Fork and submit job
#
sub submit
{
    my $pid, $subcmd, $err, $doit;

    $subcmd = $qsub . " " . $_[1];
    $doit   = $_[2];
    if (!defined($pid=fork())) {
	print "Cannot fork!\n";
	exit(1);
    } elsif (!$pid) {
	chdir("jobmix/SGE") || die "cannot chdir!\n";
	open STDERR, ">/dev/null" || die "cannot redirect stderr\n";
	if (!$doit) {
	    print "  SUBMIT -> $subcmd \n";
	} 
        else {
	    exec("$subcmd");
        }
	exit(0);
    } else {
	$err = waitpid($pid, 0);
    }
}

sub create_jobs
{
    $esp = $main::esp;
    $out = $main::espout . "/SGE";
    $scratch = $main::scratch;
    foreach $j (keys %main::jobdesc) {
	@jj = @{ $main::jobdesc{$j} };
	$cline = "./pchksum -t $jj[5]";
	@cmd = split " ", $cline;
	for ($i=0; $i<$jj[1]; ++$i) {
	    $nodecount = round($jj[0] * $main::syssize);
	    $joblabel = sprintf("%s_%03d_%03d", $j, $nodecount, $i);
	    $workdir = "$scratch/$joblabel";
	    open(NQS, ">SGE/$joblabel");
#
#  "here" template follows 
#  adapt to site batch queue system
#
	print NQS <<"EOF";
#\!/bin/sh
#\$ -N $joblabel
#\$ -o $espout/$joblabel.out
#\$ -j y
#\$ -pe mpich $jj[2]
#\$ -cwd
#\$ -p $jj[5]
#
ESP=$esp
t0=`\$ESP/Epoch`

test -d ~/.gmpi || mkdir ~/.gmpi
GMCONF=~/.gmpi/conf.\$JOB_ID
sgenodefile2gmconf \$PE_HOSTFILE >\$GMCONF
NP=\$(head -1 \$GMCONF)

echo \$t0 " S " $joblabel "  Seq# SEQNUM"

mkdir -p $workdir
cp $esp/exe/* $workdir
cd $workdir

$main::timer mpirun.ch_gm --gm-kill 10 --gm-f \$GMCONF -np \$NP $cline

echo `\$ESP/Epoch` " F " $joblabel "  Seq# SEQNUM"

rm -f \$GMCONF
EOF
#
#  end "here" document
#
	    close(NQS);
	}
    }
}

1;
