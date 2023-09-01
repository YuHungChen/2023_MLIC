#include "Monitor.h"


void Monitor:: monitor() {
	bool nb_bool ; 
	if ( rst ) {
		x = 0;
		y = 0;
    //if (!is_reset)
		//  cout << "Result: " << endl;
    //is_reset = true ; 
		return;
	}
	else if ( data_in_signal -> nb_read(nb_bool) ) {
		data_value =  data_in -> read() ; 
		cout << data_value << "  ==> " <<  type[y] <<endl ;
		if (data_value > best_value){
			best_value = data_value ; 
			best_index = y ;
		}

		x = x + 1;
		if ( x == 1 ) {
			x = 0;
			y = y + 1;
			cout << endl;
			if ( y == OUT_CLASS_NUM ) {
        cout << sc_time_stamp() << endl ;
				cout << " The largest value : " << endl ;
				cout << best_value << "  ==> " <<  type[best_index] <<endl ;
				sc_stop();
			}
		}		
  }
}


