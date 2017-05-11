

all:
	gcc -Wall -fPIC -DPIC -I/share/apps/cudatoolkit-7.5/include/ -c count_device.c -lstdc++ -lcuda -lcuda_runtime
	ld -shared -o count_device.so count_device.o -ldl

clean:
	rm -rf count_device.{o,so}

