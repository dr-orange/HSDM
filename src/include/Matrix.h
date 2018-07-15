/**
 * 行列を扱うクラス
 *
 * $Id: Matrix.cc,v 1.2 2000/08/10 23:39:41 warhol Exp $
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix {

  /** 行数 */
  int m;
  /** 列数 */
  int n;
  /** 列ベクトルの配列 */
  Vector* colVector;

public:

  /** 要素が全て 1 の正方マトリクス */
  static Matrix E(int);
  /** 単位行列 */
  static Matrix I(int);

  /** */
  Matrix() { n = m = 0; colVector = new Vector[1]; }
  /** コンストラクタ */
  Matrix(int, int);
  /** デストラクタ */
  ~Matrix(){ delete [] colVector; }
  /** コピーコンストラクタ */
  Matrix(const Matrix&);

  /** 行数を返す */
  int getHeight(){ return m; }
  /** 列数を返す */
  int getWidth(){ return n; }
  /** 行列の成分を指定 */
  void setElementAt(long double, int, int);
  /** 行列の列ベクトルを指定 */
  void setVectorAt(Vector, int);
  /** 行ベクトルを追加 */
  void addRowVector(Vector);
  /** 列ベクトルを追加 */
  void addColVector(Vector);
  /** 行列の成分を取得 */
  long double getElementAt(int, int);
  /** 行列の列ベクトルを取得 */
  Vector getVectorAt(int);
  /** 行列の行ベクトルを取得 */
  Vector getRowVectorAt(int);
  /** 行列のノルムを取得 */
  long double getNorm();
  /** row行col列を取り除いた行列 */
  Matrix getReducedMatrix(int, int);
  /** = (代入演算子)の定義 */
  Matrix& operator=(Matrix);
  /** 行列式 */
  friend long double det(Matrix);
  /** 転置行列 */
  friend Matrix trans(Matrix);
  /** 逆行列 (計算量が超多い) */
  friend Matrix inverse(Matrix);
  /** 余因子マトリクス */
  friend Matrix adj(Matrix);

  /** 行列 + 行列 */
  friend Matrix operator +(Matrix, Matrix);
  /** 行列 - 行列 */
  friend Matrix operator -(Matrix, Matrix);
  /** 行列 * 行列 */
  friend Matrix operator *(Matrix, Matrix);
  /** スカラ * 行列 */
  friend Matrix operator *(long double, Matrix);
  /** 行列 * ベクトル */
  friend Vector operator *(Matrix, Vector);
  /** ベクトル * 行列 */
  friend Vector operator *(Vector, Matrix);

  /** 出力 */
  friend ostream& operator <<(ostream&, Matrix);

};

#endif //#ifndef _MATRIX_H_
