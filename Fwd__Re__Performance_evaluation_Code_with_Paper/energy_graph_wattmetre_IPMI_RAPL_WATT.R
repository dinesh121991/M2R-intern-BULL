ConsAllEnergy<-function(F,P,G)
{
        f<-read.table(F)
	p<-read.table(P)
	g<-read.table(G)
        Tps_f<-f$V1
        Watt_f<-f$V3
        Tps_p<-p$V7
        Watt_p<-p$V8
	Tps_g<-g$V7
	Watt_g<-g$V8
	surf_f <- (sum(Watt_f))
	surf_p <- (sum(Watt_p))
        surf_g <- (sum(Watt_g))

#        png(file="Power_consumption_wattmeter.png",height=1000,width=1000)
	postscript("SLURM-IPMI-RAPL-Wattmeters.eps",width=10,height=10,onefile = TRUE, horizontal = FALSE,paper="special")
        plot(Tps_f,Watt_f,type="l",xlab="Time (sec)",ylim=c(0,max(Watt_f,Watt_p)),ylab="Instant Power Consumption [Watt]",main="Power consumption of one node measured through wattmeter during a Linpack on 16 nodes")
	#	postscript("ec-GREEN-OAR-SLURM-89.62.eps",width=10,height=10,onefile = TRUE, horizontal = FALSE,paper="special")
	par(new=T)
	plot(Tps_p,Watt_p,type="l",xlab="Time (sec)",col="blue",lty=c(2),ylim=c(0,max(Watt_f,Watt_p)),ylab="")
	par(new=T)
        plot(Tps_g,Watt_g,type="l",xlab="Time (sec)",col="red",ylim=c(0,max(Watt_g)*1.3),lty=c(3),xaxt="n",yaxt="n",ylab="")
	axis(4,col="red",col.axis="red")
	mtext("RAPL Instant Power Consumption [Watt]",side=4,col="red")
#	legend("topright",pch=22,col=c("black","red"),c("External Wattmeter","SLURM inband IPMI"),inset=0.04)
	  legend("center",title="Type of collection - Calculated Energy Consumption",c(paste("External Wattmeter - ",surf_f,"Joules"),paste("SLURM inband IPMI - ",surf_p,"Joules"),paste("SLURM inband RAPL - ",surf_g, "Joules")),col=c("black","blue","red"),lty=c(1,2,3),inset=0.001)
        dev.off()
}


ConsAllEnergy("orion-1_watt.dat","orion-1_ipmi.dat","orion-1_rapl.dat")

