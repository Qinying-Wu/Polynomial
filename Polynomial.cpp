//============================================================================
// Name        : Polynomial.cpp
// Author      : Jessica Wu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Polynomial.h"

#ifndef MARMOSET_TESTING
int main();
#endif

void init_poly(poly_t &p, double const init_coeffs[],unsigned int const init_degree);
void destroy_poly(poly_t &p);
unsigned int poly_degree(poly_t const & p);
double poly_coeff(poly_t const&p, unsigned int n);
double poly_val(poly_t const &p, double constx);
void poly_add(poly_t &p,poly_t const &q);
void poly_subtract(poly_t &p,poly_t const &q);
void poly_multiply(poly_t &p,poly_t const &q);
double poly_divide(poly_t &p,double r);
void poly_diff(poly_t &p);
double poly_approx_int(poly_t const &p, double a, double b, unsigned int n );

void init_poly(poly_t &p, double const init_coeffs[],unsigned int const init_degree){
	p.degree=init_degree;
	if(p.a_coeffs!=nullptr){
		destroy_poly(p);
	}
	p.a_coeffs=new double [init_degree+1];
	for (unsigned int i=0;i<=p.degree;i++){
		p.a_coeffs[i]=init_coeffs[i];
	}
}
void destroy_poly(poly_t &p ){
	delete[] p.a_coeffs;
	p.a_coeffs=nullptr;
}
unsigned int poly_degree(poly_t const &p){
	for(unsigned int i=0;i<p.degree;i++){
		if(p.a_coeffs==nullptr){
			throw 0;
		}
	}
	return p.degree;
}
double poly_coeff(poly_t const&p, unsigned int n ){
	for(unsigned int i=0;i<n;i++){
		if(p.a_coeffs==nullptr){
			throw 0;
		}
	}
	return *(p.a_coeffs+n);
}
double poly_val(poly_t const &p, double const x ){
	double result{0};
	for (int i=p.degree;i>=0;i--){
		if(p.a_coeffs==nullptr){
			throw 0;
		}
		result=result*(x)+*(p.a_coeffs+i);
	}
	return result;
}
void poly_add(poly_t &p,poly_t const &q){
	unsigned int new_degree=std::max(p.degree,q.degree);
	double array [new_degree+1];
	for (unsigned int i=0;i<=new_degree;i++){
		if(p.a_coeffs==nullptr){
			throw 0;
		}
		if(q.a_coeffs==nullptr){
			throw 0;
		}
		if(i<=p.degree&&i<=q.degree){
			array[i]=*(p.a_coeffs+i)+*(q.a_coeffs+i);
		}
		else{
			if(i>p.degree){
				array[i]=*(q.a_coeffs+i);
			}
			if(i>q.degree){
				array[i]=*(p.a_coeffs+i);
			}
		}

	}
	init_poly(p,array,new_degree);
}
void poly_subtract(poly_t &p, poly_t const &q){
	unsigned int new_degree=std::max(p.degree,q.degree);
	double array[new_degree+1];
	for (unsigned int i=0;i<=new_degree;i++){
		if(p.a_coeffs==nullptr){
			throw 0;
		}
		if(q.a_coeffs==nullptr){
			throw 0;
		}

		if(i<=p.degree&&i<=q.degree){
			array[i]=p.a_coeffs[i]-q.a_coeffs[i];
		}
		else{
			if(i>p.degree){
				array[i]=0-q.a_coeffs[i];
			}
			if(i>q.degree){
				array[i]=p.a_coeffs[i];
			}
		}
	}
	init_poly(p,array,new_degree);

}
void poly_multiply(poly_t &p,poly_t const &q){
	unsigned int new_degree{p.degree+q.degree};
	double array [new_degree+1];
	for (unsigned int i=0;i<=p.degree;i++){
		if(p.a_coeffs==nullptr){
			throw 0;
		}

		for (unsigned int j=0;j<=q.degree;j++){
			if(q.a_coeffs==nullptr){
				throw 0;
			}
			array[i+j]=array[i+j]+p.a_coeffs[i]*q.a_coeffs[j];
		}

	}
	init_poly(p,array,new_degree);
}
double poly_divide(poly_t &p,double r){
	double remainder{0.0};
	double array[p.degree];
	if(p.a_coeffs==nullptr){
		throw 0;
	}
	else if(p.degree==0){
		array[0]=0;
		remainder=p.a_coeffs[0];
		init_poly(p,array,0);
		return remainder;
	}
	else{
		for(int i=p.degree;i>=0;i--){
			remainder+=p.a_coeffs[i];
			if(i>0){
				array[i-1]=remainder;
				remainder*=r;
			}
		}
		init_poly(p,array,p.degree-1);
		return remainder;
	}
}
void poly_diff(poly_t &p){
	double array[p.degree];
	for(unsigned int i=0; i<p.degree;i++){
		array[i]=p.a_coeffs[i+1]*(i+1);
	}
	init_poly(p,array,p.degree-1);
}
double poly_approx_int(poly_t const &p, double a, double b, unsigned int n ){
	double h{(b-a)/n};
	double sum{h*(poly_val(p,a)+poly_val(p,b))/2};
	if(p.a_coeffs==nullptr){
		throw 0;
	}
	for (unsigned int k=1;k<n;k++){
		sum=sum+h*poly_val(p,a+k*h);
	}
	return sum;
}
#ifndef MARMOSET_TESTING
int main(){
	return 0;
}
#endif
