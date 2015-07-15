package PBS;
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
# OpenPBS specific subroutines
# --------------------------------------------------
#
#  Number of processors busy
#
sub getrunning
{
    my $nrunpe, @fields;
    $nrunpe = 0;
    open( LLS, "qstat -u $ENV{USER} |");
    while (<LLS>) {
	@fields = split " ", $_;
	if ($fields[9] eq "R") {
	  $nrunpe += $fields[5];
	}
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
    open( QSTAT, "qstat -u $ENV{USER} 2>/dev/null |");
    while (<QSTAT>) {
	@fields = split " ", $_;
        if  ($fields[9] eq "Q" ) {
  	  ++$nque;
	} elsif ($fields[9] eq "R") {
	  ++$nrun;
	}
    }
    close(QSTAT);
    $nrunpe = getrunning();
    $main::espdone = !($nque || $nrun || $nrunpe);
    printf("%d  I  Runjobs: %d PEs: %d Queued: %d espdone: %d\n", time(), $nrun, $nrunpe, $nque, $main::espdone);
    printf main::LOG "%d  I  Runjobs: %d PEs: %d Queued: %d espdone: %d\n", time(), $nrun, $nrunpe, $nque, $main::espdone;
}

#
#  Fork and submit job
#
sub submit
{
    my $pid, $subcmd, $err, $doit;

    $subcmd = "qsub " . $_[1];
    $doit   = $_[2];
    if (!defined($pid=fork())) {
	print "Cannot fork!\n";
	exit(1);
    } elsif (!$pid) {
	chdir("jobmix") || die "cannot chdir!\n";
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
    $esp = $main::ESPHOME;
    $out = $main::espout;
    foreach $j (keys %main::jobdesc) {
	@jj = @{ $main::jobdesc{$j} };
	$cline = "./pchksum -v -t $jj[2]";
        $wlimit = int($jj[2]*1.50);
	@cmd = split " ", $cline;
	for ($i=0; $i<$jj[1]; ++$i) {
	     if ($::packed) {
		 $nodecount = round($jj[0] * $main::syssize);
		 $needed = $nodecount/2;
		 $nodes = "nodes=$needed:ppn=2";
	     } else {
		 $nodecount = round($jj[0] * $main::syssize);
		 $nodes = "nodes=$nodecount:ppn=1";
	     }
	     $joblabel = sprintf("%s_%03d_%03d", $j, $nodecount, $i);
	     open(NQS, "> $joblabel");
#
#  "here" template follows 
#  adapt to site batch queue system
#
	print NQS <<"EOF";
#\!/bin/sh
#PBS -N $joblabel
#PBS -o $out/$joblabel.out
#PBS -j oe
#PBS -m n
#PBS -v SEQNUM
#PBS -l $nodes,walltime=$wlimit
ESP=$esp
t0=`\$ESP/Epoch`

# How many proc do I have?
NP=\$(wc -l \$PBS_NODEFILE | awk '{print \$1}')

cd \$PBS_O_WORKDIR

echo `\$ESP/epoch` " S  $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG
$main::timer mpirun_rsh -hostfile \$PBS_NODEFILE -np \$NP $cline
echo `\$ESP/epoch` " F  $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG

EOF
#
#  end "here" document
#
	       close(NQS);
	   }
      }
}

1;
