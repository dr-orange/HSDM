#ifndef _RESTRICTEDTOTALLEASTSQUARES_H_
#define _RESTRICTEDTOTALLEASTSQUARES_H_

class RestrictedTotalLeastSquares {

  Matrix A;
  Matrix Adash;
  Matrix Atran;
  Matrix P;
  Vector b;

  void step1();
  void step2();
  void step3();
  void step4();

public:

  RestrictedTotalLeastSquares() {};
  RestrictedTotalLeastSquares(Matrix, Vector);
  ~RestrictedTotalLeastSquares();

  void start();
};

#endif //#ifndef _RESTRICTEDTOTALLEASTSQUARES_H_
