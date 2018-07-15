/*
  $Id: RTLSExample.cc,v 1.1 2000/08/10 23:48:59 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <SVD.h>
#include <AWGN.h>
#include <RestrictedTotalLeastSquares.h>
#include "RTLSExample.h"

main (int argc,
      char *argv[]) {
  RTLSExample sim;

  sim.doSimulation();
}

RTLSExample::RTLSExample() {
}

RTLSExample::~RTLSExample() {
}

void RTLSExample::doSimulation() {
  FILE *fp1, *fp2;
  char line[1000];
  char *filename1, *filename2;
  filename1 = "ExampleData_A.txt";
  filename2 = "ExampleData_b.txt";
  bool isFileExist = true;

  // プログラムで直接データを指定するときの例
  if((fp1 = fopen(filename1,"r")) == NULL ||
     (fp2 = fopen(filename2,"r")) == NULL) {
  }
  // ファイルからデータを読み込むときの例
  else {
    Matrix A;

    bool isFirst = true;
    bool isNonScalar = false;
    int count = 1;
    while(fgets(line, 1000, fp1) != NULL){
      Vector a(1);
      long double value;
      char* temp = strtok(line, ",");
      if(sscanf(temp, "%Lf", &value) > 0){
	a.setElementAt(value, 0);
	while((temp = strtok(NULL, ",")) != NULL){
	  if(sscanf(temp, "%Lf", &value) > 0){
	    a.addElement(value);
	  } else {
	    isNonScalar = true;
	    a.addElement(0);
	  }
	  count++;
	}
	if(isFirst){
	  isFirst = false;
	  A = Matrix(count, 1);
	  A.setVectorAt(a, 0);
	} else {
	  A.addColVector(a);
	}
      }
    }
    fclose(fp1);

    Vector b(A.getHeight());

    isNonScalar = false;
    count = 1;
    while(fgets(line, 1000, fp2) != NULL){
      Vector a(1);
      long double value;
      char* temp = strtok(line, ",");
      if(sscanf(temp, "%Lf", &value) > 0){
	a.setElementAt(value, 0);
	while((temp = strtok(NULL, ",")) != NULL){
	  if(sscanf(temp, "%Lf", &value) > 0){
	    a.addElement(value);
	  } else {
	    isNonScalar = true;
	    a.addElement(0);
	  }
	  count++;
	}
	if(A.getHeight() == count){
	  b = a;
	}
	else {
	  cerr << filename1 << " and " << filename2
	       << " ... wrong size." << endl;
	  exit(0);
	}
      }
    }
    fclose(fp2);

    cout << "* read from " << filename1 << "..." << endl;
    cout << "* read from " << filename2 << "..." << endl;
    if(isNonScalar) cout << "* data contains non-scalar value.  set 0." << endl;

    RestrictedTotalLeastSquares sim(A, b);
    sim.start();

    /*
    SVD svd(A);
    svd.solve();

    cout << svd.getLeftUnitaryMatrix() << "---" << endl;
    cout << svd.getDiagonalMatrix() << "---" << endl;
    cout << svd.getRightUnitaryMatrix() << "---" << endl;
    */

    cout << "  A = " << endl << A
	 << "  b = " << b << endl;
  }
}
