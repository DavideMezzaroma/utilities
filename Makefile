CFLAGS += -std=gnu11 -Wall -lm -o

%: %.c

.PHONY: clean
clean:
    rm -f *.o
    rm -f %
