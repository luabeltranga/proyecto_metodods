//compilar con make chaos

#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <gsl/gsl_statistics.h>



const double TAU = 2*M_PI;
const int TIME = 200 ;
const int N = 100;


void time_step(std::vector<double> & point0 ,double k);
double custom_mod(double x);
double autocorrelation(const double * momentum, int &shift);

int main(void){
  
  
  
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  
  double *momentum = new double [TIME+1];
  std::vector<double> position(TIME+1);
  std::vector<double> point (2);
  
  point[0] = 0.8;
  point[1] = 0.2;
  momentum[0] = point[1];
  double K = 5.0;
  for(int ii = 0; ii < 1; ii++ ){
    for(int jj = 0; jj < TIME ; jj++){
      time_step(point,K);
      momentum[jj+1] = point[1];
      position[jj+1] = point[0];
      //    std::cout<< position[jj+1] << " " << momentum[jj+1] << std::endl;
      //std::cout<<jj+1<< " " << std::fabs(gsl_stats_lag1_autocorrelation(momentum, 1, jj+1)-gsl_stats_mean(momentum, 1, jj+1)/gsl_stats_variance(momentum, 1, jj+1)) << std::endl;
      std::cout<<jj+1<< " " <<   << std::endl;
      
    }
    
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

double autocorrelation(const double * momentum, int &shift){
  double sum = 0;
  double size = TIME+1;
  for (int ii = 0 ; ii < size-shift; ii++){
    sum += momentum[ii+shift]*momentum[ii];
  }
  
  return sum -std::pow(gsl_stats_mean(momentum, 1, TIME+1),2);
}
