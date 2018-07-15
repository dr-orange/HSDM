/**
 * ビット列のフラグ
 *
 * @author ko-ji@mars.dti.ne.jp
 */

#ifndef _BITSET_H_
#define _BITSET_H_

class BitSet {

  /**
   * ビット列を保存する内部変数
   */
  int flags;

public:

  BitSet();
 ~BitSet();

 /**
  * 指定されたビット列で表されるフラグが立っているかを返す
  * @param flag ビット列
  * @return true or false
  */
 bool check(int flag);

 /**
  * 指定されたビットのフラグが立っているかを返す
  * @param bit ビットのインデックス
  * @return true or false
  */
 bool checkBit(int bit);

 /**
  * 指定されたビット列で表されるフラグを設定する
  * @param flag ビット列
  */
 void set(int flag);

 /**
  * 指定されたビットのフラグを立てる
  * @param bit ビットのインデックス
  */
 void setBit(int bit);

 /**
  * 指定されたビットのフラグを降ろす(?)
  * @param bit ビットのインデックス
  */
 void unset(int bit);

};

#endif //#ifndef _BITSET_
