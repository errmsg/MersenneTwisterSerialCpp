
__kernel void initWithSeed_kernel(__global ulong* input, __global ulong* output, __global int *length){
int i = get_global_id(0);

// For some reason it doesn't work :)
//if(i>length)
//return;

int NN = 156;
int MM = 78;
ulong x;
ulong privateSeedVector[NN];
ulong UM = 0xFFFFFFFF80000000ULL;
ulong LM = 0x7FFFFFFFULL;
ulong MATRIX_A = 0xB5026F5AA96619E9ULL;

privateSeedVector[0] = input[i];
for(int i=1; i<NN; i++){
  privateSeedVector[i] = (6364136223846793005ULL * (privateSeedVector[i-1] ^ (privateSeedVector[i-1] >> 62)) + i);
}


for(int j=0;j<(NN-1); j++ ){
  x = (privateSeedVector[j]&UM) | (privateSeedVector[j+1]&LM);
  privateSeedVector[j] = privateSeedVector[(j + MM) % NN] ^ (x >> 1) ^ ((x & 0x1UL) ? MATRIX_A : 0x0UL);
  x = (privateSeedVector[NN - 1] & UM) | (privateSeedVector[0] & LM);
  privateSeedVector[NN - 1] = privateSeedVector[MM - 1] ^ (x >> 1) ^ ((x & 0x1UL) ? MATRIX_A : 0x0UL);
  }


  x = privateSeedVector[0];
  x = x ^ (x >> 29) & 0x5555555555555555ULL;
  x = x ^ (x << 17) & 0x71D67FFFEDA60000ULL;
  x = x ^ (x << 37) & 0xFFF7EEE000000000ULL;
  x = x ^ (x >> 43);
  x = x >> 1;
  output[i] = x;
}
