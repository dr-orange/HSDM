/*
 * Finding The Nearest Point in Polytope.
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _WOLFE_H_
#define _WOLFE_H_

#include <FindingTheNearestPoint.h>
#include <BitSet.h>

class Wolfe : public FindingTheNearestPoint {

  /**
   * 数値誤差を考慮するための定数
   */
  static const long double Z1 = 1e-12;
  static const long double Z2 = 1e-10;
  static const long double Z3 = 1e-10;

  int J;
  int m;
  /** 実行されているステップ */
  int nowStep;
  Vector S;
  Vector w;
  Vector* v;
  Vector X;
  Matrix P;
  /** STOP されたかどうか */
  bool isStop;
  /** 途中経過を表示するか */
  bool isUpShowFlag;
  /** 詳細に表示するか */
  bool isUpVerboseFlag;
  /** 実行中のステップ数を表示するか */
  bool isUpStepFlag;
  /** 表示しないか */
  bool isUpSilentFlag;
  /** 表示に関するフラグ */
  BitSet f;

  /** STEP 0 */
  void step0();
  /** STEP 1 */
  void step1();
  /** STEP 2 */
  void step2();
  /** STEP 3 */
  void step3();
  /** それぞれの値を表示 */
  void showStatus();

public:

  const static int FLAG_SHOW     = 1;
  const static int FLAG_VERBOSE  = 2;
  const static int FLAG_ONLYSTEP = 4;
  const static int FLAG_SILENT   = 8;

  Wolfe();
  ~Wolfe();

  /**
   * 点の集合を行列で指定
   *
   * @param matirx 行列
   */
  void setPoints(Matrix matrix);
  /**
   * 途中経過などの表示の指定
   * FLAG_SHOW, FLAG_VERBOSE, FLAG_ONLYSTEP の論理和
   *              
   * @param flags フラグ
   */
  void setStatus(int flags);
  /** 計算をはじめる */
  void start();
  /** 設定されている行列を表示 */
  void showMatrix();
  /** それぞれの点のノルムを表示 */
  void showNorm();
  /** 
   * 結果を返す
   *
   * @return The Nearest Point
   */
  Vector getResult();
  /**
   * S の持つインデックスで表される P の部分行列 P[S]
   */
  Matrix getSubMatrix();

};

#endif //#ifndef _WOLFE_H_

