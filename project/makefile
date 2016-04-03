# directory variables
commondir = ../common/
src = src/

linux: $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)LoadTGA.c $(commondir)simplefont.c $(src)sphere.cpp $(src)ground.cpp MicroGlut.o project.cpp
	gcc -w -Wreturn-type-c-linkage $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)simplefont.c  $(src)sphere.cpp $(src)ground.cpp MicroGlut.o project.cpp -o game -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

MicroGlut.o: $(commondir)Linux/MicroGlut.h
	gcc -w -c $(commondir)Linux/MicroGlut.c

mac: $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)LoadTGA.c $(commondir)simplefont.c $(src)sphere.cpp $(src)ground.cpp $(commondir)mac/MicroGlut.m project.cpp
	gcc -w $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)simplefont.c  $(src)sphere.cpp $(src)ground.cpp $(commondir)mac/MicroGlut.m project.cpp -o game -I$(commondir) -I../common/mac -framework Cocoa -framework OpenGL

clean:
	rm game

