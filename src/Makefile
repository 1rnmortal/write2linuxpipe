outfile:= libpipe.so
ARCH := $(shell getconf LONG_BIT)
libpipe1.so: PipeWrapper.o PipeWriter.o
	g++  -std=c++11 -fPIC -shared PipeWriter.o PipeWrapper.o  -o ../bin/linux/x$(ARCH)/$(outfile) 
PipeWriter.o: PipeWriter.cpp
	g++ -c -fPIC -std=c++11 PipeWriter.cpp
PipeWrapper.o: PipeWrapper.cpp
	g++ -c -fPIC -std=c++11 PipeWrapper.cpp

.PHONY:clean
clean:
	rm -rf *.o
	rm $(outfile)
