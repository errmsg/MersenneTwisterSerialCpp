#define __CL_ENABLE_EXCEPTIONS // Needed for try/catch blocks
#define LENGTH 20
#define TYPE unsigned long
#include <iostream>
#include <OpenCL/opencl.h>
// OpenCL 1.2 Khronos C++ wrapper
#include <OpenCL/cl.hpp>
// Utility for loading the program
#include "../include/utilities.hpp"

int main(int argc, char* argv[]) {

  // Input and output vectors
  std::vector<TYPE> stateVector(LENGTH);
  std::vector<TYPE> resultsVector(LENGTH);
  std::vector<TYPE> testVector(LENGTH,0xdeadbeef);
  std::vector<TYPE> len(1); // Only holds length value

  // initialize with defaul seed or input argument
  if(argc != 2) {
    stateVector[0] = 125ULL;
    std::cout << "Using default seed value: " << 125ULL << std::endl;
  } else {
    stateVector[0] = (unsigned long long) std::stoi(argv[1]);

  }
  for (int i = 1; i<LENGTH;i++){
    stateVector[i] = i;
  }

  // Device memeories
  cl::Buffer inputBuffer; // Used for copying stateVector
  cl::Buffer outputBuffer; // Used for copying resultsVector
  cl::Buffer lengthBuffer;

  try {
    // Create a context for GPU device
    cl::Context contextObj(CL_DEVICE_TYPE_GPU);
    unsigned int max_size;
    std::vector<cl::Device> devices = contextObj.getInfo<CL_CONTEXT_DEVICES>();
    // Create program and load the kernel file
     cl::Program programObj(contextObj, utilities::loadProgram("initWithSeed_kernel.cl"), false);

    try {
      programObj.build();

    }
    catch (cl::Error error){
         std::cout << programObj.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]) << "\n";
         throw error;
       }

    // Create command queue
    cl::CommandQueue queueObj(contextObj);
    // Make kernel
    cl::Kernel kernel;
    kernel = cl::Kernel(programObj,"initWithSeed_kernel");
    max_size = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0]);
    std::cout << "Max size is: " << max_size << std::endl;

    int nwork_groups = 2;
    int work_group_size = 10;
    cl::NDRange global(nwork_groups * work_group_size);
    cl::NDRange local(work_group_size);


    inputBuffer = cl::Buffer(contextObj, CL_MEM_READ_WRITE, sizeof(TYPE) * LENGTH);
    outputBuffer = cl::Buffer(contextObj, CL_MEM_READ_WRITE, sizeof(TYPE) * LENGTH);
    lengthBuffer = cl::Buffer(contextObj, CL_MEM_READ_ONLY, sizeof(int));
    cl::copy(queueObj, stateVector.begin(), stateVector.end(), inputBuffer);
    cl::copy(queueObj, len.begin(), len.end(),lengthBuffer);

    kernel.setArg(0, inputBuffer);
    kernel.setArg(1, outputBuffer);
    kernel.setArg(2, lengthBuffer);

    queueObj.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);


    // Wait for kernels to finish
    queueObj.finish();
    // Retirive outputBuffer by copying to outputTestVector
    cl::copy(queueObj, outputBuffer, testVector.begin(),testVector.end());
    // Output the results
    for(int i = 0; i<LENGTH; i++){
      std::cout <<  testVector[i] << std::endl;
    }

  }
  catch (cl::Error err) {
      // Handle exceptions
      std::cout << "Exception\n";
      std::cerr << "errmsg: " << err.what() << std::endl;
  }
}
