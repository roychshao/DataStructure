CXX = g++
CFLAG = -Wall -g

all: RoadModel_bheap RoadModel_array

RoadModel_bheap: pbPlots.o supportLib.o RoadModel_bheap.cc
	$(CXX) $(CFLAG) RoadModel_bheap.cc pbPlots.o supportLib.o -o RoadModel_bheap

RoadModel_array: pbPlots.o supportLib.o RoadModel_array.cc
	$(CXX) $(CFLAG) RoadModel_array.cc pbPlots.o supportLib.o -o RoadModel_array

pbPlots.o: pbPlots.cpp
	$(CXX) $(CFLAG) -c pbPlots.cpp

supportLib.o: supportLib.cpp
	$(CXX) $(CFLAG) -c supportLib.cpp

clean:
	rm *.o RoadModel_bheap RoadModel_array
