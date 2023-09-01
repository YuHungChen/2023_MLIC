# Final project
Create an 2*2 mesh NoC model, which is topology-aware model. and it can apply on AlexNet and LeNet successfully

# Block diagram description:
  My NoC architecture has a total of 4 PEs and 4 routers, each PE has its own independent router, and each router has X-direction,and Y-direction router. In my design, PE can do convolution, Max pooling, and Fully connected. 
  In order to prove that my architecture is a model-aware design, I made result of LeNet and AlexNet. Because the two architectures are very similar, as long as you tell me the size of each layer of them, you can successfully execute it in this NOC

# how to compile
  make
# how to execute
  ./LAB
