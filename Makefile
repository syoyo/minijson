SRCS = \
	main.cxx

OBJS = $(subst .cc,.o,$(subst .cxx,.o,$(subst .cpp,.o,$(SRCS))))

CXXFLAGS = -Weverything -Werror -Wno-padded -Wno-c++98-compat  -Wno-c++98-compat-pedantic -std=c++14 -fno-rtti -fno-exceptions
LIBS =
TARGET = minijson
ifeq ($(OS),Windows_NT)
TARGET := $(TARGET).exe
endif

.SUFFIXES: .cpp .cc .cxx .o

all : $(TARGET)

$(TARGET) : minijson.h
	clang++ -o $@ main.cxx

clean :
	rm -f *.o $(TARGET)
