OPENCV_SOURCE=~/Developer/workspaces/cpp/opencv-2.4/
CC=clang
CXX=clang++
CPP=${CXX}
C++=${CXX}

.PHONY: build

build:
	rm -rf build; \
	mkdir build; \
	cd build; \
	cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ../; \
	make;

install:
	cp build/image-detect /usr/local/bin

build-opencv-2:
	cd ${OPENCV_SOURCE}; \
	rm -rf build; \
	mkdir build; \
	cd build; \
	cmake ../ -DBUILD_SHARED_LIBS=OFF; \
	make; \
	make install;

run-sample:
	image-detect \
	./extras/images/screen.png \
	./extras/images/detect.png \
	./extras/images/diff.png

run-sample-double-detect:
	image-detect \
	./extras/images/screen-double.png \
	./extras/images/detect.png \
	./extras/images/diff-screen-double.png

run-sample-no-detect:
	image-detect \
	./extras/images/screen.png \
	./extras/images/no-detect.png \
	./extras/images/diff.png

build-go-sample:
	# swig -go -cgo -c++ -intgosize 64 -I${IMAGE_DETECT_HOME}/lib/include go-sample/image-detect.i 
	
	CGO_CFLAGS="-I${IMAGE_DETECT_HOME}/lib/include"; \
	CGO_LDFLAGS="-L${IMAGE_DETECT_HOME}/build -limage-detect"; \
	go build go-sample/main.go -o go-sample/image-detect