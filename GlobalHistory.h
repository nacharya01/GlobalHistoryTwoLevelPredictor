#ifndef GLOBALHISTORY_H
#define GLOBALHISTORY_H
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include"smithCounter.h"
using namespace std;
//GlobalHistory class has extended smithCounter class so we can use some of its functions
class GlobalHistory: public smithCounter{
  //Declaration of class variables
  private: string bhr;
  private: int counterValue[128];
  //Declaration of class functions
  public: GlobalHistory(){
    bhr="000";
    for( int i=0;i<128;i++)counterValue[i]=0;
  };
  //Functions declrations
  public: void globalSimulation(vector<string>,vector<string>);
  public: string getBhr();
  public: void update(int index,int value);
};

//This function returns the value of Branch history register
string GlobalHistory:: getBhr(){
   return bhr;
}
//This function updates the counter value based on the prediction
void GlobalHistory:: update(int index,int value){
  if(counterValue[index]<3 && counterValue[index]>-1 && value==1)
    counterValue[index] +=value;
  if(counterValue[index]<=3 && counterValue[index]>0 && value==-1)
    counterValue[index] +=value;
}
//This function simulates as global history branch predictor
void GlobalHistory:: globalSimulation(vector<string>branchAddress,vector<string>actualPrediction){
  //Declaration of the variables
  int index,
      notTaken=0,
      taken=0,
      takenCorrect=0,
      notTakenCorrect=0,
      totalBranches=0,instruction=0;
  //This loop go through every branch address and makes a prediction
  for(int i=0;i<branchAddress.size();i++){
    std::string binary = std::bitset<16>(stoi(branchAddress[i])).to_string();
    instruction = atoi(binary.c_str());
	  index = (((instruction/4) << (bhr.size())) | (stoi(bhr,0,2) & 0x7)) & 0x7F;
    //If the counter value is less than 2 then predict it as not taken
    if(counterValue[index]==0||counterValue[index]==1){
      //These lines of codes are used to rotate string by 1
      reverse(bhr.begin(),bhr.begin()+1);
      reverse(bhr.begin()+1,bhr.end());
      reverse(bhr.begin(),bhr.end());
      //If actual prediction is taken then increment the counter value
      if(actualPrediction[i]=="T"){
        update(index,1);
        //Inserting 1 as taken at last index of string  bhr
        bhr[bhr.length()-1]='1';
      }
      //if the actual prediction is not taken then decrement the counter value
      else{
        update(index,-1);
        //Inserting 0 as not taken at last index of string  bhr
        bhr[bhr.length()-1]='0';
        notTakenCorrect++;
      }
    }
    //If the counter value is greater or equal to 2 predict as taken
    else{
      //These 3 lines of codes are used to shift string left by  1
      reverse(bhr.begin(),bhr.begin()+1);
      reverse(bhr.begin()+1,bhr.end());
      reverse(bhr.begin(),bhr.end());
      //if the actual predition is taken then increment the counter.
      if(actualPrediction[i]=="T"){
        update(index,1);
        //Inserting 1 as taken at last index of string  bhr
        bhr[bhr.length()-1]='1';
        takenCorrect++;
      }
      //if the actual prediction is not taken then decrement the counter
      else{
        update(index,-1);
        //Inserting 0 as not taken at last index of string  bhr
        bhr[bhr.length()-1]='0';
      }
    }
    totalBranches++;
    if(actualPrediction[i]=="T")taken++;
    if(actualPrediction[i]=="N")notTaken++;
  }

  //Printing out the results that we got from the loop
  cout<<endl<<endl<<"----Global History ----"<<endl<<endl;
  cout<<"Number of branches: "<<totalBranches<<endl;
  cout<<"Number of branches taken: "<<taken<<endl;
  cout<<"Number taken branches correctly predicted: "<<takenCorrect<<endl;
  cout<<"Number of branches not taken: "<<notTaken<<endl;
  cout<<"Number not taken branches correctly predicted: "<<notTakenCorrect<<endl;
  cout<<"Overall rate of correct predictions: "<<((takenCorrect+notTakenCorrect)/(float)totalBranches)*100.00<<"%"<<endl;
}

#endif //end of globalhistory
