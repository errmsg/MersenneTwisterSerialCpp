__kernel void times_two_kernel(__global float* input, __global float* output){
int i = get_global_id(0);
output[i] = 2.0f * input[i];
}
