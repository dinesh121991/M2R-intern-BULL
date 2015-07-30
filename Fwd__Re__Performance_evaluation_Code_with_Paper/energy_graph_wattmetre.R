ConsAllEnergy<-function(F)
{
        f<-read.table(F)
        Tps<-f$V1
        Watt<-f$V3

        png(file="Power_consumption_wattmeter.png",height=1000,width=1000)
        plot(Tps,Watt,type="l",xlab="Unix Time",ylab="Consumption [Watt]",main="Power consumption of one node measured through wattmeter during a Linpack on 16 nodes")
        dev.off()
}


ConsAllEnergy("diagram-1371426975-1371432149-1-orion-3.dat")

