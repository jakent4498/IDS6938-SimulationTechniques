# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
library(ggplot2)
library(reshape2)
library(dplyr)
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Discrete2/Output/Normal")
# Read data from files
jak1 <- read.table("results_knuth_b-normalN100000.txt", header = FALSE, col.names=c("x","Count"))
jak2 <- read.table("results_minstd_rand-normalN100000.txt", header = FALSE, col.names=c("x","Count"))
jak3 <- read.table("results_mt19937_64-normalN100000.txt", header = FALSE, col.names=c("x","Count"))
jak4 <- read.table("results_ranlux48-normalN100000.txt", header = FALSE, col.names=c("x","Count"))  
#jak5 <- read.table("histogram_sobol-resultsN100000.txt", header=FALSE)
# Create a dataframe for all data
#jaklist <- list(jak2$V1,jak4$V1)
jakdf <- left_join(jak1,jak2, by = "x")
jakdf <- left_join(jakdf, jak3, by = "x")
jakdf <- left_join(jakdf, jak4, by = "x")
names(jakdf) <- c("x","knuth","minstd_rand","mt19937_64","ranlux48")
# Plot data with different colors
ggplot(jakdf, aes(ymin=0)) + labs(x="Number", y="Count",title="Normal Distribution N=100000") +
  geom_point(aes(x=jakdf$x,y=jakdf$knuth, colour="grey")) +
  geom_point(aes(x=jakdf$x,y=jakdf$minstd_rand, colour = "darkorange")) +
  geom_point(aes(x=jakdf$x,y=jakdf$mt19937_64, colour="blue")) +
  geom_point(aes(x=jakdf$x,y=jakdf$ranlux48, colour = "forestgreen")) +
  scale_color_manual(name="Generation Method", 
                     labels=c("ranlux48","mt19937_64","minstd_rand","knuth_b"), 
                     values=c("forestgreen","blue","darkorange","grey")) +
  theme(legend.position = c(1,1),legend.justification = c(1,1))
                              


