/**
 * Singular Value Decomposion
 * 特異値分解
 *
 * NUMERICAL RECIPES in C [日本語版] からアルゴリズムを流用
 *
 * $Id: SVD.cc,v 1.2 2000/08/20 04:11:29 ko-ji Exp ko-ji $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <SVD.h>

#define abs(var) (var<0)?-var:var

static long double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

static long double maxarg1, maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ? (maxarg1) : (maxarg2))

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

static int iminarg1, iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ? (iminarg1) : (iminarg2))

SVD::SVD(Matrix a)
{
  u = a;
  m = a.getHeight();
  n = a.getWidth();
  w = Matrix(n, n);
  v = Matrix(n, n);
}

SVD::~SVD()
{
}

void SVD::solve()
{
  int flag, i, its, j, jj, k, l, nm;
  long double anorm, c, f, g, h, s, scale, x, y, z;
  Vector rv1(n);

  g = scale = anorm = 0.0;
  for(i = 0; i < n; i++){
    l = i + 1;
    rv1.setElementAt(scale * g, i);
    g = s = scale = 0.0;
    if(i < m){
      for(k = i; k < m; k++) scale += fabs(u.getElementAt(k, i));
      if(scale){
	for(k = i; k < m; k++){
	  u.setElementAt(u.getElementAt(k, i) / scale, k, i);
	  s += u.getElementAt(k, i) * u.getElementAt(k, i);
	}
	f = u.getElementAt(i, i);
	g = -SIGN(sqrt(s), f);
	h = f * g - s;
	u.setElementAt(f - g, i, i);
	for(j = l; j < n; j++){
	  for(s = 0.0, k = i; k < m; k++) s += u.getElementAt(k, i) * u.getElementAt(k, j);
	  f = s / h;
	  for(k = i; k < m; k++) u.setElementAt(u.getElementAt(k, j) + f * u.getElementAt(k, i), k, j);
	}
	for(k = i; k < m; k++) u.setElementAt(u.getElementAt(k, i) * scale, k, i);
      }
    }
    w.setElementAt(scale * g, i, i);
    g = s = scale = 0.0;
    if(i < m && i != n - 1){
      for(k = l; k < n; k++) scale += fabs(u.getElementAt(i, k));
      if(scale){
	for(k = l; k < n; k++){
	  u.setElementAt(u.getElementAt(i, k) / scale, i, k);
	  s += u.getElementAt(i, k) * u.getElementAt(i, k);
	}
	f = u.getElementAt(i, l);
	g = -SIGN(sqrt(s), f);
	h = f * g - s;
	u.setElementAt(f - g, i, l);
	for(k = l; k < n; k++) rv1.setElementAt(u.getElementAt(i, k) / h, k);
	for(j = l; j < m; j++){
	  for(s = 0.0, k = l; k < n; k++) s += u.getElementAt(j, k) * u.getElementAt(i, k);
	  for(k = l; k < n; k++) u.setElementAt(u.getElementAt(j, k) + s * rv1.getElementAt(k), j, k);
	}
	for(k = l; k < n; k++) u.setElementAt(u.getElementAt(i, k) * scale, i, k);
      }
    }
    anorm = FMAX(anorm, (fabs(w.getElementAt(i, i)) + fabs(rv1.getElementAt(i))));
  }
  for(i = n - 1; i >= 0; i--){
    if(i < n - 1){
      if(g){
	for(j = l; j < n; j++) v.setElementAt((u.getElementAt(i, j) / u.getElementAt(i, l)) / g, j, i);
	for(j = l; j < n; j++){
	  for(s = 0.0, k = l; k < n; k++) s += u.getElementAt(i, k) * v.getElementAt(k, j);
	  for(k = l; k < n; k++) v.setElementAt(v.getElementAt(k, j) + s * v.getElementAt(k, i), k, j);
	}
      }
      for(j = l; j < n; j++){
	v.setElementAt(0.0, i, j);
	v.setElementAt(0.0, j, i);
      }
    }
    v.setElementAt(1.0, i, i);
    g = rv1.getElementAt(i);
    l = i;
  }
  for(i = IMIN(m, n) - 1; i >= 0; i--){
    l = i + 1;
    g = w.getElementAt(i, i);
    for(j = l; j < n; j++) u.setElementAt(0.0, i, j);
    if(g){
      g = 1.0 / g;
      for(j = l; j < n; j++){
	for(s = 0.0, k = l; k < m; k++) s += u.getElementAt(k, i) * u.getElementAt(k, j);
	f = (s / u.getElementAt(i, i)) * g;
	for(k = i; k < m; k++) u.setElementAt(u.getElementAt(k, j) + f * u.getElementAt(k, i), k, j);
      }
      for(j = i; j < m; j++) u.setElementAt(u.getElementAt(j, i) * g, j, i);
    } else for(j = i; j < m; j++) u.setElementAt(0.0, j, i);
    u.setElementAt(u.getElementAt(i, i) + 1, i, i);
  }
  for(k = n - 1; k >= 0; k--){
    for(its = 1; its < 30; its++){
      flag = 1;
      for(l = k; l >= 0; l--){
	nm = l;
	if((long double)(fabs(rv1.getElementAt(l)) + anorm) == anorm){
	  flag = 0;
	  break;
	}
	if((long double)(fabs(w.getElementAt(nm, nm)) + anorm) == anorm) break;
      }
      if(flag){
	c = 0.0;
	s = 1.0;
	for(i = l; i < k; i++){
	  f = s * rv1.getElementAt(i);
	  rv1.setElementAt(c * rv1.getElementAt(i), i);
	  if((long double)(fabs(f) + anorm) == anorm) break;
	  g = w.getElementAt(i, i);
	  h = pythag(f, g);
	  w.setElementAt(h, i, i);
	  h = 1.0 / h;
	  c = g * h;
	  s = -f * h;
	  for(j = 0; j < m; j++){
	    y = u.getElementAt(j, nm);
	    z = u.getElementAt(j, i);
	    u.setElementAt(y * c + z * s, j, nm);
	    u.setElementAt(z * c - y * s, j, i);
	  }
	}
      }
      z = w.getElementAt(k, k);
      if(l == k){
	if(z < 0.0){
	  w.setElementAt(-z, k, k);
	  for(j = 0; j < n; j++) v.setElementAt(-v.getElementAt(j, k), j, k);
	}
	break;
      }
      if(its == 30){
	cerr << "* error in SVD::solve()." << endl;
	cerr << "  no convergence in 30 SVD iterations" << endl;
	exit(0);
      }
      x = w.getElementAt(l, l);
      nm = k;
      y = w.getElementAt(nm, nm);
      g = rv1.getElementAt(nm);
      h = rv1.getElementAt(k);
      f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
      g = pythag(f, 1.0);
      f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h)) / x;
      c = s = 1.0;
      for(j = l; j < nm; j++){
	i = j + 1;
	g = rv1.getElementAt(i);
	y = w.getElementAt(i, i);
	h = s * g;
	g = c * g;
	z = pythag(f, h);
	rv1.setElementAt(z, j);
	c = f / z;
	s = h / z;
	f = x * c + g * s;
	g = g * c - x * s;
	h = y * s;
	y *= c;
	for(jj = 0; jj < n; jj++){
	  x = v.getElementAt(jj, j);
	  z = v.getElementAt(jj, i);
	  v.setElementAt(x * c + z * s, jj, j);
	  v.setElementAt(z * c - x * s, jj, i);
	}
	z = pythag(f, h);
	w.setElementAt(z, j, j);
	if(z){
	  z = 1.0 / z;
	  c = f * z;
	  s = h * z;
	}
	f = c * g + s * y;
	x = c * y - s * g;
	for(jj = 0; jj < m; jj++){
	  y = u.getElementAt(jj, j);
	  z = u.getElementAt(jj, i);
	  u.setElementAt(y * c + z * s, jj, j);
	  u.setElementAt(z * c - y * s, jj, i);
	}
      }
      rv1.setElementAt(0.0, l);
      rv1.setElementAt(f, k);
      w.setElementAt(x, k, k);
    }
  }
}

long double SVD::pythag(long double a, long double b)
{
  long double absa, absb;
  absa = fabs(a);
  absb = fabs(b);
  if(absa > absb) return absa * sqrt(1.0 + SQR(absb / absa));
  else return (absb == 0.0 ? 0.0 : absb * sqrt(1.0 + SQR(absa / absb)));
}

Matrix SVD::getLeftUnitaryMatrix()
{
  return u;
}

Matrix SVD::getDiagonalMatrix()
{
  return w;
}

Matrix SVD::getRightUnitaryMatrix()
{
  return trans(v);
}
