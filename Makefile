CC=gcc
# CFLAGS=-Wall -Werror -g
CFLAGS=-Wall
SRC=emojiset.c emojicrypt.c
OBJ=$(SRC:.c=.o)

emojicrypt: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f emojicrypt $(OBJ)
