OPENGL_LIB= -I/usr/lib64 -lGLU -lGL -lglut

OBJS= Common.o Cube.o Ghost.o Lamp.o Map.o Pacman.o textures.o Tile.o Material.o
CXX= g++
COMPILER_FLAGS= -g
LIBS= $(OPENGL_LIB)

OUT= pacman3d

$(OUT):	$(OBJS)
	$(CXX) $(COMPILER_FLAGS) main.cpp -o $(OUT) $(OBJS) $(LIBS)

%.o:	%.cpp
	$(CXX) -c $(COMPILER_FLAGS) -o $@ $<

clean:
	rm -f $(OUT) $(OBJS)
