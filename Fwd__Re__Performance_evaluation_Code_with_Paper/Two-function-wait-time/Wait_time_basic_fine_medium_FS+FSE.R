Wait<-function(F1,F2)
{
	f1<-read.table(F1)
	f2<-read.table(F2)
	
	f1<-subset(f1,V3>=0)
	f2<-subset(f2,V3>=0)
	
	Wait1<-f1$V3
	Wait2<-f2$V3
	
	#nclass<-50 # number of bars

	# Single histogram representing the wait time of the first file
	#png(file="Wait_time (OAR).png",height=850,width=1000)
	h<-hist(Wait1,plot=F)
	#plot(h,ylim=range(pretty(range(0,h$counts))),labels=TRUE,xlab="Wait Time",main="Histogram of wait time (OAR)")
  	#mtext(paste("File :",F1))
	#dev.off()

	postscript("cdf-wait-esp231jobs_180cores_FS+FSE.eps",width=8,height=5,onefile = TRUE, horizontal = FALSE,paper="special")
#	png(file="Cumulated Distribution function on Wait time(OAR-SLURM).png",height=850,width=1000)
	
	plot(ecdf(sort(Wait1)),pch=22, xlim=c(0,max(Wait1,Wait2)),xlab="Wait time [s]",ylab="Jobs [%]", main= "CDF on waiting time for ESP benchmark upon 5040 nodes(16cpus/node) cluster  \n resource selection comparison")
#plot(ecdf(sort(Wait1)),do.points =F, verticals= T,xlim=c(0,max(Wait1,Wait2)),xlab="Wait time [s]",ylab="Jobs [%]", main= "Cumulated Distribution function on Wait time")	
	par(new=T)
	plot(ecdf(sort(Wait2)),pch=20, xlim=c(0,max(Wait1,Wait2)),xlab="Wait time [s]",ylab="Jobs [%]", main= "")	
#	axis(2,seq(0,1.0,0.2),line=0)
#	axis(1,seq(0,max(Wait1,Wait2),1000),line=0)
#lines(ecdf(sort(Wait2)),xlab="",pch=(22),ylab="", main= "Cumulated Distribution function on Wait time")
#	mtext(paste("files :",F1, "-", F2)) 
	legend("topleft",c("cons_res_layout_no_overhead","cons_res_no_overhead"),pch=c(22,20,21),lty=c(1,0),inset=0.02)
	dev.off()
	
	# Single histogram representing the wait time of the second file
	#png(file="Wait_time (SLURM).png",height=850,width=1000)
}
Wait("cons_res_lay_no_overhead.swf","cons_res_no_overhead.swf")
