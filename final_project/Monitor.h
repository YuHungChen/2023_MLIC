#include "systemc.h"
#include <iostream>
#include <fstream>
#include <string>
#include "mode.h"

using namespace std;

SC_MODULE( Monitor ) {
	sc_in < bool > rst;
	sc_in < bool > clk;
	sc_port <sc_fifo_in_if<float> > data_in ; 
  sc_port <sc_fifo_in_if<bool> > data_in_signal ; 

	void monitor();
	int x, y;
	bool is_reset ; 
  vector<string> type ;
  float data_value ;
  float best_value  ; 
  int best_index ; 
  string value ; 
  ifstream fin;
	SC_CTOR( Monitor )
	{	
		if (MODE == 1)
			fin.open( "/home/ML310580023/final_project/input_pattern/image_class.txt", ios::in );
		else
			fin.open( "/home/ML310580023/final_project/input_pattern_Lenet/image_class.txt", ios::in );
		
		while ( getline(fin , value)){
			type.emplace_back(value) ; 
		}
		fin.close() ; 
		//cout << "YES" <<  endl ; 
		//cout << type.size() << endl ;
	// for (int i= 0 ; i< 100 ; i++)
	//		cout << "  :  " << type[i] << endl   ;
		//cout << "no " << endl ; 
			SC_METHOD( monitor );
			sensitive << clk.pos()  ;
		is_reset = false ; 
		best_value = 0 ;
	}
};

