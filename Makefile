
CC = gcc
CFLAGS = -Wall -O2 -I/opt/homebrew/Cellar/freetds/1.5.6/include
LDFLAGS = -L/opt/homebrew/Cellar/freetds/1.5.6/lib -lsybdb

SRCS = test_sel.c init.c
OBJS = $(SRCS:.c=.o)
TARGET = test_sel.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
