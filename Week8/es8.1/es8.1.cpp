

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "es8.1.h"

using namespace std;
 
int main (int argc, char *argv[]){

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

   /**********************************************************/

   double x0 = 0.5;

   x = x0;

   for(int iblock = 1; iblock <=nblocks;iblock++){
	
	Blk_Reset();
	//ofstream Pos_out("pos.out");
	for(int istep = 0; istep <nsteps;istep++){
		Move();
		Measure();
	//	Pos_out << walker << endl;
		Accumulate();
	}
	
	Average(iblock); 

	if(iblock%10 == 0){
		cout << endl << "Completed " << iblock << "/" << nblocks;
	}
   }


   ofstream H_out("output.H.o");

   /*  		THIS IS TO SHOW CONVERGENCE, NOT JUST FINAL VALUE

   for (int iblock = 0; iblock < nblocks;iblock ++){
	
	for(int j = 0; j <= iblock;j++){
		prog_sum[iblock] += stima_H[j];
		prog_sum2[iblock] += stima_H[j]*stima_H[j];
   	}

	prog_sum[iblock]/=(iblock+1);
	prog_sum2[iblock]/=(iblock+1);

	prog_err[iblock] = sqrt( prog_sum2[iblock] - pow(prog_sum[iblock],2) ) / sqrt(iblock+1);
   }
   */

   for(int iblock = 1; iblock <=nblocks;iblock++){

   	prog_sum += stima_H[iblock-1];
	//cout << stima_H[iblock-1] << endl;
	prog_sum2 += stima_H[iblock-1]*stima_H[iblock-1];

	prog_sum/=nblocks;
	prog_sum/=nblocks;
   }

   prog_err = sqrt( prog_sum2 - pow(prog_sum,2) ) / sqrt(nblocks);
    
   H_out << prog_sum << " " << prog_err;







  rnd.SaveSeed();
   return 0;

}

/*****************************************/

	
   void Blk_Reset(){
	H_ave = 0;
   }

   void Move(){

	xnew = x + rnd.Rannyu(-L,L);

	double alpha = min( 1., Psi_square(xnew,mu,sigma)/Psi_square(x,mu,sigma) );

	if(rnd.Rannyu() < alpha){
		x = xnew;
	}

   }

   void Measure(){
	double H = H_Psi(x,sigma,mu) / Psi_trial(x,sigma,mu);
	walker = H;
   }

   void Accumulate(){
	H_ave += walker;
   }

   void Average(int iblock){
	stima_H[iblock-1] = H_ave/nsteps;
   }


   double Potential(double x){
	return pow(x,4) - 5./2.*pow(x,2);
   }

   double Potential_first(double x){
	return 4.*pow(x,3) - 5.*x;
   }

   double Potential_second(double x){
	return 12.*pow(x,2);
   }


   double Psi_trial(double x, double mu, double sigma){

	double e_plus = exp(-(x+mu)*(x+mu)/(2.*sigma*sigma));
	double e_minus = exp(-(x-mu)*(x-mu)/(2.*sigma*sigma));

	return e_minus + e_plus;
   }
  
   double Psi_square(double x, double mu, double sigma){
	return Psi_trial(x,mu,sigma)*Psi_trial(x,mu,sigma);
   }



   double Psi_first(double x, double mu, double sigma){

	double e_plus = exp(-(x+mu)*(x+mu)/(2.*sigma*sigma));
	double e_minus = exp(-(x-mu)*(x-mu)/(2.*sigma*sigma));

	return -(x-mu)/pow(sigma,2)*e_minus - (x+mu)/pow(sigma,2)*e_plus;
   }
   double Psi_second(double x, double mu, double sigma){

	double e_plus = exp(-(x+mu)*(x+mu)/(2.*sigma*sigma));
	double e_minus = exp(-(x-mu)*(x-mu)/(2.*sigma*sigma));

	return (pow(x-mu,2) - pow(sigma,2))/pow(sigma,4) * e_minus + (pow(x+mu,2) - pow(sigma,2))/pow(sigma,4) * e_plus;
   }

   double H_Psi(double x,double mu,double sigma){
 	return - hbar/(2.*mass) * Psi_second(x,mu,sigma) + Potential(x)*Psi_trial(x,mu,sigma);
   }

