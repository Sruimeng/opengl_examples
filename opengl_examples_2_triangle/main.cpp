#include "../include/glad/glad.h"

#include "../include/GLFW/glfw3.h"
#pragma comment(lib,"../lib/glfw3.lib")


#include "Shader.h"

#include <iostream>

#define GET_ARRAY_SIZE(array,length){length = (sizeof(array) / sizeof(array[0]));}

namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow *window)
	{
		//��esc�˳�
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}


int main()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 outColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"	outColor = aColor;\n"
		"}\n\0";
	const char *fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 outColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(outColor,1.0);\n"
		"}\n"
		;
	/*//�򵥵�uniform���ı���ɫ
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor; \n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";*/
	//glfw��ʼ��
	glfwInit();
	//�������������ð汾��GLFW_CONTEXT_VERSION_MAJOR->���汾 GLFW_CONTEXT_VERSION_MINOR->С�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//���õ�ǰ���ڵ�������
	glfwMakeContextCurrent(window);
	//glad��ʼ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//�жϴ���
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	////�����ζ�������
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};
	////���������� ��ͨ��Ⱦ��ʽ
	//float vertices[] = {
	//	// ��һ��������
	//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, 0.5f, 0.0f,  // ���Ͻ�
	//	// �ڶ���������
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, -0.5f, 0.0f, // ���½�
	//	-0.5f, 0.5f, 0.0f   // ���Ͻ�
	//};
	
	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};
	float colors[] = {
		1.0f, 0.0f, 0.0f,   // ���Ͻ�
		0.0f, 1.0f, 0.0f,  // ���½�
		0.0f, 0.0f, 1.0f,  // ���½�
		0.5f, 0.5f, 0.0f   // ���Ͻ�
	};
	int verticesLength;
	int	indicesLength;
	GET_ARRAY_SIZE(vertices, verticesLength);
	GET_ARRAY_SIZE(indices, indicesLength);
	//����vbo
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	//�½�vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//��VAO
	glBindVertexArray(VAO);
	//��vbo ע��˳��
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	//������
	

	//����ebo����������
	{
		//����ebo 
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	//���ö������Ե�ָ��
	
	
	//int vertexColorLocation;
	////��ɫ�����
	//{
	//	//����vs
	//	unsigned int vertexShader;
	//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//	//��vs
	//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//	//����vs
	//	glCompileShader(vertexShader);
	//	//���÷�������
	//	int  success;
	//	char infoLog[512];
	//	//��ñ���״̬
	//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	}

	//	unsigned int fragmentShader;
	//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//	glCompileShader(fragmentShader);
	//	//��ñ���״̬
	//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	}

	//	//������ɫ������
	//	unsigned int shaderProgram;
	//	shaderProgram = glCreateProgram();
	//	//����ɫ������
	//	glAttachShader(shaderProgram, vertexShader);
	//	glAttachShader(shaderProgram, fragmentShader);
	//	glLinkProgram(shaderProgram);
	//	vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	//	//���õ���
	//	glUseProgram(shaderProgram);
	//	//ɾ����ɫ��
	//	glDeleteShader(vertexShader);
	//	glDeleteShader(fragmentShader);
	//	
	//	glUseProgram(shaderProgram);
	//}
	
	//�����ӵ�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	std::cout << indicesLength << std::endl;
	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//������ɫ
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//������ɫ����
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, verticesLength);
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		//��������
		glfwSwapBuffers(window);
		//�¼���ѯ
		glfwPollEvents();
	}
	//��ֹglfw
	glfwTerminate();
	return 0;
}