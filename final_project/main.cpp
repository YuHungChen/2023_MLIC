#include "clockreset.h"
#include "Monitor.h"
#include <iostream>

#include "PE.h"
#include "Router.h"
#include "ROM.h"

using namespace std;

int sc_main( int argc,char* argv[] ) {
	sc_signal < bool > clk, reset;
  
  sc_fifo   < bool  > rom_rd;
  sc_fifo   < float > data_in ;
  sc_fifo   < int > rom_addr ;
  sc_fifo   < sc_uint<4> > now_layer ;
  
  sc_fifo   < bool  > rom_rd_2;
  sc_fifo   < float > data_in_2 ;
  sc_fifo   < int > rom_addr_2 ;
  sc_fifo   < sc_uint<4> > now_layer_2 ;
  
  sc_fifo   < bool  > trash_rd ;
  sc_fifo   < float > trash_data_in ;
  sc_fifo   < int > trash_addr ;
  sc_fifo   < sc_uint<4> > trash_now_layer ;
  
  sc_fifo   < bool  > rom_rd_4;
  sc_fifo   < float > data_in_4 ;
  sc_fifo   < int > rom_addr_4 ;
  sc_fifo   < sc_uint<4> > now_layer_4 ;
  
  
  
  sc_fifo   < bool  > data_out_signal_1;
  sc_fifo   < float > data_out_1 ;
  sc_fifo   < bool  > data_out_signal_2;
  sc_fifo   < float > data_out_2 ;
  sc_fifo   < bool  > data_out_signal_3;
  sc_fifo   < float > data_out_3 ;
  sc_fifo   < bool  > data_out_signal_4;
  sc_fifo   < float > data_out_4 ;
 
 
	Reset      m_reset( "m_reset", 20    );
	Clock      m_clock( "m_clock", 5, 20 );
  ROM        m_rom( "m_rom");
  ROM        m_rom_2( "m_rom_2");
  ROM_DENSE  m_dense( "m_dense");
  PE         PE_conv_1   ("PE_conv_1") ;    // PE1
  PE         PE_conv_2   ("PE_conv_2") ;    // PE2
  PE         PE_max_pool ("PE_max_pool") ;  // PE3
  PE         PE_dense    ("PE_dense") ;     // PE4
  
  Router   Router_PE1    ("Router_PE1") ;
  Router   Router_PE2    ("Router_PE2") ;
  Router   Router_PE3    ("Router_PE3") ;
  Router   Router_PE4    ("Router_PE4") ;
  
  Monitor  m_monitor( "m_monitor");
 // Conv     m_conv( "m_conv" ) ;
  
  m_clock   (clk) ; 
  m_reset   (reset) ; 
  m_rom     (clk, rom_rd, rom_addr, data_in , now_layer) ; 
  m_rom_2   (clk, rom_rd_2, rom_addr_2, data_in_2 , now_layer_2) ; 
  m_dense   (clk, rom_rd_4, rom_addr_4, data_in_4 , now_layer_4) ; 
  
  sc_signal<int> zero   ; 
  sc_signal<int> one    ;
  sc_signal<int> two    ;
  sc_signal<int> three  ;
  
  zero  = 0 ; 
  one   = 1 ;
  two   = 2 ;
  three = 3 ;

  sc_fifo<float> router_in_data ; 
  sc_fifo<sc_uint<6> > input_target_layer ;
  //   5:2 ==> now layer    , bit 1 : x    bit 0 : y  
  sc_fifo<float> router_out_data ; 
  sc_fifo<sc_uint<6> > output_target_layer ; 
  
  // PE1        PE2
  //   \          \
  //   router1--<1>---router2
  //      |          |
  //      |          |
  //     <2>        <3>
  // PE3  |     PE4	 |
  //   \  |       \  |
  //   router3--<4>---router4
   
  // <1> r1_r2_data ¡B r1_r2_target ; 
  // <2> r1_r3_data ¡B r1_r3_target ; 
  // <3> r2_r4_data ¡B r2_r4_target ; 
  // <4> r3_r4_data ¡B r3_r4_target ; 
  // others
  //   local_r1_data ¡B local_r1_target ; 
  //   local_r2_data ¡B local_r2_target ; 
  //   local_r3_data ¡B local_r3_target ; 
  //   local_r4_data ¡B local_r4_target ; 
  sc_fifo<float> r1_r2_data ;
  sc_fifo<float> r2_r1_data ;
   
  sc_fifo<float> r1_r3_data ; 
  sc_fifo<float> r3_r1_data ;
  
  sc_fifo<float> r2_r4_data ;
  sc_fifo<float> r4_r2_data ;
   
  sc_fifo<float> r3_r4_data ; 
  sc_fifo<float> r4_r3_data ;
  
  sc_fifo<float> local_r1_data ; 
  sc_fifo<float> r1_local_data ;
  
  sc_fifo<float> local_r2_data ; 
  sc_fifo<float> r2_local_data ;
  
  sc_fifo<float> local_r3_data ; 
  sc_fifo<float> r3_local_data ;
  
  sc_fifo<float> local_r4_data ;
  sc_fifo<float> r4_local_data ;
   
  sc_fifo<sc_uint<6> > r1_r2_target ; 
  sc_fifo<sc_uint<6> > r2_r1_target ; 
  
  sc_fifo<sc_uint<6> > r1_r3_target ;
  sc_fifo<sc_uint<6> > r3_r1_target ; 
   
  sc_fifo<sc_uint<6> > r2_r4_target ; 
  sc_fifo<sc_uint<6> > r4_r2_target ; 
  
  sc_fifo<sc_uint<6> > r3_r4_target ; 
  sc_fifo<sc_uint<6> > r4_r3_target ; 
  
  sc_fifo<sc_uint<6> > local_r1_target ; 
  sc_fifo<sc_uint<6> > r1_local_target ; 
  
  sc_fifo<sc_uint<6> > local_r2_target ; 
  sc_fifo<sc_uint<6> > r2_local_target ; 
  
  sc_fifo<sc_uint<6> > local_r3_target ;
  sc_fifo<sc_uint<6> > r3_local_target ; 
   
  sc_fifo<sc_uint<6> > local_r4_target ; 
  sc_fifo<sc_uint<6> > r4_local_target ; 
  
  PE_conv_1   (zero  , reset ,clk , rom_rd , rom_addr , data_in , now_layer , r1_local_data , r1_local_target , local_r1_data , local_r1_target   , data_out_1, data_out_signal_1 ) ; 
  PE_conv_2   (one   , reset ,clk , rom_rd_2 , rom_addr_2 , data_in_2 , now_layer_2 , r2_local_data , r2_local_target , local_r2_data , local_r2_target , data_out_2, data_out_signal_2 ) ; 
  PE_max_pool (two   , reset ,clk , trash_rd , trash_addr , trash_data_in , trash_now_layer , r3_local_data , r3_local_target , local_r3_data , local_r3_target , data_out_3, data_out_signal_3 ) ; 
  PE_dense    (three , reset ,clk , rom_rd_4 , rom_addr_4 , data_in_4 , now_layer_4 , r4_local_data , r4_local_target , local_r4_data , local_r4_target , data_out_4, data_out_signal_4 ) ; 
  
  //    router    //    X_axis            //    y_axis          // local                                 // output 
  Router_PE1  ( r2_r1_data, r2_r1_target,  r3_r1_data, r3_r1_target,  local_r1_data, local_r1_target ,   
                r1_r2_data, r1_r2_target,  r1_r3_data, r1_r3_target,  r1_local_data, r1_local_target  ) ; 
  
  Router_PE2  ( r1_r2_data, r1_r2_target,  r4_r2_data, r4_r2_target,  local_r2_data, local_r2_target ,   
                r2_r1_data, r2_r1_target,  r2_r4_data, r2_r4_target,  r2_local_data, r2_local_target  ) ; 
  
  Router_PE3  ( r4_r3_data, r4_r3_target,  r1_r3_data, r1_r3_target,  local_r3_data, local_r3_target ,   
                r3_r4_data, r3_r4_target,  r3_r1_data, r3_r1_target,  r3_local_data, r3_local_target  ) ; 
  
  Router_PE4  ( r3_r4_data, r3_r4_target,  r2_r4_data, r2_r4_target,  local_r4_data, local_r4_target ,   
                r4_r3_data, r4_r3_target,  r4_r2_data, r4_r2_target,  r4_local_data, r4_local_target  ) ; 
  
   
  
  m_monitor (reset, clk, data_out_4, data_out_signal_4) ;  
 // m_conv    (reset, clk, rom_rd, rom_addr, data_in, data_out, data_out_signal ) ; 
  
	sc_start( );
	return 0;
}











