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
  /** 表示に関するフラグ */
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
   * 途中経過などの表示の指定
   * FLAG_SILENT 等の論理和
   *              
   * @param flags フラグ
   */
  void setStatus(int flags);
};

#endif //#ifndef _HYBRIDSTEEPESTDESCENTMETHOD_H_
