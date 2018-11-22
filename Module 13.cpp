#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cstdlib>
#include <cmath>
#include <iomanip>

/* Variables for 13.1
const int		nvar = 2;
const double	tEnd = 200.0;
const double	dt = 0.05;
const double	dtsav = 0.5;

const double	r = 2.0;		//Growth rate of prey
const double	a = 1.0;		//Predator attack rate
const double	c = 0.2;		//#Predator produced per consumed prey
const double	d = 0.1;		//Death rate of predator
*/

/*Variables for 13.2
const int		nvar = 2;
const double	tEnd = 1.0;
double			dt = 1.0e-2;

const double	epsilon = 4.0;
const double	b = 1000.0;
*/

/*Variables for 13.3
const int		nvar = 2;
const double	tEnd = 1000.0;
const double	dt = 1.0e-2;

double			a = 0.5;
const double	b = 0.5;
*/

//Variables for 13.4
const int		nvar = 4;
const double	tEnd = 150.00;
const double	dt = 0.005;
const double	dtsav = 0.100;

//Functions for 13.1 & 13.2 & 13.3 & 13.4
void rhs(const double &t, const std::vector<double> &x, std::vector<double> &dxdt, const double &s)
{
	/*13.1
	dxdt[0] = r * x[0] - a * x[0] * x[1];
	dxdt[1] = a * c * x[0] * x[1] - d * x[1];

	//13.2
	dxdt[0] = x[1];
	dxdt[1] = -epsilon * x[1] - b * x[0];

	//13.3
	dxdt[0] = -a * x[0] + x[1];
	dxdt[1] = (x[0] * x[0]) / (1.0 + x[0] * x[0]) - b * x[1];
	*/

	dxdt[0] = -(120.0 * x[1] * x[1] * x[1] * x[2] * (x[0] + 115.0)
			  + 36.0 * x[3] * x[3] * x[3] * x[3] * (x[0] - 12.0)
			  + 0.3 * (x[0] + 10.5989) + s);
	dxdt[1] = 0.1 * (1.0 - x[1]) * (x[0] + 25.0) 
			  / (exp(0.1 * x[0] + 2.5) - 1.0) - 4.0 * x[1] * exp(x[0] / 18.0);
	dxdt[2] = 0.07 * (1.0 - x[2]) * exp(x[0] / 20.0) - x[2] 
			  / (exp(0.1 * x[0] + 3.0) + 1.0);
	dxdt[3] = 0.01 * (1.0 - x[3]) * (x[0] + 10.0) 
			  / (exp(0.1 * x[0] + 1.0) - 1.0) - 0.125 * x[3] * exp(x[0] / 80.0);
}

/*
void eulerStepper(double &t, std::vector<double> &x, const double &h)
{
	std::vector<double> dxdt(nvar);
	rhs(t, x, dxdt);

	for (int i = 0; i < nvar; ++i) {
		x[i] += h * dxdt[i];
	}
	t += h;
}
*/

double rungeKuttaStepper(double &t, std::vector<double> &x, const double &h, const double &s)
{
	//Calculate a
	std::vector<double> dxdt1(nvar);
	rhs(t, x, dxdt1, s);

	//Calculate b
	std::vector<double> xtmp(nvar);
	for (int i = 0; i < nvar; ++i) {
		xtmp[i] = x[i] + 0.5 * h * dxdt1[i];
	}
	std::vector<double> dxdt2(nvar);
	rhs(t + 0.5 * h, xtmp, dxdt2, s);

	//Calculate c
	for (int i = 0; i < nvar; ++i) {
		xtmp[i] = x[i] + 0.5 * h * dxdt2[i];
	}
	std::vector<double> dxdt3(nvar);
	rhs(t + 0.5 * h, xtmp, dxdt3, s);

	//Calculate d
	for (int i = 0; i < nvar; ++i) {
		xtmp[i] = x[i] + h * dxdt3[i];
	}
	std::vector<double> dxdt4(nvar);
	rhs(t + h, xtmp, dxdt4, s);

	//Calculate full solution and mean-square-displacement
	double msd = 0.0;
	for (int i = 0; i < nvar; ++i) {
		const double dxi = (dxdt1[i] + 2.0 * dxdt2[i] + 2.0 * dxdt3[i] + dxdt4[i]) / 6.0;
		x[i] += h * dxi;
		msd += dxi * dxi;
	}
	t += h;
	return msd / nvar;
}

/*
bool checkConvergenceState(std::vector<double> &x)
{
	x[0] = 0.0;

	const double	epsilon = 1.0e-10;

	for (double t = 0.0; t < tEnd;) {
		const double msd = rungeKuttaStepper(t, x, dt);
		if (msd < epsilon) {
			return (x[0] >= 0.5 / (a * b));
		}
	}
	throw(std::exception("System did not converge in time"));
	return false;
}

double findRoot(double ymax)
{
	const double	epsilon = 1.0e-8;
	const int		maxIt = 100;

	std::vector<double> x(nvar);

	x[1] = ymax;

	if (!checkConvergenceState(x)) {
		throw std::logic_error("Unable to reach active state from this initial concentration.\n");
	}

	double ymin = 0.0;
	for (int it = 0; it < maxIt; ++it) {
		double ymid = (ymin + ymax) / 2;
		if (ymax - ymin < epsilon) {
			return ymid;
		}
		x[1] = ymid;
		if (checkConvergenceState(x)) {
			ymax = ymid;
		}
		else {
			ymin = ymid;
		}
	}
	throw std::runtime_error("Took too long to find the root.\n");
}
*/

