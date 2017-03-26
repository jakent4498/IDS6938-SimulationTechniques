# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
# Generate five different distributions and analyze the results with graphs 
# and statistics of choice
library(ggplot2)
library(grid)
library(gridExtra)
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Discrete2/Output/2DwithDist")
jakuniform <- read.csv("2Draw_results_mt19937_64-uniformN100000.txt", header=FALSE, col.names = c("x","y"))
jaknormal <- read.csv("2Draw_results_mt19937_64-normalN100000.txt",header=FALSE, col.names = c("x","y"))
jakpoisson <- read.csv("2Draw_results_mt19937_64-poissonN100000.txt",header=FALSE, col.names = c("x","y"))
jakexponential <- read.csv("2Draw_results_mt19937_64-exponentialN100000.txt", header=FALSE, col.names = c("x","y"))
jakchisq <- read.csv("2Draw_results_mt19937_64-chi_squaredN100000.txt", header=FALSE, col.names = c("x","y"))
jaklognorm <- read.csv("2Draw_results_mt19937_64-lognormN100000.txt", header=FALSE, col.names = c("x","y"))

p1 <- ggplot(jakuniform) + geom_point(aes(x=jakuniform$x, y=jakuniform$y)) +
  xlab("Uniform") + ylab("")
p2 <- ggplot(jaknormal) + geom_point(aes(x=jaknormal$x, y=jaknormal$y)) +
  xlab("Normal") + ylab("")
p3 <- ggplot(jakpoisson) + geom_point(aes(x=jakpoisson$x, y=jakpoisson$y)) +
  xlab("Poisson") + ylab("")
p4 <- ggplot(jakexponential) + geom_point(aes(x=jakexponential$x,y=jakexponential$y)) +
  xlab("Exponential") + ylab("")
p5 <- ggplot(jakchisq) + geom_point(aes(x=jakchisq$x, y=jakchisq$y)) +
  xlab("Chi-squared") + ylab("")
p6 <- ggplot(jaklognorm) + geom_point(aes(x=jaklognorm$x, y=jaklognorm$y)) +
  xlab("Lognormal") + ylab("")
grid.arrange(p1,p2,p3,p4,p5,p6,ncol=3)
