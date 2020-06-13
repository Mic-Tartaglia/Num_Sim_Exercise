CC = g++
CFLAGS = -Wall -O3 --std=c++11

es8.2.exe : es8.2.o random.o
	$(CC) random.o es8.2.o -o es8.2.exe
es8.2.o : es8.2.cpp
	$(CC) -c es8.2.cpp -o es8.2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es8.2.exe seed.out
exec: es8.1.exe
	./es8.2.exe
