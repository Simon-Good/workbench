#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\operation.hpp>
#include<boost\numeric\ublas\io.hpp>
#include"dataEater.h"

using namespace boost::numeric::ublas;	
using namespace std;

int main(){
	matrix<int> inputData(zero_matrix<int>(R, LEN));
	matrix<int> mm(1, LEN);
	matrix<int> mt(LEN, 1);
	matrix<int> weight(zero_matrix<int>(LEN,LEN));
	int errorFlag=0;

	dataEater de = dataEater();
	try{
	de.coldDish(inputData);
	cout<<"input good"<<endl;
	//cout<<inputData<<endl;
	}catch(int){
		cout<<"Subprocess Exception.(Hebb_main())"<<endl;
		errorFlag = 1;
	}
	
	if(errorFlag != 1){
		for(unsigned k = 0; k< R; k++){
			for(unsigned i= 0; i< LEN; i++){
				mm(0, i)= inputData(k, i);
				mt(i, 0)= inputData(k, i);
			}
		axpy_prod(mt, mm, weight, false);
		}/**/
		//cout<<weight<<endl;
		
		
		while(1){
			string str;
			cout<<"choose pattern 0~9 to recognize(-1 to stop):";
			getline (cin,str);
			if(str.compare("-1")==0)
				break;

			matrix<int> pattern(1, LEN);
			matrix<int> output(1 ,LEN);
			matrix<int> recgPtn(1, LEN);

			for(unsigned i= 0; i< inputData.size2(); i++)
				pattern(0, i)= inputData(atoi(str.c_str()), i);

			axpy_prod(pattern, weight, output);

			for(unsigned i=0; i <LEN; i++){
				if(output(0, i)>0)
					recgPtn(0, i)= 1;
				else if(output(0, i)<0)
					recgPtn(0, i)= -1;
			}
			cout<<"pattern "<<str<<": "<<pattern<<endl;
			cout<<"recognized:"<<recgPtn<<endl;
		}
	}
}

/*#include <iostream>
#include <string>
using namespace std;

int main () {
  string str;
  cout << "Please enter full name: ";
  getline (cin,str);
  cout << "Thank you, " << str << ".\n";
}*/

/*  for(unsigned i=0; i< mm.size1(); ++i)
		for(unsigned j= 0; j< mm.size2(); ++j){
			mm(i, j) = inputData(k,i*mm.size1()+j);
		}

	for(unsigned i=0; i< mt.size1(); ++i)
		for(unsigned j= 0; j< mt.size2(); ++j){
			mt(i, j) = inputData(k,j*mt.size2()+i);
		}
	for(unsigned i=0; i< mm.size1(); ++i)
		for(unsigned j= 0; j< mm.size2(); ++j){
			mm(i, j) = vec[i*mm.size1()+j];
		}

	for(unsigned i=0; i< mt.size1(); ++i)
		for(unsigned j= 0; j< mt.size2(); ++j){
			mt(i, j) = vec[j*mt.size2()+i];
		}
	axpy_prod(mt, mm, weight);

	matrix<int> input(mm);
	matrix<int> output(1 ,LEN);
	matrix<int> recgPtn(1, LEN);

	axpy_prod(input, weight, output);

	for(unsigned i=0; i <LEN; i++){
		if(output(0, i)>0)
			recgPtn(0, i)= 1;
		else if(output(0, i)<0)
			recgPtn(0, i)= -1;
	}
	cout<<recgPtn<<endl;*/
