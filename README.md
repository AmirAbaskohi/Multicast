# Multicast

This is a basic implementation of a simple network supporting multicast using IP/TCP protocol.


## How to run?
Just use below command to run the makefile:
```
make
```

and then run below command:
```
./network.out
```

The application runs processes for routers and clients to test the network but you can run each of the using their command.
To learn how to run each of them yourself check the `execv` procedures in network.

## Test file
In test directory, there is an `in.txt` file which can contain base commands to test the application.

## Log

After you run the app, app will log the thing which is going on in the app for you in the terminal.
Such as `router sth created` or `client added to sth router`.

## Command
You can see of the commands below:
```
router r1 192.168.20.0 3 # creating router with name r1 and selected ip and 3 ports
client c1 192.168.20.1 # creating client with name c1 and selected ip
connectClient c5 r3 3 # connect client c5 to router r3 in port 3
createGroup c1 200.1.1.1 # creating a group with name c1 and multicast ip 200.1.1.1
multicast c1 200.1.1.1 A.txt # sending multicast message to multicast ip 200.1.1.1
```
<img src="https://www.researchgate.net/profile/Deepika-Vodnala/publication/278023165/figure/fig2/AS:294435494612993@1447210300269/Classification-of-Multicast-Routing-Protocols.png">

*Made By Amirhossein Abaskohi and Arash Rasouli* 
