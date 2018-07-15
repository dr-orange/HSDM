#ifndef _LU_H_
#define _LU_H_

class LU {

  long double **a;
  long double *b;
  long double *x;
  int n;
  int *ip;

  void decomposition();

public:

  LU() {};
  LU(Matrix, Vector);
  ~LU();

  void solve();
  Vector getResult();

};

#endif //#ifndef _LU_H_
