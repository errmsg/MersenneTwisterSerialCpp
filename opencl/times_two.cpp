#define __CL_ENABLE_EXCEPTIONS
#define LENGTH 10
#include <iostream>
#include <OpenCL/opencl.h>
// OpenCL 1.2 Khronos C++ wrapper
#include <OpenCL/cl.hpp>
// Utility for loading the program
#include "../include/utilities.hpp"

int main() {

  // Input and output vectors
  std::vector<float> inputVector(LENGTH);
  std::vector<float> outputVector(LENGTH);
  std::vector<float> outputTestVector(LENGTH);

  // Device memeories
  cl::Buffer inputBuffer;
  cl::Buffer outputBuffer;

  // Fill the input vector
  for (int i=0; i < LENGTH; i++) {
    inputVector[i] = (float) i;
  }

  try {
    // Create a context
    cl::Context contextObj(CL_DEVICE_TYPE_DEFAULT);
    // Create program and load the kernel file
    cl::Program programObj(contextObj, utilities::loadProgram("times_two_kernel.cl"), true);
    // Create command queue
    cl::CommandQueue queueObj(contextObj);
    // Make kernel
    cl::make_kernel<cl::Buffer, cl::Buffer> times_two(programObj, "times_two_kernel");
    // Allocate buffers for gpu memory
    inputBuffer = cl::Buffer(contextObj, inputVector.begin(),inputVector.end(),true);
    outputBuffer = cl::Buffer(contextObj, outputVector.begin(),outputVector.end(),true);
    // Set kernel arguments
    times_two(cl::EnqueueArgs(queueObj, cl::NDRange(LENGTH)),inputBuffer, outputBuffer);
    // Wait for kernels to finish
    queueObj.finish();
    // Retirive outputBuffer by copying to outputTestVector
    cl::copy(queueObj, outputBuffer, outputTestVector.begin(),outputTestVector.end());
    // Check the results
    for (int i=0; i < LENGTH; i++) {
      if(outputTestVector[i] == (2.0 * inputVector[i])){
      std::cout << outputTestVector[i] << " correct!" <<std::endl;
    } else {
        std::cerr << "Test has failed!" << std::endl;
        exit(1);
      }
    }
  }
  catch (cl::Error err) {
      // Handle exceptions
      std::cout << "Exception\n";
      std::cerr << "errmsg: " << err.what() << std::endl;
  }
}
