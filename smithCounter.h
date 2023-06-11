//Defining header file for smith counter
#ifndef SMITHCOUNTER_H
#define SMITHCOUNTER_H
#include<vector>
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
using namespace std;
//Class for smithcounter

class smithCounter{
  private: int counterValue[128];
  public: smithCounter(){
     for(int i=0;i<128;i++) counterValue[i]=0;
  }
  //This function are used to update the counter value
  public: void updateCounter(int index,int value);
  //This function is used to get the array of counter values
  public: int* getCounterValue();
  //Declaration of the function readData which helps to read data from the trace file
  public: void readData(vector<string>&,vector<string>&,char*);
};

//Function defination of updateCounter
void smithCounter:: updateCounter(int index,int value){
  if(counterValue[index]<3 && counterValue[index]>-1 && value==1)
    counterValue[index] +=value;
  if(counterValue[index]<=3 && counterValue[index]>0 && value==-1)
    counterValue[index] +=value;
}
//Function defination of getCounterValue
int * smithCounter:: getCounterValue(){
  return counterValue;
}
//Defination of the function readData
void smithCounter:: readData(vector<string>&branchAddress,vector<string>&actualPrediction,char*fileName){
  string line;
  string temp1 , temp2;
  //variables declrations
  fstream fout;
  //It will ask for the argument during the execution argument= location of file
  fout.open(fileName);
  //Reading the data from the data file
  while(fout){
    getline(fout,line);
    if(line!=""){
      std::stringstream ss(line);
      ss>>temp1;
      ss>>temp2;
      branchAddress.push_back(temp1);
      actualPrediction.push_back(temp2);
    }
  }
}
#endif  //End of smithCounter
