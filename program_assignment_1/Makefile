CC = clang

TARGET = ashell

all: $(TARGET)

$(TARGET): main.c command.c
	$(CC) main.c command.c -o $(TARGET)

clean:
	rm -f $(TARGET)

