#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include<GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/transform.hpp>
#include <soil.h>
#include "shader_s.h"

float vertices[] = {

	0.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	0.5f, 1.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	-1.5f, 2.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 2.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f,


	0.5f, 3.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	0.0f, 3.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,

	
	-1.5f, 3.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	-1.0f, 3.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, //9

	
	0.0f, 4.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f, // 10
	0.5f, 4.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f, // 11

	
	-1.5f, 5.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	-1.0f, 5.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f, // 13

	
	0.0f, 6.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 6.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f,

	
	-1.5f, 6.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	-1.0f, 6.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,

	//trunk
	-1.0f, 7.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,//18
	0.0f, 7.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f, //19 !
	-1.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f, // 20 !

	
	0.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,

	//leafs
	-5.5f,5.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,//22
	-1.5f, 9.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,//23!
	0.5f,7.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f, // 24!

	-5.5f,11.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,
	-1.5f, 7.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,// 26!
	0.5f,9.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f, // 27!

	4.5f,11.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f, // 28

	4.5f,5.0f, 0.0f, 1.0f,0.0f, 0.0f, 0.5f, 1.0f,//29

};
unsigned int indices[] =
{
	22,23,24,
	25,26,27,
	23,24,28,
	26,27,29,
	0,1,2,
	3,4,5,
	2,6,7,
	5,8,9,
	7,10,11,
	9,12,13,
	10,14,15,
	13,16,17,
	18,19,20,
	19,20,21,
};


int main()
{
	
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello texture", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// textures
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nChannels;
	unsigned char* data = SOIL_load_image("orangepalm.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "texture error\n";
	}
	SOIL_free_image_data(data);
	Shader ourShader("vertexshader.vs", "fragmentshader.fs");
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.07f, 0.07f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, texture);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 1.0f, -15.0f),
			glm::vec3(0.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 model(1.0f);
		glm::mat4 mvp = projection * view * model;
		GLuint mvpLoc = glGetUniformLocation(ourShader.ID, "mvp");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
		ourShader.use();
		glBindVertexArray(VAO);
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, 0);
	
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	return 0;
}
