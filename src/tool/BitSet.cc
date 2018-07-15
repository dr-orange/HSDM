/*
  $Id: BitSet.cc,v 1.1 2000/08/10 23:41:08 warhol Exp $
 */

#include <header.h>
#include <BitSet.h>

BitSet::BitSet() {
  flags = 0;
}

BitSet::~BitSet() {
}

bool BitSet::check(int flag){
  if((flags & flag) == flag){
    return true;
  } else {
    return false;
  }
}

bool BitSet::checkBit(int bit){
  int flag = (int)pow(2, bit);
  if((flags & flag) == flag){
    return true;
  } else {
    return false;
  }
}

void BitSet::set(int flag){
  flags = (flags | flag);
}

void BitSet::setBit(int bit){
  int flag = (int)pow(2, bit);
  flags = (flags | flag);
}

void BitSet::unset(int bit){
  int flag = (int)pow(2, bit);
  flags = (flags & !flag);
}
