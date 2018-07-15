/*
 * Hybrid Steepest Descent Method
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _HYBRIDSTEEPESTDESCENTMETHOD_H_
#define _HYBRIDSTEEPESTDESCENTMETHOD_H_

class HybridSteepestDescentMethod {

  int dimension;
  Matrix A;
  Matrix K;
  Vector b;
  Vector u;
  /** ɽ���˴ؤ���ե饰 */
  BitSet f;
  bool isUpSilentFlag;

public:

  const static int FLAG_SILENT = 1;

  HybridSteepestDescentMethod() {};
  HybridSteepestDescentMethod(Matrix, Matrix, Vector);
  ~HybridSteepestDescentMethod();

  void setPoint(Vector);
  void start();
  Vector projectionOntoPi(Vector, int);
  Vector projectionOntoK(Vector);
  Vector getResult();
  /**
   * ����в�ʤɤ�ɽ���λ���
   * FLAG_SILENT ����������
   *              
   * @param flags �ե饰
   */
  void setStatus(int flags);
};

#endif //#ifndef _HYBRIDSTEEPESTDESCENTMETHOD_H_
