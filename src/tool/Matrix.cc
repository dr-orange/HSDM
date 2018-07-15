/**
 * ����򰷤����饹
 *
 * $Id: Matrix.cc,v 1.2 2000/08/10 23:39:41 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>

/**
 * ���󥹥ȥ饯��
 *
 * @param m �Կ�
 * @param n ���
 */
Matrix::Matrix(int m, int n){
  this->m = m;
  this->n = n;

  // �������٥��ȥ������Ȥ��ư���
  colVector = new Vector[n];
  // ����ν����
  for(int i = 0; i < n; i++){
    colVector[i] = Vector(m);
    for(int j = 0; j < m; j++)
      colVector[i].setElementAt(0, j);
  }
}

/**
 * ���ԡ����󥹥ȥ饯��
 */
Matrix::Matrix(const Matrix& a){
  m = a.m;
  n = a.n;

  // �������٥��ȥ������Ȥ��ư���
  colVector = new Vector[n];
  for(int i = 0; i < n; i++){
    // ����ν����
    colVector[i] = Vector(m);
    // ���ǤΥ��ԡ�
    colVector[i] = a.colVector[i];
  }
}

/**
 * = (�����黻��)�����
 *
 * @param a �����������
 * @return �������줿����
 */
Matrix& Matrix::operator=(Matrix a){
  // ������줿�������ѿ��ν���
  if(n == 0 || m == 0) {
    delete [] colVector;
    colVector = new Vector[a.n];
    m = a.m;
    n = a.n;
  }
#ifndef _OPTIMIZE_
  // �礭���ΰ㤦������������Ԥ�줿���, ��λ����
  else if(m != a.m || n != a.n) {
    cerr << "* error in Matrix::operator=(Matrix a)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  // ���ǤΥ��ԡ�
  for(int i = 0; i < n; i++)
    colVector[i] = a.colVector[i];

  return *this;
}

void Matrix::setElementAt(long double value, int index_h, int index_w) {
  colVector[index_w].setElementAt(value, index_h);
}

long double Matrix::getElementAt(int index_h, int index_w) {
  return colVector[index_w].getElementAt(index_h);
}

long double Matrix::getNorm() {
  cerr << "* error in Matrix::getNorm()." << endl;
  cerr << "  Norm is undefined." << endl;
  exit(0);

  return 0;
}

void Matrix::setVectorAt(Vector vector, int index){
#ifndef _OPTIMIZE_
  if(vector.getLength() != m){
    cerr << "* error in Matrix::setVectorAt(Vector vector, int index)." << endl;
    cerr << "  the vector's size does not match the matrix size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  colVector[index] = vector;
}

Vector Matrix::getVectorAt(int index){
  return colVector[index];
}

Vector Matrix::getRowVectorAt(int index){
  Vector c = Vector(n);

  for(int i = 0; i < n; i++)
    c.setElementAt(getElementAt(index, i), i);

  return c;
}

/**
 * ñ�̹���
 *
 * static �������Ƥ���Τ� Matrix::I(3) �ǸƤӽФ��롣
 *
 * @param size ������礭��
 * @return ñ�̹���
 */
Matrix Matrix::I(int size){
  Matrix c = Matrix(size, size);

  for(int i = 0; i < size; i++)
    c.setElementAt(1, i, i);

  return c;
}

/**
 * ���Ǥ����� 1 �������ޥȥꥯ��
 *
 * static �������Ƥ���Τ� Matrix::E(3) �ǸƤӽФ��롣
 *
 * @param size ������礭��
 * @return ���Ǥ����� 1 �������ޥȥꥯ��
 */
Matrix Matrix::E(int size){
  Matrix c = Matrix(size, size);

  for(int i = 0; i < size; i++)
    c.setVectorAt(Vector::e(size), i);

  return c;
}

/**
 * row��col��������������
 *
 * @param row ��
 * @param col ��
 * @return row��col��������������
 */
Matrix Matrix::getReducedMatrix(int row, int col){
#ifndef _OPTIMIZE_
  if(getHeight() <= 2  || getWidth() <= 2 ||
     getHeight() < row || getWidth() < col ||
     row < 0 || col < 0){
    cerr << "* error in Matrix::getReducedMatrix(int row, int col)." << endl;
    cerr << *this << "cant be reduced." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix c = Matrix(getWidth() - 1, getHeight() - 1);

  for(int j = 0; j < getWidth(); j++){
    if(j == col) continue;
    int jnew = (j < col)?j:j - 1;
    for(int i = 0; i < getHeight(); i++){
      if(i == row) continue;
      int inew = (i < row)?i:i - 1;
      c.setElementAt(getElementAt(i, j), inew, jnew);
    }
  }

  return c;
}

void Matrix::addRowVector(Vector a) {
#ifndef _OPTIMIZE_
  if(a.getLength() != n){
    cerr << "* error in Matrix::addRowVector(Vector a)." << endl;
    cerr << "  the vector's size does not match the matrix size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix temp = Matrix(m, n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      temp.setElementAt(getElementAt(j, i) , j, i);
  delete [] colVector;
  m++;
  colVector = new Vector[n];
  for(int i = 0; i < n; i++){
    colVector[i] = Vector(m);
    for(int j = 0; j < m - 1; j++)
      colVector[i].setElementAt(temp.getElementAt(j, i), j);
    colVector[i].setElementAt(a.getElementAt(i), m - 1);
  }
}

void Matrix::addColVector(Vector a) {
#ifndef _OPTIMIZE_
  if(a.getLength() != m){
    cerr << "* error in Matrix::addColVector(Vector a)." << endl;
    cerr << "  the vector's size does not match the matrix size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix temp = Matrix(m, n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      temp.setElementAt(getElementAt(j, i) , j, i);
  delete [] colVector;
  n++;
  colVector = new Vector[n];
  for(int i = 0; i < n - 1; i++){
    colVector[i] = Vector(m);
    for(int j = 0; j < m; j++)
      colVector[i].setElementAt(temp.getElementAt(j, i), j);
  }
  colVector[n - 1] = Vector(m);
  setVectorAt(a, n - 1);
}

Matrix operator +(Matrix a, Matrix b) {
#ifndef _OPTIMIZE_
  if(a.getHeight() != b.getHeight() ||
     a.getWidth()  != b.getWidth()) {
    cerr << "* error in Matrix::operator+(Matrix a, Matrix b)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix c = Matrix(a.getHeight(), a.getWidth());

  for(int i = 0; i < a.getWidth(); i++)
    c.setVectorAt(a.getVectorAt(i) + b.getVectorAt(i), i);

  return c;
}

Matrix operator -(Matrix a, Matrix b) {
#ifndef _OPTIMIZE_
  if(a.getHeight() != b.getHeight() ||
     a.getWidth()  != b.getWidth()) {
    cerr << "* error in Matrix::operator-(Matrix a, Matrix b)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix c = Matrix(a.getHeight(), a.getWidth());

  for(int i = 0; i < a.getWidth(); i++){
    c.setVectorAt(a.getVectorAt(i) - b.getVectorAt(i), i);
  }

  return c;
}

Matrix operator *(Matrix a, Matrix b) {
#ifndef _OPTIMIZE_
  if(a.getWidth()  != b.getHeight()) {
    cerr << "* error in Matrix::operator*(Matrix a, Matrix b)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Matrix c = Matrix(a.getHeight(), b.getWidth());

  for(int i = 0; i < a.getHeight(); i++)
    for(int j = 0; j < b.getWidth(); j ++)
      c.setElementAt(a.getRowVectorAt(i) * b.getVectorAt(j), i, j);

  return c;
}

Vector operator *(Matrix a, Vector b) {
#ifndef _OPTIMIZE_
  if(a.getWidth()  != b.getLength()) {
    cerr << "* error in Matrix::operator*(Matrix a, Vector b)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Vector c = Vector(a.getHeight());

  for(int i = 0; i < a.getHeight(); i++)
    c.setElementAt(a.getRowVectorAt(i) * b, i);

  return c;
}

Vector operator *(Vector a, Matrix b) {
#ifndef _OPTIMIZE_
  if(b.getHeight()  != a.getLength()) {
    cerr << "* error in Matrix::operator*(Vector a, Matrix b)." << endl;
    cerr << "  both of matrix does not have same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Vector c = Vector(b.getWidth());

  for(int i = 0; i < b.getWidth(); i++)
    c.setElementAt(a * b.getVectorAt(i), i);

  return c;
}

Matrix operator *(long double a, Matrix b) {
  Matrix c = Matrix(b.getHeight(), b.getWidth());

  for(int i = 0; i < b.getWidth(); i++)
    c.setVectorAt(a * b.getVectorAt(i), i);

  return c;
}

/**
 * ž�ֹ���
 *
 * @param a ����
 * @return a��ž�ֹ���
 */
Matrix trans(Matrix a){
  Matrix c = Matrix(a.getWidth(), a.getHeight());

  for(int i = 0; i < a.getHeight(); i++)
    c.setVectorAt(a.getRowVectorAt(i), i);

  return c;
}

/**
 * ����
 *
 * @param a ����
 * @return a�ι���
 */
long double det(Matrix a){
#ifndef _OPTIMIZE_
  if(a.getWidth() != a.getHeight() || a.getWidth() <= 0){
    cerr << "* error in det(Matrix a)." << endl;
    cerr << a << "has no determinant.";
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  long double determinant;

  if(a.getWidth() == 1){
    determinant = a.getElementAt(0, 0);
  }
  else if(a.getWidth() == 2){
    determinant = a.getElementAt(0, 0) * a.getElementAt(1, 1)
      - a.getElementAt(0, 1) * a.getElementAt(1, 0);
  }
  else {
    determinant = 0;
    for(int i = 0; i < a.getWidth(); i++){
      long double temp = a.getElementAt(i, a.getHeight() - 1)
	* det(a.getReducedMatrix(i, a.getHeight() - 1));
      if((i + a.getHeight() - 1) % 2 != 0) temp = -temp;
      determinant += temp;
    }
  }

  return determinant;
}

/**
 * ;���ҥޥȥꥯ��
 *
 * @param a ����
 * @return a��;���ҥޥȥꥯ��
 */
Matrix adj(Matrix a){
  Matrix c = Matrix(a.getWidth(), a.getHeight());

  if(a.getWidth() == 1 && a.getHeight() == 1){
    c = a;
  }
  else if(a.getWidth() == 2 && a.getHeight() == 2){
    c.setElementAt(a.getElementAt(1, 1), 0, 0);
    c.setElementAt(a.getElementAt(0, 0), 1, 1);
    c.setElementAt(-a.getElementAt(0, 1), 0, 1);
    c.setElementAt(-a.getElementAt(1, 0), 1, 0);
  } else {
    for(int i = 0; i < a.getHeight(); i++)
      for(int j = 0; j < a.getWidth(); j++)
	c.setElementAt((((i + j) % 2 != 0)?-1:1) * det(a.getReducedMatrix(i, j)), j, i);
  }

  return c;
}

/**
 * �չ��� (�׻��̤�Ķ¿��)
 *
 * @param a ����
 * @return a�εչ���
 */
Matrix inverse(Matrix a){
#ifndef _OPTIMIZE_
  if(a.getWidth() != a.getHeight() || a.getWidth() <= 0){
    cerr << "* error in inverse(Matrix a)." << endl;
    cerr << a << "has no inverse matrix.";
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  return 1 / det(a) * adj(a);
}

ostream& operator <<(ostream& os, Matrix a) {
  for(int j = 0; j < a.getHeight(); j++){
    os << "( " << _F(a.getElementAt(j, 0));
    for(int i = 1; i < a.getWidth(); i++)
      os << " " << _F(a.getElementAt(j, i));
    os << " )" << endl;
  }

  return os;
}
