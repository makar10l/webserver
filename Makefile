CC = clang
TARGET = server
SRCS = src/main.c lib/socket/socket.c  lib/http_server/server.c lib/http_server/http_parser/parser.c lib/http_server/file_searcher.c
CFLAGS = -Wall -Wextra -O2 -I./lib/socket -I./lib/http_server  -I./lib/http_server/http_parser
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
run: $(TARGET)
	./$(TARGET)
re:
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) clean

.PHONY: all clean run re