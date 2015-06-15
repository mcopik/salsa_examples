BOOST_INCLUDE=/usr/include/boost/
BOOST_LIB=-lboost_mpi	
CXXFLAGS =-O2 -g -Wall -std=c++11 -I $(BOOST_INCLUDE)
LDFLAGS= $(BOOST_LIB)
CXX=mpic++
SRCDIR = src
TARGETDIR=bin
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(TARGETDIR)/%.o)
TARGET= $(TARGETDIR)/example.exe

$(TARGET):      $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

all:    $(TARGET)

$(OBJS): | $(TARGETDIR)
$(OBJS): $(TARGETDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@
.cpp.o:	
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGETDIR):
	mkdir -p $(TARGETDIR)
