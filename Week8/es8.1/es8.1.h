#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

//generator
Random rnd;

//variables

double hbar = 1;
double mass = 1;


double mu = sqrt(5.)/2.;
double sigma = 0.5;

int const nsteps = 1e5;
int const nblocks = 50;
   

double x, xnew;
double L = 0.5;

double walker;
double stima_H [nblocks];
double H_ave;

double prog_sum = 0;
double prog_sum2 = 0;
double prog_err;

//functions
double Potential(double);
double Potential_first(double);
double Potential_second(double);

double Psi_trial(double x, double mu, double sigma);
double Psi_square(double x, double mu, double sigma);
double Psi_first(double x, double mu, double sigma);
double Psi_second(double x, double mu, double sigma);
double H_Psi(double x, double mu, double sigma);

void Move();
void Measure();

void Blk_Reset();
void Accumulate();
void Average(int iblock);
