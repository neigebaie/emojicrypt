CC=gcc
CCWIN=x86_64-w64-mingw32-cc
# CFLAGS=-Wall -Werror -g
CFLAGS=-Wall -pg
SRC=emojiset.c emojicrypt.c
OBJ=$(SRC:.c=.o)

emojicrypt: $(OBJ)
	$(CC) $(CFLAGS) -D__LINUX__ -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

windows: $(OBJ)
	$(CCWIN) $(CFLAGS) -D__WINDOWS__ -o emojicrypt.exe $(SRC)

clean:
	rm -f emojicrypt $(OBJ)
