#ifndef MODE_H
#define MODE_H

// mode can be revised here
#define MODE 2

#if (MODE == 1 )  // AlexNet
	#define  INPUT_FILE "/home/ML310580023/final_project/input_pattern/input_plane.txt"
//  #define  INPUT_FILE "/home/ML310580023/final_project/input_pattern/input_cat.txt"
//  #define  INPUT_FILE "/home/ML310580023/final_project/input_pattern/input_dog.txt"
	#define  MAX_LAYER 8
	#define  OUT_CLASS_NUM 1000 
#elif (MODE == 2 )  // Lenet  
	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input1.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input2.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input3.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input4.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input5.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input6.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input7.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input8.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input9.txt"
//	#define  INPUT_FILE "/home/ML310580023/final_project_lenet/input_pattern/input10.txt"
	#define  MAX_LAYER 5
	#define  OUT_CLASS_NUM 10
#endif

#endif

