all:kaiserVision
convert:bmp

shaders.o: shaders.cpp
	g++ -c shaders.cpp -lopengl32 -lglew32 -lfreeglut -lglu32

Kaiser_vision.o: Kaiser_vision.cpp
	g++ -c Kaiser_vision.cpp -lopengl32 -lglew32 -lfreeglut -lglu32

engine.o: engine.cpp
	g++ -c engine.cpp -lopengl32 -lglew32 -lfreeglut -lglu32

kaiserVision: Kaiser_vision.o engine.o shaders.o
	g++ engine.o Kaiser_vision.o shaders.o -o kaiserVision -lopengl32 -lglew32 -lfreeglut -lglu32

bmp: readBMP.cpp
	g++ readBMP.cpp -o bmptovertices
