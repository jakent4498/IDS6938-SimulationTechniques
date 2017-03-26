# SimTech Spring 2017 
# Homework 2
# Julie Kent 3/7/17
#
# Generate five different distributions and analyze the results with graphs 
# and statistics of choice
library(ggplot2)
library(grid)
library(gridExtra)
setwd("C:/Users/jaken/OneDrive/Documents/Spring 2017 SimTech/IDS6938-SimulationTechniques/Discrete2/Output")
jakuniform <- read.table("Uniform/results_knuth_b-uniformN10000.txt", header=FALSE, col.names = c("x","count"))
jaknormal <- read.table("Normal/results_knuth_b-normalN10000.txt",header=FALSE, col.names = c("x","count"))
jakpoisson <- read.table("Poisson/results_knuth_b-poissonN10000.txt",header=FALSE, col.names = c("x","count"))
jakexponential <- read.table("Exponential/results_knuth_b-exponentialN10000.txt", header=FALSE, col.names = c("x","count"))
jakchisq <- read.table("Chi-squared/results_knuth_b-chi_squaredN10000.txt", header=FALSE, col.names = c("x","count"))
jaklognorm <- read.table("Lognormal/results_knuth_b-lognormN10000.txt", header=FALSE, col.names = c("x","count"))

p1 <-ggplot(jakuniform) + geom_point(aes(x=jakuniform$x, y=jakuniform$count)) +
  xlab("Uniform") + ylab("")
p2 <- ggplot(jaknormal) + geom_point(aes(x=jaknormal$x, y=jaknormal$count)) +
  xlab("Normal") + ylab("")
p3 <- ggplot(jakpoisson) + geom_point(aes(x=jakpoisson$x, y=jakpoisson$count)) +
  xlab("Poisson") + ylab("")
p4 <- ggplot(jakexponential) + geom_point(aes(x=jakexponential$x,y=jakexponential$count)) +
  xlab("Exponential") + ylab("")
p5 <- ggplot(jakchisq) + geom_point(aes(x=jakchisq$x, y=jakchisq$count)) +
  xlab("Chi-squared") + ylab("")
p6 <- ggplot(jaklognorm) + geom_point(aes(x=jaklognorm$x, y=jaklognorm$count)) +
  xlab("Lognormal") + ylab("")
grid.arrange(p1,p2,p3,p4,p5,ncol=2)
