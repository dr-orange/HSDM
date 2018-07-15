#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector {

  int nSpace;
  long double* vector;

public:

  Vector() { nSpace = 0; vector = new long double[1]; }
  Vector(int);
  ~Vector();
  Vector(const Vector&);

  /**
   * �v�f���S�� 1 �̃x�N�g��
   *
   * static �錾����Ă���̂� Vector::e(3) �ŌĂяo����B
   *
   * @param col �x�N�g���̗v�f��
   * @return �v�f���S�� 1 �̃x�N�g��
   */
  static Vector e(int col);

  int getLength();
  void setAllZero();
  void setElementAt(long double, int);
  void addElement(long double);
  void removeElement(int);
  long double getElementAt(int);
  long double getNorm();
  Vector& operator =(Vector);
  friend bool operator >(Vector, Vector);
  friend Vector operator +(Vector, Vector);
  friend Vector operator +=(Vector& a, Vector b);
  friend Vector operator -(Vector, Vector);
  friend Vector operator -=(Vector& a, Vector b);
  friend Vector operator *(long double, Vector);
  friend Vector operator /(Vector, long double);
  friend long double operator *(Vector, Vector);
  friend ostream& operator <<(ostream&, Vector);
};

#endif //#ifndef _VECTOR_H_
