#include <boost/array.hpp>
#include"../GaussJackson8.hpp"

/*
Orbit propagation using the Gauss-Jackson method

Simulation of a unit mass around a large body (Earth) in two dimensions. The force model is a simple monopole gravitational
model (i.e. the Earth is approximated as a point mass).

The initial coniditions are such that the unit mass follows a circular orbit at a constant radius of 10,000 km.
*/

// Define the differential equation to be integrated
void ode(const boost::array<double,4> &x, boost::array<double,4> &dxdt, double time){
	const double mu = 398600.4415; // Gravitational parameter G*Mass_{Earth} [km^3 s^-2]

	double radius = sqrt(x[0]*x[0]+x[1]*x[1]);
	double radius3 = pow(radius, 3.0);

	// Second order equation is decomposed into two coupled first order equations. Such that:
	// y''= f() -> y' = v, v' = f()

	dxdt[0]=x[2]; 
	dxdt[1]=x[3];
	
	dxdt[2]=-(mu/radius3)*x[0];
	dxdt[3]=-(mu/radius3)*x[1];
}


int main()
{	
	// Define the initial conditions which is at a radius of 10,000 km, initial velocity is calculated by sqrt(mu/radius)
	boost::array<double,4> state = {{10000.0,0.0,0.0,6.313481143553056}};
	
	// Run GaussJackson for 24 hours with a time-step of 60 seconds. Output is requested and saved to 'output.csv' but only saved for every 600 seconds
	// state is updated once propagate has returned.
	GJ8::propagate(state, ode, 0.0, 60*60*24, 60, 1, 600);

	return 0;
}