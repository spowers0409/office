#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture matrixTexture;
Texture grayMetal;
Texture whiteSpeaker;
Texture speakerCone;
Texture floorPlane;
Texture theWork;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


void CreateObjects()
{
	unsigned int indices[] = {
		// Desk top
		0, 3, 2,
		0, 1, 2,

		// Left front leg
		4, 7, 6,
		4, 5, 6,

		// Right front leg
		9, 10, 11,
		9, 8, 11,

		// Left back leg
		12, 15, 14,
		12, 14, 13,

		// Right back leg
		17, 18, 19,
		17, 19, 16,



	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v
			// Desk top
			-1.0f, 0.0f, -0.5f,		0.0f,  0.5f,  // 0
			 1.0f, 0.0f, -0.5f,		1.0f,  0.5f,  // 1
			 1.0f, 0.0f,  0.5f,		1.0f,  0.5f,  // 2
			-1.0f, 0.0f,  0.5f,		0.0f,  0.5f,  // 3


			// Front Left leg
			-1.0f,  -0.5f, 0.5f,	0.0f,  0.0f,  // 4
			-0.75f, -0.5f, 0.5f,	0.0f,  0.0f,  // 5
			-0.75f,  0.0f, 0.5f,	0.0f,  0.0f,  // 6
			-1.0f,   0.0f, 0.5f,	0.0f,  0.0f,  // 7


			// Front Right leg
			1.0f,  -0.5f, 0.5f,		0.0f,  0.0f,  // 8
			0.75f, -0.5f, 0.5f,		0.0f,  0.0f,  // 9
			0.75f,  0.0f, 0.5f,		0.0f,  0.0f,  // 10
			1.0f,   0.0f, 0.5f,		0.0f,  0.0f,  // 11 


			// Back Left leg
			-1.0f,  -0.5f, -0.5f,	0.0f,  0.0f, // 12
			-0.75f, -0.5f, -0.5f,	0.0f,  0.0f, // 13
			-0.75f,  0.0f, -0.5f,	0.0f,  0.0f, // 14
			-1.0f,   0.0f, -0.5f,	0.0f,  0.0f, // 15


			// Back Right leg
			1.0f,  -0.5f, -0.5f,	0.0f,  0.0f, // 16
			0.75f, -0.5f, -0.5f,	0.0f,  0.0f, // 17
			0.75f,  0.0f, -0.5f,	0.0f,  0.0f, // 18
			1.0f,   0.0f, -0.5f,	0.0f,  0.0f, // 19


	};

	Mesh* objDesk = new Mesh();
	objDesk->CreateMesh(vertices, indices, 100, 30);
	meshList.push_back(objDesk);
}


void CreateMonitor()
{
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v
			-1.0f, -0.5f, 0.0f,		0.0f, 0.0f,		// 0
			-1.0f,  0.5f, 0.0f,		0.0f, 1.0f,		// 1
			 1.0f,  0.5f, 0.0f,		1.0f, 1.0f,		// 2
			 1.0f, -0.5f, 0.0f,		1.0f, 0.0f,		// 3
	};

	Mesh* objMonitor1 = new Mesh();
	objMonitor1->CreateMesh(vertices, indices, 100, 30);
	meshList.push_back(objMonitor1);

	Mesh* objMonitor2 = new Mesh();
	objMonitor2->CreateMesh(vertices, indices, 60, 18);
	meshList.push_back(objMonitor2);

	Mesh* objMonitor3 = new Mesh();
	objMonitor3->CreateMesh(vertices, indices, 60, 18);
	meshList.push_back(objMonitor3);

	Mesh* objMonitor4 = new Mesh();
	objMonitor4->CreateMesh(vertices, indices, 60, 18);
	meshList.push_back(objMonitor4);

}

