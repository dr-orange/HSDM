/*
  $Id: SolutionOfTheExample.cc,v 1.1 2000/08/10 23:44:16 warhol Exp $
 */

#include <header.h>
#include <Vector.h>
#include <Matrix.h>
#include <Wolfe.h>
#include "SolutionOfTheExample.h"

main (int argc,
      char *argv[])
{
    /* Solution of the example */
    SolutionOfTheExample sim;

    sim.doSimulation();
}

SolutionOfTheExample::SolutionOfTheExample() {
}

SolutionOfTheExample::~SolutionOfTheExample() {
}

void SolutionOfTheExample::doSimulation(){
  FILE *fp;
  char line[1000];
  char* filename;
  filename = "ExampleData.txt";
  bool isFileExist = true;

  Matrix g;

  // プログラムで直接データを指定するときの例
  if((fp = fopen(filename,"r")) == NULL) {
    isFileExist = false;
    cerr << "\"" << filename << "\" not found. " << endl;

    Vector* v = new Vector[3];
    for(int i = 0; i < 3; i++)
      v[i] = Vector(2);

    v[0].setElementAt(0, 0);
    v[0].setElementAt(2, 1);
    v[1].setElementAt(3, 0);
    v[1].setElementAt(0, 1);
    v[2].setElementAt(-2, 0);
    v[2].setElementAt(1, 1);

    g = Matrix(2, 3);
    for(int i = 0; i < 3; i++)
      g.setVectorAt(v[i], i);

    delete [] v;
  }
  // ファイルからデータを読み込むときの例
  else {
    bool isFirst = true;
    bool isNonScalar = false;
    int count = 1;
    while(fgets(line, 1000, fp) != NULL){
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
	  g = Matrix(count, 1);
	  g.setVectorAt(a, 0);
	} else {
	  g.addColVector(a);
	}
      }
    }
    cout << "* read from " << filename << "..." << endl;
    if(isNonScalar) cout << "* data contains non-scalar value.  set 0." << endl;
    cout << g << endl;

    fclose(fp);
  }
  Wolfe f;
  f.setStatus(Wolfe::FLAG_VERBOSE);
  f.setPoints(g);
  f.showMatrix();
  f.showNorm();
  f.start();
  cout << "result : " << f.getResult() << endl;
}
