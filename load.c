#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main (int argc, char *argv) {
  int SIZE_IN = 0x1FFF0000 , i=0, j= SIZE_IN-1, index=0;

#if defined(ALIGNED)

  uint8_t  *in_byte = (uint8_t*)malloc(sizeof(uint8_t)*SIZE_IN+16);
  if (in_byte == NULL) return 0;

  while(1) {
    if(((int64_t) &(in_byte[i]) & 0xf) == 0) break;
    i++;
  }

  uint8_t *ptr_first = (uint8_t*)&(in_byte[i]);

#else
  uint8_t  *in_byte = (uint8_t*)malloc(sizeof(uint8_t)*SIZE_IN+16);
  if (in_byte == NULL) return 0;

  while(1) {
    if(((int64_t) &(in_byte[i]) & 0xf) == 8) break;
    i++;
  }

  uint8_t *ptr_first = (uint8_t*)&(in_byte[i]);

#endif

  for (int k = 0; k < SIZE_IN; k++) in_byte[k] = k;
  for (int SIZE = 16; SIZE < SIZE_IN; SIZE = SIZE + 16*100000) {
    clock_t t;
    t = clock();
#if defined(LXVD2X)
  asm volatile (
    "li  %[index],0\n\t"
    "LOOP:\n\t"
    "lxvd2x 32,%[index],%[in]\n\t"
    "xxswapd 32,32\n\t"
    "addi %[index],%[index],16\n\t"
    "cmpw %[index],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [index] "=&b" (index)
    :
    [in] "b" (ptr_first),
    [SIZE] "b" (SIZE)
    :
    "memory","v0"
    );
#else
  asm volatile (
    "li  %[index],0\n\t"
    "lvx 0, %[index], %[in]\n\t"
    "lvsr 3, %[index], %[in]\n\t"
    "LOOP:\n\t"
    "lvx 1,%[index],%[in]\n\t"
    "vperm 2,0, 1,3\n\t"
    "vmr 0,1\n\t"
    "addi %[index],%[index],16\n\t"
    "cmpw %[index],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [index] "=&b" (index)
    :
    [in] "b" (ptr_first),
    [SIZE] "b" (SIZE)
    :
    "memory","v0","v1","v2","v3"
    );
#endif
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("%d %f\n", SIZE, time_taken);
  }

  return 0;
}
