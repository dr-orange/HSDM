/*
  $Id: Wolfe.cc,v 1.1 2000/08/10 23:42:33 warhol Exp warhol $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <LU.h>
#include <FindingTheNearestPoint.h>
#include <Wolfe.h>

Wolfe::Wolfe() {
  m = 0;
  J = 0;
  nowStep = 0;
  isUpSilentFlag  = false;
  isStop          = false;
  isUpShowFlag    = false;
  isUpVerboseFlag = false;
  isUpStepFlag    = false;
  v = new Vector(1);
}

Wolfe::~Wolfe() {
  delete v;
}

void Wolfe::setStatus(int flags) {
  f.set(flags);

  if(f.check(FLAG_SHOW)){
    isUpShowFlag = true;
  }
  if(f.check(FLAG_VERBOSE)){
    isUpShowFlag = true;
    isUpVerboseFlag = true;
  }
  if(f.check(FLAG_ONLYSTEP)){
    isUpShowFlag = true;
    isUpStepFlag = true;
  }
  if(f.check(FLAG_SILENT)){
    isUpSilentFlag  = true;
    isUpShowFlag    = false;
    isUpVerboseFlag = false;
    isUpStepFlag    = false;
  }
}

void Wolfe::setPoints(Matrix matrix) {
  if(m != 0) return;

  P = matrix;
  m = matrix.getWidth();
}

void Wolfe::start() {
  if(!isStop) step0();
  if(isStop && !isUpSilentFlag) cout <<  endl << "* Terminated by STOP." << endl << endl;
}

void Wolfe::showMatrix() {
  if(m == 0) return;

  for(int i = 0; i < m; i++)
    cout << "P" << i << " = " << P.getVectorAt(i) << endl;

  cout << "P = [";
  for(int i = 0; i < m; i++)
    cout << " P" << i;
  cout << " ]" << endl;
}

void Wolfe::showNorm() {
  if(m == 0) return;

  for(int i = 0; i < m; i++)
    cout << "|P" << i << "| = " <<  _F(P.getVectorAt(i).getNorm()) << endl;
}

void Wolfe::showStatus() {
  if(!isUpSilentFlag) {
    if(!isUpStepFlag) cout << endl;

    cout << "* step " << nowStep << endl;

    if(!isUpStepFlag){
      cout << " X = " << getSubMatrix() * w << endl;
      if(isUpVerboseFlag){
	if(nowStep > 2) cout << " v = " << *v << endl;

	cout << " S = { " << (int)S.getElementAt(0);
	for(int i = 1; i < S.getLength(); i++)
	  cout << ", " << (int)S.getElementAt(i);
	cout << " }" << endl;

	cout << " w = " << w << endl;
      }
    }
  }
}

Matrix Wolfe::getSubMatrix(){
  Matrix c = Matrix(P.getHeight(), S.getLength());
  for(int i = 0; i < S.getLength(); i++)
    c.setVectorAt(P.getVectorAt(S.getElementAt(i)), i);

  return c;
}

void Wolfe::step0() {
  if(m == 0) return;

  nowStep = 0;

  long double min = pow(P.getVectorAt(0).getNorm(), 2), norm;
  int j = 0;

  for(int i = 1; i < m; i++){
    norm = pow(P.getVectorAt(i).getNorm(), 2);
    if(norm < min){
      min = norm;
      j = i;
    }
  }
  J = j;

  S.addElement(J);
  w.addElement(1);

  if(isUpShowFlag)showStatus();
  if(!isStop)step1();
}

void Wolfe::step1() {
  if(m == 0) return;

  nowStep = 1;

  /* (a) */
  X = getSubMatrix() * w;

  /* (b) */
  long double min = X * (P.getVectorAt(0)), norm;
  int j = 0;
  for(int i = 1; i < m; i++){
    norm = X * (P.getVectorAt(i));
    if(norm < min){
      min = norm;
      j = i;
    }
  }
  J = j;

  /* (c) */
  long double max = pow(P.getVectorAt(J).getNorm(), 2);
  for(int i = 0; i < S.getLength(); i++)
    if(max < pow(P.getVectorAt(S.getElementAt(i)).getNorm(), 2))
      max = pow(P.getVectorAt(S.getElementAt(i)).getNorm(), 2);
  if( X * P.getVectorAt(J) > X * X - Z1 * max )
    isStop = true;

  /* (d) */
  if(!isStop)
    for(int i = 0; i < S.getLength(); i++)
      if(J == S.getElementAt(i))
	isStop = true;

  /* (e) */
  if(!isStop){
    S.addElement(J);
    w.addElement(0);
  }

  if(isUpShowFlag)showStatus();
  if(!isStop)step2();
}

