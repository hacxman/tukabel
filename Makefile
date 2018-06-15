all: pub sub

sub: sub.c
	g++ sub.c -o sub -lczmq -lzmq

pub: pub.c
	g++ pub.c -o pub -lczmq -lzmq
