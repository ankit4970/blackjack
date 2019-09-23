SRC_DIR = src
INC_DIR = "../"
src = $(wildcard $(SRC_DIR)/*.cpp)
CPPFLAGS = -I$(INC_DIR) -std=c++11
CC = g++

blackjack: $(src)
	$(CC) -o $@ $^ $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f blackjack
	rm -f src/*.o 
