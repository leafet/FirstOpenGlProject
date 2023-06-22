#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaded.h"

float yoffset = 0;
float xoffset = 0;
float xvelocity = 0;
float yvelocity = 0;

float r = 0;
float g = 0;
float b = 0;

void bounce(float xoffset, float yoffset)
{
	
	if (xoffset > 1)
	{
		float ran = xvelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.03 - xvelocity)));
		xvelocity = -ran;
		r = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		g = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		b = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
	}

	if (xoffset < -1)
	{
		float ran = xvelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.03 - xvelocity)));
		xvelocity = ran;
		r = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		g = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		b = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
	}

	if (yoffset > 1)
	{
		float ran = yvelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.03 - yvelocity)));
		yvelocity = -ran;
		r = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		g = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		b = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
	}

	if (yoffset < -1)
	{
		float ran = yvelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.03 - yvelocity)));
		yvelocity = ran;
		r = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		g = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
		b = 0.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - xvelocity)));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		xvelocity = 0;
		yvelocity = 0.01;
	}
		
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		xvelocity = 0;
		yvelocity = -0.01;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		xvelocity = 0.01;
		yvelocity = 0;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		xvelocity = -0.01;
		yvelocity = 0;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		xvelocity = 0;
		yvelocity = 0;
	}
}

int main()
{

	srand((unsigned)time(NULL));

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	GLfloat vertices[] =
	{
		 -0.1f,  0.1f, 0.0f,
		 -0.1f, -0.1f, 0.0f,
		 0.1f, -0.1f, 0.0f,
		 0.1f, 0.1f, 0.0f,
	};

	GLuint indices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	Shader ourShader("shader.vs", "shader.frag");

	xvelocity = 0.01;
	yvelocity = 0.03;

	

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.439f, 0.812f, 0.365f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat timeValue = glfwGetTime();

		xoffset += xvelocity;
		yoffset += yvelocity;

		bounce(xoffset, yoffset);

		ourShader.Use();

		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "outColor");

		glUniform1f(glGetUniformLocation(ourShader.Program, "xOffset"), xoffset);
		glUniform1f(glGetUniformLocation(ourShader.Program, "yOffset"), yoffset);

		glUniform4f(vertexColorLocation, r, g, b, 1.0f);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}