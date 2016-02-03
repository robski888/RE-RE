CXXFLAGS = -mno-ms-bitfields -static -O3 -ggdb -D UNICODE -D _UNICODE -Wall -pedantic --std=c++11 -pthread
CC = i686-w64-mingw32-g++

all: $(patsubst %.cpp, %.exe, $(wildcard *.cpp)) demo

%.exe: %.cpp Makefile
	$(CC) $(CXXFLAGS) $< -o $@

demo:
	WINEDEBUG=-all ./edpr_server_office.exe openwall.pages  # for iWork files!
	# ./edpr_server.exe user-64-RC2-openwall.id
