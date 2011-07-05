
#build the test
all: test.c Source/ictclas.a
	gcc -o ictclas test.c Source/ictclas.a
	ictclas < chinese.raw.txt > chinese.seg.txt


#build the library
Source/ictclas.a: Source/*.cpp
	cd Source; g++ -c *.cpp
	cd Source; ar -r ictclas.a *.o

clean:
	rm ictclas 
	rm ./Source/ictclas.a 
	rm ./Source/*.o 