void CreateSpeaker()
{
	unsigned int indices[] = {
		// Front
		0, 2, 3,
		0, 1, 2,
		//Right
		1, 2, 6,
		1, 5, 6,
		// Back
		4, 7, 6,
		4, 5, 6,
		// Left
		0, 3, 7,
		0, 4, 7,
		// Top
		3, 7, 6,
		3, 2, 6,
		// Bottom
		0, 4, 5,
		0, 1, 5,
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		// 0
		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		// 1
		 1.0f,  1.0f, 0.0f,		1.0f, 1.0f,		// 2
		-1.0f,  1.0f, 0.0f,		0.0f, 1.0f,		// 3
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		// 4
		 1.0f, -1.0f, 1.0f,		1.0f, 0.0f,		// 5
		 1.0f,  1.0f, 1.0f,		1.0f, 1.0f,		// 6
		-1.0f,  1.0f, 1.0f,		0.0f, 1.0f,		// 7
	};

	Mesh* objSpeaker = new Mesh();
	objSpeaker->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker);

	Mesh* objSpeaker2 = new Mesh();
	objSpeaker2->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker2);

	Mesh* objSpeaker3 = new Mesh();
	objSpeaker3->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker3);

	Mesh* objSpeaker4 = new Mesh();
	objSpeaker4->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker4);

	Mesh* objSpeaker5 = new Mesh();
	objSpeaker5->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker5);

	Mesh* objSpeaker6 = new Mesh();
	objSpeaker6->CreateMesh(vertices, indices, 40, 36);
	meshList.push_back(objSpeaker6);

}

void CreateFloorPlane()
{
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v
			-1.0f, 0.0f, 1.0f,		0.0f, 0.0f,		// 0
			 1.0f, 0.0f, 1.0f,		0.0f, 1.0f,		// 1
			 1.0f, 0.0f, -1.0f,		1.0f, 1.0f,		// 2
			-1.0f, 0.0f, -1.0f,		1.0f, 0.0f,		// 3
	};

	Mesh* objFloor = new Mesh();
	objFloor->CreateMesh(vertices, indices, 20, 6);
	meshList.push_back(objFloor);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateMonitor();
	CreateSpeaker();
	CreateFloorPlane();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 2.0f, 2.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -10.0f, 3.0f, 0.2f);

	brickTexture = Texture((char*)"Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture((char*)"Textures/dirt.png");
	dirtTexture.LoadTexture();
	matrixTexture = Texture((char*)"Textures/matrix.png");
	matrixTexture.LoadTexture();
	grayMetal = Texture((char*)"Textures/grayMetal.png");
	grayMetal.LoadTexture();
	whiteSpeaker = Texture((char*)"Textures/white.png");
	whiteSpeaker.LoadTexture();
	speakerCone = Texture((char*)"Textures/speaker.png");
	speakerCone.LoadTexture();
	floorPlane = Texture((char*)"Textures/carpet.png");
	floorPlane.LoadTexture();
	theWork = Texture((char*)"Textures/theWork.png");
	theWork.LoadTexture();

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.5f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientcolor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientcolor = shaderList[0].GetAmbientcolorLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientcolor);

		glm::mat4 model(1.0f);

		// Desk
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(2.5f, 1.4f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		// Left Side Monitor
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.74f, 0.5f, -3.00f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		theWork.UseTexture();
		meshList[1]->RenderMesh();

		// Left Side Monitor Metal Frame
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.74f, 0.5f, -3.02f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.75f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		grayMetal.UseTexture();
		meshList[2]->RenderMesh();

		// Right Side Monitor
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.74, 0.5f, -3.00f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		matrixTexture.UseTexture();
		meshList[3]->RenderMesh();

		// Right Side Monitor Metal Frame
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.74f, 0.5f, -3.02f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.73f, 0.75f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		grayMetal.UseTexture();
		meshList[4]->RenderMesh();

		// Left Side Speaker Box
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 0.4f, -3.3f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		whiteSpeaker.UseTexture();
		meshList[5]->RenderMesh();

		// Left Side Speaker Cone Top
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 0.58f, -3.28f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.18f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		speakerCone.UseTexture();
		meshList[6]->RenderMesh();

		// Left Side Speaker Cone Bottom
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 0.2f, -3.28f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.18f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		speakerCone.UseTexture();
		meshList[7]->RenderMesh();

		// Right Side Speaker Box
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.4f, -3.3f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		whiteSpeaker.UseTexture();
		meshList[8]->RenderMesh();

		// Right Side Speaker Cone Top
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.58f, -3.28f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.18f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		speakerCone.UseTexture();
		meshList[9]->RenderMesh();

		// Right Side Speaker Cone Bottom
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.2f, -3.28f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.18f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
		speakerCone.UseTexture();
		meshList[10]->RenderMesh();

		// Floor Plane
		model = glm::translate(model, glm::vec3(-11.0f, -5.0f, 1.0f));
		
		model = glm::scale(model, glm::vec3(20.0f, 5.0f, 10.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		floorPlane.UseTexture();
		meshList[11]->RenderMesh();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}