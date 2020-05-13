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
		//按esc退出
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
	/*//简单得uniform来改变颜色
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor; \n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";*/
	//glfw初始化
	glfwInit();
	//下面两句是设置版本，GLFW_CONTEXT_VERSION_MAJOR->主版本 GLFW_CONTEXT_VERSION_MINOR->小版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//设置当前窗口的上下文
	glfwMakeContextCurrent(window);
	//glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//判断窗口
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	////三角形顶点数组
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};
	////两个三角形 普通渲染方式
	//float vertices[] = {
	//	// 第一个三角形
	//	0.5f, 0.5f, 0.0f,   // 右上角
	//	0.5f, -0.5f, 0.0f,  // 右下角
	//	-0.5f, 0.5f, 0.0f,  // 左上角
	//	// 第二个三角形
	//	0.5f, -0.5f, 0.0f,  // 右下角
	//	-0.5f, -0.5f, 0.0f, // 左下角
	//	-0.5f, 0.5f, 0.0f   // 左上角
	//};
	
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	float colors[] = {
		1.0f, 0.0f, 0.0f,   // 右上角
		0.0f, 1.0f, 0.0f,  // 右下角
		0.0f, 0.0f, 1.0f,  // 左下角
		0.5f, 0.5f, 0.0f   // 左上角
	};
	int verticesLength;
	int	indicesLength;
	GET_ARRAY_SIZE(vertices, verticesLength);
	GET_ARRAY_SIZE(indices, indicesLength);
	//创建vbo
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	//新建vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//绑定VAO
	glBindVertexArray(VAO);
	//绑定vbo 注意顺序
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	//绑定数据
	

	//利用ebo绘制三角形
	{
		//创建ebo 
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	//设置顶点属性的指针
	
	
	//int vertexColorLocation;
	////着色器相关
	//{
	//	//创建vs
	//	unsigned int vertexShader;
	//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//	//绑定vs
	//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//	//编译vs
	//	glCompileShader(vertexShader);
	//	//设置返回数据
	//	int  success;
	//	char infoLog[512];
	//	//获得编译状态
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
	//	//获得编译状态
	//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	}

	//	//创建着色器程序
	//	unsigned int shaderProgram;
	//	shaderProgram = glCreateProgram();
	//	//绑定着色器数据
	//	glAttachShader(shaderProgram, vertexShader);
	//	glAttachShader(shaderProgram, fragmentShader);
	//	glLinkProgram(shaderProgram);
	//	vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	//	//设置调用
	//	glUseProgram(shaderProgram);
	//	//删除着色器
	//	glDeleteShader(vertexShader);
	//	glDeleteShader(fragmentShader);
	//	
	//	glUseProgram(shaderProgram);
	//}
	
	//设置视点
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	std::cout << indicesLength << std::endl;
	//循环渲染
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//设置颜色
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//清理颜色缓存
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, verticesLength);
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		//交换缓存
		glfwSwapBuffers(window);
		//事件轮询
		glfwPollEvents();
	}
	//终止glfw
	glfwTerminate();
	return 0;
}