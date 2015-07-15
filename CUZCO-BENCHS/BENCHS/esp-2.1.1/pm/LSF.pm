package LSF;
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
# LSF specific subroutines
# --------------------------------------------------
#
#  Number of processors busy
#
sub getrunning
{
    my $nrunpe, @fields;
    $nrunpe = 0;
    open( LLS, "qstat normal | grep run|");
    while (<LLS>) {
	@fields = split " ", $_;
	$nrunpe += $fields[0];
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
    open( QSTAT, "bjobs |");
    while (<QSTAT>) {
	@fields = split " ", $_;
	if ($fields[2] eq "PEND") {
	  ++$nque;
	}
	if ($fields[2] eq "RUN" ) {
	  ++$nrun;
	}
#	print "nque = $nque nrun = $nrun\n";
    }
    close(QSTAT);
    $nrunpe = getrunning();
    $main::espdone = !($nque || $nrun || $nrunpe);
    $myepoch = main::epoch();

    printf("%d I nrun: %d, nrunpe: %d, nque: %d, espdone: %d\n", $myepoch, $nrun, $nrunpe, $nque, $main::espdone);
    printf main::LOG "%d  I  Runjobs: %d %d PEs Queued: %d espdone: %d\n", $myepoch, $nrun, $nrunpe, $nque, $main::espdone;
}

#
#  Fork and submit job
#
sub submit
{
    my $pid, $subcmd, $err;
    my $doit;

    $subcmd = "bsub < " . $_[1];
    $doit   = $_[2];
    print "subcmd = $subcmd\n";
    if (!defined($pid=fork())) {
	print "Cannot fork!\n";
	exit(1);
    } elsif (!$pid) {
	chdir("jobmix/LSF") || die "cannot chdir!\n";
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




sub makereservation 
{
    my $pid, $subcmd, $err;
    $startdate = `date -d "+1 min" +%H:%M`;
    $enddate = `date -d "+5 min" +%H:%M`;

    chop $startdate;
     chop $enddate;

    foreach $i (`bhosts`) {
      ($host,$null) = split / /, $i;
      if ($host ne "HOST_NAME") {
	$hosts = $hosts . $host . " ";
      }
    }

    ($null, $reservation, $null)  = split " ", `brsvadd -n 32 -m "$hosts" -u tdavis -b $startdate -e $enddate`;
    print "reservation = $reservation\n";

}

sub create_jobs 
{
    $esp = $main::esp;
    $out = $main::espout . "/LSF";
    $scratch = $main::scratch;
    foreach $j (keys %main::jobdesc) {
	@jj = @{ $main::jobdesc{$j} };
	$cline = "./pchksum -t $jj[4]";
	@cmd = split " ", $cline;
	for ($i=0; $i<$jj[1]; ++$i) {
	    if ($::packed) {
		$nodecount = round($jj[0] * $main::syssize);
		$nodes = "span[ptile=2]"
	    } else {
		$nodecount = round($jj[0] * $main::syssize);
		$needed = $nodecount;
		$nodes = "span[ptile=1]"
	    }
	    $joblabel = sprintf("%s_%03d_%03d", $j, $nodecount, $i);
	    $workdir = "$scratch/$joblabel";
	    open(NQS, ">LSF/$joblabel");
#	print "nodecount = $nodecount, jj[7]=$jj[7], machinesize=$machinesize\n";
#
#  "here" template follows 
#  adapt to site batch queue system
#
	print NQS <<"EOF";
#\!/bin/sh
#BSUB -n $nodecount
#BSUB -R $nodes
#BSUB -o $out/$joblabel.out
#BSUB -J $joblabel
#BSUB -sp $jj[5]
##BSUB -x
#
ESP=$esp

echo `\$ESP/Epoch` " S " $joblabel "  Seq# SEQNUM"

mkdir -p $workdir
cp $esp/exe/* $workdir
cd $workdir

# How many proc do I have?
NP=\$(wc -l /tmp/nodelist.\$LSB_JOBID | awk '{print \$1}')

echo "starting mpirun.."

$main::timer mpirun.ch_gm --gm-kill 10 -machinefile /tmp/nodelist.\$LSB_JOBID -np \$NP $cline

echo "mpirun finished."

echo `\$ESP/Epoch` " F " $joblabel "  Seq# SEQNUM"

EOF
#
#  end "here" document
#
	    close(NQS);
	}
    }
}

1;
