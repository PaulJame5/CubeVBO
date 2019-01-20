#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		//std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[6];
GLubyte triangles[6];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = 0.0f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = 0.0f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.0f;

	vertex[3].coordinate[0] = 0.5f; 
	vertex[3].coordinate[1] = 0.5f;  
	vertex[3].coordinate[2] = 0.0f;

	vertex[4].coordinate[0] = 0.5f; 
	vertex[4].coordinate[1] = -0.5f;  
	vertex[4].coordinate[2] = 0.0f;

	vertex[5].coordinate[0] = -0.5f; 
	vertex[5].coordinate[1] = -0.5f;  
	vertex[5].coordinate[2] = 0.0f;

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	//translate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// vertex index
		for (int i = 0; i < 6; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			
			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::translation(displace) * tempVec);

			std::cout << "tempVec before: " << tempVec.toString() << std::endl;

			//vertex[i] = tempVec;

			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;


			
			std::cout << "placing" << i << std::endl;
			
			
		}

		//Change vertex data
		//vertex[0].coordinate[0] += -0.0001f;
		//vertex[0].coordinate[1] += -0.0001f;
		//vertex[0].coordinate[2] += -0.0001f;
	}


	//scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// vertex index
		for (int i = 0; i < 6; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::scale(1.001f) * tempVec);

			std::cout << "tempVec before: " << tempVec.toString() << std::endl;

			//vertex[i] = tempVec;

			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




			std::cout << "placing" << i << std::endl;


		}
	}

	//scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// vertex index
		for (int i = 0; i < 6; i++)
		{
			MyVector3 tempVec = MyVector3{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

			MyVector3 displace = MyVector3{ 0, 0.0002f, 0 };

			MyVector3 newVec = (MyMatrix3::rotationZ(1) * tempVec);

			std::cout << "tempVec before: " << tempVec.toString() << std::endl;

			//vertex[i] = tempVec;

			vertex[i].coordinate[0] = newVec.x;
			vertex[i].coordinate[1] = newVec.y;
			vertex[i].coordinate[2] = newVec.z;




			std::cout << "placing" << i << std::endl;


		}
	}


	//std::cout << "Update up" << std::endl;
}

void Game::render()
{
	//std::cout << "Drawing" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	//std::cout << "Cleaning up" << std::endl;

	glDeleteBuffers(1, vbo);
}

