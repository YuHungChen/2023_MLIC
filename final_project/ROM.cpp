#include "ROM.h"
#include "mode.h"

void ROM::read_data() {
     //bool signal ; 	
	   while (1){
          if ( rom_rd -> read() ) {
               layer_index = now_layer -> read() ; 
               if ( layer_index == 0 ){
                    data -> write (  input[rom_addr -> read()] )  ;
               }else if ( layer_index == 1 ){
                    data -> write (  rom_Conv_1[ rom_addr -> read() ] )  ;
               }else if ( layer_index == 2 ){
                    data -> write (  rom_Conv_2[rom_addr -> read()] )  ;
               }else if ( layer_index == 3 ){
                    data -> write (  rom_Conv_3[rom_addr -> read()] )  ;
               }else if ( layer_index == 4 ){
                    data -> write (  rom_Conv_4[rom_addr -> read()] )  ;
               }else if ( layer_index == 5 ){
                    data -> write (  rom_Conv_5[rom_addr -> read()] )  ;
               }else if ( layer_index >= 6 ){
                    cout << "ROM error" << endl ; 
                    sc_stop() ; 
               }
          }

		    // wait() ; 
          
     }
}

void ROM_DENSE::read_data(){
  while(1){
     if ( rom_rd -> read() ) {
       layer_index = now_layer -> read() ;
       if ( layer_index == MAX_LAYER - 2  ){
            data -> write (  rom_FC_1[rom_addr -> read()] )  ;
       }else if ( layer_index == MAX_LAYER - 1 ){
            data -> write (  rom_FC_2[rom_addr -> read()] )  ;
       }else if ( layer_index == MAX_LAYER  ){
            data -> write (  rom_FC_3[rom_addr -> read()] )  ;
       }else{
            cout << "ROM_DENSE error" << endl ; 
            sc_stop() ; 
       }
     }
   }

}



