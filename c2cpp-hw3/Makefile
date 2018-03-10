CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main.o\
            graph.o\
            shortest_path.o\
            priority_queue.o

LIBS =

TARGET =	c2cpp-hw3.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
