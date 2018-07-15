#ifndef _AWGN_H_
#define _AWGN_H_

enum AWGN_STATUS { noiseless = 0, noisy = 1 };

class AWGN {

  long double sqrt_n;
  long double snr;

public:

  //  static const int NOISELESS = 999999;
  static const AWGN_STATUS NOISELESS = noiseless;

  AWGN() {}
  AWGN(long double);
  ~AWGN();

  void setSNR(long double);
  void setSNR(AWGN_STATUS);
  void setVariance(long double);
  long double addNoise(long double);

};

#endif //#ifndef _AWGN_H_
