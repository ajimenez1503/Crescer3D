# directory variables
commondir = ../common/
bindir = bin/
src = src/

linux: compile linux_link
	
mac: compile mac_link

linux_link:
	g++ -o game $(bindir)GL_utilities.o $(bindir)loadobj.o $(bindir)VectorUtils3.o $(bindir)LoadTGA.o $(bindir)simplefont.o $(bindir)Engine.o $(bindir)Logger.o $(bindir)Window.o $(bindir)Game.o $(bindir)Player.o $(bindir)System.o $(bindir)Sphere.o $(bindir)Ground.o $(bindir)Input.o $(bindir)MicroGlut.o $(bindir)main.o -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

mac_link:
	g++ -o game $(bindir)GL_utilities.o $(bindir)loadobj.o $(bindir)VectorUtils3.o $(bindir)LoadTGA.o $(bindir)simplefont.o $(bindir)Engine.o $(bindir)Logger.o $(bindir)Window.o $(bindir)Game.o $(bindir)System.o $(bindir)Player.o $(bindir)Sphere.o $(bindir)Ground.o $(bindir)Input.o $(bindir)MicroGlut.o $(bindir)main.o -I$(commondir) -I../common/mac -framework Cocoa -framework OpenGL

compile:
	gcc -c -w -std=c99 -o $(bindir)GL_utilities.o $(commondir)GL_utilities.c
	gcc -c -w -std=c99 -o $(bindir)VectorUtils3.o $(commondir)VectorUtils3.c
	gcc -c -w -std=c99 -o $(bindir)loadobj.o $(commondir)loadobj.c
	gcc -c -w -std=c99 -o $(bindir)LoadTGA.o $(commondir)LoadTGA.c
	gcc -c -w -std=c99 -o $(bindir)simplefont.o $(commondir)simplefont.c
	gcc -c -w -std=c99 -o $(bindir)GL_utilities.o $(commondir)GL_utilities.c
	gcc -c -w -std=c99 -o $(bindir)MicroGlut.o $(commondir)mac/MicroGlut.m
	g++ -c -w -std=c++11 -o $(bindir)Engine.o $(src)Engine.cpp
	g++ -c -w -std=c++11 -o $(bindir)Window.o $(src)Window.cpp
	g++ -c -w -std=c++11 -o $(bindir)Game.o $(src)Game.cpp
	g++ -c -w -std=c++11 -o $(bindir)System.o $(src)System.cpp
	g++ -c -w -std=c++11 -o $(bindir)Sphere.o $(src)Sphere.cpp
	g++ -c -w -std=c++11 -o $(bindir)Ground.o $(src)Ground.cpp
	g++ -c -w -std=c++11 -o $(bindir)Input.o $(src)Input.cpp
	g++ -c -w -std=c++11 -o $(bindir)Logger.o $(src)Logger.cpp
	g++ -c -w -std=c++11 -o $(bindir)Player.o $(src)Player.cpp
	g++ -c -w -std=c++11 -o $(bindir)main.o main.cpp

clean:
	rm game

