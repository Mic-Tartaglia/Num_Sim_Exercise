LIBS:= random.o

es3_102.exe: es3_102.cpp ${LIBS}
	g++ -o $@ $^

%.o: %.cpp %.h
	g++ -c $<

clean:
	rm *.o
