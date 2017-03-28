# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
library(ggplot2)
library(reshape2)
library(dplyr)
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Homework2/SnakesAndLadders/output")
#markov <- read.csv("null_markov_results.txt", header=TRUE)
#markov <- read.csv("ladders_markov_results.txt", header=TRUE)
#markov <- read.csv("sl_markov_results.txt", header=TRUE)
markov <- read.csv("snakes_markov_results.txt", header=TRUE)
row.names(markov) <- markov$RowName
markov <- markov[,2:length(markov)]
markov_matrix <- data.matrix(markov)
heatmap(markov_matrix, Rowv=NA, Colv=NA, col=terrain.colors(256),
        scale="row", margins=c(5,10))