void Wolfe::step2() {
  if(m == 0) return;

  nowStep = 2;

  /* (a) */
  int s = getSubMatrix().getWidth();
  Vector u = Vector(s);
  delete v;
  v = new Vector(s);
  LU lu(Matrix::E(s) + trans(getSubMatrix()) * getSubMatrix(), Vector::e(s));
  lu.solve();

  u = lu.getResult();
//  u = inverse(Matrix::E(s) + trans(getSubMatrix()) * getSubMatrix()) * Vector::e(s);
  *v = u / (Vector::e(s) * u);

  if(isUpShowFlag)showStatus();

  /* (b) */
  if(*v > (Z2 * Vector::e(s))){
    for(int i = 0; i < w.getLength(); i++)
      w.setElementAt(v->getElementAt(i), i);
    step1();
    return;
  }

  if(!isStop)step3();
}

void Wolfe::step3() {
  if(m == 0) return;

  nowStep = 3;

  /* (a) */
  Vector POS;
  for(int i = 0; i < S.getLength(); i++)
    if(w.getElementAt(i) - v->getElementAt(i) > Z3)
      POS.addElement(i);

  /* (b) */
  long double theta;
  /* modified by ISAO. */ /*
  if(POS.getLength() > 0){
    long double temp, max = -v->getElementAt(POS.getElement(0)) / (w.getElementAt(POS.getElement(0))
                                             - v->getElementAt(POS.getElement(0)));
    for(int i = 1; i < POS.getLength(); i++){
      temp = -v->getElementAt(POS.getElement(i)) / (w.getElementAt(POS.getElement(i))
                              - v->getElementAt(POS.getElement(i)));
      if(temp > max) max = temp;
    }
    theta = (max < 1)?max:1;
  }
  */
  // original
  if(POS.getLength() > 0){
    long double temp, min = 1;
    for(int i = 0; i < POS.getLength(); i++){
      temp = w.getElementAt(POS.getElementAt(i)) / (w.getElementAt(POS.getElementAt(i))
                            - v->getElementAt(POS.getElementAt(i)));
      if(temp < min) min = temp;
    }
    theta = min;
  }

  /* (c) */
  if(POS.getLength() > 0)
    for(int i = 0; i < w.getLength(); i++)
      w.setElementAt(theta * w.getElementAt(i) + (1 - theta) * v->getElementAt(i), i);

  /* (d) */
  for(int i = 0; i < w.getLength(); i++)
    if(w.getElementAt(i) <= Z2) w.setElementAt(0, i);

  /* (e) */
  for(int i = 0; i < w.getLength(); i++)
    if(w.getElementAt(i) == 0){
      w.removeElement(i);
      S.removeElement(i);
    }

  if(isUpShowFlag)showStatus();
  if(isUpVerboseFlag){
    cout << " POS = { " << (int)POS.getElementAt(0);
    for(int i = 1; i < POS.getLength(); i++)
      cout << ", " << (int)POS.getElementAt(i);
    cout << " }" << endl;
  }

  step2();
}

Vector Wolfe::getResult() {
  if(!isStop){
    cerr << "* error in Wolfe::getResult()." << endl
         << "  call start() before getResult()." << endl;
    exit(0);
  }
  return getSubMatrix() * w;
}
