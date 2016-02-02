.PHONY: all clean

BIN = digit_clock
OBJS = main.o texture.o controller.o view.o model.o
CC = gcc
LD = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lSDL2

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	-rm $(BIN) $(OBJS)
	-rm *~

