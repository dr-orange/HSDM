/*
  $Id: AWGN.cc,v 1.1 2000/08/10 23:41:17 warhol Exp $
 */

#include <header.h>
#include <AWGN.h>

AWGN::AWGN(long double snr) {
  setSNR(snr);
}

AWGN::~AWGN() {
}

void AWGN::setSNR(long double snr)
{
  sqrt_n = sqrt(1.0L / exp(log(10.0L) * snr / 10.0L));
}

void AWGN::setSNR(AWGN_STATUS snr)
{
  if(snr == NOISELESS){
    sqrt_n = 0;
  }
  else {
    sqrt_n = 0;
    cerr << "set to noiseless." << endl;
  }
}

void AWGN::setVariance(long double variance)
{
  //  this->snr = snr;
  //  sqrt_n = sqrt(0.5L / exp(log(10.0L) * snr / 10.0L));
  if(snr == NOISELESS){
    sqrt_n = 0;
  }
  else {
    sqrt_n = sqrt(variance);
  }
  cout << "SNR: " << - 20.0L * log(sqrt_n) / log(10.0L) << endl;
}

long double AWGN::addNoise(long double signal){
  long double r1, r2;
  long double sigma;

  r1 = /*1.0L - */(long double)rand() / RAND_MAX;
  r2 = 2.0L * M_PI * (/*1.0L - */(long double)rand() / RAND_MAX);

  sigma = sqrt_n * sqrt(-2.0L * log(r1));
  signal += sigma * cos(r2);
  // abave is 0 mean. berrow is A mean.
  //  signal += A + sigma * cos(r2);
  
  return signal;
}
