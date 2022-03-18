# make cryptor

all:cryptor

objects:=cryptor.o algo.o base64.o
CC:=g++
CCFLAGS:=-g -Iinc/

vpath %.cpp src
vpath %.h   inc

$(objects):%.o:%.cpp
	$(CC) -o $@ $(CCFLAGS) -c $^

cryptor:$(objects)
	$(CC) -o $@ $^
	mv $@ bin/

base64:base64_main.o base64.o
	$(CC) -o $@ $(CCFLAGS) $^
base64_main.o:base64_main.cpp
	$(CC) -o $@ -c $(CCFLAGS) $<

.PHONY:clean
clean:
	rm -f *.o
