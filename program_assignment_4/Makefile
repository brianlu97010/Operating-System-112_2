# 定義編譯器
CC = gcc

# 定義編譯選項
CFLAGS = -Wall -Wextra -O2

# 定義可執行檔文件名稱
TARGET = disk_scheduling_demo

# 定義source code文件
SRCS = main.c disk_scheduling.c
OBJ = $(SRCS:.c=.o)

# 默認目標
all: $(TARGET)

# 編譯目標可執行文件
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# 將源文件編譯成目標文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJ) $(TARGET)

# 運行程序
run: $(TARGET)
	./$(TARGET) 0


