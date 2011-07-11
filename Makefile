
#build the test
all: test_ictclas.c sharedlib
	g++ -o test_ictclas -g test_ictclas.c -L./ -lictclas
	#ictclas < chinese.raw.txt > chinese.seg.txt


fts: lib
	g++ -o test_fts -I/usr/local/include  test_ftsict.c -L/usr/lib/trident/ -lsqlite3 -lpthread -ldl

lib: fts3_ictclas.c sharedlib 
	g++ -fPIC -I/usr/local/include -I./Source -c fts3_ictclas.c
	g++ -shared -o libftsict.so fts3_ictclas.o -L./ -lictclas

#build the library
sharedlib: Source/*.cpp
	cd Source; g++ -g -fPIC -c  *.cpp
	cd Source; g++ -shared -o ../libictclas.so *.o
	#cd Source; ar -r ictclas.a *.o

clean:
	rm ictclas 
	rm ./Source/libictclas.so
	rm ./Source/*.o 
