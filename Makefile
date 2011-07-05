
#build the test
all: test.c sharedlib
	g++ -o ictclas test.c -L./Source/ -lictclas
	ictclas < chinese.raw.txt > chinese.seg.txt


lib: fts3_ictclas.c sharedlib 
	g++ -fPIC -I/usr/local/include -I./Source -c fts3_ictclas.c
	g++ -shared -o libftsict.so fts3_ictclas.o -L./Source -lictclas

#build the library
sharedlib: Source/*.cpp
	cd Source; g++ -fPIC -c  *.cpp
	cd Source; g++ -shared -o libictclas.so *.o
	#cd Source; ar -r ictclas.a *.o

clean:
	rm ictclas 
	rm ./Source/libictclas.so
	rm ./Source/*.o 
