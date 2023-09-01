#include "PE.h"
#include "mode.h"

void PE::run() {
	// vvvvv put your code here vvvvv
	
  //cout << sc_time_stamp() << endl ; 
  while (true){
  if (rst) {
    wait() ; 
    //cout << sc_time_stamp() << endl ; 
    store_input_from_itself = false ;
    write_to_monitor        = false ; 
    if (type.read() ==0 ) {
      set_type    = true ; 
    
      store_input_from_router = false ; 
      store_input = true ; 
      store_weight = true ; 
      store_bias   = true ; 
    
      is_conv = true ;
      is_maxpool = false ; 
      is_dense = false ;  
      writing_data =true ; 
      now_index = 0 ; 
      if (MODE == 1 ){
        count_x = 2 ;  // padding for 2 
        count_y = 2 ;  // padding for 2 
      }else{
        count_x = 0 ;  // no padding
        count_y = 0 ;  // no padding 
      }
      count_z = 0 ; 
      counter = 0 ;  // address ; 
      count_output_ch = 0 ; 

    }else if (type.read() == 1){
      set_type    = true ; 
    
      store_input_from_router = true ; 
      store_input = false ;
      store_weight = true ; 
      store_bias   = true ; 
      
      is_conv = true ;
      is_maxpool = false ; 
      is_dense = false ;  
      writing_data =true ; 
      now_index = 4 ; 
      
       
    }else if (type.read() == 2){  // max_pooling
      set_type    = true ; 
      store_input_from_router = true ; 
      store_input = false ;
      store_weight = false ; 
      store_bias   = false ; 
      
      is_conv = false ;
      is_maxpool = true ; 
      is_dense = false ;  
      writing_data =true ; 
      now_index = 2 ; 
    }else if (type.read() == 3 ){  // dense
      set_type    = true ; 
      store_input_from_router = true ; 
      store_input = false ;
      store_weight = true ; 
      store_bias   = true ; 
      
      is_conv = false ;
      is_maxpool = false ; 
      is_dense = true ;  
      writing_data = false ;
      now_index = 6 ; 
    }else{
      sc_stop() ; 
    }
    
  }else{
    wait() ; 
    // input file into picture [228][228][3] ;
    if (set_type ){
        // for   initial
        if (now_index == 0 ){
          if (MODE ==1){
            input_size  = 228 ;  
            stride_size = 4 ; 
            weight_size = 11 ;
            input_cha_size = 3 ;
            output_cha_size = 64 ;
            padding_size = 2 ; 
          }else{
            input_size  = 28 ;  
            stride_size = 1 ; 
            weight_size = 5 ;
            input_cha_size = 1 ;
            output_cha_size = 6 ;
            padding_size = 0 ; 
          }
          output_size =  ( input_size - weight_size ) / stride_size  + 1 ;   
          picture.resize(input_size) ; 
          for (auto& v : picture) v.resize(input_size) ; 
          for (auto& v : picture) 
            for (auto& w : v) w.resize(input_cha_size) ; 
            
          weight.resize(weight_size) ; 
          for (auto& v : weight) v.resize(weight_size) ; 
          for (auto& v : weight) 
            for (auto& w : v) w.resize(input_cha_size) ; 
          for (auto& v : weight) 
            for (auto& w : v) 
              for (auto& x : w) x.resize(output_cha_size) ; 
      
          bias.resize(output_cha_size) ; 
      	  
          output_pic.resize(output_size) ; 
          for (auto& v : output_pic) v.resize(output_size) ; 
          for (auto& v : output_pic) 
            for (auto& w : v) w.resize(output_cha_size) ; 
          
          set_type = false ; 
        }

        // for data from PE itself 
        if (now_index == MAX_LAYER -1 ) {
          //cout << "dense_2  now index " << now_index  << endl  ;
          if (MODE == 1 ){
            input_cha_size = 4096 ;
            output_cha_size   = 4096 ;
          }else{
            input_cha_size = 128 ;
            output_cha_size   = 84 ; 
          }
          padding_size = 0 ;
          
          set_type = false ; 
          count_x = 0 ;
          count_y = 0 ; 
          count_z = 0 ;
          picture.resize(1) ; 
          for (auto& v : picture) v.resize(input_cha_size) ; 
          for (auto& v : picture) 
            for (auto& w : v) w.resize(1) ; 
            
          weight.resize(1) ; 
          for (auto& v : weight) v.resize(1) ; 
          for (auto& v : weight) 
            for (auto& w : v) w.resize(input_cha_size) ; 
          for (auto& v : weight) 
            for (auto& w : v) 
              for (auto& x : w) x.resize(output_cha_size) ; 
          
          //bias.resize(output_cha_size) ; 
      
          //sc_stop() ;  
        }else if(now_index == MAX_LAYER ){
          //cout << "dense_2   now index " << now_index  << endl  ;
          if (MODE == 1 ){
            input_cha_size = 4096 ;
            output_cha_size   = 1000 ;
          }else{
            input_cha_size = 84 ;
            output_cha_size   = 10 ; 
          } 
          padding_size = 0 ;
          
          set_type = false ; 
          count_x = 0 ;
          count_y = 0 ; 
          count_z = 0 ;
          
          picture.resize(1) ; 
          for (auto& v : picture) v.resize(input_cha_size) ; 
          for (auto& v : picture) 
            for (auto& w : v) w.resize(1) ; 
            
          weight.resize(1) ; 
          for (auto& v : weight) v.resize(1) ; 
          for (auto& v : weight) 
            for (auto& w : v) w.resize(input_cha_size) ; 
          for (auto& v : weight) 
            for (auto& w : v) 
              for (auto& x : w) x.resize(output_cha_size) ; 
      
          bias.resize(output_cha_size) ; 
           
          //sc_stop() ; 
        }
        // for data from router
        
        if (in_layer_target -> nb_read(temp) ) {
          now_index = temp(5,2)  ;
          //cout << " set_type " << set_type << endl ; 
          //cout << " now_index : " << now_index << " type : "  <<   type.read()   << endl ;
          if (now_index == 2 ){ // maxpool
             if ( type.read() == 2 ){
               //cout << " now_index : 2 max pool " << endl ; 
               if (MODE == 1 ){
                input_size = 55 ;
                stride_size = 2 ; 
                max_pool_size = 3 ;
                input_cha_size = 64 ;
                output_cha_size = 64 ;
                padding_size = 0 ;
               } else{
                input_size = 24 ;
                stride_size = 2 ; 
                max_pool_size = 2 ;
                input_cha_size = 6 ;
                output_cha_size = 6 ;
                padding_size = 0 ; 
               }
               output_size   = (input_size - max_pool_size) / stride_size +1 ; 
             }else {
               //cout << " now_index : 2 convolution " << endl ;
               if (MODE == 1 ){
                input_size  = 31 ;   // 27 + 2* padding size 
                stride_size = 1 ; 
                weight_size = 5 ;
                input_cha_size = 64 ;
                output_cha_size = 192 ;
                padding_size = 2 ;
               }else{
                input_size  = 12 ;  
                stride_size = 1 ; 
                weight_size = 5 ;
                input_cha_size = 6 ;
                output_cha_size = 16 ;
                padding_size = 0 ;
               }
               output_size =  ( input_size - weight_size ) / stride_size  + 1 ;
             }
          }else if (now_index == 3){
             if (type.read() == 2 ){ // maxpool
               //cout << " now_index : 3 max pool " << endl ; 
               if (MODE == 1 ){
                input_size = 27 ;
                stride_size = 2 ; 
                max_pool_size = 3 ;
                input_cha_size = 192 ;
                output_cha_size = 192 ;
                padding_size = 0 ;
               }else{
                input_size = 8 ;
                stride_size = 2 ; 
                max_pool_size = 2 ;
                input_cha_size = 16 ;
                output_cha_size = 16 ;
                padding_size = 0 ; 
               }
               output_size   = (input_size - max_pool_size) / stride_size +1 ; 
             }else{ // conv
               //cout << " now index : 3   // only " << endl ; 
               if (MODE == 1 ){
               input_size  = 15 ;   // 13 + 2* padding size 
               stride_size = 1 ; 
               weight_size = 3 ;
               input_cha_size = 192 ;
               output_cha_size = 384 ;
               padding_size = 1 ;
               output_size =  ( input_size - weight_size ) / stride_size  + 1 ;  
               }else{
                stride_size = 1 ; 
                input_cha_size = 256 ;
                output_cha_size   = 128 ; 
                padding_size = 0 ;
               }
             }
          }else if (now_index == 4){
             //cout << " now index : 4   // only conv" << endl ; 
             input_size  = 15 ;   // 13 + 2* padding size 
             stride_size = 1 ; 
             weight_size = 3 ;
             input_cha_size = 384 ;
             output_cha_size = 256 ;
             padding_size = 1 ;
             output_size =  ( input_size - weight_size ) / stride_size  + 1 ;  
          }else if (now_index == 5){
              // conv
               //cout << " now_index : 5 only convolution " << endl ;
               input_size  = 15 ;   // 13 + 2* padding size 
               stride_size = 1 ; 
               weight_size = 3 ;
               input_cha_size = 256 ;
               output_cha_size = 256 ;
               padding_size = 1 ;
               output_size =  ( input_size - weight_size ) / stride_size  + 1 ; 
             
          }else if (now_index == 6 ) {  // dense 
             if (type.read() == 2 ){ // maxpool
               //cout << " now_index : 6 , max pool " << endl ; 
               input_size = 13 ;
               stride_size = 2 ; 
               max_pool_size = 3 ;
               input_cha_size = 256 ;
               output_cha_size = 256 ;
               padding_size = 0 ; 
               output_size   = (input_size - max_pool_size) / stride_size +1 ; 
             }else{
              // cout << "now_index : 6 dense " << endl ; 
               
               stride_size = 0 ; 
               input_cha_size = 9216 ;
               output_cha_size   = 4096 ; 
               padding_size = 0 ;
               //sc_stop() ;
             }
          }
          
          set_type = false ; 
          count_x = padding_size ;
          count_y = padding_size ; 
          count_z = 0 ;
          //cout << "set type " << set_type << endl ;
          if (type.read() == 3 ) {
            

            picture.resize(1) ; 
            for (auto& v : picture) v.resize(input_cha_size) ; 
            for (auto& v : picture) 
              for (auto& w : v) w.resize(1) ; 

              
            weight.resize(1) ; 
            for (auto& v : weight) v.resize(1) ; 
            for (auto& v : weight) 
              for (auto& w : v) w.resize(input_cha_size) ; 
            for (auto& v : weight) 
              for (auto& w : v) 
                for (auto& x : w) x.resize(output_cha_size) ; 

            
            bias.resize(output_cha_size) ; 
        	  
            // cout << picture.size()         << endl ; 
            // cout << picture[0].size()      << endl ; 
            // cout << picture[0][0].size()   << endl ; 
  
            output_pic.resize(1) ; 
            for (auto& v : output_pic) v.resize(output_cha_size) ; 
            for (auto& v : output_pic) 
              for (auto& w : v) w.resize(1) ;
              
          }else {
            picture.resize(input_size) ; 
            for (auto& v : picture) v.resize(input_size) ; 
            for (auto& v : picture) 
              for (auto& w : v) w.resize(input_cha_size) ; 
              
            weight.resize(weight_size) ; 
            for (auto& v : weight) v.resize(weight_size) ; 
            for (auto& v : weight) 
              for (auto& w : v) w.resize(input_cha_size) ; 
            for (auto& v : weight) 
              for (auto& w : v) 
                for (auto& x : w) x.resize(output_cha_size) ; 
        
            bias.resize(output_cha_size) ; 
        	  
            output_pic.resize(output_size) ; 
            for (auto& v : output_pic) v.resize(output_size) ; 
            for (auto& v : output_pic) 
              for (auto& w : v) w.resize(output_cha_size) ;
          }
          
        }

        

        
    }else if (store_input_from_itself){
      // input 1 4096 1 
      // output 1 4096 1 
      counter = 0 ;
      count_x = 0 ;
      count_y = 0 ;
      count_z = 0 ; 
      //cout << " store_input_from_itself "  << endl ; 
      for (int i=0 ; i<input_cha_size ; i++){
         picture[0][i][0] = output_pic[0][i][0] ; 
      }
      
      store_input_from_itself = false ; 
      output_pic.resize(1) ; 
      for (auto& v : output_pic) v.resize(output_cha_size) ; 
      for (auto& v : output_pic) 
        for (auto& w : v) w.resize(1) ;
      
    }else if (store_input_from_router){
      //cout << " store_input_from_router "  << endl ; 
      x_max =  picture.size()  ; 
      y_max =  picture[0].size() ; 
      z_max =  picture[0][0].size()  ;
      
      if ( router_in_data -> nb_read (value)) {
         picture[count_x][count_y][count_z] = value ;
         in_layer_target -> nb_read(temp) ; 
        if (count_y == y_max -  padding_size - 1 ) {  // 226 227 for padding
          count_y = padding_size ; 
          if (count_x == x_max - padding_size - 1 ) { // 226 227 for padding
              count_x = padding_size ;
              if (count_z == z_max - 1){
                count_z = 0 ;
                store_input_from_router = false ; 
                // cout << x_max << " , " << y_max << " , " << z_max << endl ;
                // cout << "store_input_from router done " << endl ; 
                count_x = 0 ;
                count_y = 0 ; 
                counter = 0 ;
              }else{
                count_z ++ ; 
              }
          }else{
              count_x ++ ;
          }
        }else{
          count_y ++ ; 
        } 
      }
    }else if (store_input){
      x_max =  picture.size()  ; 
      y_max =  picture[0].size() ; 
      z_max =  picture[0][0].size()  ; 
      //cout << x_max << " " << y_max << " "  << z_max  << endl ; 
      // store input
      if (counter != (x_max-2*padding_size) * (y_max-2*padding_size) * (z_max) ){ // total 150528 parameters
         if ( rom_rd -> nb_write (1) ){
           rom_addr -> write (counter) ; 
          now_layer -> write (now_index) ; 
          counter ++ ; 
          //cout << counter <<" " << now_index << endl  ;
       }
      }else{
         //cout << counter <<endl ;
      }

      if ( data_in -> nb_read (value)) {
      
      
      
        //cout << value << endl ; 
        if (MODE == 2 )
          value = value /255 ; 
        picture[count_x][count_y][count_z] = value ;

        if (count_y == y_max -  padding_size - 1 ) {  // 226 227 for padding
          count_y = padding_size ; 
          if (count_x == x_max - padding_size - 1 ) { // 226 227 for padding
              count_x = padding_size ;
              if (count_z == z_max - 1){
                count_z = 0 ;
                store_input = false ; 
                //cout << "store_input done " << endl ; 
                //cout << (x_max-2*padding_size) * (y_max-2*padding_size) * (z_max)   << endl ; 
                counter = 0 ;
                count_x = 0 ;
                count_y = 0 ; 
                if (now_index == 0) 
                  now_index = now_index + 1 ;
              }else{
                count_z ++ ; 
              }
          }else{
              count_x ++ ;
          }
        }else{
          count_y ++ ; 
        } 
      }

    }else if ( (store_weight || store_bias )){
      // store weight 
        
        x_max =  weight.size()  ; 
        y_max =  weight[0].size() ; 
        z_max =  weight[0][0].size()  ; 
        channel_max =  weight[0][0][0].size() ; 
        
        //cout << "counter " <<  counter << endl ; 
        //cout << "now_index " <<  now_index << endl ; 
                
        if (counter != ( x_max* y_max * z_max * channel_max  + channel_max) ){ // total 23296 parameters   3
          if ( rom_rd -> nb_write (1) ){
            //cout << counter << " " << now_index << " "; 
            
            rom_addr -> write (counter) ; 
            now_layer -> write (now_index) ; 
            counter ++ ; 
            
           // cout << counter <<" " << count_x << " " << count_y << " " << count_z << " " <<  count_output_ch  << endl  ;
          }
        }else{
          // cout << counter ; 
        }
       if ( data_in -> nb_read (value)) {
          //cout << value << endl ; 
         // if (counter == 0 ){
          //  cout << count_x << " " << count_y << " " << count_z << endl ;
         // }
          if (store_weight){
              weight[count_x][count_y][count_z][count_output_ch] = value ; 
              if (count_y == y_max -1 ) {  
                count_y = 0 ; 
                if (count_x == x_max -1 ) { 
                    count_x = 0 ;
                    if (count_z == z_max -1 ){
                      count_z = 0 ;
                      if (count_output_ch == channel_max -1){
                          count_output_ch = 0 ;
                          store_weight = false ; 
                          count_x = 0 ;
                          count_y = 0 ;
                          //cout << "store_weight _ done " << endl ;
                      }else{
                          count_output_ch ++ ; 
                      }
                      
                    }else{
                      count_z ++ ; 
                    }
                }else{
                    count_x ++ ;
                } 
              }else{
                count_y ++ ; 
              } 
          }else{
              //cout << count_output_ch << "  : index : " << now_index << "  counter : " << counter<< " "  << value << endl ; 
              
              bias[count_output_ch] = value ; 
              count_output_ch++ ; 
              if (count_output_ch == output_cha_size){
                store_bias = false ; 
                count_output_ch = 0 ;
                counter = 0 ;
                //cout << ( x_max* y_max * z_max * channel_max  + channel_max)    << endl ; 
                //cout << "store_bias done" << endl ;
              }
            
          }
        }
    }else if (is_conv ){
      // conv 
      cout << "convolution : " << endl ; 
      //float picture[228][228][3] ; 
	    //float weight [11][11][3][64] ; 
      //float output_pic[55][55][64] ; 

      // cout << output_pic.size() << endl ; 
      // cout << output_pic[0].size() << endl ; 
      // cout << output_pic[0][0].size() << endl ; 
      for (int out_ch = 0; out_ch < output_cha_size ; out_ch ++ ){
        for (int i=0 ; i < output_size ; i ++ ){
          for (int j=0 ; j < output_size; j ++ ){
            result = 0 ;
              for (int in_ch=0 ; in_ch < input_cha_size ; in_ch++){
                for (int w_i =0 ; w_i < weight_size ; w_i ++){
                  for (int w_j=0 ; w_j < weight_size ; w_j++){
                    //cout << i << " " <<  j << " "<< w_i << " "<< w_j << " "<< in_ch << " "<<  out_ch << endl ; 
                   
                    result = result + picture[i*stride_size + w_i][j*stride_size + w_j][in_ch] * weight[w_i][w_j][in_ch][out_ch] ;
                    //wait(2,SC_NS) ;  
                    //cout << sc_time_stamp() << endl ;
                    //if ( i==0 && j==0 && (w_i < 11 ) && (w_j < 11) && out_ch==1 ) {
                      //cout << result << " " ; 
                      //cout << picture[i*stride_size + w_i][j*stride_size + w_j][in_ch] * weight[w_i][w_j][in_ch][out_ch]  << " "  ;
                    //}
                  }
                  //if ( i==0 && j==0  && out_ch==1 )
                  //cout << endl ;
                }
              }
            result = result + bias[out_ch] ; 
            if (result < 0 )
              output_pic[i][j][out_ch] = 0 ; 
            else  
              output_pic[i][j][out_ch] = result ; 
            }
          }
        } 
      //sc_stop() ; 
      // for (int i=0 ; i<64  ; i++)
      //    cout << bias[i] << endl ;  

      // cout bias
      /*
      if ( now_index == 2 ){
        for (int j=0 ; j < output_cha_size ; j++){
            cout << bias[j] << endl; 
        }
        sc_stop() ; 
      }
*/
      // cout weight
      /*
      if (now_index == 2 ){
        //cout << output_cha_size << endl ; 
        //cout << input_cha_size << endl ; 
        //cout << weight_size << endl ; 
        //sc_stop() ; 
        for (int out_ch = 0; out_ch < output_cha_size ; out_ch ++ ){
          for (int in_ch=0 ; in_ch < input_cha_size ; in_ch++){
            for (int i =0 ; i < weight_size ; i ++){
              for (int j=0 ; j < weight_size ; j++){
                cout << weight[i][j][in_ch][out_ch] << endl; 
              }
              //cout << endl ;
            }
          }
        }
        sc_stop() ; 
      }
      */

      // cout input picture ; 
    /*
      if (now_index == 1 ){
        //cout << input_cha_size << endl ; 
        //cout << output_size << endl ; 
        for (int in_ch=0 ; in_ch < input_cha_size ; in_ch++){
          for (int i =0 ; i < input_size; i ++){
            for (int j=0 ; j < input_size ; j++){
              cout << picture[i][j][in_ch] << " "; 
            }
            cout << endl ;
          }
        }
        sc_stop() ; 
      }*/

      // cout output
      /*
      if (now_index == 2 ){
        for (int out_ch=0 ; out_ch < output_cha_size ; out_ch++){
          for (int i =0 ; i < output_size ; i ++){
            for (int j=0 ; j < output_size ; j++){
              cout << output_pic[i][j][out_ch] << " " ; 
            }
            cout << endl ;
          }
        }
        sc_stop() ; 
      }*/
      
      //}
      
      //cout << endl ; 
      //cout << "output_pic : "  <<  output_pic[0][0][1] << endl ;
      //cout << bias[0] ;
      count_x = 0 ;
      count_y = 0 ; 
      count_z = 0 ;
      is_conv = false ; 
      //cout << " convolution done " << endl ; 
      now_index = now_index +1  ; 
      //conv_done = true ;
      //sc_stop() ; 
    }else if( is_maxpool ){
       // max_pooling
       
       // maxpool size 
       // stride_size 
       // input size
       // input channel size
       // output size ; 
       // output channel size ; 
       cout << " maxpool  " << endl ; 
       /*
       cout <<  " max_pool_size  : " << max_pool_size << endl ; 
       cout <<  " input_size  : " << input_size << endl ; 
       cout <<  " stride_size  : " << stride_size << endl ; 
       cout <<  " input_cha_size  : " << input_cha_size << endl ; 
       cout << " output_cha_size : " << output_cha_size << endl ;
       cout <<  " output_size  : " << output_size << endl ;  
       
       cout << output_pic.size() << endl ; 
       cout << output_pic[0].size() << endl ; 
       cout << output_pic[0][0].size() << endl ; 
       */
/*
       for (int in_ch=0 ; in_ch < input_cha_size ; in_ch++){
        for (int i =0 ; i < output_size ; i ++){
          for (int j=0 ; j < output_size ; j++){
            cout << picture[i][j][in_ch] << " " ; 
          }
          cout << endl ;
        }
      }
        sc_stop() ; 
*/
       
        for (int in_ch = 0; in_ch < input_cha_size ; in_ch ++ ){
          for (int i=0 ; i < output_size ; i++){
            for (int j =0 ; j < output_size ; j ++){
               max_value = picture[i*stride_size  ][j*stride_size  ][in_ch] ;
               for (int shift_x = 0 ; shift_x<max_pool_size ; shift_x++){
                   for (int shift_y = 0 ; shift_y<max_pool_size ; shift_y++){
                    if ( max_value < picture[i*stride_size + shift_x ][j*stride_size + shift_y][in_ch] )
                        max_value = picture[i*stride_size + shift_x ][j*stride_size + shift_y][in_ch]  ;
                    
                  }
               }
               output_pic[i][j][in_ch] = max_value ; 
            }
          }
        }
        //cout << 123123 << endl ; 
        is_maxpool = false ; 
        //cout << " maxpool done " << endl ; 
        // should be revised 
        count_x = 0 ;
        count_y = 0 ; 
        count_z = 0 ;
        /*
      if (now_index == 3){
        for (int in_ch=0 ; in_ch < input_cha_size ; in_ch++){
          for (int i =0 ; i < output_size ; i ++){
            for (int j=0 ; j < output_size ; j++){
              cout << output_pic[i][j][in_ch] << endl ; 
            }
          }
        }
          sc_stop() ;
      }*/
        
    }else if (is_dense) {
        // picture 1    9216 1 
        // weight  9216 4096 1 1 
        // output  1    4096 1
        //cout << " is dense " <<endl ; 
        
        //cout << output_size << endl ; 
        //cout << input_size << endl ; 
        cout << "Fully_connect " <<endl ;
        //for (int i=0 ; i< input_size ; i++ ){
        //    cout << picture[0][i][0] <<endl ; 
        //}
        // cout << weight.size() << endl ; 
        // cout << weight[0].size() << endl ; 
        // cout << weight[0][0].size() << endl ; 
        // cout << weight[0][0][0].size() << endl ;

        for (int out=0 ; out < output_cha_size ; out++ ){
          result = 0 ;
          for (int i=0 ; i< input_cha_size ; i++ ){
             //cout << i << " , " << out << endl ;
             result = result + picture[0][i][0] * weight[ 0 ] [ 0 ][i][out] ; 
          }
          
          result = result + bias [out] ;
          // 1 4096 1 
          if(now_index == MAX_LAYER || result >= 0)
            output_pic[0][out][0] = result ;
          else
            output_pic[0][out][0] = 0 ;
        }
        
        is_dense = false ; 
       // cout << " dense done " << endl ;  
        now_index = now_index +1  ; 
        count_x = 0 ;
        count_y = 0 ;
        count_z = 0 ;
      //for (int out=0 ; out < output_size ; out++){
      //      cout << output_pic[0][out][0] << endl ; 
      //}
       // sc_stop() ;
       // sc_stop() ;  
    }else if (writing_data){  
      //   now_index       0,1              2                       3                         
            //         conv (PE1) -> max_pooling (PE3) -> conv (PE1) -> max_pooling (PE3)
      //   now_index        3               4               5                6          
            //      -> conv (PE1) -> conv(PE2)         -> conv (PE1) -> max_pooling (PE3)
      //   now_index        6               7               8      
            //      -> dense(PE4) -> dense (PE4)       -> dense(PE4)

        //cout << "writing_data" << endl ; 
        x_max =  output_pic.size()  ; 
        y_max =  output_pic[0].size() ; 
        z_max =  output_pic[0][0].size()  ; 
        
        //if ( count_x == 0 && count_y == 0 && count_z == 0)
        //  cout << "start write " << endl ; 

        value = output_pic[count_x][count_y][count_z] ; 
        if (out_data -> nb_write(value) ){
          // if successful writing
          //cout << " write : " << endl ; 
          // type , now layer  : decide the next operation
          // 10 = 2   // x = 1 
          // 01 = 1   // y = 1 
          if (type.read() == 0){ // PE1
            if (now_index == 4 ){  // go to PE2
              out_target_val = 2 ; 
              
            }else{                  // go to PE3
              out_target_val = 1 ;
            } 
          }else if (type.read() == 1 ){   // PE2 
            out_target_val = 2 ; 
            //cout << "
          }else if (type.read() == 2 ){   // PE3
            if (now_index == MAX_LAYER -2  ){  // go to PE4
              out_target_val = 2 ;
            }else{                  // go to PE1
              out_target_val = 1 ;
            } 
          }else {
             cout << " dense should not do writing " << endl ; 
             sc_stop() ; 
          }
         
          temp = (now_index , out_target_val ) ; 
          
          out_layer_target -> write(temp) ; 
          
          if (count_y == y_max  - 1 ) {  // 226 227 for padding
            count_y = 0 ; 
            if (count_x == x_max - 1 ) { // 226 227 for padding
                count_x = 0 ;
                if (count_z == z_max - 1){
                  writing_data = false ; 
                  //cout << "write data to router done " << endl ; 
                  count_z = 0 ;
                  
                }else{
                  count_z ++ ; 
                }
            }else{
                count_x ++ ;
            }
          }else{
            count_y ++ ; 
          } 

        }

        //sc_stop() ; 
    
    
    }else if (write_to_monitor){
       value =  output_pic[0][count_y][0] ;
       if (data_out -> nb_write(value) ){
          data_out_signal -> write(true) ; 
          count_y++ ; 
          if (count_y == output_size)
             write_to_monitor = false ; 
       }
    }else{
       // idle 
       
       if (type.read() == 0 ){
          set_type    = true ; 
          store_input_from_router = true ; 
          store_weight = true ; 
          store_bias   = true ;
          is_conv = true ;
          writing_data =true ; 
          
          // cout << endl << endl ; 
          // cout << " PE1 finish" << endl ; 
          // cout << endl << endl ; 
          
        }else if (type.read() == 1 ){
          set_type    = true ; 
          store_input_from_router = true ; 
          store_weight = true ; 
          store_bias   = true ;
          is_conv = true ;
          writing_data =true ; 
          
          // cout << endl << endl ; 
          // cout << " PE2 finish" << endl ; 
          // cout << endl << endl ; 
          
        }else if (type.read() == 2 ){
          set_type    = true ; 
          store_input_from_router = true ; 
          store_input = false ;
          store_weight = false ; 
          store_bias   = false ; 
          
          is_conv = false ;
          is_maxpool = true ; 
          is_dense = false ;  
          writing_data =true ; 
          
          // cout << endl << endl ; 
          // cout << " PE3 finish" << endl ; 
          // cout << endl << endl ; 
        }else if (type.read() == 3 ){
          set_type    = true ; 
          store_input_from_itself = true  ;
          store_input_from_router = false ; 
          store_input = false ;
          store_weight = true ; 
          store_bias   = true ; 
          
          is_conv = false ;
          is_maxpool = false ; 
          is_dense = true ;  
          writing_data = false ;
          // cout << endl << endl ; 
          // cout << " PE4 finish" << endl ; 
          // cout << endl << endl ; 
          if (now_index == MAX_LAYER ){
            write_to_monitor = true ; 
          }
        }
    
    }
  }
 
   
  }
	// ^^^^^ put your code here ^^^^^
}



