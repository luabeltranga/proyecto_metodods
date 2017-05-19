//compilar con make chaos

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

const double K = 1.0;
const double TAU = 2*M_PI;
const int TIME = 10000 ;
const int N = 100;

void time_step(std::vector<double> & point0);
double decimal_part(double x );

int main(void){
  
  // GSL's Taus generator:
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_taus2);
  // Initialize the GSL generator with time:
  gsl_rng_set(rng, 1000); // Seed with time
  
 
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  std::ofstream datos;

  std::vector<double> point (2);
  
  datos.open("chaos_map.dat");
  for(int ii = 0; ii < N ; ii++){
    point[0] = gsl_rng_uniform(rng);
    point[1] = gsl_rng_uniform(rng);
    datos << point[0] << " " << point[1] << std::endl;        
    for(int jj = 0; jj < TIME ; jj++){
      time_step(point);
      datos << point[0] << " " << point[1] << std::endl;        
    }
    datos << std::endl;
  }

  datos.close();
  
}

void time_step(std::vector<double> & point0){
  
  point0[1] = decimal_part(point0[1] + K/TAU*std::sin(TAU*point0[0]) );

  point0[0] = decimal_part(point0[0] + point0[1]);
}

double decimal_part(double x ){
  int x_tmp = x;
  if(x>0)return x - x_tmp;
  if(x<=0)return  x_tmp - x;
}
