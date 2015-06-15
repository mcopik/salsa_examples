
CXXFLAGS =-O2 -g -Wall -std=c++11
CXX=mpic++
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=bin/%.o)
TARGET = bin/example.exe

$(TARGET):      $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

all:    $(TARGET)

$(OBJS): bin/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@
.cpp.o:	
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(TARGET)
