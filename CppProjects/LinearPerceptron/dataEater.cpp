#include "dataEater.h"
//#include <iostream>
#include <fstream>

dataEater::dataEater(void)
{
}


dataEater::~dataEater(void)
{
}

template<class T>
void dataEater::print2Matrix(int col, matrix<T> &inputData){
	for(unsigned i= 0; i< inputData.size1(); i++)
		for(unsigned j= 0; j< inputData.size2(); j++){
			cout<<setiosflags(ios::right)<<setw(2)<<setprecision(2)<<inputData(i, j);
			if((i*inputData.size2() + j +1)%col == 0)
				cout<<endl;
		}
}

template<class T>
void dataEater::coldDish(matrix<T> &inputData, int len, int row, string filename){
	ifstream ifs;
	char read;
	int i = 0, j = -1, mark = 1;

	string path = boost::filesystem::initial_path<boost::filesystem::path>().string();
	path = path + "\\" + filename;
	ifs.open(path, fstream::in);
	try{
		while(ifs>>read){
			if(read == '1'){
				j++;
				if(j>=len){
					cout<<"error:1 ";
					throw 1;
				}
				if(mark == -1){
					inputData(i, j) = -1;
					mark *= -1;				
				}else if(mark == 1){
					inputData(i, j) = 1;			
				}	
			}else if(read == '-')
				mark *= -1;
			else if(read == ';'){
				j =-1;
				i++;
				if(i>=row){
					cout<<"error:2 ";
					throw 2;
				}
			}
		}
	}catch(int){
		cout<<"Exception Occur!Fault about matrix length. (dataEater_coldDish())"<<endl;
		ifs.close();
		cout<<"error:11 ";
		throw 11;
	}
	ifs.close();	
}
