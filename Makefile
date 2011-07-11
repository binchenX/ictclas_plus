
#build the ict test
icttest: test_ictclas.c libict 
	g++ -o test_ictclas -g test_ictclas.c -L./ -lictclas
	#ictclas < chinese.raw.txt > chinese.seg.txt

#build fts test code
ftstest: libfts
	g++ -o test_fts -I/usr/local/include  test_ftsict.c -L/usr/lib/trident/ -lsqlite3 -lpthread -ldl


#build ftsict extention lib
libfts: fts3_ictclas.c libict 
	g++ -fPIC -I/usr/local/include -I./Source -c fts3_ictclas.c
	g++ -shared -o libftsict.so fts3_ictclas.o -L./ -lictclas

#build citclas library
libict: Source/*.cpp
	cd Source; g++ -g -fPIC -c  *.cpp
	cd Source; g++ -shared -o ../libictclas.so *.o
	#cd Source; ar -r ictclas.a *.o

clean:
	rm test_fts -fv 
	rm test_ictclas -fv 
	rm ./libictclas.so
	rm ./libftsict.so
	rm ./Source/*.o 
