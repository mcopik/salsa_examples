BOOST_INCLUDE=/usr/include/boost/
BOOST_LIB=-L/usr/lib/x86_64-linux-gnu/ -lboost_mpi	
CXXFLAGS =-O2 -g -Wall -std=c++11 -I $(BOOST_INCLUDE)
LDFLAGS= $(BOOST_LIB)
CXX=mpic++
SRCDIR = src
TARGETDIR=bin
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(TARGETDIR)/%.exe)
#TARGET= $(TARGETDIR)/example.exe

$(TARGET):      $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:    $(OBJS)

$(OBJS): | $(TARGETDIR)
$(OBJS): $(TARGETDIR)/%.exe : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS)  $<  -o $@ $(LDFLAGS)
.cpp.o:	
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGETDIR):
	mkdir -p $(TARGETDIR)
