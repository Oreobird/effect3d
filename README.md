# effect3d
A 3D effect demo based on yolact using NCNN.

Project build:
	mkdir build
	cd build && cmake ..
	make
	
Usage:
	./effect3d --file hand.wmv --video hand3d.mp4 --detector yolact --effect lr --target person
