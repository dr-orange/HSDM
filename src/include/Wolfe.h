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
   * ���l�덷���l�����邽�߂̒萔
   */
  static const long double Z1 = 1e-12;
  static const long double Z2 = 1e-10;
  static const long double Z3 = 1e-10;

  int J;
  int m;
  /** ���s����Ă���X�e�b�v */
  int nowStep;
  Vector S;
  Vector w;
  Vector* v;
  Vector X;
  Matrix P;
  /** STOP ���ꂽ���ǂ��� */
  bool isStop;
  /** �r���o�߂�\�����邩 */
  bool isUpShowFlag;
  /** �ڍׂɕ\�����邩 */
  bool isUpVerboseFlag;
  /** ���s���̃X�e�b�v����\�����邩 */
  bool isUpStepFlag;
  /** �\�����Ȃ��� */
  bool isUpSilentFlag;
  /** �\���Ɋւ���t���O */
  BitSet f;

  /** STEP 0 */
  void step0();
  /** STEP 1 */
  void step1();
  /** STEP 2 */
  void step2();
  /** STEP 3 */
  void step3();
  /** ���ꂼ��̒l��\�� */
  void showStatus();

public:

  const static int FLAG_SHOW     = 1;
  const static int FLAG_VERBOSE  = 2;
  const static int FLAG_ONLYSTEP = 4;
  const static int FLAG_SILENT   = 8;

  Wolfe();
  ~Wolfe();

  /**
   * �_�̏W�����s��Ŏw��
   *
   * @param matirx �s��
   */
  void setPoints(Matrix matrix);
  /**
   * �r���o�߂Ȃǂ̕\���̎w��
   * FLAG_SHOW, FLAG_VERBOSE, FLAG_ONLYSTEP �̘_���a
   *              
   * @param flags �t���O
   */
  void setStatus(int flags);
  /** �v�Z���͂��߂� */
  void start();
  /** �ݒ肳��Ă���s���\�� */
  void showMatrix();
  /** ���ꂼ��̓_�̃m������\�� */
  void showNorm();
  /** 
   * ���ʂ�Ԃ�
   *
   * @return The Nearest Point
   */
  Vector getResult();
  /**
   * S �̎��C���f�b�N�X�ŕ\����� P �̕����s�� P[S]
   */
  Matrix getSubMatrix();

};

#endif //#ifndef _WOLFE_H_

