all: client.out router.out

# client linking
client.out: client.o
	g++  client.o -o client.out

# client
client.o: client.cpp client.h
	g++ -c client.cpp -o client.o
	
# router linking
router.out: router.o
	g++  router.o -o router.out

# router
router.o: router.cpp router.h
	g++ -c router.cpp -o router.o

clean:
	rm -r -f *.out
	rm -r -f *.o