# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
# Write code to call the functions to output and generate data from the airport senario. 
# Plot and analyze the useful statistics/results in the program of your choice.  (Hint -  
# basically call  *.output();* on the MM1_Queue objects you create. Hint2 - two other use 
# functions are *get_current_time()* and  *plot_results_output()* call intially on your 
# intial MM1_Queue object.)
#
# Generated two files for each queue - one with wait time, the other with service time
#
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Homework2/queues/queue-files")
library(ggplot2)
library(grid)
library(gridExtra)
#
# First read the files into R
# Then create individual plots
# Then combine them into one graphic
#
quCheckin <- read.csv("checkin-service.txt",header=FALSE)
p1a <- ggplot(quCheckin) + geom_histogram(aes(x=quCheckin$V1),bins=90,center =.0001) +
  xlab("Service Time") + ylab("Count") + ggtitle("Service Time for Checkin Histogram")
quCheckwait <- read.csv("checkin-wait.txt",header=FALSE)
p1b <- ggplot(quCheckwait) + geom_histogram(aes(x=quCheckwait$V1),bins=90, center = 0.01)+
  xlab("Wait Time") + ylab("Count") + ggtitle("Wait Time for Checkin Histogram")

quTSA1 <- read.csv("TSA1-service.txt",header=FALSE)
p2a <- ggplot(quTSA1) + geom_histogram(aes(x=quTSA1$V1),bins=90, center = 0.01)+
  xlab("Service Time") + ylab("Count") + ggtitle("Service Time for TSA line 1")
quTSA1w <- read.csv("TSA1-wait.txt",header=FALSE)
p2b <- ggplot(quTSA1w) + geom_histogram(aes(x=quTSA1w$V1),bins=90, center = 0.01)+
  xlab("Wait Time") + ylab("Count") + ggtitle("Wait Time for TSA line 1")


quTSA2 <- read.csv("TSA2-service.txt",header=FALSE)
p3a <- ggplot(quTSA2) + geom_histogram(aes(x=quTSA2$V1),bins=90, center = 0.01)+
  xlab("Service Time") + ylab("Count") + ggtitle("Service Time for TSA line 2 ")
quTSA2w <- read.csv("TSA2-wait.txt",header=FALSE)
p3b <- ggplot(quTSA2w) + geom_histogram(aes(x=quTSA2w$V1),bins=90, center = 0.01)+
  xlab("Wait Time") + ylab("Count") + ggtitle("Wait Time for TSA line 2")


quTSA3 <- read.csv("TSA3-service.txt",header=FALSE)
p4a <- ggplot(quTSA3) + geom_histogram(aes(x=quTSA3$V1),bins=90, center = 0.01)+
  xlab("Service Time") + ylab("Count") + ggtitle("Service Time for TSA line 3")
quTSA3w <- read.csv("TSA3-wait.txt",header=FALSE)
p4b <- ggplot(quTSA3w) + geom_histogram(aes(x=quTSA3w$V1),bins=90, center = 0.01)+
  xlab("Wait Time") + ylab("Count") + ggtitle("Wait Time for TSA line 3 ")

quBoard <- read.csv("Board-service.txt",header=FALSE)
p5a <- ggplot(quBoard) + geom_histogram(aes(x=quBoard$V1),bins=90, center = 0.01)+
  xlab("Service Time") + ylab("Count") + ggtitle("Service Time for Boarding Histogram")
quBoardw <- read.csv("Board-wait.txt",header=FALSE)
p5b <- ggplot(quBoardw) + geom_histogram(aes(x=quBoardw$V1),bins=90, center = 0.01)+
  xlab("Wait Time") + ylab("Count") + ggtitle("Wait Time for Boarding Histogram")

grid.arrange(p2a,p3a,p4a,p2b,p3b,p4b,nrow=2)
grid.arrange(p1a,p5a,p1b,p5b,ncol=2)
