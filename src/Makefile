TARGET = out
SRCS = main.cpp Portifolio.cpp Stock.cpp Market.cpp Menus.cpp Saver.cpp Tick.cpp 
OBJS = $(SRCS:.cpp=.o)
CXX = g++
CXXFLAGS = -Wall -g -std=c++23

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
