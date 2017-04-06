LDFLAGS=-L/usr/lib/x86_64-linux-gnu -lpng12 
CFLAGS=-I/usr/include/libpng12

RotateImage: RotateImage.o
	g++ -o RotateImage RotateImage.o $(LDFLAGS) 

RotateImage.o: RotateImage.cpp
	g++ $(CFLAGS) -c RotateImage.cpp

.PHONY: clean

clean:
	rm *.o RotateImage
