#include<stdio.h>

int main()
{
	int i,nb_of_nodes=240;
	printf("Priority=10 \n Root=Cluster \n Entity=Cluster Type=Center CurrentSumPower=0 IdleSumWatts=0 MaxSumWatts=0 Enclosed=virtual[0-%d]",nb_of_nodes-1);
	for( i=0 ; i< nb_of_nodes ; i++ )
	{
		printf("Entity=virtual[0-%d] Type=Node CurrentPower=0 IdleWatts=103 MaxWatts=308 CurrentFreq=0 \
        Cpufreq1=1200000 Cpufreq2=1400000 Cpufreq3=1600000 Cpufreq4=1800000 \
        Cpufreq5=2000000 Cpufreq6=2200000 Cpufreq7=2400000 Cpufreq8=2600000 \
        Cpufreq1Watts=172 Cpufreq2Watts=187 Cpufreq3Watts=203 Cpufreq4Watts=226 \
        Cpufreq5Watts=252 Cpufreq6Watts=273 Cpufreq7Watts=293 Cpufreq8Watts=308 \
        NumFreqChoices=8 PowerCapPriority=1",nb_of_nodes-1);
	}
}
