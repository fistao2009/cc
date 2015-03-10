EXE = cc
CXX = g++
CFLAGS =  -g -Wno-deprecated
	SRCS = $(wildcard *.cpp)
	OBJS = $(SRCS:.cpp=.o)
$(EXE):$(OBJS)
	$(CXX) $(CFLAGS)  $(OBJS) -o $@
#-c 只编译，不链接
%.o:%.cpp
	$(CXX) -c $< $(CFLAGS)
clean:
	-rm *.o

