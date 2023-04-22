CC = gcc
CFLAGS = -Wall -Werror

TARGET = program
SRCS = main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all build clean run

all: build

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)