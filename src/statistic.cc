/*
 * @Author : Alexandre Behling        - 13200626
 * @Author : Gustavo Tarciso da Silva - 14100833
 */

#include "statistic.h"
#include <iostream>
#include <iterator>
#include <limits>
#include <math.h>
#include <bits/stdc++.h> 


#define _USE_MATH_DEFINES

using namespace std;

// Class constructor
Statistic::Statistic() {

	this->_n = 0;
	this->_avg = 0.0;
	this->_avg_sum = 0.0;
	this->_min = numeric_limits<double>::max();
	this->_max = numeric_limits<double>::min();
	this->_variance = 0.0;
	this->_stddev = 0.0;

	// an auxiliar atribute to save the incremental calculation of variance, 
	// to know the variance we need to divide by the size of sample
	this->_variance_sum = 0.0; 

}

// Insert a new data and calculate the statistics
void Statistic::addValue(double value) {

	
	if(value < this->_min) {
		this->_min = value;
	}
	if(value > this->_max) {
		this->_max = value;
	}
	

	this->_n++;

	// The following lines calculate the incremental mean and variance
	// according to: http://datagenetics.com/blog/november22017/index.html
	/*
	double oldavg = this->_avg;
	this->_avg = (this->_avg + (value - this->_avg)/this->_n); // incremental calculation of mean

	this->_variance_sum = (this->_variance_sum + (value - oldavg)*(value - this->_avg)); // 
	this->_variance = this->_variance_sum/(this->_n-1);
	*/

	this->_avg_sum += value;
	this->_avg = (double)(this->_avg_sum/this->_n);
	this->_variance_sum += (value*value);


	// variance = [sum(xi²) - sum(xi)²/n]/n-1
	// https://math.stackexchange.com/questions/102006/is-it-possible-to-compute-the-variance-without-computing-the-mean-first
	// https://www.thoughtco.com/sum-of-squares-formula-shortcut-3126266
	this->_variance = (double)(((this->_variance_sum) - (pow((double)this->_avg_sum, 2.0)/this->_n))/(this->_n-1));
	this->_stddev = sqrt(this->_variance);



}

// clear all statistics data
void Statistic::clear() {

	this->_n = 0;
	this->_avg = 0.0;
	this->_avg_sum = 0.0;
	this->_min = numeric_limits<double>::max();
	this->_max = numeric_limits<double>::min();
	this->_variance = 0.0;
	this->_stddev = 0.0;
	this->_variance_sum = 0.0;

}

unsigned int Statistic::numElements() {

	return this->_n;

}
double Statistic::min() {

	return this->_min;

}

double Statistic::max() {

	return this->_max;

}
double Statistic::average() {

	return this->_avg;

}

double Statistic::variance() {

	return this->_variance;

}

double Statistic::stddeviation() {

	return this->_stddev;

}

// following https://pt.wikipedia.org/wiki/Coeficiente_de_varia%C3%A7%C3%A3o
double Statistic::variationCoef() {

	double var_coef = this->_stddev/this->_avg;

	return var_coef;

}

// IC = z(1-alpha/2) * standard of deviation / n
double Statistic::halfWidthConfidenceInterval(double confidencelevel) {

	double x = (1.0-confidencelevel)/2.0;
	double zstar = calculateZ(1 - x);

	return (zstar * this->_stddev)/sqrt((double)this->_n);

}

unsigned int Statistic::newSampleSize(double confidencelevel, double halfWidth) {
	
	double x = (1.0-confidencelevel)/2.0;
	double zstar = calculateZ(1 - x);
	double n_size = n_size = (zstar*this->_stddev/halfWidth)*(zstar*this->_stddev/halfWidth);
	return ((unsigned int) n_size) +  1;

}

