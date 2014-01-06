#include "dataEater.h"
//#include <iostream>
#include <fstream>

dataEater::dataEater(void)
{
}


dataEater::~dataEater(void)
{
}

void dataEater::coldDish(matrix<int> &inputData){
	string path = boost::filesystem::initial_path<boost::filesystem::path>().string();
	path = path + "\\" + DATAFROM;

	ifstream ifs;
	ifs.open(path, fstream::in);
	//cin.rdbuf(ifs.rdbuf());

	char read;
	int i = 0, j = -1, mark = 1;
	try{
		while(ifs>>read){
			if(read == '1'){
				j++;
				if(j>=LEN){
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
				if(i>=R){
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
