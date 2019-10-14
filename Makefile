outfile:= libpipe.so
ARCH := $(shell getconf LONG_BIT)
path:=./bin/linux/x$(ARCH)/$(outfile) 
libpipe1.so: ./src/PipeWrapper.o ./src/PipeWriter.o
	g++  -std=c++11 -fPIC -shared ./src/PipeWriter.o ./src/PipeWrapper.o  -g -o $(path)
PipeWriter.o: ./src/PipeWriter.cpp
	g++ -c -fPIC -g -std=c++11 PipeWriter.cpp
PipeWrapper.o: ./src/PipeWrapper.cpp
	g++ -c -fPIC -g -std=c++11 PipeWrapper.cpp
.PHONY:clean
clean:
	cd ./src
	rm -rf *.o
	rm $(path)
