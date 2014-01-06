#include "numToLet.h"


numToLet::numToLet(void){
	errorFlag = 0;
	de = dataEater();
	inputData = zero_matrix<double>(ADVR, ADVLEN);
	inputDataMP = zero_matrix<double>(ADVR, ADVLEN);
	targetPtn = zero_matrix<double>(ADVR, ADVLEN);
	inputPtn = zero_matrix<double>(ADVR, ADVLEN);
	targetPtnT = zero_matrix<double>(ADVLEN, ADVR);
	weight = zero_matrix<double>(ADVLEN, ADVLEN);
    pattern = zero_matrix<double>(ADVLEN, 1);
	output = zero_matrix<double>(ADVLEN, 1);
	recgPtn = zero_matrix<double>(1, ADVLEN);
}

numToLet::~numToLet(void){
}

void numToLet::doMapping(){
	try{
	de.coldDish(inputData, ADVLEN, ADVR, ADVDATAFROM);
	de.coldDish(targetPtn, ADVLEN, ADVR, ADVTARGFROM);
	de.coldDish(inputPtn, ADVLEN, ADVR, ADVPTNFROM);
	cout<<"input good"<<endl;
	}catch(int){
		cout<<"Subprocess Exception.(numToLet_doMapping())"<<endl;
		errorFlag = 1;
	}
	
	if(errorFlag != 1){
		targetPtnT = trans(targetPtn);
		numToLet::makeMPMatrix(inputData, inputDataMP);//»ñµÃ·ÂÄæ¾ØÕó

		for(unsigned i = 0; i<inputData.size1(); i++){//normalize
			for(unsigned j = 0; j<inputData.size2(); j++){
				inputData(i, j) = inputData(i, j)/sqrt(30.0);
			}
		}
		axpy_prod(targetPtnT, inputDataMP, weight);
		
		while(1){
			string str;
			cout<<"choose pattern 0~9 to recognize(-1 to stop):";
			getline (cin,str);
			if(str.compare("-1")==0)
				break;

			for(unsigned i= 0; i< inputPtn.size2(); i++)
				pattern(i, 0)= inputPtn(atoi(str.c_str()), i);

			axpy_prod(weight, pattern, output);

			for(unsigned i=0; i <ADVLEN; i++){//hardline function
				if(output(i, 0)>0)
					recgPtn(0, i)= 1;
				else if(output(i, 0)<0)
					recgPtn(0, i)= -1;
			}
			cout<<"pattern "<<str<<": "<<endl;
			de.print2Matrix(ADVCOL, pattern);
			cout<<"recognized:"<<endl;
			de.print2Matrix(ADVCOL, recgPtn);
		}
	}
}

void numToLet::makeMPMatrix(matrix<double>& mt, matrix<double>& mtMp){
	matrix<double>inverse(ADVR, ADVR);
	matrix<double>mtTrans(mt.size1(), mt.size2());
	matrix<double>temp(ADVR, ADVR);
	mtTrans = trans(mt);
	axpy_prod(mt, mtTrans, temp);
	if(InvertMatrix(temp, inverse)==1)
	    axpy_prod(inverse, mt, mtMp);
	else
		mtMp = zero_matrix<double>(ADVR, ADVLEN);
}