int main()
{
	/*13.1
	try {
		std::ofstream ofs("data.csv");
		if (!ofs.is_open()) {
			throw std::runtime_error("Unable to open file.\n");
		}

		std::vector<double> x(nvar);
		x[0] = 0.4;
		x[1] = 2.0;

		for (double t = 0.0, tsav = 0.0; t < tEnd; ) {
			//eulerStepper(t, x, dt);
			rungeKuttaStepper(t, x, dt);

			if (t > tsav) {
				std::cout << t << " " << x[0] << " " << x[1] << "\n";
				ofs       << t << "," << x[0] << "," << x[1] << "\n";
				tsav += dtsav;
			}
		}
		ofs.close();
	}

	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}
	*/

	/*13.2
	try {
		std::ofstream ofs("data.csv");
		if (!ofs.is_open()) {
			throw std::runtime_error("Unable to open file.\n");
		}

		for (int it = 0; it < 80; ++it) {
			std::vector<double> x(nvar), y(nvar), z(nvar);
			x[0] = y[0] = 1.0;
			x[1] = y[1] = 0.0;

			double tx, ty;
			for (tx = 0.0, ty = 0.0; tx < tEnd;) {
				eulerStepper(tx, x, dt);
				rungeKuttaStepper(ty, y, dt);
			}

			const double delta = 0.5 * epsilon;
			const double omega = sqrt(b - delta * delta);
			z[0] = exp(-delta * tx) * (cos(omega * tx) + 
				                      delta * sin(omega * tx) / omega);

			double errx = fabs(x[0] - z[0]);
			double erry = fabs(y[0] - z[0]);

			std::cout << it << "\n" 
				<< "step size           = " << dt << "\n" 
				<< "error (Euler)       = " << errx << "\n"
				<< "error (Runge-Kutta) = " << erry << "\n";
			ofs << dt << "," << errx << "," << erry << "\n";
			dt *= 0.9;
		}
		ofs.close();
	}
	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}
	*/

	/*13.3
	try {
		for (a = 0.2; a <= 1.2; a += 0.1) {
			std::cout << a << " " << findRoot(2.0) << "\n";
		}
	}
	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}
	*/

	//13.4
	try {

		//Initial conditions
		std::vector<double> x(nvar);
		std::vector<double> y(nvar);
		x[0] = y[0] = 0.0;
		x[1] = y[1] = 0.05;
		x[2] = y[2] = 0.59;
		x[3] = y[3] = 0.32;

		//Open output file
		std::ofstream ofs("data.csv");
		if (!ofs.is_open()) {
			throw std::logic_error("Unable to open output file");
		}

		//Output initial conditions
		std::cout << std::fixed << std::setprecision(5);
		std::cout << std::left << std::setw(10) << "t" 
			      << std::right << std::setw(10) << "V" 
			      << std::setw(10) << "m" << std::setw(10) << "h" 
			      << std::setw(10) << "n\t" << std::setw(10) << "V" 
			      << std::setw(10) << "m" << std::setw(10) << "h" 
			      << std::setw(10) << "n\n";
		std::cout << std::left << std::setw(10) << "0.00000"
			      << std::right << std::setw(10) << x[0]
				  << std::setw(10) << x[1] << std::setw(10) << x[2]
				  << std::setw(10) << x[3] << "\t" << std::setw(10) << y[0]
				  << std::setw(10) << y[1] << std::setw(10) << y[2]
				  << std::setw(10) << y[3] << "\n";
		ofs << "0.00000," << x[0] << "," << x[1] << "," << x[2] << "," << x[3]
			<< "," << y[0] << "," << y[1] << "," << y[2] << "," << y[3] << "\n";

		//Run integrations and output results
		for (double t = 0.000, tsav = dtsav; t < tEnd;) {

			//Run integrations
			rungeKuttaStepper(t, x, dt, 10.0 * (1.0 - cos(2 * M_PI * t / 150.0))); //Sinusoidal current
			if (t > 50.0 && t < 100.0) {
				rungeKuttaStepper(t, y, dt, 10.0); //Stepwise current active
			}
			else {
				rungeKuttaStepper(t, y, dt, 0.0); //Stepwise current inactive
			}

			//Output results
			if (t >= tsav) {
				std::cout << std::left << std::setw(10) << t
						  << std::right << std::setw(10) << x[0]
						  << std::setw(10) << x[1] << std::setw(10) << x[2]
						  << std::setw(10) << x[3] << "\t" << std::setw(10) 
					      << y[0] << std::setw(10) << y[1] << std::setw(10) 
					      << y[2] << std::setw(10) << y[3] << "\n";
				ofs << t << "," << x[0] << "," << x[1] << "," << x[2] << "," 
					<< x[3]	<< "," << y[0] << "," << y[1] << "," << y[2] << "," 
					<< y[3] << "\n";
				tsav += dtsav;
			}
		}
	}
	catch (std::exception &error) {
		std::cerr << "Error: " << error.what();
		return 1;
	}

	return 0;
}

//13.1.a
//Both population densities oscillate around their initial values with increasing amplitude.

//13.1.b
//Both population densities oscillate around their initial values with constant amplitude.

//13.2.b
//Underflow errors?