- #Homework 1 : The Jello Cube (Continuous Simulation Assignment
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

(d) Plot the error percentages.  A graph showing the error percentages is shown above.  A complete set of results and errors is given in tab jak-HW1a of the file (../Lecture6-Solution/results/jak-HW1a.xlsx). 
How does hyperlink work
[(https://github.com/jakent4498/IDS6938-SimulationTechniques/blob/master/Lecture6-Solution/results/jak-HW1a.xlsx)]

#Part 2: Programming a Jello Cube
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
