CXXFLAGS =    -O0 -g -Wall -fmessage-length=0 -DDEBUG -DCANNED_GRAPH

OBJS =    main.o\
          graph.o\
          shortest_path.o\
          priority_queue.o

TARGET =    c2cpp-hw3.exe

$(TARGET):  $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

#SRCS := $(shell find . -type f -name "*.cpp")
#OBJS := $(SRCS:.cpp=.o)
#DEPS := $(shell find . -type f -name "*.hpp")
#
#TARGET =    c2cpp-hw3.exe
#
#$(TARGET):  $(OBJS) $(DEPS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)


all:    $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
