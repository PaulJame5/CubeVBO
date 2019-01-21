#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Vector3.h"
#include "MyMatrix3.h"

using namespace std;
using namespace sf;
/// xcopy $(SFML_SDK\bin $(TargetDir) /C /Y ///
class Game
{
public:
	Game();
	~Game();
	void run();

	bool pressedRotation = false;
	bool pressedScale = false;
	bool pressedTransformation = false;

	MyVector3 t_displacement { 1.0f, 1.0f, 0.0f };
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0001f;

	float z = 10;
};