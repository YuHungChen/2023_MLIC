#include "systemc.h"
#include <iostream>
#include <fstream>

#include "mode.h"

using namespace std;

SC_MODULE( ROM ) {	
	sc_in_clk clock;
  
  sc_port <sc_fifo_in_if<bool> > rom_rd ; 
  sc_port <sc_fifo_in_if<int> > rom_addr ; 
  sc_port <sc_fifo_out_if<float> > data ; 
  sc_port <sc_fifo_in_if<sc_uint<4> > > now_layer;  

  vector <float> input ; 
  vector <float> rom_Conv_1 ; 
  vector <float> rom_Conv_2 ; 
  vector <float> rom_Conv_3 ; 
  vector <float> rom_Conv_4 ; 
  vector <float> rom_Conv_5 ; 
  //vector <float> rom_FC_1 ; 
  //vector <float> rom_FC_2 ; 
  //vector <float> rom_FC_3 ; 
	//float rom_M[50000000];
	ifstream fin;
	void read_data();
	int temp;
	int counter ; 
  sc_uint<4> layer_index ; 
  float value ; 
	SC_CTOR( ROM ) 
	{
		// vvvvv change the path of input file here vvvvv

    // input file  
    // can be modified in "mode.h"; 
		fin.open( INPUT_FILE , ios::in );
		while (fin >> value){
			input.emplace_back(value) ; 
		}
		fin.close() ; 
    
    if (MODE == 1 ){
      // feature conv_1 ;
      fin.open( "/home/ML310580023/final_project/weights/features0_weight.txt", ios::in );
      while (fin >> value){
          rom_Conv_1.emplace_back(value) ; 
      }
      fin.close() ; 
      
      fin.open( "/home/ML310580023/final_project/weights/features0_bias.txt", ios::in );
      while (fin >> value){
          rom_Conv_1.emplace_back(value) ; 
      }
      fin.close() ; 
      
      // feature conv_2 ;
      fin.open( "/home/ML310580023/final_project/weights/features1_weight.txt", ios::in );
      while (fin >> value){
          rom_Conv_2.emplace_back(value) ; 
      }
      fin.close() ; 
      fin.open( "/home/ML310580023/final_project/weights/features1_bias.txt", ios::in );
      while (fin >> value){
          rom_Conv_2.emplace_back(value) ; 
      }
      fin.close() ; 
      
      // feature conv_3 ;
      fin.open( "/home/ML310580023/final_project/weights/features2_weight.txt", ios::in );
      while (fin >> value){
          rom_Conv_3.emplace_back(value) ; 
      }
      fin.close() ; 
      fin.open( "/home/ML310580023/final_project/weights/features2_bias.txt", ios::in );
      while (fin >> value){
          rom_Conv_3.emplace_back(value) ; 
      }
      fin.close() ; 
      
      // feature conv_4 ;
      fin.open( "/home/ML310580023/final_project/weights/features3_weight.txt", ios::in );
      while (fin >> value){
          rom_Conv_4.emplace_back(value) ; 
      }
      fin.close() ; 
      fin.open( "/home/ML310580023/final_project/weights/features3_bias.txt", ios::in );
      while (fin >> value){
          rom_Conv_4.emplace_back(value) ; 
      }
      fin.close() ; 
      
      // feature conv_5 ;
      fin.open( "/home/ML310580023/final_project/weights/features4_weight.txt", ios::in );
      while (fin >> value){
          rom_Conv_5.emplace_back(value) ; 
      }
      fin.close() ; 
      fin.open( "/home/ML310580023/final_project/weights/features4_bias.txt", ios::in );
      while (fin >> value){
          rom_Conv_5.emplace_back(value) ; 
      }
      fin.close() ; 
    }else{
      // feature conv_1 ;
      fin.open( "/home/ML310580023/final_project_lenet/weights/c1.txt", ios::in );
      while (fin >> value){
          rom_Conv_1.emplace_back(value) ; 
      }
      fin.close() ; 
      
      // feature conv_2 ;
      fin.open( "/home/ML310580023/final_project_lenet/weights/c2.txt", ios::in );
      while (fin >> value){
          rom_Conv_2.emplace_back(value) ; 
      }
      fin.close() ;   

    }
    
		SC_THREAD( read_data );
		  sensitive << clock.pos();
	}
};



SC_MODULE( ROM_DENSE ) {	
	sc_in_clk clock;
  
  sc_port <sc_fifo_in_if<bool> > rom_rd ; 
  sc_port <sc_fifo_in_if<int> > rom_addr ; 
  sc_port <sc_fifo_out_if<float> > data ; 
  sc_port <sc_fifo_in_if<sc_uint<4> > > now_layer;  

  vector <float> rom_FC_1 ; 
  vector <float> rom_FC_2 ; 
  vector <float> rom_FC_3 ; 
	//float rom_M[50000000];
	ifstream fin;
	void read_data();
	int temp;
	int counter ; 
  sc_uint<4> layer_index ; 
  float value ; 
	SC_CTOR( ROM_DENSE ) 
	{
		// vvvvv change the path of input file here vvvvv
    
    if (MODE == 1 ){
        // feature FC_1 ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier1_weight.txt", ios::in );
        while (fin >> value){
            rom_FC_1.emplace_back(value) ; 
        }
        fin.close() ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier1_bias.txt", ios::in );
        while (fin >> value){
            rom_FC_1.emplace_back(value) ; 
        }
        fin.close() ; 
        
        // feature FC_2 ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier2_weight.txt", ios::in );
        while (fin >> value){
            rom_FC_2.emplace_back(value) ; 
        }
        fin.close() ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier2_bias.txt", ios::in );
        while (fin >> value){
            rom_FC_2.emplace_back(value) ; 
        }
        fin.close() ; 
        
        // feature FC_3 ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier3_weight.txt", ios::in );
        while (fin >> value){
            rom_FC_3.emplace_back(value) ; 
        }
        fin.close() ; 
        fin.open( "/home/ML310580023/final_project/weights/classifier3_bias.txt", ios::in );
        while (fin >> value){
            rom_FC_3.emplace_back(value) ; 
        }
        fin.close() ; 
    }else {
        // feature FC_1 ; 
        fin.open( "/home/ML310580023/final_project_lenet/weights/d1.txt", ios::in );
        while (fin >> value){
            rom_FC_1.emplace_back(value) ; 
        }
        fin.close() ; 
        
        // feature FC_2 ; 
        fin.open( "/home/ML310580023/final_project_lenet/weights/d2.txt", ios::in );
        while (fin >> value){
            rom_FC_2.emplace_back(value) ; 
        }
        fin.close() ; 
        
        // feature FC_3 ; 
        fin.open( "/home/ML310580023/final_project_lenet/weights/d3.txt", ios::in );
        while (fin >> value){
            rom_FC_3.emplace_back(value) ; 
        }
        fin.close() ; 

    }



		SC_THREAD( read_data );
		  sensitive << clock.pos();
	}
};


