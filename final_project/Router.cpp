#include "Router.h"

void Router::run() {
	// vvvvv put your code here vvvvv
	
  //cout << sc_time_stamp() << endl ; 
  while (1) {
      from_local = true ; 
      if ( from_local ){
         if (local_in_data -> nb_read(data)){
             target = local_in_layer_target -> read() ; 
             
             temp    = target(5,2) ; 
             x_value = target(1,1) ; 
             y_value = target(0,0) ;
             //cout << x_value << " , " << y_value << endl ;  
             //cout << data << endl ; 
             // x-y routing
             if (x_value >0 ){
                x_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                x_out_data -> write(data) ; 
                x_out_layer_target -> write(target) ; 
             }else if ( y_value > 0 ){
                y_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                y_out_data -> write(data) ; 
                y_out_layer_target -> write(target) ; 
             }else { // arrive the target 
               cout << " wrong local" << endl ; 
               sc_stop() ; 
             }
             
         }else{
            from_x = true; 
         }
          
      }
      if (from_x ){
         if (x_in_data -> nb_read(data)){
             target = x_in_layer_target -> read() ; 
             temp    = target(5,2) ; 
             x_value = target(1,1) ; 
             y_value = target(0,0) ;
             //cout << x_value << " , " << y_value << endl ;  
             //cout << data << endl ; 
             // x-y routing
             if (x_value >0 ){
                x_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                x_out_data -> write(data) ; 
                x_out_layer_target -> write(target) ; 
             }else if ( y_value > 0 ){
                y_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                y_out_data -> write(data) ; 
                y_out_layer_target -> write(target) ; 
             }else { // arrive the target 
                local_out_data -> write(data) ; 
                local_out_layer_target -> write(target) ; 
             }
         }else{
            from_y = true; 
         }
         
      }
      if (from_y ){
         if (y_in_data -> nb_read(data)){
             target = y_in_layer_target -> read() ; 
             temp    = target(5,2) ; 
             x_value = target(1,1) ; 
             y_value = target(0,0) ;
             //cout << x_value << " , " << y_value << endl ;  
             //cout << data << endl ; 
             // x-y routing
             if (x_value >0 ){
                x_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                x_out_data -> write(data) ; 
                x_out_layer_target -> write(target) ; 
             }else if ( y_value > 0 ){
                y_value = 0 ; 
                target = (temp , x_value , y_value) ; 
                
                y_out_data -> write(data) ; 
                y_out_layer_target -> write(target) ; 
             }else { // arrive the target 
                local_out_data -> write(data) ; 
                local_out_layer_target -> write(target) ; 
             }
         }
         
      }
      wait (4,SC_NS) ; 
  }
	// ^^^^^ put your code here ^^^^^
}



