#
# --------------------------------------------------
# Torque/PBS specific subroutines
# --------------------------------------------------
#
use strict;
use warnings;

use BATCH;

package SLURM;

our @ISA = qw{BATCH};

sub new {
	return bless  BATCH::new;
}

#  Number of processors busy
#
sub getrunning {
   my ($nrunpe, @fields);
    $nrunpe = 0;
    #my $line;
#    my $disco = `squeue -o %C`;
    open( LLS , "/usr/local/slurm-schedmd-2.4/bin/squeue -o \'%C %N %t\' |grep R |sed \'s/l/ /g\' 2>/dev/null |");
#	open( LLS , "squeue-24 -o \'%C %N %t\' |grep R 2>/dev/null |");
   while ( <LLS> ) {
 #  while( defined( $line = <LLS> )){
   #my $line = $_;
#   	chomp($line);
#	print $line;
	$fields[0] = 0;
	$fields[1] = "";
	@fields = split " ", $_;
	#print"$fields[0],$fields[1]";
	if ($fields[1] eq "virtua") {
###CRAY count tasks, not nodes
	  $nrunpe += $fields[0];
	}
   }
    close(LLS);
    return $nrunpe;
}

#
#  Monitor & log batch queues
#
sub monitor_queues {
    my ($nque, $nrun, @fields, $nrunpe);
    my ($sleeptime, $txx0, $ty);
    
    sleep($_[1]);
    $nque = 0;
    $nrun = 0;
    open( QSTAT, "/usr/local/slurm-schedmd-2.4/bin/squeue  2>/dev/null |");
    while (<QSTAT>) {
	@fields = split " ", $_;
        if  ($fields[4] eq "PD" ) {
  	  ++$nque;
	} elsif ($fields[4] eq "R") {
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
sub submit {
    my ($pid, $subcmd, $err, $doit);

    $subcmd = "/usr/local/slurm-schedmd-2.4/bin/sbatch /home_nfs/georgioy/BENCHS/Light.ESP-2.2.1/" . $_[1];
#    system("$subcmd");
#    $subcmd = $_[1];
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
	print "  SUBMIT -> $subcmd \n";

exec("$subcmd");
	    die "commande_qui_prend_du_temps non trouvée dan}";
       }
	exit(0);
   } else {
#	$err = waitpid($pid, 0);
   }
}

sub create_jobs {
	my $self = shift;
	$self->initialize;

	my ($timer, $esphome, $espout, $packed)
		= ($self->timer, $self->esphome, $self->espout, $self->packed);
	foreach my $j (keys %{$self->jobdesc}) {
		my @jj = @{$self->jobdesc->{$j}};
		my $taskcount = $self->taskcount($jj[0]);
		my $cline = $self->command("\$ESP/","$jj[2]");
		my $wlimit = int($jj[2]*1.50);
		my $min = int($wlimit/60);
		my $sec = int($wlimit%60);
		for (my $i=0; $i < $jj[1]; $i++) {
			my $needed = $taskcount/$packed;
			my $nodes = "$taskcount";
			my $walltime = "$min:$sec";
			my $np=$taskcount;
			if ($taskcount == 2){ $np = 2; } 
			if ($taskcount == 16){ $np = 15; }
			my $joblabel = $self->joblabel($j,$taskcount,$i);
			print STDERR "creating $joblabel\n" if $self->verbose;
			open(NQS, "> $joblabel");
#
#  "here" template follows 
#  adapt to site batch queue system
#
print NQS <<"EOF";
#\!/bin/sh
#SBATCH -J $joblabel
#SBATCH -n $nodes
#SBATCH -t $walltime
#SBATCH -p exclusive
#SBATCH -o /home_nfs/georgioy/BENCHS/Light.ESP-2.2.1/logs/$joblabel.out

ESP=/home_nfs/georgioy/BENCHS/Light.ESP-2.2.1

ulimit -n 800000
echo `\$ESP/bin/epoch` " START  $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG
#$timer mpirun -np $np $cline
sleep \$(( $wlimit * 2 / 3 ))
echo `\$ESP/bin/epoch` " FINISH $joblabel   Seq_\${SEQNUM}" >> \$ESP/LOG


exit
EOF
	       		close(NQS);
		}
	}
}

1;