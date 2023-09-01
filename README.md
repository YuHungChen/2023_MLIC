## Final project:
* Create an 2*2 mesh NoC model, which is topology-aware model. and it can apply on AlexNet and LeNet successfully

## Block diagram description:
* My NoC architecture has a total of 4 PEs and 4 routers, each PE has its own independent router
* In my design, PE can do convolution, Max pooling, and Fully connected. 
* For each router, it has X-direction and Y-direction routers.
![image](https://github.com/YuHungChen/2023_MLIC/assets/120573862/25087826-ab76-49fd-b1dc-85ab8e9f86cf)

## Block diagram of PE and router 
* PE
![image](https://github.com/YuHungChen/2023_MLIC/assets/120573862/1e1759b7-d54d-4a9d-96af-0a3c602a5fa3)

* Router
![image](https://github.com/YuHungChen/2023_MLIC/assets/120573862/1bb583a7-2ee0-4323-85c0-f2f624a53add)

## topology-aware model:
* I made result of LeNet and AlexNet. Because the two architectures are very similar
* As long as you tell me the size of each layer of them, you can successfully execute it in this NOC
* Result
![image](https://github.com/YuHungChen/2023_MLIC/assets/120573862/ee0ccbf0-0f9c-45a4-91ca-5d59713b793a)


## how to compile:
  * make
## how to execute:
  * ./LAB

## mode switch:
* open mode.h file to change the path of the user-defined picture and the mode for AlexNet and LeNet
