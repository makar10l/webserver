CC = clang
TARGET = server
SRCS = src/main.c lib/socket/socket.c  lib/http_server/server.c
CFLAGS = -Wall -Wextra -O2 -I./lib/socket -I./lib/http_server 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run