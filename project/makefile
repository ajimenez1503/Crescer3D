# set this variable to the director in which you saved the common files
commondir = ../common/
src = src/
all : project

project :  $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)loadobj.c $(commondir)LoadTGA.c  $(commondir)simplefont.c  $(src)sphere.cpp $(src)ground.cpp MicroGlut.o project.cpp
	gcc   -Wall $(commondir)GL_utilities.c $(commondir)loadobj.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)simplefont.c  $(src)sphere.cpp $(src)ground.cpp MicroGlut.o project.cpp -o project -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

MicroGlut.o: $(commondir)Linux/MicroGlut.h
	gcc -w -c $(commondir)Linux/MicroGlut.c

clean :
	rm project

