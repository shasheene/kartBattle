LINUX_GL_OPTIONS= -lGLEW -lglut -lGL
MAC_GL_OPTIONS= -framework OpenGL -framework GLUT 
CXX = g++

#Library base filename
SOIL=lib/SOIL/SOIL
GLM_MOD=lib/GLM_MOD

all: kartBattle

kartBattle:  soil.o display.o idle.o entity.o kartBattle.o image_helper.o stb_image_aug.o image_DXT.o global.o movement.o glLibAndConst.o shader_utils.o
	$(CXX) kartBattle.o display.o idle.o entity.o movement.o glLibAndConst.o $(LINUX_GL_OPTIONS) SOIL.o image_helper.o stb_image_aug.o image_DXT.o global.o shader_utils.o -o kartBattle 

#
#$(CXX) kartBattle.o display.o car.o SOIL.o glm_mod.o image_helper.o stb_image_aug.o image_DXT.o -o kartBattle 

kartBattle.o: glLibAndConst.h kartBattle.cpp kartBattle.h movement.h
	$(CXX) -c kartBattle.cpp 

display.o: display.cpp display.h glLibAndConst.h movement.h shader_utils.h
	$(CXX) -c display.cpp

idle.o: idle.cpp idle.h glLibAndConst.h global.h
	$(CXX) -c idle.cpp

entity.o: entity.cpp entity.h glLibAndConst.h glm_mod.o
	$(CXX) -c entity.cpp

global.o: global.cpp global.h glLibAndConst.h
	$(CXX) -c global.cpp

glLibAndConst.o: glLibAndConst.cpp glLibAndConst.h
	$(CXX) -c glLibAndConst.cpp

movement.o: movement.cpp movement.h global.h glLibAndConst.h entity.h
	$(CXX) -c movement.cpp

shader_utils.o: shader_utils.cpp shader_utils.h
	$(CXX) -c shader_utils.cpp

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


# -w means if file exists and writable
clean:
	if [ -w kartBattle ]; then rm kartBattle; fi;
	rm *.o
