LIBRARY =./src/gpio_library

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinclude -g

EXECUTABLES = followLine

ASSIGNMENT1B_SRC = \
	./src/main.c \
	$(LIBRARY)/core/pins.c \
	$(LIBRARY)/core/timer.c \
	$(LIBRARY)/core/i2c_access.c

all: $(EXECUTABLES)

followLine: $(ASSIGNMENT1B_SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(EXECUTABLES);
	./assignment2

clean:
	rm -f $(EXECUTABLES)
