#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <vector>

const double K = 10.0;
const double TAU = 2*M_PI;
const int TIME = 500;
const int N = 1;


void time_step(std::vector<double> & point0);
double custom_mod(double x);
void autocorrelation(std::vector<double> & momentum);

int main(void){
  std::random_device rd;
  std::mt19937_64 gen(rd()); 
  std::uniform_real_distribution<double> dis(0, 1);
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  std::ofstream datos;
  
  std::vector<double> point (2);
  std::vector<double> momentum (N*TIME+1 );
  
  datos.open("chaos_map.dat");
  for(int ii = 0; ii < N ; ii++){
    //q
    point[0] = dis(gen);
    //p
    point[1] = dis(gen);
    
    momentum[0] = point[1];  
    
    datos << point[0] << " " << point[1]  << " " << momentum[0] << std::endl;        
    for(int jj = 0; jj < TIME ; jj++){
      time_step(point);
      momentum[ii*TIME + jj+1] = point[1];  
      datos << point[0] << " " << point[1] << " " << momentum[ii*TIME+jj+1] << std::endl;        
    }
    datos << std::endl;
  }
  datos.close();

  autocorrelation(momentum);

}


void time_step(std::vector<double> & point0){
  
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

void autocorrelation(std::vector<double> & momentum){
  int N = momentum.size();
  double sum = 0.0;
  std::ofstream autocorr ;
  double mean = std::accumulate(momentum.begin(),momentum.end(),0.0)/N;
  autocorr.open("corr.dat");
  for(int tau = 0 ; tau < N-1; tau++){
    for(int t = 0 ; t < N-1-tau ; t++){
      sum += momentum[t]*momentum[t+tau];
    }
    sum /= N-tau; 
    autocorr << tau << " " <<std::fabs(sum - std::pow(mean,2))<< "\n";
  }
  
  autocorr.close();
  
}
