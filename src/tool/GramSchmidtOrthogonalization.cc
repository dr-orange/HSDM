/*
  $Id: GramSchmidtOrthogonalization.cc,v 1.1 2000/08/20 02:59:04 ko-ji Exp ko-ji $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <GramSchmidtOrthogonalization.h>

GramSchmidtOrthogonalization::GramSchmidtOrthogonalization(Matrix matrix){
  this->matrix = matrix;
  orthogonal = Matrix(matrix.getHeight(), matrix.getWidth());
}

GramSchmidtOrthogonalization::~GramSchmidtOrthogonalization(){
}

void GramSchmidtOrthogonalization::start(){
  Vector f[matrix.getWidth()];

  for(int i = 0; i < matrix.getWidth(); i++){
    f[i] = Vector(matrix.getHeight());
    f[i] = matrix.getVectorAt(i);
  }
  orthogonal.setVectorAt(f[0] / f[0].getNorm(), 0);

  Vector h(matrix.getHeight());
  for(int i = 1; i < matrix.getWidth(); i++){
    h = f[i];
    for(int j = 0; j < i; j++)
      h = h - (f[i] * orthogonal.getVectorAt(j)) * orthogonal.getVectorAt(j);
    orthogonal.setVectorAt(h / h.getNorm(), i);
  }
}

Matrix GramSchmidtOrthogonalization::getResult(){
  return orthogonal;
}
