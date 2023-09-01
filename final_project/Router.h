#include "systemc.h"
#include <iostream>
#include <fstream>

using namespace std;


SC_MODULE( Router ) {	
	//sc_in < bool > rst;
	//sc_in_clk clk;
 
  sc_port<sc_fifo_in_if<float> > x_in_data ; 
  sc_port<sc_fifo_in_if<sc_uint<6> > > x_in_layer_target ; 
  
  sc_port<sc_fifo_in_if<float> > y_in_data ; 
  sc_port<sc_fifo_in_if<sc_uint<6> > > y_in_layer_target ; 
   
  sc_port<sc_fifo_in_if<float> > local_in_data ; 
  sc_port<sc_fifo_in_if<sc_uint<6> > > local_in_layer_target ;
  
  
  sc_port<sc_fifo_out_if<float> > x_out_data ; 
  sc_port<sc_fifo_out_if<sc_uint<6> > > x_out_layer_target ; 
  
  sc_port<sc_fifo_out_if<float> > y_out_data ; 
  sc_port<sc_fifo_out_if<sc_uint<6> > > y_out_layer_target ; 
  
  sc_port<sc_fifo_out_if<float> > local_out_data ; 
  sc_port<sc_fifo_out_if<sc_uint<6> > > local_out_layer_target ;
  
  // now layer : 5:2  , x:1 , y :0  
  
	void run();
	
  float data ; 
  sc_uint<6> target ; 
  bool from_local ; 
  bool from_x ; 
  bool from_y ; 
  
  sc_uint<4> temp ; 
  sc_uint<1> x_value ;
  sc_uint<1> y_value ;
  
	SC_CTOR( Router )
	{	
		SC_THREAD( run );
    
    /*
    SC_THREAD( from_x) ; 
    SC_THREAD( from_y) ; 
    SC_THREAD( from_local) ;
    SC_THREAD( run_x) ; 
    SC_THREAD( run_y) ; 
    SC_THREAD( run_local) ;
	  */
  }
};


