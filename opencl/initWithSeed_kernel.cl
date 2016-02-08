__kernel void initWithSeed_kernel(__global ulong* input, __global ulong* output, __global int *length){
int i = get_global_id(0);
if(i>length)
return;
ulong x = input[i];
//output[i] = input[i] << 5;
//output[i] =  (6364136223846793005UL * (output[i-1] ^ (output[i-1] >> 62)) + i);
x ^= (x >> 29) & 0x5555555555555555ULL;
x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
x ^= (x << 37) & 0xFFF7EEE000000000ULL;
x ^= (x >> 43);
x = x >> 1;
output[i] = x;
}
