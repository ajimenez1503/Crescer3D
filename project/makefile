# Global variables
commondir = ../common/
bindir = bin/
src = src/
cStd = c99
cppStd = c++0x
debugFlag = 

# Variables to build for centos
centos: SYSTEM_FLAG := -D__CENTOS__
centos: MICROGLUT := Linux/MicroGlut.c
centos: PARAM := -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

# Variables to build for Linux
linux: SYSTEM_FLAG := -D__LINUX__
linux: MICROGLUT := Linux/MicroGlut.c
linux: PARAM := -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11 -I"../irrKlang/include" -L"/usr/lib" ../irrKlang/bin/linux-gcc-64/libIrrKlang.so -pthread

# Variables to build for OS X
mac: SYSTEM_FLAG := -D__OSX__
mac: MICROGLUT := mac/MicroGlut.m
mac: PARAM := -I$(commondir) -I../common/mac -framework Cocoa -framework OpenGL -I"../irrKlang/include" -L"../irrKlang/bin/macosx-gcc" ../irrKlang/bin/macosx-gcc/libirrklang.dylib

# Build Target for Linux
linux: compile link

# Build Target for OS X
mac: compile link

# Build Target for Cent OS (Without sound)
centos: compile link

# Compile Commands
compile:
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)GL_utilities.o $(commondir)GL_utilities.c
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)VectorUtils3.o $(commondir)VectorUtils3.c
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)loadobj.o $(commondir)loadobj.c
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)LoadTGA.o $(commondir)LoadTGA.c
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)simplefont.o $(commondir)simplefont.c
	gcc $(debugFlag) -c -w -std=$(cStd) $(SYSTEM_FLAG) -o $(bindir)GL_utilities.o $(commondir)GL_utilities.c
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Sphere.o $(src)Sphere.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)HighScore.o $(src)HighScore.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Button.o $(src)Button.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)GUI.o $(src)GUI.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Engine.o $(src)Engine.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Window.o $(src)Window.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Game.o $(src)Game.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Camera.o $(src)Camera.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Enemy.o $(src)Enemy.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)System.o $(src)System.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Cube.o $(src)Cube.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)World.o $(src)World.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Input.o $(src)Input.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Logger.o $(src)Logger.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Player.o $(src)Player.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Food.o $(src)Food.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Sound.o $(src)Sound.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)Timing.o $(src)Timing.cpp
	g++ $(debugFlag) -c -w -std=$(cppStd) $(SYSTEM_FLAG) -o $(bindir)main.o main.cpp

# Link Commands
link:
	gcc -c -w -std=$(cStd) -o $(bindir)MicroGlut.o $(commondir)$(MICROGLUT)
	g++ -o game $(bindir)GL_utilities.o $(bindir)loadobj.o $(bindir)VectorUtils3.o $(bindir)LoadTGA.o $(bindir)simplefont.o $(bindir)Engine.o $(bindir)Logger.o $(bindir)Sound.o $(bindir)HighScore.o $(bindir)GUI.o $(bindir)Button.o $(bindir)Window.o $(bindir)Game.o $(bindir)Player.o $(bindir)Food.o $(bindir)System.o $(bindir)Cube.o $(bindir)Sphere.o $(bindir)World.o $(bindir)Camera.o $(bindir)Enemy.o $(bindir)Input.o $(bindir)Timing.o $(bindir)MicroGlut.o $(bindir)main.o $(PARAM)

# Removing the Binary
clean:
	rm game
	rm $(bindir)*.o
