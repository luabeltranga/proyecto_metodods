//compilar con make chaos

#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <gsl/gsl_statistics.h>



const double TAU = 2*M_PI;
const int TIME = 15000 ;
const int N = 100;


void time_step(std::vector<double> & point0 ,double k);
double custom_mod(double x);
int main(void){
  
  
  
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  
  double *momentum = new double [TIME+1];
  std::vector<double> position(TIME+1);
  std::vector<double> point (2);
  
  point[0] = 0.3;
  point[1] = 0.7;
  momentum[0] = point[1];
  double K = 0;
  for(int ii = 1; ii < 90; ii++ ){
    K=ii*0.1+1.0;
    for(int jj = 0; jj < TIME ; jj++){
      time_step(point,K);
      momentum[jj+1] = point[1];
      position[jj+1] = point[0];
      //    std::cout<< position[jj+1] << " " << momentum[jj+1] << std::endl;
    }
    std::cout<<K<< " " << std::fabs(gsl_stats_lag1_autocorrelation(momentum, 1, 5001)) << std::endl;
  }
  delete [] momentum;
}


void time_step(std::vector<double> & point0,double K){
  
  point0[1] = custom_mod(point0[1] + K/TAU*std::sin(TAU*point0[0])) ;
  point0[0] = custom_mod(point0[0] + point0[1]);
}

double custom_mod(double x){
  if (x >= 0){
    return std::fmod(x,1);
  }
  if (x < 0){
    return 1-std::fmod(-x,1);
  }
}
