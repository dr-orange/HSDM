#ifndef _GRAMSCHMIDTORTHOGONALIZATION_H_
#define _GRAMSCHMIDTORTHOGONALIZATION_H_

class GramSchmidtOrthogonalization {

  Matrix matrix;
  Matrix orthogonal;

public:

  GramSchmidtOrthogonalization() {};
  GramSchmidtOrthogonalization(Matrix);
  ~GramSchmidtOrthogonalization();

  void start();
  Matrix getResult();

};

#endif //#ifndef _GRAMSCHMIDTORTHOGONALIZATION_H_
