#include "verifyThrNum.h"

verifyThrNum::verifyThrNum(void){
	errorFlag = 0;
	de = dataEater();
	inputData = zero_matrix<int>(R, LEN);
	ptnData = zero_matrix<int>(R, LEN);
	weight = zero_matrix<int>(LEN,LEN);
	mm = zero_matrix<int>(1, LEN);
	mt = zero_matrix<int>(LEN, 1);
	pattern= zero_matrix<int>(1, LEN);
	output= zero_matrix<int>(1, LEN);
	recgPtn= zero_matrix<int>(1, LEN);
}

verifyThrNum::~verifyThrNum(void){
}

void verifyThrNum::doJob(){
	try{
	de.coldDish(inputData, LEN, R, DATAFROM);
	de.coldDish(ptnData, LEN, R, PTNFROM);
	cout<<"input good"<<endl;
	}catch(int){
		cout<<"Subprocess Exception.(verifyThrNum_doJob())"<<endl;
		errorFlag = 1;
	}
	
	if(errorFlag != 1){
		for(unsigned k = 0; k< R; k++){
			for(unsigned i= 0; i< LEN; i++){
				mm(0, i)= inputData(k, i);
				mt(i, 0)= inputData(k, i);
			}
		axpy_prod(mt, mm, weight, false);
		}
		
		while(1){
			string str;
			cout<<"choose pattern 0~2 to recognize(-1 to stop):";
			getline (cin,str);
			if(str.compare("-1")==0)
				break;

			for(unsigned i= 0; i< ptnData.size2(); i++)
				pattern(0, i)= ptnData(atoi(str.c_str()), i);

			axpy_prod(pattern, weight, output);

			for(unsigned i=0; i <LEN; i++){
				if(output(0, i)>0)
					recgPtn(0, i)= 1;
				else if(output(0, i)<0)
					recgPtn(0, i)= -1;
			}
			cout<<"pattern "<<str<<": "<<endl;
			de.print2Matrix(COL, pattern);
			cout<<"recognized:"<<endl;
			de.print2Matrix(COL, recgPtn);
		}
	}
}


