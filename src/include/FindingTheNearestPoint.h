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
   * �_�̏W�����s��Ŏw��
   *
   * @param matirx �s��
   */
  virtual void setPoints(Matrix) {};
  /** �v�Z���͂��߂� */
  virtual void start() {};
  /** 
   * ���ʂ�Ԃ�
   *
   * @return The Nearest Point
   */
  virtual Vector getResult() {};

};

#endif //#ifndef _FINDINGTHENEARESTPOINT_H_
