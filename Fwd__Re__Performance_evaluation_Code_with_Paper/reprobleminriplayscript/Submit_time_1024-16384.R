Wait<-function(F1,F2,F3,F4,F5,F6)
{
	f1<-read.table(F1)
	f2<-read.table(F2)
	f3<-read.table(F3)
	f4<-read.table(F4)
        f5<-read.table(F5)
        f6<-read.table(F6)
	f1<-subset(f1,V2>=0)
	f2<-subset(f2,V2>=0)
	f3<-subset(f3,V2>=0)
	f4<-subset(f4,V2>=0)
        f5<-subset(f5,V2>=0)
        f6<-subset(f6,V2>=0)
	Wait1<-f1$V2-1328708330
	Wait2<-f2$V2-1328707049
	Wait3<-f3$V2-1328705133
	Wait4<-f4$V2-1328702030
        Wait5<-f5$V2-1328698865
        Wait6<-f6$V2-1328695625



	#nclass<-50 # number of bars

	# Single histogram representing the wait time of the first file
	#png(file="Wait_time (OAR).png",height=850,width=1000)
	h<-hist(Wait1,plot=F)
	#plot(h,ylim=range(pretty(range(0,h$counts))),labels=TRUE,xlab="Wait Time",main="Histogram of wait time (OAR)")
  	#mtext(paste("File :",F1))
	#dev.off()

	postscript("cdf-submit-SLURM-1024-16384.eps",width=8,height=5,onefile = TRUE, horizontal = FALSE,paper="special")
#	png(file="Cumulated Distribution function on Wait time(OAR-SLURM).png",height=850,width=1000)
	
	plot(ecdf(sort(Wait1)),pch=22, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="Submission time difference from start [s]",ylab="Jobs [%]", main= "CDF on Submission time for Light-ESP benchmark (230 jobs)\nupon a 16 cpu/node cluster with variation on the number of nodes \n (emulation with 400 physical nodes)")
#plot(ecdf(sort(Wait1)),do.points =F, verticals= T,xlim=c(0,max(Wait1,Wait2)),xlab="Wait time [s]",ylab="Jobs [%]", main= "Cumulated Distribution function on Wait time")	
	par(new=T)
	plot(ecdf(sort(Wait2)),pch=20, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="",ylab="", main= "")	
	par(new=T)
	plot(ecdf(sort(Wait3)),pch=21, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="",ylab="", main= "")
	par(new=T)
	plot(ecdf(sort(Wait4)),pch=19, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="",ylab="", main= "")
	par(new=T)
        plot(ecdf(sort(Wait5)),pch=18, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="",ylab="", main= "")
        par(new=T)
        plot(ecdf(sort(Wait6)),pch=17, xlim=c(0,max(Wait1,Wait2,Wait3,Wait4,Wait5,Wait6)),xlab="",ylab="", main= "")

#	axis(2,seq(0,1.0,0.2),line=0)
#	axis(1,seq(0,max(Wait1,Wait2),1000),line=0)
#lines(ecdf(sort(Wait2)),xlab="",pch=(22),ylab="", main= "Cumulated Distribution function on Wait time")
#	mtext(paste("files :",F1, "-", F2)) 
	legend("bottomright",c("1024 nodes","2048 nodes","4096 nodes","8192 nodes","12288 nodes","16384 nodes"),pch=c(22,20,21,19,18,17),lty=c(1,0),inset=0.02)
	dev.off()
	
	# Single histogram representing the wait time of the second file
	#png(file="Wait_time (SLURM).png",height=850,width=1000)
	h1<-hist(Wait2,plot=F)
#plot(h1,xlim=range(pretty(range(0,h1$breaks))),ylim=range(pretty(range(0,h1$counts))),labels=TRUE,xlab="Wait Time [s]",main="Histogram of wait time (SLURM)")
#		 mtext(paste("File :",F2))
#	dev.off()
  	h2<-hist(Wait3,plot=F)
	h3<-hist(Wait4,plot=F)
	h4<-hist(Wait5,plot=F)
	h5<-hist(Wait6,plot=F)
  	# Comparaison of the 2 wait times with histograms
  	
	png(file="Wait_time (comparaison).png",height=850,width=1000)
	# the files aren't the same length
	# h$counts is a way to get y values on histograms
   longest<-ifelse(length(h$counts)<length(h1$counts),length(h1$counts),length(h$counts))
   # we get the results 
   without<-h$counts
   with<-h1$counts
   # we add 0 to the shortest vector 
   if (length(without)!=longest) {
   	without<-append(without,rep(0,longest-length(without)),after=length(without))}
   else with<-append(with,rep(0,longest-length(with)),after=length(with))

   # to display the 2 histograms require a matrix
   # rbind enables to make a matrix, given 2 vectors (those will be rows)
   
  	m<-rbind(without,with)
  	
  	# colnames will be the x-axis labels
  #	colnames(m)<-h1$breaks[2:length(h1$breaks)]
  	
   	barplot(m,													# matrix
   		beside=TRUE,										# put histograms next to each other
  		col=c("pink","cornsilk","green") ,					# colors of the histograms
   		xlab="Wait Time [s]",							# x-axis title
   		ylab="Frequency",								# y-axis title
   		space=c(0,0.5),								
   		main="Histograms of Wait Time"	)
   		
   	# Add a subtitle	
	mtext(paste("Files :",F1,"-",F2,"-",F3,"-",F4,"-",F5,"-",F6))	
	
   	# Add  a legend on top of the graph
  	legend("top",														# where to put the legend
  		col=c("pink","cornsilk","green","cornsilk","green","pink"),							# colors used	
  		c("with 2048 nodes","with 8192 nodes","with 16384 nodes","with 2048 nodes","with 8192 nodes","with 16384 nodes"),	# what to write
  		lty=c(NaN,NaN,NaN,NaN,NaN,NaN),											# we don't want lines for the line type
  		pch=c(22,20,21,19,18,17),															# we want the symbol 22 for the legend
  		lwd=3,																# width of the symbols 
  		inset=0.05)														# distance (as a fraction of a the plot) from where we want to put it
  
  	dev.off()

	# Comparaison of the 2 wait times with plots
#	png(file="Wait_time.png",height=850,width=1000)
#	plot(Wait1,type="b",ylim=c(0,max(Wait1,Wait2)),col="red",xaxs="i",xlab="Jobs",ylab="Wait Time",main="Wait Time")
#	points(Wait2,type="l",col="blue")
#	mtext(paste("data files:" ,F1,"and",F2,"and",F3))
#	legend("topleft",col=c("blue","red","green"),c("OAR","SLURM"),lty=c(1,0),pch=c(NaN,21),lwd=3)

#	dev.off()
}
Wait("ESP_400physical_1024/new_stats.swf","ESP_400physical_2048/new_stats.swf","ESP_400physical_4096/new_stats.swf","ESP_400physical_8192/new_stats.swf","ESP_400physical_12288/new_stats.swf","ESP_400physical_16384/new_stats.swf")
