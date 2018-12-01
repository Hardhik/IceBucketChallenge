CC = g++
CFLAGS = -Wall
PROG = executable

SRCS = mine.cpp imageloader.cpp
LIBS = -lglut -lGL -lGLU


all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
