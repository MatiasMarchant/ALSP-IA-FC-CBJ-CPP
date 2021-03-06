flags=-Wno-deprecated -g -ggdb
comp=g++
prog=FCCBJ

#problema
instancias = InstanciasALSP/Txt/

#semilla
semilla = 439923
debug = 1
random = 0

comp:$(prog)

exe0:$(prog)
	./$(prog) $(instancias)airland0.txt $(random) $(semilla) $(debug)

exe1:$(prog)
	#valgrind --leak-check=full --show-reachable=yes
	./$(prog) $(instancias)airland1.txt $(random) $(semilla) $(debug)

$(prog): main.o
	$(comp) main.o -o $(prog) $(flags)

main.o: main.cpp
	$(comp) -c main.cpp $(flags)

clean:
	rm -f *.o
	rm -f $(prog)
	rm -f *.out
	rm -f out.txt
