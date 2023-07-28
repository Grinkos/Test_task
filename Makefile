CC := g++
CFLAGS := -std=c++11 -Wall -Wpedantic
SRCS :=Test.cpp
TARGET := program

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	./program

clean:
	rm -f $(TARGET)



