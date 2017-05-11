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


cudaError_t (*orig_cudaMemcpy)( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind );

__host__
cudaError_t cudaMemcpy ( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind ) {
        FILE *f = fopen("deviceCounter.txt", "a");
        fprintf(f, "Memcpy: %p -> %p   [%d]\n", src, dst, (int)count);
        fclose(f);

	return orig_cudaMemcpy(dst, src, count, kind);
}





void _init(void) {
	printf("---------========== Loading overloaded CUDA functions...  ==============---------------\n");
	orig_cudaSetDevice = (cudaError_t (*)(int)) dlsym(RTLD_NEXT, "cudaSetDevice");
        orig_cudaMemcpy = (cudaError_t (*)(void*, const void*, size_t , enum cudaMemcpyKind)) dlsym(RTLD_NEXT, "cudaMemcpy");

}

