//compilar con make chaos

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <vector>

const double K = 0.99;
const double TAU = 2*M_PI;
const int TIME = 5000 ;
const int N = 100;


void time_step(std::vector<double> & point0);
double custom_mod(double x);
int main(void){

  std::mt19937_64 gen(10000); 
  std::uniform_real_distribution<> dis(0, 1);
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  std::ofstream datos;

  std::vector<double> point (2);
  std::vector<double> momentum( );

  datos.open("chaos_map.dat");
  for(int ii = 0; ii < N ; ii++){
    point[0] = dis(gen);
    point[1] = dis(gen);
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
