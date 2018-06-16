all: pub sub

sub: sub.c
	gcc sub.c -o sub -lczmq -lzmq

pub: pub.c
	gcc pub.c -o pub -lczmq -lzmq
