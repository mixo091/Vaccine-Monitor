
VaccineMonitor: main.o ProgrammFunctionality.o  SpecialDataStructures.o DataStructures.o  
	g++ main.o ProgrammFunctionality.o  SpecialDataStructures.o DataStructures.o -o VaccineMonitor

main.o: main.cpp
	g++ -c main.cpp

ProgrammFunctionality.o: ProgrammFunctionality.cpp ProgrammFunctionality.h
	g++ -c ProgrammFunctionality.cpp

SpecialDataStructures.o: SpecialDataStructures.cpp DataStructures.h
	g++ -c SpecialDataStructures.cpp

DataStructures.o: DataStructures.cpp DataStructures.h
	g++ -c DataStructures.cpp
clean:
	rm*.o VaccineMonitor