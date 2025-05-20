DIR =./src/gpio_library

CC = gcc

CFLAGS = -I./include -g -Wno-unused-parameter
LDFLAGS = -L. -lm
STATIC_FLAGS = -c

EXECUTABLES = main
LIBRARIES = libRGB_lib.a

LIB_SRC = $(DIR)/core/pins.c \
	$(DIR)/core/timer.c \
	$(DIR)/core/i2c_access.c \
	$(DIR)/TCS34725/tcs_controller.c \
	$(DIR)/TCS34725/color_converter.c

LIB_OBJ = $(LIB_SRC:.c=.o)

all: $(LIBRARIES) $(EXECUTABLES)

$(EXECUTABLES): src/main.c $(LIBRARIES)
	$(CC) $(CFLAGS) -o $@ $< -L. -lRGB_lib $(LDFLAGS)

$(LIBRARIES): $(LIB_OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(STATIC_FLAGS) $< -o $@

run: $(EXECUTABLES)
	./$(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES) $(LIBRARIES)
	rm -f $(LIB_OBJ)
	rm -f $(DIR)/core/*.o $(DIR)/TCS34725/*.o
	rm -f src/main.o
