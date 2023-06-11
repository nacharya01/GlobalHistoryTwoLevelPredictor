//Name: Nirajan Acharya
// YID= Y00807637
//Course= Computer Architecture
//Project= Global history two-level predictor
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include"GlobalHistory.h"
using namespace std;

//main function for simulating global history branch predictor
int main(int argc,char ** argv){
  GlobalHistory globalHistory;
  vector<string> branchAddress;
  vector<string> actualPrediction;

  //This line read branch address and actual prediction from branch_trace.dat file
  globalHistory.readData(branchAddress,actualPrediction,argv[1]);
  //This simulates global history branch predictor
  globalHistory.globalSimulation(branchAddress,actualPrediction);
  return 0;
}
