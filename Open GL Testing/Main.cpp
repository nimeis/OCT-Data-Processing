#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

//GLfloat my

// Vertices coordinates
GLfloat vertices[] =
{


	/* TRIANGLES
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	*/

	//SMALL CUBE
	-0.5f,-0.5f,-0.5f,
	0.0f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,

	-0.5f,0.0f,-0.5f,
	0.0f,0.0f,-0.5f,
	0.5f,0.0f,-0.5f,

	-0.5f,0.5f,-0.5f,
	0.0f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,

	- 0.5f,-0.5f,0.0f,
	0.0f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,

	- 0.5f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.5f,0.0f,0.0f,

	-0.5f,0.5f,0.0f,
	0.0f,0.5f,0.0f,
	0.5f,0.5f,0.0f,

	- 0.5f,-0.5f,0.5f,
	0.0f,-0.5f,0.5f,
	0.5f,-0.5f,0.5f,

	- 0.5f,0.0f,0.5f,
	0.0f,0.0f,0.5f,
	0.5f,0.0f,0.5f,

	-0.5f,0.5f,0.5f,
	0.0f,0.5f,0.5f,
	0.5f,0.5f,0.5f,

	
	
};



// Indices for vertices order
GLuint indices[] =
{
	/*
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
	*/
	0,2,
	2,8,
	8,6,
	6,0,

	0,18,
	2,20,
	6,24,
	8,26,
	
	24,26,
	26,20,
	20,18,
	18,24,
	
};





int main()
{	//initialize glfw
	glfwInit();

	//Tell glfw what version of glfw it is
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//use core profile of openGL (only new functions no depricated stuff)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	


	//Create windowo
	GLFWwindow* window0 = glfwCreateWindow(width, height, "WINDOW 0", NULL, NULL);
	//Check if window was created properely
	if (window0 == NULL)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Create windowo
	GLFWwindow* window1 = glfwCreateWindow(width, height, "WINDOW 1", NULL, NULL);
	//Check if window was created properely
	if (window0 == NULL)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}


	///////////////WINDOW 0//////////////
	
	//set window as the current context for openGL
	glfwMakeContextCurrent(window0);

	//Load openGl using glad
	gladLoadGL();

	//set viewport of OpenGL (area of window it uses)
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));


	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, -10.0f));
	
	//main while loop
	while (!glfwWindowShouldClose(window0))
	{
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window0);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawArrays(GL_POINTS, 0,27);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window0);
		// Take care of all GLFW events
		glfwPollEvents();

		

		
	}



	
	VAO1.Delete();
	VBO1.Delete();
	//EBO1.Delete();
	shaderProgram.Delete();
	//delete window before exiting
	glfwDestroyWindow(window0);
	//end glfw
	glfwTerminate();
	return 0;
}