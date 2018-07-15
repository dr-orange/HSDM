/**
 * Singular Value Decomposion
 *
 * �ð���ʬ�� A = UWV^T �򤹤�
 *
 * ���줾��ʲ��Υ᥽�åɤǹ������Ф�
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
