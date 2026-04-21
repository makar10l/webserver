# Комментарий начинается с решетки

# Переменные (чтобы не повторять одно и то же)
CC = clang
TARGET = server
SRCS = src/main.c lib/socket/socket.c  lib/http_server/server.c
CFLAGS = -Wall -Wextra -O2 -I./lib/socket -I./lib/http_server 
OBJS = $(SRCS:.c=.o)

# Правило по умолчанию (то, что запускается по `make`)
all: $(TARGET)

# Как собрать итоговый файл из объектных
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Как собрать .o файл из .c (это правило сработает автоматически)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Запуск (удобная фишка)
run: $(TARGET)
	./$(TARGET)

# Файлы, которые не нужно искать в папке
.PHONY: all clean run