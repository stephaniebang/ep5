CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -O2

.PHONY: clean

ep5: hex.o jogo.o jogador.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ ep5
