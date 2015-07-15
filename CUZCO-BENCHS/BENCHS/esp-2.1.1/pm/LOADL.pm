package LOADL;

use FileHandle;

# 
# Site variables
#
# Number of processors per node
#
$proc_smp = 16;

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
#  Loadleveler specific subroutines (LOADL)
# --------------------------------------------------
#
#  Number of processors busy
#
sub getrunning
{
    my $nrunpe, @fields;
    $nrunpe = 0;
    open( LLS, "llstatus -r %r |");
    while (<LLS>) {
      $nrunpe += $_
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

    sleep($_[1]);
    $nque = 0;
    $nrun = 0;
    open( QSTAT, "llq -u $ENV{USER} -r %st 2>/dev/null |");
    while (<QSTAT>) {
	++$nque if (/^I/);
	++$nrun if (/^R/);
    }
    close(QSTAT);
    $espdone = !($nque || $nrun);
    $nrunpe = getrunning();
    printf(    "%d  I  Runjobs: %d %d PEs   Queued: %d\n", time(), $nrun, $nrunpe, $nque);
    printf main::LOG "%d  I  Runjobs: %d %d PEs   Queued: %d\n", time(), $nrun, $nrunpe, $nque;
    return $espdone;
}


#
#  Fork and submit job
#
sub submit
{
    my $pid, $subcmd, $err, $doit;

    $doit   = $_[2];
    $subcmd = "llsubmit " . $_[1];
    $subcmd = "printf \"SUBMIT -> $_[1]\n\"" if (!$doit);
    if (!defined($pid=fork())) {
	print "Cannot fork!\n";
	exit(1);
    }
    elsif (!$pid) {
	open STDERR, ">/dev/null" || die "cannot redirect stderr\n";
	exec("$subcmd");
	exit(0);
    }
    else {
	$err = waitpid($pid, 0);
    }
}



#
#  Create batch scripts
#  
#
sub create_jobs
{
    $esp = $main::ESPHOME;
    $out = "$main::ESPHOME/logs";
    foreach $j (keys %main::jobdesc) {
	@jj = @{ $main::jobdesc{$j} };
	$cline     = "\$ESP/pchksum -t $jj[2]";
	$taskcount = round($jj[0] * $main::syssize);
        $nnode     = int(($taskcount/$proc_smp)) + (($taskcount % $proc_smp) ? 1 : 0);
	$class     = ($j eq "Z") ? "system"  : "special1";
	$wlimit    = ($j eq "Z") ? "00:03:00" : "10:00:00";
	for ($i=0; $i<$jj[1]; ++$i) {
	    $joblabel = sprintf("%s_%04d_%03d", $j, $taskcount, $i);
	    open(NQS, "> $joblabel") || die("open failed");
#
#  "here" template follows 
#  adapt to site batch queue system
#
	print NQS <<"EOF";
# @ job_type         = parallel
# @ job_name         = $joblabel
# @ output           = $out/$joblabel.out
# @ error            = $out/$joblabel.out
# @ notification     = never
# @ environment      = \$SEQNUM
# @ node_usage       = not_shared
# @ class            = $class
# @ network.MPI      = csss,shared,us
# @ wall_clock_limit = $wlimit
# @ node             = $nnode
# @ total_tasks      = $taskcount
#
# @ queue
export ESP=$esp
echo `\$ESP/epoch` " S  $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG
$cline
echo `\$ESP/epoch` " F  $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG
EOF
#
#  end "here" document
#
	    close(NQS);
	    chmod 0744, "$joblabel";
	}
    }
}

1;
