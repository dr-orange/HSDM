/*
  $Id: Vector.cc,v 1.1 2000/08/10 23:40:21 warhol Exp $
 */

#include <header.h>
#include <Vector.h>

Vector::Vector(int nSpace) {
  this->nSpace = nSpace;

  vector = new long double[nSpace];
  for(int i = 0; i < nSpace; i++)
    vector[i] = 0;
}

Vector::~Vector() {
 delete [] vector;
}

Vector::Vector(const Vector& a){
  nSpace = a.nSpace;
  vector = new long double[nSpace];
  for(int i = 0; i < nSpace; i++)
    vector[i] = a.vector[i];
}

Vector& Vector::operator=(Vector a){
  if(nSpace == 0) {
    delete [] vector;
    vector = new long double[a.nSpace];
  }
  nSpace = a.nSpace;
  for(int i = 0; i < nSpace; i++) vector[i] = a.vector[i];

  return *this;
}

void Vector::addElement(long double elem) {
  Vector temp = *this;

  delete [] vector;
  nSpace++;
  vector = new long double[nSpace];
  for(int i = 0; i < nSpace - 1; i++)
    setElementAt(temp.getElementAt(i), i);
  setElementAt(elem, nSpace - 1);
}

void Vector::removeElement(int index) {
  Vector temp = *this;

  delete [] vector;
  nSpace--;
  vector = new long double[nSpace];
  for(int i = 0; i < index; i++)
    setElementAt(temp.getElementAt(i), i);
  for(int i = index + 1; i < nSpace + 1; i++)
    setElementAt(temp.getElementAt(i), i - 1);
}

int Vector::getLength(){
  return nSpace;
}

void Vector::setElementAt(long double value, int index) {
  vector[index] = value;
}

long double Vector::getElementAt(int index) {
  return vector[index];
}

long double Vector::getNorm() {
  long double sum = 0;

  for(int i = 0; i < nSpace; i++)
    sum += vector[i] * vector[i];

  return sqrt(sum);
}

bool operator >(Vector a, Vector b) {
#ifndef _OPTIMIZE_
  if(a.getLength() != b.getLength()) {
    cerr << "* error in Vector::operator>(Vector a, Vector b)." << endl;
    cerr << "  both of vector does not have the same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  bool isSmall = true;

  for(int i = 0; i < a.getLength(); i++)
    if(a.getElementAt(i) <= b.getElementAt(i)) isSmall = false;
  
  return isSmall;
}

Vector operator +(Vector a, Vector b) {
#ifndef _OPTIMIZE_
  if(a.getLength() != b.getLength()) {
    cerr << "* error in Vector::operator+(Vector a, Vector b)." << endl;
    cerr << "  both of vector does not have the same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Vector c(a.getLength());

  for(int i = 0; i < a.getLength(); i++)
    c.setElementAt(a.getElementAt(i) + b.getElementAt(i), i);

  return c;
}

Vector operator +=(Vector& a, Vector b) {
  a = a + b;
  return a;
}

Vector operator -(Vector a, Vector b) {
#ifndef _OPTIMIZE_
  if(a.getLength() != b.getLength()) {
    cerr << "* error in Vector::operator-(Vector a, Vector b)." << endl;
    cerr << "  both of vector does not have the same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  Vector c(a.getLength());

  for(int i = 0; i < a.getLength(); i++)
    c.setElementAt(a.getElementAt(i) - b.getElementAt(i), i);

  return c;
}

Vector operator -=(Vector& a, Vector b) {
  a = a - b;
  return a;
}

Vector operator *(long double a, Vector b) {
  Vector c(b.getLength());

  for(int i = 0; i < b.getLength(); i++)
    c.setElementAt(a * b.getElementAt(i), i);

  return c;
}

Vector operator /(Vector a, long double b) {
  Vector c(a.getLength());

  for(int i = 0; i < a.getLength(); i++)
    c.setElementAt(a.getElementAt(i) / b, i);

  return c;
}

long double operator *(Vector a, Vector b) {
#ifndef _OPTIMIZE_
  if(a.getLength() != b.getLength()) {
    cerr << "* error in Vector::operator*(Vector a, Vector b)." << endl;
    cerr << "  both of vector does not have the same size." << endl;
    exit(0);
  }
#endif //#ifndef _OPTIMIZE_

  long double c = 0;
  for(int i = 0; i < a.getLength(); i++)
    c += a.getElementAt(i) * b.getElementAt(i);

  return c;
}

ostream& operator <<(ostream& os, Vector a) {
  os << "( " << _F(a.getElementAt(0));
  for(int i = 1; i < a.getLength(); i++)
    os << ", " << _F(a.getElementAt(i));
  os << " )";

  return os;
}

Vector Vector::e(int col){
  Vector c(col);

  for(int i = 0; i < col; i++)
    c.setElementAt(1, i);

  return c;
}

void Vector::setAllZero(){
  for(int i = 0; i < nSpace; i++)
    vector[i] = 0;
}
