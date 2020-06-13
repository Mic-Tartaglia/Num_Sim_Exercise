
#include <iostream>
#include <fstream>
#include <cmath>
#include "random.h"

using namespace std;
 
double StdDev(double mean, double sq_mean, int n){

	return sqrt (( sq_mean - mean*mean )/n);

}

double max( double x1, double x2){

	if (x1 >= x2)
		return x1;
	else
		return x2;
}



int main (int argc, char *argv[]){

/***************************************************************///GENERATOR SETUP

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

/****************************************************************/

	int const M = 1e5;
	int const N = 1e2;
	int L=M/N;


	double const s0 = 100;
	double const T= 1;
	double const K=100;
	double const r= 0.1;
	double const sigma = 0.25;

	//double GAUSS = 1;//PLACEHOLDER FOR GAUSSIAN

	double S[M];
	double profit[M];

	for (int k=0;k<M;k++){
	
		S[k]=s0;

		for(int j=0;j<100;j++){

			S[k] = S[k] * exp( (r-sigma*sigma/2)* T/100 + sigma* rnd.Gauss(0,1)*sqrt(T/100));
		}

		profit[k]= max( - S[k] + K, 0);

	}

	







	double ave[N], sq_ave[N], prog_sum[N], prog_sq[N], prog_err[N];




	for(int i=0;i<N;i++){
		ave[i]=0;
		prog_sq[i]=0;
		prog_sum[i]=0;		

		for(int k=0;k<L;k++)
			ave[i]+=profit[i*L+k];
		
		ave[i]/=L;
		sq_ave[i]= ave[i]*ave[i];

		for(int j=0;j<i;j++){
			prog_sum[i]+= ave[j];
			prog_sq[i]+= sq_ave[j];
		}

		prog_sum[i]/=(i+1);		
		prog_sq[i]/=(i+1);
		prog_err[i]= StdDev(prog_sum[i], prog_sq[i] , i+1);

	}

	ofstream res_out("results.dat");
	ofstream err_out("errors.dat");

	for (int i=0;i<N;i++){
		res_out << prog_sum[i] << "\n";
		err_out << prog_err[i] << "\n";
	}
	res_out.close();
	err_out.close();


	





	rnd.SaveSeed();
	return 0;
}

