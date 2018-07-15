/*
 * Finding The Nearest Point in Polytope.
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _FINDINGTHENEARESTPOINT_H_
#define _FINDINGTHENEARESTPOINT_H_

class FindingTheNearestPoint {

public:

  FindingTheNearestPoint() {};
  ~FindingTheNearestPoint() {};

  /**
   * 点の集合を行列で指定
   *
   * @param matirx 行列
   */
  virtual void setPoints(Matrix) {};
  /** 計算をはじめる */
  virtual void start() {};
  /** 
   * 結果を返す
   *
   * @return The Nearest Point
   */
  virtual Vector getResult() {};

};

#endif //#ifndef _FINDINGTHENEARESTPOINT_H_
