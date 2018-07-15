/*
  $Id: LU.cc,v 1.2 2000/08/11 00:12:25 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <LU.h>

#define abs(var) (var<0)?-var:var

LU::LU(Matrix a, Vector b)
{
    n = b.getLength();
    this->ip = new int[n];
    this->a = new long double*[a.getHeight()];
    for(int i  = 0; i < a.getHeight(); i++){
      this->a[i] = new long double[a.getWidth()];
      for(int j  = 0; j < a.getWidth(); j++)
        this->a[i][j] = a.getElementAt(i, j);
    }
    this->b = new long double[b.getLength()];
    for(int i = 0; i < b.getLength(); i++)
      this->b[i] = b.getElementAt(i);
    x = new long double[n];
}

LU::~LU(){
  delete [] ip;
  delete [] b;
  delete [] x;
  for(int i = 0; i < n; i++)
    delete [] a[i];
  delete [] a;
}

Vector LU::getResult(){
  Vector result(n);
  for(int i = 0; i < n; i++)
    result.setElementAt(x[i], i);

  return result;
}

void LU::decomposition()
{
  int i, j, k, ii, ik;
  long double t, u;
  long double *weight;
  
  weight = new long double[n];
  
  for(i = 0; i < n; i++){
    ip[i] = i;
    u = 0;
    for(j = 0; j < n; j++){
      if((t = abs(a[i][j])) > u){
	u = t;
      }
    }
    if(u == 0){
      delete [] weight;
      cerr << "* error in LU();" << endl;
      exit(0);
    }
    weight[i] = 1 / u;
  }
  for(k = 0; k < n; k++){
    u = -1;
    for(i = k; i < n; i++){
      ii = ip[i];
      if((t = abs(a[ii][k]) * weight[ii]) > u){
	u = t;
	j = i;
      }
    }
    ik = ip[j];
    if(j != k){
      ip[j] = ip[k];
      ip[k] = ik;
    }
    long double uu;
    uu = a[ik][k];
    for(i = k + 1; i < n; i++){
      long double temp;
      ii = ip[i];
      temp = (a[ii][k] = a[ii][k]/uu);
      for(j = k + 1; j < n; j++){
	a[ii][j] = a[ii][j]- temp * a[ik][j];
      }
    }
  }
  
  delete [] weight;
}	

void LU::solve()
{
  int i, j, ii;
  long double t;

  decomposition();
  
  for(i = 0; i < n; i++){
    ii = ip[i];
    t = b[ii];
    for(j = 0; j < i; j++){
      t -= a[ii][j] * x[j];
    }
    x[i] = t;
  }
  for(i = n - 1; i >= 0; i--){
    t = x[i];
    ii = ip[i];
    for(j = i + 1; j < n; j++){
      t -= a[ii][j] * x[j];
    }
    x[i] = t / a[ii][i];
  }
}

