//Eulers Method to solve a differential equation
#define _USE_MATH_DEFINES

#include <cmath>
#include<iostream>
#include<iomanip>
#include<math.h>




/*
Compute the dy/dx
*/
double df(double x, double y)            //function for defining dy/dx
{
    return (y * log(y)) / x;
}


/*
Compute the exact answer
*/
double exact(double x)            //function for defining dy/dx
{
    return pow(M_E, (x / 2));
}


/*
Calculate the error
*/
double error(double exact, double approx)
{
    return abs(exact - approx) / exact;
}


/*
This implements the Euler method equation
*/
double rk1(double y, double h, double x)
{
    return y + h * df(x, y);
}


/*
This implements the Midpoint method equation
*/
double rk2(double y, double h, double x)
{
	double k1 = df(x, y);

	// Add midpoint code here !
    return y + h*df(x+h/2, y+ (h/2)*k1);
}


/*
This implements the RK4 method equation
*/
double rk4(double y, double h, double x)
{
	double k1 = df(x, y);
	double k2 = df(x + (h / 2), y + k1*(h / 2));
	double k3 = df(x + (h / 2), y + k2* (h / 2));
	double k4 = df(x + h, y + h*k3);

	// Add RK4 code here!
	double y1 = y + 1.0 / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4) * h;
	return y1;
}




int main()
{
	double ye = M_E;
    double yrk1 = M_E;
	double yrk2 = M_E;
	double yrk4 = M_E;
    double x = 2.0;
    double h = 0.1;


	
    // Euler Method Test
    //*************************
    // This code reproduces the table: (Euler's Method (Example 1 - Accuracy))
    std::cout << "dy/dx" << "\t\t" << "EXACT" << "\t\t" << "x" << "\t" 
		<< "y (Euler)" << "\t" << "%Error(Euler)" << "\t"
		<< "y (midpoint)" << "\t" << "%Error(midpoint)" << "\t"
		<< "y (Runge-Kutta)" << "\t" << "%Error(Runge-Kutta)" 
		<< std::endl;
    std::cout << "------------" << "\t" << "------" << "\t\t" << "----" << "\t" 
		<< "------------" << "\t" << "------------" << "\t"
		<< "------------" << "\t" << "----------------" << "\t"
		<< "---------------" << "\t" << "------------------"
		<< std::endl;

    std::cout << df(x, ye) << "\t\t" << exact(x) <<"\t\t"<< x << "\t" 
		<< std::setprecision(11) << yrk1 << "\t" << std::setprecision(11) << error(exact(x), yrk1) * 100 << "%" << "\t\t"
		<< std::setprecision(11) << yrk2 << "\t" << std::setprecision(11) << error(exact(x), yrk2) * 100 << "%" << "\t\t\t"
		<< std::setprecision(11) << yrk4 << "\t" << std::setprecision(11) << error(exact(x), yrk4) * 100 << "%"
		<< std::endl;


    for (int i = 0; i < 10; i++)
    {
		yrk1 = rk1(yrk1, h, x);  //caculate y_{i+1}
		yrk2 = rk2(yrk2, h, x);  //caculate y_{i+1}
		yrk4 = rk4(yrk4, h, x);  //caculate y_{i+1}
		x = x + h;       //increment x

        std::cout << df(x, ye) << "\t" << exact(x) << "\t" << x << "\t" 
			<< std::setprecision(11) << yrk1 << "\t" << std::setprecision(11) << error(exact(x), yrk1) * 100 << "%" << "\t"
			<< std::setprecision(11) << yrk2 << "\t" << std::setprecision(11) << error(exact(x), yrk2) * 100 << "%" << "  \t"
			<< std::setprecision(11) << yrk4 << "\t" << std::setprecision(11) << error(exact(x), yrk4) * 100 << "%"
			<< std::endl;
    }


    return 0;
}