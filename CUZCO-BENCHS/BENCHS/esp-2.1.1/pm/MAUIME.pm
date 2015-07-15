package MAUIME;
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



#---------------------------------------------------------
# MauiME-specific functions
#---------------------------------------------------------

#----------------------------------------------------------------------
# getClusterStatus - uses 'showq' to get number of active PEs
# Returns an array of the following in this order:
#	Number of Active PEs	( $numActivePE )
#	Number of Active Nodes	( $numActiveNodes )
#	Number of Active Jobs	( $numActiveJobs )
#	Number of Queued Jobs	( $numQueuedJobs )
#----------------------------------------------------------------------
sub getClusterStatus
{
	my $numActivePE, $numActiveNodes, $numActiveJobs, $numQueuedJobs;
	open( SHOWQ, "/usr/local/mauime/bin/showq |");
	while( <SHOWQ> )
	{
		if ( /Active:/ )
		{
 			s/Active: (\d+)\/\((\d+)//;

			$numActiveNodes = $1;
			$numActivePE = $2;
		}
		if ( /ACTIVE JOBS:/ )
		{
			s/(\d+)$//;
			$numActiveJobs = $1;
		}
		if ( /QUEUED JOBS:/ )
		{
			s/(\d+)$//;
			$numQueuedJobs = $1;
		}
	}
	close( SHOWQ );
	return( $numActivePE, $numActiveNodes, $numActiveJobs, $numQueuedJobs );
	
}

#----------------------------------------------------------------------
# getrunning - some shorthand
#----------------------------------------------------------------------
sub getrunning
{
	return (&getClusterStatus)[0];
}

#----------------------------------------------------------------------
# monitor_queues - uses &getClusterStatus to get state of the queues.
# Takes one argument: time to sleep in seconds before getting info
# and printing. With no argument there's no sleeping.
#----------------------------------------------------------------------
sub monitor_queues
{
	my $numActivePE, $unused, $numActiveJobs, $numQueuedJobs;

	sleep($_[1]) if  $_[1] != "";
	( $numActivePE, $unused, $numActiveJobs, $numQueuedJobs ) =
		&getClusterStatus;
	$espdone = !( $numQueuedJobs || $numActiveJobs || $numActivePE );
	printf("%d  I  Runjobs: %d PEs %d  Queued: %d espdone: %d\n",
		main::epoch(), $numActiveJobs, $numActivePE, $numQueuedJobs);
	printf(main::LOG "%d  I  Runjobs: %d PEs: %d  Queued: %d espdone: %d\n",
		main::epoch(), $numActiveJobs, $numActivePE, $numQueuedJobs);
}


#
#  Fork and submit job
#
sub submit
{
    my $pid, $subcmd, $err, $doit;
    $subcmd = "mauisubmit " . $_[1] . ".cmd";
    $doit   = $_[2];

    if (!defined($pid=fork())) {
	print "Cannot fork!\n";
	exit(1);
    } elsif (!$pid) {
	chdir("jobmix/MAUIME") || die "cannot chdir!\n";
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
    $scratch = $main::scratch;
    $espout = $main::espout . "/MauiME";
    $espbin = $main::esp;
    $jobmix = $esp . "/jobmix/MAUIME";

    foreach $j (keys %main::jobdesc) {
	@jj = @{ $main::jobdesc{$j} };
	$cline = $esp . "/exe/pchksum -t $jj[4]";
	@cmd = split " ", $cline;
	for ($i=0; $i<$jj[1]; ++$i)
	{
		if ($::packed) {
		    $pePerNode = 2;
		    $nodecount = round($jj[0] * $main::syssize / 2);
		    $numPE= $nodecount * $pePerNode;
		} else {
		    $pePerNode = 1;
		    $nodecount = round($jj[0] * $main::syssize);
		    $numPE= $nodecount;
		}

		$joblabel = sprintf("%s_%03d_%03d", $j, $nodecount, $i);
		open(SH, ">MAUIME/$joblabel");
		open(CMD, ">MAUIME/".$joblabel.".cmd");
		#print "nodecount = $nodecount, jj[7]=$jj[7], machinesize=$machinesize\n";
		print CMD <<"EOF_CMD";
# Initial working directory and wallclock time
IWD == "$scratch"
WCLimit == "3600"
# Account stanza
Account == "tdavis"
# Task geometry
Nodes == $nodecount
Tasks == $numPE
TaskPerNode == $pePerNode
# Feature requests
Arch == x86
OS == Linux
# MPI Myrinet job
JobType == "mpi.ch_gm"
# Launch script (SEE NOTE BELOW)
Exec == "$jobmix/$joblabel"
# NOTE: args, if any, are separated by whitespace ` '
#Args == ""
# Output (Notice the envvar references!)
Output == "$espout/$joblabel.out"
Error  == "$espout/$joblabel.err"
Log    == "$espout/$joblabel.log"
# Stdin tied to null
Input == "/dev/null"
EOF_CMD
close CMD;


print SH <<"EOF_SH";
#!/bin/sh

MAUI_TASK_COUNT=$numPE
export MAUI_TASK_COUNT

echo `$espbin/Epoch` " S " $joblabel "  Seq# SEQNUM"
mkdir -p $scratch

#test -d ~/.gmpi || mkdir ~/.gmpi
#GMCONF=~/.gmpi/conf.\$MAUI_JOB_ID
#
## create tasks file
#touch \$GMCONF
#for node in `echo \$MAUI_JOB_TASKS | sed -e 's/:/ /g'` ; do
#        echo \$node >> \$GMCONF
#done
#
#NP=\$(wc -l \$GMCONF | awk '{print \$1}')
#
#echo "tasks_file=\$GMCONF, NP=\$NP"
#
#$main::timer mpirun.ch_gm -machinefile \$GMCONF --gm-kill 10 -np \$NP $cline
#
#rm -f \$GMCONF

#$main::timer sh -x /usr/local/mauime/bin/runmpi_gm $cline
$main::timer /usr/local/mauime/bin/runmpi_gm $cline
echo `$espbin/Epoch` " F " $joblabel "  Seq# SEQNUM"
EOF_SH
		close SH;
		`chmod +x "MAUIME/$joblabel"`;

	    }

    }

}

1;
