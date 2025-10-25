CXX = g++
CXXFLAGS = -Wall -pg -O2 -Wall -pg -std=c++17 -O2 -Iinclude
LDFLAGS = -pg -pthread

SRC = src/main.cpp src/Stock.cpp src/StdInReader.cpp src/FileReader.cpp src/InputWallet.cpp src/Strategy.cpp src/Wallet.cpp src/market_simulator.cpp
OBJ = $(SRC:.cpp=.o) 
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) gmon.out
