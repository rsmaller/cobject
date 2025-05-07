CC = gcc
FLAGS = -Wall
RM = rm -f

default: all

all: object

object: object.c
	$(CC) $(FLAGS) -o object object.c

clean:
	$(RM) object