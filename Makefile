#!/usr/bin/gmake

CC = gcc -g
CFLAGS = -DDOOR_FILE='"/var/run/test_door"'

all: server client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client
