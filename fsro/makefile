vpath	%.cpp	./src
vpath	%.h	./inc

all:fsro

CXX:=g++
objects:=fsro_definition.o fsro.o
CXXFLAGS:=-I./inc -g

$(objects):%.o:%.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $<

fsro:$(objects)
	$(CXX) -o $@ $^
	[ -e /etc/fsro ] || mkdir /etc/fsro
	@echo "#This file is the config file of fsro,configure statement only one line that like \"<the path of exec file> <options>\"." > /etc/fsro/fsro.cfg
	@echo "#If the exec program has an option needs either file path or directory path,should let the option on the end position!(# is annotation)" >> \
	/etc/fsro/fsro.cfg
	@echo "/usr/bin/du -s -h" >> /etc/fsro/fsro.cfg

.PHONY:clean
clean:
	rm -f *.o
