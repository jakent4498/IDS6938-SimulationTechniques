Starting a markdown file to track what I am doing on homework 2.
Created 5 files
4 using Random 
1 using QuasiRandom-Sobol
file names:
	results_knuth_b-uniformN100000.txt
    results_minstd_rand-uniformN100000.txt
    results_mt19937_64-uniformN100000.txt
    results_ranlux48-uniformN100000.txt
    results_sobol-uniformN100000.txt

I pulled the results from two into R and managed to plot them using ggplot earlier in the week.  I am going to try to repeat that feat.

Okay the two end points have about half as many entries as the other values and there are 101 entries rather than 100.  I looked in the code, but I could not find a way to easily combine the values for the two end points.  There may be somewhere that > needs to be >= or < needs to be <= but I have not found it.

Therefore, I am taking the values of the two end points and summing them in R storing the result in the first end point and deleting the last end point.  The resulting graphs should not have the same outliers.

I am then looking at how to do a comparison with the uniform distribution.  How do I know that the uniform distribution in R is any more uniform than any of these?  Of course, a purely uniform distribution of 100 numbers in 100,000 picks would be 1,000 of each number.  I shoud be able to create that as a matrix and do a comparison.

Well, I created that matrix, but I am still not sure about doing the comparison.

3/25/17
The end points have about half as many entries as the other values because the random numbers are generated on an interval between 0 and 1.  They are then scaled to integers for the interval from 0 to 100.  For all integer values inside the interval the real numbers below and above the integer will round to the integer.  For example, values from 0.50000 to 1.49999 will round to 1.  However, there are no values below 0 so only values from 0.00001 to 0.49999 round to 0, about half as many as would round to any interior digit.  The same is true at the other end of the scale.  There are no values above 100 so only values from 99.50000 to 100.00000 will round to 100.  This means the end points have about half as many entries as any of the interior values.  This is clearly seen in the image ![](Graphs/Scatterplot as read from files.png)
Make the image better - 
	1. Scale the Y axis from 0 so the beginning and ending points are at about half way.  
	2. Add a legend showing which color is from which random number generator.
	3. Change the title to reflect this is a count of times a number appears.

Well that took a lot longer to figure out than I thought it would.  Did it using the following R code:```
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
```
With the number of values generated equal to 100,000 and the values ranging from 0 to 100, the expectation is that each value would appear about 1,000 times.  Based on the results in the following image ![](Graphs/Five Method of Generating Uniform Distributions.png) these methods generally meet that expectation.


