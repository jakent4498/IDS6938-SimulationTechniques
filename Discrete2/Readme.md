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
The end points have about half as many entries as the other values because the random numbers are generated on an interval between 0 and 1.  They are then scaled to integers for the interval from 0 to 100.  For all integer values inside the interval the real numbers below and above the integer will round to the integer.  For example, values from 0.50000 to 1.49999 will round to 1.  However, there are no values below 0 so only values from 0.00001 to 0.49999 round to 0, about half as many as would round to any interior digit.  The same is true at the other end of the scale.  There are no values above 100 so only values from 99.50000 to 100.00000 will round to 100.  This means the end points have about half as many entries as any of the interior values.  This is clearly seen in the image ![..Graphs/Scatterplot as read from files.png](http://..Graphs/Scatterplot as read from files.png)