# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
library(ggplot2)
library(reshape2)
library(dplyr)
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Homework2/SnakesAndLadders/output")
dtmc <- read.csv("null_dtmc_results.txt", header=FALSE)
dtmc <- read.csv("ladders_dtmc_results.txt", header=FALSE)
dtmc <- read.csv("sl_dtmc_results.txt", header=FALSE)
dtmc <- read.csv("snakes_dtmc_results.txt", header=FALSE)

dtmc_rolls <- dtmc[102]

ggplot(dtmc_rolls, aes(dtmc_rolls)) +
  geom_histogram(binwidth=1, fill="thistle", color="darkorchid") +
  xlab("Number of rolls") + ylab("Games (out of 1000) Won at this Number of Rolls") +
  ggtitle("Number of Rolls Required to Win a Game")

dtmc <- dtmc[,1:101]

dtmc_matrix <- data.matrix(dtmc)
heatmap(dtmc_matrix, Rowv=NA, Colv=NA, col=terrain.colors(256),
        scale="row", margins=c(5,10))

dtmc2 <- dtmc[,1:35]
dtmc2m <- data.matrix(dtmc2)
heatmap(dtmc2m,Rowv=NA, Colv=NA, col=terrain.colors(256),
        scale="row", margins=c(5,10))

r25 <- dtmc[25]
ggplot(r25, aes(r25)) +
  geom_histogram(binwidth=1, fill="goldenrod1", color="brown") +
  xlab("Position") + ylab("Games (out of 1000) ") +
  ggtitle("Position at 25th Roll")

r5 <- dtmc[5]
ggplot(r5, aes(r5)) +
  geom_histogram(binwidth=1, fill="lightyellow3", color="goldenrod2") +
  xlab("Position") + ylab("Games (out of 1000) ") +
  ggtitle("Position at 5th Roll")
