CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../math
LDFLAGS  = -lgmpxx -lgmp

SRCS = test_main.cpp test_gcd.cpp test_pow_mod.cpp test_mul_mod.cpp ../math/mod_arith.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) && echo "ALL PASSED"

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean