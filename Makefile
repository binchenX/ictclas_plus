
#build the test
all: test.c sharelib
	g++ -o ictclas test.c -L./Source/ -lictclas
	ictclas < chinese.raw.txt > chinese.seg.txt


lib: fts3_ictclas.c Source/ictclas.a
	g++ -o -fPIC -I/usr/local/include -c fts3_ictclas.c
	g++ -shared -o libftsict.so fts3_ictclas.o -L./Source -lictclas

#build the library
sharelib: Source/*.cpp
	cd Source; g++ -fPIC -c  *.cpp
	cd Source; g++ -shared -o libictclas.so *.o
	#cd Source; ar -r ictclas.a *.o

clean:
	rm ictclas 
	rm ./Source/libictclas.so
	rm ./Source/*.o 