// Algorithm AS 241
// following http://csg.sph.umich.edu/abecasis/gas_power_calculator/algorithm-as-241-the-percentage-points-of-the-normal-distribution.pdf
double Statistic::erf_inv(double p) {
	
	const double split1=0.425;
    const double split2=5;
    const double const1=0.180625;
    const double const2=1.6;

    double q = p-0.5;
    double r;
    
    if(p==0){ 
    	return -HUGE_VAL; 
    }
    if(p==1){ 
    	return HUGE_VAL; 
    }

    if(fabs(q)<=split1){
		r=const1-q*q;
		const double A0 = 3.3871328727963666080E0;
	    const double A1 = 1.3314166789178437745E2;
	    const double A2 = 1.9715909503065514427E3;
	    const double A3 = 1.3731693765509461125E4;
	    const double A4 = 4.5921953931549871457E4;
	    const double A5 = 6.7265770927008700853E4;
	    const double A6 = 3.3430575583588128105E4;
	    const double A7 = 2.5090809287301226727E3;

	    const double B1 = 4.2313330701600911252E1;
	    const double B2 = 6.8718700749205790830E2;
	    const double B3 = 5.3941960214247511077E3;
	    const double B4 = 2.1213794301586595867E4;
	    const double B5 = 3.9307895800092710610E4;
	    const double B6 = 2.8729085735721942674E4;
	    const double B7 = 5.2264952788528545610E3;
		return q*( (((((((A7*r+A6)*r+A5)*r+A4)*r+A3)*r+A2)*r+A1)*r+A0) / 
		   (((((((B7*r+B6)*r+B5)*r+B4)*r+B3)*r+B2)*r+B1)*r+1) );
    }

    if(q<0)
		r=p;
    else
		r=1-p;

    if(r<=0)
		return NAN; // ERROR!!
    	r=sqrt(-log(r));

    if(r<=split2){
		r-=const2;
		const double C0 = 1.42343711074968357734E0;
	    const double C1 = 4.63033784615654529590E0;
	    const double C2 = 5.76949722146069140550E0;
	    const double C3 = 3.64784832476320460504E0;
	    const double C4 = 1.27045825245236838258E0;
	    const double C5 = 2.41780725177450611770E-1;
	    const double C6 = 2.27238449892691845833E-2;
	    const double C7 = 7.74545014278341407640E-4;

	    const double D1 = 2.05319162663775882187E0;
	    const double D2 = 1.67638483018380384940E0;
	    const double D3 = 6.89767334985100004550E-1;
	    const double D4 = 1.48103976427480074590E-1;
	    const double D5 = 1.51986665636164571966E-2;
	    const double D6 = 5.47593808499534494600E-4;
	    const double D7 = 1.05075007164441684324E-9;

		if(q<0) 
			return - (((((((C7*r+C6)*r+C5)*r+C4)*r+C3)*r+C2)*r+C1)*r+C0) /
			    (((((((D7*r+D6)*r+D5)*r+D4)*r+D3)*r+D2)*r+D1)*r+1);
		else{

			return (((((((C7*r+C6)*r+C5)*r+C4)*r+C3)*r+C2)*r+C1)*r+C0) / 
			 (((((((D7*r+D6)*r+D5)*r+D4)*r+D3)*r+D2)*r+D1)*r+1);
		}
    }

    r-=split2;
    const double E0 = 6.65790464350110377720E0;
    const double E1 = 5.46378491116411436990E0;
    const double E2 = 1.78482653991729133580E0;
    const double E3 = 2.96560571828504891230E-1;
    const double E4 = 2.65321895265761230930E-2;
    const double E5 = 1.24266094738807843860E-3;
    const double E6 = 2.71155556874348787815E-4;
    const double E7 = 2.01033439929228813265E-7;

    const double F1 = 5.99832206555887937690E-1;
    const double F2 = 1.36929880922735805310E-1;
    const double F3 = 1.48753612908506148525E-2;
    const double F4 = 7.86869131145613259100E-4;
    const double F5 = 1.84631831751005468180E-5;
    const double F6 = 1.42151175831644588870E-7;
    const double F7 = 2.04426310338993978564E-15;

    if(q<0) 
    	return - (((((((E7*r+E6)*r+E5)*r+E4)*r+E3)*r+E2)*r+E1)*r+E0) /
			(((((((F7*r+F6)*r+F5)*r+F4)*r+F3)*r+F2)*r+F1)*r+1);
    else 
    	return (((((((E7*r+E6)*r+E5)*r+E4)*r+E3)*r+E2)*r+E1)*r+E0) / 
	     	(((((((F7*r+F6)*r+F5)*r+F4)*r+F3)*r+F2)*r+F1)*r+1);

}

// based on https://en.wikipedia.org/wiki/Normal_distribution#Quantile_function
// probit function | probit(p) = sqrt(2)erf⁻¹(2p-1)
double Statistic::calculateZ(double confidencelevel) {

	double zstar = erf_inv(confidencelevel);
	if(zstar < 0) {
		return -1*zstar;
	} else {
		return zstar;
	}

}