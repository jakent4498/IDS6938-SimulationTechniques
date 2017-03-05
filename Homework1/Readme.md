#Homework 1 : The Jello Cube (Continuous Simulation Assignment
## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)


This is the framework for homework #1. Please first read the [homework writeup](HomeWork%231.pdf).

The assignment is due: Wednesday, March 1 at 11:59PM (EST)
This file has been edited by Julie A Kent.

I will be submitting 3 days late making use of the extension granted due to an unexpected business trip outside the US where I could not take personal electronics.

#Part 1 Numerical Analysis of Integration

Initial Value Problem 
The initial value problem given is the assignment is ![](images/IVP Equation.png?raw=true) where y(0)=0
(a) Solve for the exact symbolic (analytical) solution by taking the integral gives ![](images/IVP Solution.png?raw=true) 
Thank you Wolfram Alpha for making this easy. http://www.wolframalpha.com/calculators/integral-calculator/

(b) Now there are values for the df and exact functions.  Inserting code block below for df.

```
double df(double x, double y)            //function for defining dy/dx
{
    return y - (1.0 / 2.0)*exp(x / 2.0)*sin(5.0 * x) + 5.0 * exp(x / 2.0)*cos(5.0 * x);
}
```
Inserting code block for exact.
```
double exact(double x)            //function for defining dy/dx
{
    return (exp(x/2.0))*sin(5.0*x);
}
```
(c) Run three numerical integration solutions: RK1, RK2, and RK4 to generate the numerical and exact values. A graph comparing the results for the different integration methods is shown below.


| Comparison of integration Methods  | Comparison of Error from Integration Methods |
| ------------- | ------------- |
| ![](../Lecture6-Solution/results/Comparison of Integration Methods.png?raw=true) | ![](../Lecture6-Solution/results/Comparison of Error Generated from Different Integration Methods.png?raw=true) |
###### The results for the first four integration intervals are shown in the table below.

|  x | y (Euler) | y (midpoint) | y (RK4) | Exact |
|--------|--------|-----------|-----------|---------|
| 0 | 0 | 0 | 0 | 0 |
| 0.1 |0.5|0.509037|0.504015|0.992528|
|0.2|0.986088|0.941892|0.929983|1.779364|
|0.3|1.336762|1.17828|1.158939|2.134285|
|0.4|1.453584|1.136381|1.110628|1.91958|

