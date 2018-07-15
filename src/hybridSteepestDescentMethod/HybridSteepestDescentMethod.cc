/**
 * �ϥ��֥�åɺǵ޹߲�ˡ
 *
 * $Id: HybridSteepestDescentMethod.cc,v 1.1 2000/08/10 23:42:16 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <Wolfe.h>
#include <HybridSteepestDescentMethod.h>

// ��«���: ||x_{n - 1} - x_n|| < CONVERGED
#define CONVERGED 1e-10

/**
 * ���󥹥ȥ饯��
 *
 * @param K ���̽��� K
 * @param A endmenber A
 * @param b observation b
 */
HybridSteepestDescentMethod::HybridSteepestDescentMethod(Matrix K,
							 Matrix A,
							 Vector b) {
  this->K = K;
  this->A = A;
  this->b = b;
  u = Vector(K.getHeight());

  isUpSilentFlag  = false;
}

HybridSteepestDescentMethod::~HybridSteepestDescentMethod() {
}

/**
 * ����ͤ�����
 *
 * @param v �����
 */
void HybridSteepestDescentMethod::setPoint(Vector v) {
  u = v;
}

/**
 * �׻�����
 */
void HybridSteepestDescentMethod::start() {
  Vector udash = u;
  long double sumnorm = 0;
  long double lambda;
  int n = 0;
  long double w[b.getLength()];
  Vector sumOfProjectionOntoPi(u.getLength());

  for(int i = 0; i < b.getLength(); i++)
    sumnorm += pow(A.getRowVectorAt(i).getNorm(), 2);

  for(int i = 0; i < b.getLength(); i++)
    w[i] = pow(A.getRowVectorAt(i).getNorm(), 2) / sumnorm;

  
  do {
    sumOfProjectionOntoPi.setAllZero();

    u = udash;
    for(int i = 0; i < b.getLength(); i++)
      sumOfProjectionOntoPi += w[i] * projectionOntoPi(u, i);

    lambda = (long double)n / (n + 1);
    udash = lambda * projectionOntoK(sumOfProjectionOntoPi);
    n++;

    if(!isUpSilentFlag)cout << n << ":" << u << endl;
  } while((u - udash).getNorm() > CONVERGED ||
	  n <= 1);
}

/**
 * ���̽��� Pi_i �ؤ��̼ͱ� P_{Pi_i}
 *
 * @param v �ͱƸ�
 * @param index i
 * @return P_{Pi_i}(v)
 */
Vector HybridSteepestDescentMethod::projectionOntoPi(Vector v,
						     int index) {
  Vector rowVector = A.getRowVectorAt(index);

  return - (rowVector * v - b.getElementAt(index)) * rowVector / pow(rowVector.getNorm(), 2) + v;
}

/**
 * ���̽��� K �ؤ��̼ͱ� P_K
 *
 * @param v
 * @return P_K(v)
 */
Vector HybridSteepestDescentMethod::projectionOntoK(Vector v) {
  Wolfe wolfe;
  Matrix Kdash = K;

  for(int i = 0; i < K.getWidth(); i++)
    Kdash.setVectorAt(K.getVectorAt(i) - v, i);

  wolfe.setPoints(Kdash);
  wolfe.setStatus(Wolfe::FLAG_SILENT);
  wolfe.start();

  return wolfe.getResult() + v;
}

/**
 * ��̤��֤�.
 *
 * @return ��«��
 */
Vector HybridSteepestDescentMethod::getResult() {
  return u;
}

void HybridSteepestDescentMethod::setStatus(int flags) {
  f.set(flags);

  if(f.check(FLAG_SILENT))
    isUpSilentFlag  = true;
}
