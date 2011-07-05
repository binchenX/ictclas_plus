#chinese.seg.txt: chinese.raw.txt ictclas
#	ictclas < chinese.raw.txt > chinese.seg.txt

all: main.cpp Source/ictclas.a
	g++ -o ictclas main.cpp Source/ictclas.a

Source/ictclas.a: Source/*.cpp
	cd Source; g++ -c *.cpp
	cd Source; ar -r ictclas.a *.o

clean:
	rm ictclas 
	rm ./Source/ictclas.a 
	rm ./Source/*.o 
