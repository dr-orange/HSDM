/*
  $Id: RestrictedTotalLeastSquares.cc,v 1.1 2000/08/10 23:42:01 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <GramSchmidtOrthogonalization.h>
#include <RestrictedTotalLeastSquares.h>

RestrictedTotalLeastSquares::RestrictedTotalLeastSquares(Matrix A, Vector b){
  this->A = A;
  this->b = b;

  Adash = Matrix(A.getHeight(), A.getWidth());
  Atran = Matrix(A.getWidth(), A.getWidth());
  P = Matrix(A.getWidth(), A.getHeight());

  for(int i = 0; i < A.getWidth(); i++)
    Adash.setVectorAt(A.getVectorAt(i) - b, i);
}

RestrictedTotalLeastSquares::~RestrictedTotalLeastSquares(){
}

void RestrictedTotalLeastSquares::start(){
  step1();
}

void RestrictedTotalLeastSquares::step1(){
  step2();
}

void RestrictedTotalLeastSquares::step2(){
  step3();
}

void RestrictedTotalLeastSquares::step3(){
  GramSchmidtOrthogonalization g(Adash);
  g.start();

  P = trans(g.getResult());
  cout << P << endl;

  step4();
}

void RestrictedTotalLeastSquares::step4(){
  for(int i = 0; i < A.getWidth(); i++)
    Atran.setVectorAt(P * Adash.getVectorAt(i), i);
  cout << Atran << endl;
}

