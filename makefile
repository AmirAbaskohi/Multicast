all: client.out router.out network.out

# network linking
network.out: network.o utilities.o
	g++  network.o utilities.o -o network.out

# network
network.o: network.cpp network.h utilities.h
	g++ -c network.cpp -o network.o

# router.out
router.out: router.o ip.o utilities.o
	g++ router.o ip.o utilities.o -o router.out

# client.out
client.out: client.o utilities.o ip.o
	g++ client.o utilities.o ip.o -o client.out

# router
router.o: router.cpp router.h
	g++ -c router.cpp -o router.o

# client
client.o: client.cpp client.h ip.h
	g++ -c client.cpp -o client.o

# ip
ip.o: ip.cpp ip.h utilities.h
	g++ -c ip.cpp -o ip.o

# utilities
utilities.o: utilities.cpp utilities.h
	g++ -c utilities.cpp utilities.h

clean:
	rm -r -f *.out
	rm -r -f *.o
	rm -r -f *.gch
