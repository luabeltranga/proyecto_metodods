//compilar con make chaos

#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

const double K = 1.0;
const double TAU = 2*M_PI;
const int TIME = 10000 ;

struct Point{
  double q {0};
  double p {0};
  Point(double q0,double p0);
};

Point::Point(double q0,double p0){
  q = q0;
  p = p0;
}

void time_step(Point & point0);

int main(void){

  std::random_device rd;  
  std::mt19937_64 gen(rd()); 
  std::uniform_real_distribution<> dis(0, 1);
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  std::ofstream datos;
  
  Point P (0.0 , 0.0);
  int N = 1000;

  datos.open("chaos_map.dat");
  for(int ii = 0; ii < N ; ii++){
    P.q = dis(gen);
    P.p = dis(gen);
    datos << P.q << " " << P.p << std::endl;        
    for(int jj = 0; jj < TIME ; jj++){
      time_step(P);
      datos << P.q << " " << P.p << std::endl;        
    }
    datos << std::endl;
  }

  datos.close();
  
}

void time_step(Point & point0){
  
  point0.p = std::fabs(std::fmod(point0.p + K*(std::sin(TAU*point0.q))/TAU,1.0)) ;
  
  point0.q =  std::fabs(std::fmod(point0.q + point0.p,1.0));
}

