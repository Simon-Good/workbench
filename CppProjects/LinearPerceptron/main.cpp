#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include "verifyThrNum.h"
#include "numToLet.h"
 
using namespace boost::numeric::ublas;	
using namespace std;

int main(){
	while(1){
		string choice;
		cout<<"1.recognize from image 0~2 to 0~2."<<endl;
		cout<<"2.recognize from image 0~9 to A~J."<<endl;
		cout<<"choose mission(0 to stop):";
		getline (cin, choice);
		if(choice.compare("0")==0)
			break;
		else if(choice.compare("1")==0){
			verifyThrNum vtn= verifyThrNum();
			vtn.doJob();
		}else if(choice.compare("2")==0){
			numToLet ntl = numToLet();
			ntl.doMapping();
		}else
			break;
	}
