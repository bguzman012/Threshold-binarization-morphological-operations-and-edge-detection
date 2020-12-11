

all:
	g++ Video.cpp main.cpp -I/home/bryam/opencv/include/opencv2/ -L/home/bryam/opencv/build/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio  -o vision.bin #--stdc++20

run: 
	./vision.bin