(d) Plot the error percentages.  A graph showing the error percentages is shown above.  A complete set of results and errors is given in tab jak-HW1a of the file (../Lecture6-Solution/results/jak-HW1a.xlsx (https://github.com/jakent4498/IDS6938-SimulationTechniques/blob/master/Lecture6-Solution/results/jak-HW1a.xlsx).

(e) Vary the step size h=n  and plot the results for RK4 with 3 different values and the exact solution.  I used step size h=0.1, h=0.2 and h=0.5.  The resulting comparison is shown in the below along with a comparison of the errors.

| Integration Intervals || Error for Integration Intervals |
|------------------------||--------------------------------|
|![](../Lecture6-Solution/results/Comparison of RK4 Integration Intervals.png?raw=true)||![](../Lecture6-Solution/results/Comparison of Error for RK4 Integration Intervals.png?raw=true)|
(f) Analyze your results.
RK4 is the most accurate and Euler is the least.  However, RK4 is the most computationaly intensive method and Euler requires the least computation.  As x gets large the small differences in accuracy get magnified resulting in much larger error for large values of x.  Smaller step sizes improve the accuracy of all methods.  RK4 is the most accurate because it takes into account changes in the function over the length of the interval being estimated and how fast those changes are occurring.  Euler mearly estimates based on the value of the function at the start of the interval.  Midpoint estimates based on the value at the start and the change at the midpoint.  RK4 allows for better estimate of changes during the course of the interval.

When it came time to try multiple intervals I initially ran my program with .1, .05, and .001.  The difference in the errors was orders of magnitude.  The magnitude of the errors was very, very small.  The .1 interval reached magnitudes 0.00026236 while the .05 interval reached 0.0000019487 and the .001 reached 0.00000000000027898.  It was interesting to me that all of these ran on my laptop without a noticeable difference in run time from the original program which just had a single loop and a maximum interval of .1.  I realize when the integration is being performed for a simulation with many objects moving in the scenario it requires exponentially more processing power both to move the objects and to account for collisions.  So I wondered what happened to the error if I reduced the integration interval.  Therefore, I ran the same code after modifying the intervals to be .1, .2 and .5.  I suppose I could have tried to get sophisticated and create a GUI to prompt for parameters such as the output file name and the intervals which would make this more versatile.  I then created graphs for the exact solution plus the RK4 integration for these three intervals.  Even at an interval of .5 the error only reached 3.4194% in the range of 0 to 10 using RK4 estimation.  I can see why, depending on the specific simulation needs, a less precise integration estimation which is also computationally less expense can be very appropriate.

#Part 2: Programming a Jello Cube
I implemented all three integration methods.  While I initially had difficulty finding spring constants for Euler which would not make the cube fly apart, I eventually found some.  On the way I captured some interesting videe, such as https://youtu.be/-CQVXKcSMTE.  I found ways that unexpected results could look like something different, https://www.youtube.com/watch?v=oWsiQSNCgCQ.  This was my first attempt to create video other than with a camcorder and it was interesting.

It took some trial and error, but I implemented spring forces including spring damping. I then worked on collision and penetration detection first with the floor and then with a single cylinder half embedded in the floor.  Figuring out how to detect and react to the cylinder also resulted in some amusing video https://youtu.be/wHofAiOWbig.  After that implementing a sphere seemed straight forward. I could not figure out how to position the sphere off the origin so the video https://youtu.be/0kWteKsEsZw is a little dull, but the second drop is with Euler integration. 

I implemented shear and bend springs.  Since I am in the habit, I made a short video https://youtu.be/HptVgqDrLjs showing these as well.  Then I made a more interesting scene by combining the sphere and a cylinder https://www.youtube.com/watch?v=ywd8XUog0QI.  I posted my videos to YouTube and I also created one with two jello cubes with obviously different spring constants https://www.youtube.com/watch?v=5IPBego3-wQ.  The blue cube has Ks = 3666 but the red cube has Ks = 366.

At that point having set up a completely separate directory so I would not break anything I had done above, I added a third cube and did some comparisons.  First I compared different spring constants.  Then I tried different integration methods in the same output.  Finally I ran the simulation with different integration methods at a variety of different intervals based on the intervals from part 1.  Euler integration with an interval of 0.005 looks good in my opinion.  I am working on concatenating all of the files and creating a YouTube video that might be interesting to someone outside of this class.  These are in Homework1b directory and I am going to attempt to commit and push it.

Video editing is not for the faint of heart.  I have managed to stitch together four videos using various parameters with three different cubes each showing a different effect.  The text introductions are not as long or as smooth as I would like, but I have learned a lot about ffmpeg.  I have learned a bit about YouTube as well.  Final video is https://www.youtube.com/watch?v=D9D-b_CEmnw.

#Part 3: Written Questions
1. What is the effect of the Ks and Kd parameters on the jello?  Ks is the spring constant from Hook's Law and represents how stiff or how elastic the spring is.  In the case of the jello, higher Ks made stiffer jello just like adding more gelatin will do when cooking jello.  Kd is the damping force that decreases the spring force over time.  Decreasing Kd will increase the time required for the spring to return to equilibrium.  Decreasing Kd in the project increases the time for the jello to settle down and stop wobbling.  
2. Wat are the benefits and the drawbacks of the collision system used here?  What are some different ways in which it could be improved?  
	Benefits: Less messy than actual Jello, can be used for different shapes, once implemented it can be reused easily for different projects, can be used to model collisions of different types without destroying anything
    Drawbacks: May require significant computing power to accurately model significant scenarios, determining appropriate spring constants for to model real materials could be a challenge, may require time and effort to assemble shapes into more complex models rather than simple geometric shapes
3. What are some example systems you could model with Mass-spring simulations?  Explain how you would construct the model.
	The first thing that comes to mind is an elevator.  In that case the model would be similar to the jello cube except that it would be constrained on all four sides by an elevator shaft.  It would be important to include friction as a force is such a model.  The model would show the impact of an unrestrained or partially restrained fall of the elevator.  Another thought is the car collision tests where the car impacts with a variety of different surfaces.  In that case you would want to put some detail into modeling the different parts of the car because there are different spring forces in different areas, engine, body, tires.  Then a starting velocity from one side moving to impact on the other side would show how the model car would react. I am sure there are many other things that can be modeled using mass-spring simulations.  Apparently, it has been used to model the human body https://www.researchgate.net/publication/221818875_Mass-spring-damper_modelling_of_the_human_body_to_study_running_and_hopping_-_an_overview
4. Does the jello behave realistically?  What integration method did you choose to make the Jello stable?
Based on the comments of my children the jello behaves realistically.  I find realism limited by the lack of friction in the model.  If the jello is impacting with a slick surface, including wet counter tops or wet plastic balls, then it acts a lot like the jello in the model.  If the jello is impacting s wooden object then the lack of friction in the model will be more apparent.  This could be solved by implementing friction.  I eventually found spring constants to work for RK4, midpoint, and Euler integration.  Once I found constants for Euler, I found that method to be more realistic than the others for the jello I make.  My jello tends to be wobbly because my children like to play with it.
5. How would you model and simulate water (in terms of a continuous simulation)?
I think water could be modeled as particles with very small spring forces between the particles.  Water will break apart quickly so Ks would need to be relatively small.

#Conclusion
Once I was able to follow the existing code, or at least portions of it, this became a very interesting assignment.  I enjoy doing comparisons and this gave a means to visualize the different mathematical methods.  I found the different possibilities a little addictive and I wish I could spend more time trying other possibilities.  I also learned a variety of new tools while working on this assignment.  The final composite video is available https://youtu.be/D9D-b_CEmnw.

####References
http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html