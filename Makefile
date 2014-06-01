LINUX_GL_OPTIONS= -lGLEW -lglut -lGL
MAC_GL_OPTIONS= -framework OpenGL -framework GLUT 
CXX = g++

#Library base filename
SOIL=lib/SOIL/SOIL
GLM_MOD=lib/GLM_MOD

all: kartBattle

kartBattle:  soil.o glm_mod.o display.o car.o kartBattle.o image_helper.o stb_image_aug.o image_DXT.o global.o
	$(CXX) kartBattle.o display.o car.o $(LINUX_GL_OPTIONS) SOIL.o glm_mod.o image_helper.o stb_image_aug.o image_DXT.o global.o -o kartBattle 

#
#$(CXX) kartBattle.o display.o car.o SOIL.o glm_mod.o image_helper.o stb_image_aug.o image_DXT.o -o kartBattle 

kartBattle.o: main.cpp glLibAndConst.h kartBattle.cpp kartBattle.h
	$(CXX) -c kartBattle.cpp 

display.o: display.cpp display.h glLibAndConst.h
	$(CXX) -c display.cpp

car.o: car.cpp car.h glLibAndConst.h glm_mod.o
	$(CXX) -c car.cpp

global.o: global.cpp global.h glLibAndConst.h
	$(CXX) -c global.cpp

#lib/SOIL/SOIL.h lib/SOIL/SOIL.cpp
soil.o: 
	$(CC) -c lib/SOIL/SOIL.c
#lib/glm_mod.h lib/glm_mod.cpp
glm_mod.o: 
	$(CC) -c lib/glm_mod.c

image_helper.o: 
	$(CC) -c lib/image_helper.c

image_DXT.o:
	$(CC) -c lib/image_DXT.c

stb_image_aug.o:
	$(CC) -c lib/stb_image_aug.c


clean:
	rm kartBattle *.o