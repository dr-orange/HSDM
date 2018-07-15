/**
 * Singular Value Decomposion
 *
 * 特異値分解 A = UWV^T をする
 *
 * それぞれ以下のメソッドで行列を取り出す
 * U : getLeftUnitaryMatrix()
 * W : getDiagonalMatrix()
 * V : getRightUnitaryMatrix()
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _SVD_H_
#define _SVD_H_

class SVD {

  int m;
  int n;
  //  Matrix a;
  Matrix u;
  Matrix w;
  Matrix v;

  long double pythag(long double, long double);

public:

  SVD(Matrix);
  ~SVD();

  void solve();
  Matrix getLeftUnitaryMatrix();
  Matrix getDiagonalMatrix();
  Matrix getRightUnitaryMatrix();

};

#endif //#ifndef _SVD_H_
