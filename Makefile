XX = g++

CXXFLAGS = -std=c++11  -c  -g 


MYSQL_LIBS = $(shell mysql_config --libs)
MYSQL_CFLAGS = $(shell mysql_config --cflags)


SRC=$(wildcard *.cpp)
OBJECTS:=$(patsubst %.cpp,%.o,$(SRC))

PROGRAM:= test
TARGET = ./$(PROGRAM)



all: $(TARGET)  


$(TARGET) : $(OBJECTS) 
	$(XX)  -o $(TARGET)  $(OBJECTS)   $(MYSQL_LIBS)


$(OBJECTS) : %.o : %.cpp 
	$(XX)  $(CXXFLAGS) $< -o $@  $(MYSQL_CFLAGS)


.PHONY : clean

clean:
	rm -rf $(TARGET) $(OBJECTS)

