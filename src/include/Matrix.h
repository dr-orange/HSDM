/**
 * ����򰷤����饹
 *
 * $Id: Matrix.cc,v 1.2 2000/08/10 23:39:41 warhol Exp $
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix {

  /** �Կ� */
  int m;
  /** ��� */
  int n;
  /** ��٥��ȥ������ */
  Vector* colVector;

public:

  /** ���Ǥ����� 1 �������ޥȥꥯ�� */
  static Matrix E(int);
  /** ñ�̹��� */
  static Matrix I(int);

  /** */
  Matrix() { n = m = 0; colVector = new Vector[1]; }
  /** ���󥹥ȥ饯�� */
  Matrix(int, int);
  /** �ǥ��ȥ饯�� */
  ~Matrix(){ delete [] colVector; }
  /** ���ԡ����󥹥ȥ饯�� */
  Matrix(const Matrix&);

  /** �Կ����֤� */
  int getHeight(){ return m; }
  /** ������֤� */
  int getWidth(){ return n; }
  /** �������ʬ����� */
  void setElementAt(long double, int, int);
  /** �������٥��ȥ����� */
  void setVectorAt(Vector, int);
  /** �ԥ٥��ȥ���ɲ� */
  void addRowVector(Vector);
  /** ��٥��ȥ���ɲ� */
  void addColVector(Vector);
  /** �������ʬ����� */
  long double getElementAt(int, int);
  /** �������٥��ȥ����� */
  Vector getVectorAt(int);
  /** ����ιԥ٥��ȥ����� */
  Vector getRowVectorAt(int);
  /** ����ΥΥ������ */
  long double getNorm();
  /** row��col�������������� */
  Matrix getReducedMatrix(int, int);
  /** = (�����黻��)����� */
  Matrix& operator=(Matrix);
  /** ���� */
  friend long double det(Matrix);
  /** ž�ֹ��� */
  friend Matrix trans(Matrix);
  /** �չ��� (�׻��̤�Ķ¿��) */
  friend Matrix inverse(Matrix);
  /** ;���ҥޥȥꥯ�� */
  friend Matrix adj(Matrix);

  /** ���� + ���� */
  friend Matrix operator +(Matrix, Matrix);
  /** ���� - ���� */
  friend Matrix operator -(Matrix, Matrix);
  /** ���� * ���� */
  friend Matrix operator *(Matrix, Matrix);
  /** ������ * ���� */
  friend Matrix operator *(long double, Matrix);
  /** ���� * �٥��ȥ� */
  friend Vector operator *(Matrix, Vector);
  /** �٥��ȥ� * ���� */
  friend Vector operator *(Vector, Matrix);

  /** ���� */
  friend ostream& operator <<(ostream&, Matrix);

};

#endif //#ifndef _MATRIX_H_
