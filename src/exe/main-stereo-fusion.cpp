#include <stdio.h>
#include <stdlib.h>

#include "HOCR.h"
#include "QPBO.h"
#include "Image.h"
#include <algorithm>
#include <sstream>
#include <iostream>


const int disp_mult = 4;
// Parameters
typedef int REAL;	// Type for the energy value
const REAL sigma = 1;	// Sigma of the noise added
const int dmax = 40;    // Max disparity
const int tresh = 50;   // Robust treshold for likelyhood
const int mult = 10;	// Multiplier for representing real values by integers
const int lambda = 1.7; // Smoothness / Prior weight

// direction vectors
const int v[3] = {-1, 0, 1};


template<typename T> T square(const T& t) {return t * t;}

double Reg2nd(unsigned int v[3]){
  double err =  abs((int)(v[0]) - (int)(2*v[1]) + (int)v[2]);
  if(err > tresh)return tresh;
  return err;
}



double unaryEnergy(int data1,int data2, int sigma){
  double err = square(data1 - data2) / (square(sigma) * 2);
  if(err > 100)return 100;
  return err;
}




template<typename F>
void addEnergy(F& f, const image& cur, const image& iml, const image& imr, const image& pro, int W, int H, int N, REAL mult, REAL sigma, REAL ld) {
  double e0,e1;
  for (int y = 1; y + 1 < H; y++){	// FoE prior
    for (int x = 1; x + 1 < W; x++){
      int idx = x + y*W;
      int ndsX[3];
      int ndsY[3];
      for (int j = 0; j < 3; j++){
	ndsX[j] = x + v[j] + y*W;
	ndsY[j] = x + (y+v[j])*W;
      }
      REAL EX[8];
      REAL EY[8];
	
      for (int i = 0; i < 8; i++){                      
	unsigned int hX[3],hY[3];
	int b = 4;
	for (int j = 0; j < 3; j++){
	  hX[j] = (i & b) ? pro.buf[ndsX[j]] : cur.buf[ndsX[j]];
	  hY[j] = (i & b) ? pro.buf[ndsY[j]] : cur.buf[ndsY[j]];
	  b >>= 1;
	}
	EX[i] = (REAL)(ld * Reg2nd(hX) * mult);
	EY[i] = (REAL)(ld * Reg2nd(hY) * mult);
      }
      f.AddHigherTerm(3, ndsX, EX);
      f.AddHigherTerm(3, ndsY, EY);


      int idxc = y*W + x-round(cur.buf[idx]/(double)disp_mult);
      int idxp = y*W + x-round(pro.buf[idx]/(double)disp_mult);
      e0 = e1 = 10000000;
      if(idxc >= 0) e0 = unaryEnergy(iml.buf[idx], imr.buf[idxc], sigma);
      if(idxp >= 0) e1 = unaryEnergy(iml.buf[idx], imr.buf[idxp], sigma);
      f.AddUnaryTerm(idx, (REAL)(e0 * mult), (REAL)(e1 * mult));
    }
  }
}

void buildQPBF1(QPBO<REAL>& qpbo, const image& cur, const image& iml, const image& imr, const image& pro, int W, int H, int N, REAL mult, REAL sigma,REAL ld){
  HOCR<REAL,4,QPBO<REAL> > hocr(qpbo);
  hocr.AddNode(N);
  addEnergy(hocr, cur, iml,imr, pro, W, H, N, mult, sigma,ld); // Prior
}


int main(int argc, char **argv){
  
  if(argc < 6){
    std::cout << "number of args  : " << argc -1 << " != 5 " << std::endl;
    std::cout << "usage : " << argv[0] << " image_left image_righ disp1 disp2 disp_result" << std::endl;
    return 1;
  }
  std::cout << " ----- /!\\ WARNING /!\\ -----" << std::endl;
  std::cout << "this is a toy example for testing, lot of things are not generic and should be changed (like the disparity quantification for the test)" << std::endl;
  std::cout << "Please be careful :)" << std::endl;
  
    
  int arg_acc=1 ;
  
  image disp,iml,imr,pro,cur;
  iml.readPGM(argv[arg_acc++]);
  imr.readPGM(argv[arg_acc++]);
  cur.readPGM(argv[arg_acc++]);
  pro.readPGM(argv[arg_acc++]);
  std::string output_name(argv[arg_acc++]);
  
  if (iml.empty() || imr.empty() || cur.empty() || pro.empty()) {
    printf("Error. Cannot load the image.\n");
    return 1;
  }


  
  int W = iml.W, H = iml.H, N = W * H;

  
  QPBO<REAL> qpbo(N * 10, N * 20);
  buildQPBF1(qpbo, cur, iml,imr, pro, W, H, N, mult, sigma,lambda); 
  qpbo.MergeParallelEdges();
  qpbo.Solve();
  qpbo.ComputeWeakPersistencies();

  
  int labeled = 0;
  for (int j = 0; j < N; j++) {
    int res = qpbo.GetLabel(j);
    if (res == 1){
      cur.buf[j] = pro.buf[j];
    }else if(res == 0){
    }
    if (res >= 0)
      labeled++;	  
  }
      

  cur.writePGM(output_name.c_str());
  printf("Fusion written to %s\n", output_name.c_str());
  return 0;
}

  

