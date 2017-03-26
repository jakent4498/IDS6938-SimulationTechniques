# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
library(ggplot2)
# Read data from files
jak1 <- read.table("results_knuth_b-uniformN100000.txt", header = FALSE)
jak2 <- read.table("results_minstd_rand-uniformN100000.txt")
jak3 <- read.table("results_mt19937_64-uniformN100000.txt", header = FALSE)
jak4 <- read.table("results_ranlux48-uniformN100000.txt", header = FALSE)  
jak5 <- read.table("histogram_sobol-resultsN100000.txt", header=FALSE)
# Plot data with different colors
ggplot(jak5, aes(ymin=0)) + labs(x="Number", y="Count",title="Uniform Distribution") +
  geom_point(aes(x=jak5$V1, y=jak5$V2, colour = "yellow")) +
  geom_point(aes(x=jak4$V1, y=jak4$V2, colour = "forestgreen")) +
  geom_point(aes(x=jak3$V1, y=jak3$V2, colour = "blue")) +
  geom_point(aes(x=jak2$V1, y=jak2$V2, colour="darkorange")) + 
  geom_point(aes(x=jak1$V1,y=jak1$V2, colour="grey")) +
scale_color_manual(name="Generation Method", 
                   labels=c("sobol","ranlux48","mt19937_64","minstd_rand","knuth_b"), 
                   values=c("yellow","forestgreen","blue","darkorange","grey")) +
  theme(legend.position = c(.6,.5),legend.justification = c(1,1))
# Repeat for other values of N
# Read files for N=10,000
jak1 <- read.table("results_knuth_b-uniformN10000.txt", header = FALSE)
jak2 <- read.table("results_minstd_rand-uniformN10000.txt")
jak3 <- read.table("results_mt19937_64-uniformN10000.txt", header = FALSE)
jak4 <- read.table("results_ranlux48-uniformN10000.txt", header = FALSE)  
jak5 <- read.table("histogram_sobol-resultsN10000.txt", header=FALSE)
# Plot data with different colors
ggplot(jak5, aes(ymin=0)) + labs(x="Number", y="Count",title="Uniform Distribution  N=10,000") +
  geom_point(aes(x=jak5$V1, y=jak5$V2, colour = "yellow")) +
  geom_point(aes(x=jak4$V1, y=jak4$V2, colour = "forestgreen")) +
  geom_point(aes(x=jak3$V1, y=jak3$V2, colour = "blue")) +
  geom_point(aes(x=jak2$V1, y=jak2$V2, colour="darkorange")) + 
  geom_point(aes(x=jak1$V1,y=jak1$V2, colour="grey")) +
  scale_color_manual(name="Generation Method", 
                     labels=c("sobol","ranlux48","mt19937_64","minstd_rand","knuth_b"), 
                     values=c("yellow","forestgreen","blue","darkorange","grey")) +
  theme(legend.position = c(.6,.5),legend.justification = c(1,1))
# Read files for N=1,000,000
jak1 <- read.table("results_knuth_b-uniformN1000000.txt", header = FALSE)
jak2 <- read.table("results_minstd_rand-uniformN1000000.txt")
jak3 <- read.table("results_mt19937_64-uniformN1000000.txt", header = FALSE)
jak4 <- read.table("results_ranlux48-uniformN1000000.txt", header = FALSE)  
jak5 <- read.table("histogram_sobol-resultsN1000000.txt", header=FALSE)
# Plot data with different colors
ggplot(jak5, aes(ymin=0)) + labs(x="Number", y="Count",title="Uniform Distribution  N=10,000") +
  geom_point(aes(x=jak5$V1, y=jak5$V2, colour = "yellow")) +
  geom_point(aes(x=jak4$V1, y=jak4$V2, colour = "forestgreen")) +
  geom_point(aes(x=jak3$V1, y=jak3$V2, colour = "blue")) +
  geom_point(aes(x=jak2$V1, y=jak2$V2, colour="darkorange")) + 
  geom_point(aes(x=jak1$V1,y=jak1$V2, colour="grey")) +
  scale_color_manual(name="Generation Method", 
                     labels=c("sobol","ranlux48","mt19937_64","minstd_rand","knuth_b"), 
                     values=c("yellow","forestgreen","blue","darkorange","grey")) +
  theme(legend.position = c(.6,.5),legend.justification = c(1,1))
# Read in raw values for knuth_b
knuth1 <- as.data.frame(read.table("raw_results_knuth_b-uniformN10000.txt", header=FALSE))
knuth2 <- as.data.frame(read.table("raw_results_knuth_b-uniformN100000.txt", header=FALSE))
knuth3 <- as.data.frame(read.table("raw_results_knuth_b-uniformN1000000.txt", header=FALSE))
#library(spgs)
chisq.unif.test(knuth1[,1],interval=c(0,100))
chisq.unif.test(knuth2[,1],interval=c(0,100))
chisq.unif.test(knuth3[,1],interval=c(0,100))
chisq.unif.test(knuth1[,1],interval=c(1,99))
chisq.unif.test(knuth2[,1],interval=c(1,99))
chisq.unif.test(knuth3[,1],interval=c(1,99))
