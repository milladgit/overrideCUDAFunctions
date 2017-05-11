#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <cuda_runtime.h>


// __host__
cudaError_t (*orig_cudaSetDevice)( int  device );

 __host__
cudaError_t cudaSetDevice ( int  device ) {
	FILE *f = fopen("deviceCounter.txt", "a");
	fprintf(f, "Device ID: %d\n", device);
	fclose(f);

	return orig_cudaSetDevice(device);
}

void _init(void) {
	printf("---------========== Loading overloaded CUDA functions...  ==============---------------\n");
	orig_cudaSetDevice = (cudaError_t (*)(int)) dlsym(RTLD_NEXT, "cudaSetDevice");
}

