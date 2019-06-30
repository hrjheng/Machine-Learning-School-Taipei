CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : ReadToTree Exercise_Tuesday

ReadToTree : src/ReadToTree.cxx src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/ReadToTree.cxx src/Event.cc src/Minitree.cc -o ReadToTree

Exercise_Tuesday : src/Exercise_Tuesday.cxx src/Event.cc src/Minitree.cc
		g++ ${CFLAGS} src/Exercise_Tuesday.cxx src/Event.cc src/Minitree.cc -o Exercise_Tuesday
