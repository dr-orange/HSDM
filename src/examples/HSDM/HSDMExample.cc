/*
  $Id: HSDMExample.cc,v 1.3 2000/08/10 23:47:28 warhol Exp warhol $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <Wolfe.h>
#include <HybridSteepestDescentMethod.h>
#include <AWGN.h>
#include <LU.h>
#include <SVD.h>
#include "HSDMExample.h"
#include <fstream.h>

main (int argc,
      char *argv[]) {
  HSDMExample sim;

  srand(time(NULL));
  cout << "$Id: HSDMExample.cc,v 1.3 2000/08/10 23:47:28 warhol Exp warhol $" << endl;
  sim.doSimulation();
}

HSDMExample::HSDMExample() {
}

HSDMExample::~HSDMExample() {
}

void HSDMExample::doSimulation(){
  FILE *fp1, *fp2;
  char line[1000];
  char *filename1, *filename2;
  filename1 = "data/ExampleData_A.dat";
  filename2 = "data/ExampleData_b.dat";
  bool isFileExist = true;
  int snrOfA = AWGN::NOISELESS;
  int snrOfB = 40;

  // プログラムで直接データを指定するときの例
  if((fp1 = fopen(filename1,"r")) == NULL ||
     (fp2 = fopen(filename2,"r")) == NULL) {
    cerr << "* Error: "
	 << filename1
	 << " or "
	 << filename2
	 << "is/are not found."
	 << endl;
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
    Matrix Adash(A.getHeight(), A.getWidth());
    Matrix K(A.getWidth(), A.getWidth());
    Vector p0(A.getWidth());
    Vector noise(A.getWidth());
    AWGN awgn;

    cout << "* read from " << filename1 << "..." << endl;
    cout << "* read from " << filename2 << "..." << endl;
    if(isNonScalar) cout << "* data contains non-scalar value.  set 0." << endl;

    Vector noiseless(A.getWidth());
    noiseless.setElementAt(0.8, 0);
    noiseless.setElementAt(0.2, 1);
    noiseless.setElementAt(0, 2);

    for(int i = 0; i < A.getWidth(); i++)
      K.setElementAt(1, i, i);

    awgn.setSNR(snrOfA);
    //awgn.setVariance(10000);

    for(int j = 0; j < A.getHeight(); j++)
      for(int i = 0; i < A.getWidth(); i++)
	Adash.setElementAt(awgn.addNoise(A.getElementAt(j, i)), j, i);
    
    awgn.setSNR(snrOfB);
    //awgn.setVariance(10000);
    
    ofstream AaFile("result/material_a.dat", ios::out);
    ofstream AbFile("result/material_b.dat", ios::out);
    ofstream AcFile("result/material_c.dat", ios::out);
    ofstream bNFile("result/noised_b.dat", ios::out);
    ofstream bOFile("result/original_b.dat", ios::out);
    AaFile << "#Material A: " << endl;
    AbFile << "#Material B: " << endl;
    AcFile << "#Material C: " << endl;
    for(int i = 0; i < b.getLength(); i++){
      AaFile << 0.375+0.0625*i << " " << A.getElementAt(i, 0) << endl;
      AbFile << 0.375+0.0625*i << " " << A.getElementAt(i, 1) << endl;
      AcFile << 0.375+0.0625*i << " " << A.getElementAt(i, 2) << endl;
    }
    bOFile << "#Original: " << endl;
    for(int i = 0; i < b.getLength(); i++)
      bOFile << 0.375+0.0625*i << " " << b.getElementAt(i) << endl;
    for(int i = 0; i < b.getLength(); i++)
      b.setElementAt(awgn.addNoise(b.getElementAt(i)), i);
    bNFile << "#S/N " << snrOfB << ": " << endl;
    for(int i = 0; i < b.getLength(); i++)
      bNFile << 0.375+0.0625*i << " " << b.getElementAt(i) << endl;
    
    HybridSteepestDescentMethod sim(K, Adash, b);

    LU lu(trans(Adash) * Adash, trans(A) * b);
    lu.solve();

    p0 = lu.getResult();

    sim.setPoint(p0);
    sim.start();

    long double vlu, vhsdm, vludash;

    vlu = (noiseless - lu.getResult()).getNorm();
    vhsdm = (noiseless - sim.getResult()).getNorm();
    vludash = (noiseless - sim.projectionOntoK(lu.getResult())).getNorm();

    cout << "---" << endl;
    cout << "old method: " << _F(vlu) << lu.getResult() << endl;
    cout << "old method onto K: " << _F(vludash) << sim.projectionOntoK(lu.getResult()) << endl;
    cout << "new method: " << _F(vhsdm) << sim.getResult() << endl;
  }
}
