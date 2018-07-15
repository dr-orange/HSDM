/**
 * �ӥå���Υե饰
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _BITSET_H_
#define _BITSET_H_

class BitSet {

  /**
   * �ӥå������¸���������ѿ�
   */
  int flags;

public:

  BitSet();
 ~BitSet();

 /**
  * ���ꤵ�줿�ӥå����ɽ�����ե饰��Ω�äƤ��뤫���֤�
  * @param flag �ӥå���
  * @return true or false
  */
 bool check(int flag);

 /**
  * ���ꤵ�줿�ӥåȤΥե饰��Ω�äƤ��뤫���֤�
  * @param bit �ӥåȤΥ���ǥå���
  * @return true or false
  */
 bool checkBit(int bit);

 /**
  * ���ꤵ�줿�ӥå����ɽ�����ե饰�����ꤹ��
  * @param flag �ӥå���
  */
 void set(int flag);

 /**
  * ���ꤵ�줿�ӥåȤΥե饰��Ω�Ƥ�
  * @param bit �ӥåȤΥ���ǥå���
  */
 void setBit(int bit);

 /**
  * ���ꤵ�줿�ӥåȤΥե饰��ߤ�(?)
  * @param bit �ӥåȤΥ���ǥå���
  */
 void unset(int bit);

};

#endif //#ifndef _BITSET_
