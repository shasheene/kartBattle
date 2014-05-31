MAC_GL_OPTIONS= -framework OpenGL -framework GLUT 
LINUX_GL_OPTIONS= -lGLEW -lglut -lGL

GL_OPTIONS = $(LINUX_GL_OPTIONS)

all: kartBattle

kartBattle: kartBattle.cpp 
	g++ -I. kartBattle.cpp -o kartBattle $(GL_OPTIONS)

clean:
	rm kartBattle *.o  
