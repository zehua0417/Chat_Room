CXX = g++
TARGET = bin/chatroom_server.out
OBJ = obj/main.o obj/server.o
CXXFLAGS = -c -Wall

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^
	
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean_obj:
	rm -r bin/*
