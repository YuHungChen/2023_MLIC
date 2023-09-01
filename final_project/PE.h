 #include "systemc.h"
#include <iostream>
#include <fstream>

using namespace std;


SC_MODULE( PE ) {	
  sc_in < int  > type ; // 0 : init conv  1 : conv ( no init input)  2 : max_pool   3 : dense     
	sc_in < bool > rst;
	sc_in_clk clk;
	
	sc_port < sc_fifo_out_if <bool> >rom_rd ; 
  sc_port < sc_fifo_out_if <int > >rom_addr ; 
  sc_port < sc_fifo_in_if  <float> >data_in ; 
	sc_port < sc_fifo_out_if <sc_uint<4>> >now_layer ; 


  sc_port<sc_fifo_in_if<float> > router_in_data ; 
  sc_port<sc_fifo_in_if <sc_uint<6> > > in_layer_target ;

  sc_port<sc_fifo_out_if<float> > out_data ; 
  sc_port<sc_fifo_out_if<sc_uint<6> > > out_layer_target ; 

  sc_port < sc_fifo_out_if <float> >data_out ; 
  sc_port < sc_fifo_out_if <bool> >data_out_signal ; 

  void run() ; 
	
	float value ; 
  sc_uint<2> out_target_val ; 
	sc_uint<4> now_index ;  
  int counter ; 
  sc_uint<6> temp ; 
  //sc_uint<4> now_layer ; 
  
  vector <vector<vector<float> >> picture ;
  vector <vector<vector<float> >> output_pic ;
	vector <vector<vector<vector<float> >>> weight ;
  vector <float> bias ; 
  //float picture[228][228][3] ; 
	//float weight [11][11][3][96] ; 
	int count_x , count_y , count_z , count_output_ch; 
  int x_max , y_max ,z_max , channel_max ; 
  int padding_size ; 
  int input_size ;
  int weight_size ; 
  int stride_size ; 
  int output_size ; 
  int input_cha_size ; 
  int output_cha_size ;
  int max_pool_size ; 

  float result ;  
  float max_value ; 
  
	bool store_input ; 
	bool store_weight ;
  bool store_bias  ;
  bool store_input_from_router ; 
  bool store_input_from_itself ; 
	
  bool is_conv ; 
  bool is_maxpool  ; 
  bool is_dense  ;  
  bool writing_data ;
  bool set_type ; 
  bool write_to_monitor ;  
	SC_CTOR( PE )
	{	
    
      
    //cout << (input_size-2*padding_size) * (input_size-2*padding_size) * (input_cha_size) << endl ;


		SC_THREAD( run );
		sensitive << rst.pos() << clk.pos();
		dont_initialize() ; 
  }
};


