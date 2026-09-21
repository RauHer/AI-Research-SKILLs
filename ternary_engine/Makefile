CC = gcc
CFLAGS = -std=c11 -O3 -march=native -Wall -Wextra -pedantic \
         -fomit-frame-pointer -flto -D_GNU_SOURCE

# In a true environment we add AVX-512 flags:
# -mavx512f -mavx512vl -mavx512bw -mavx512dq -mavx512vpopcntdq
# But here we stick to generic -march=native to ensure it compiles in the sandbox

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = ternary_engine

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all dirs clean
