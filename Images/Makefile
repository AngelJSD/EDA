GCC = g++
CXXFLAGS = -std=c++11 -pthread -o main.o

OPENCV = -I/usr/include/opencv -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lGL -lGLU -lrt -lpthread -lm -ldl

m1:
	@$(GCC) $(CXXFLAGS) $(OPENCV) main.cpp

m2:
	@$(GCC) $(CXXFLAGS) $(OPENCV) main1.cpp

clean:
	rm main.o
