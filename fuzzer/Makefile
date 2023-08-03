SRCS = \
	main.cxx

OBJS = $(subst .cc,.o,$(subst .cxx,.o,$(subst .cpp,.o,$(SRCS))))

CXX=clang++
CC=clang

CXXFLAGS = -fsanitize=address,fuzzer -I../ -std=c++14 -fno-rtti -fno-exceptions
LDFLAGS = -fsanitize=address,fuzzer
LIBS =
TARGET = fuzz_minijson
ifeq ($(OS),Windows_NT)
TARGET := $(TARGET).exe
endif

.SUFFIXES: .cpp .cc .cxx .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.cxx.o :
	$(CXX) -c $(CXXFLAGS) -I. $< -o $@

.cpp.o :
	$(CXX) -c $(CXXFLAGS) -I. $< -o $@

.cc.o :
	$(CXX) -c $(CXXFLAGS) -I. $< -o $@

clean :
	rm -f *.o $(TARGET)
