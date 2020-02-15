// ǥ�� ��� ����
#include <stdio.h>
#include <stdlib.h>

// GLEW ���� - The OpenGL Extension Wrangler Library
// OpenGL�� �ϳ��� ���̺귯���� ������ ���� �ƴϿ���
// GLEW ���� ���̺귯���� ������ �޾� ������Ʈ�� ������ �� �ִ�
#include <GL/glew.h>

// GLFW ����
// ������, Ű���� ����
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM ����
// ���� ����� ���� ���
#include <glm/glm.hpp>
using namespace glm;

// ���̴� ����� ���� ��� �߰�
#include <common/shader.hpp>

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	/// ������ ����

	glfwWindowHint(GLFW_SAMPLES, 4);									// 4x ��Ƽ�������
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// ������ ������¡ ��� �¿��� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL 3.3�� ����Ѵ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS X ������ �̰��� �߰��ؾ� �ڵ尡 ���������� �۵��� ���Դϴ�.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// ���� OpenGL ������ �������� �ʰڴ�

	// �����츦 ����
	window = glfwCreateWindow(
		1024,				// â �ʺ�
		768,				// â ����
		"Playground",		// â�� �̸�
		NULL,
		NULL);

	// ������ ���� �������� �� �����޽��� ��� �� ����
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// �� �������� OpenGL context�� �����Ѵ�
	glfwMakeContextCurrent(window);
	
	// �ھ� ���������� ���� �ʿ���
	glewExperimental = true;

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// �Է� ����
	// Ű ������ ���� ������ �����Ѵ�
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// ȭ�� Ŭ����
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	/// ȭ�� �۾� �Ϸ� �� ����
	// Vertex Array ��ü ����
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);

	// Bind - �޸𸮸� ���ڴٴ� ��
	// glBindBuffer ���� ���� ȣ���ϸ� �ش� ������ �� VertexArray�� ����ȴ�
	// �ε��� ����
	glBindVertexArray(VertexArrayID);

	// �� ���� Vertex�� ǥ���ϴ� �� ���� �迭
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,		// ���ϴ�
		1.0f, -1.0f, 0.0f,		// ���ϴ�
		0.0f, 1.0f, 0.0f,		// ���
	};

	// vertex �����͸� GPU�� ���� -  Vertex Buffer Object(VBO)
	// Vertex Buffer ��ü ����
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	// Vertex Buffer�� ����� ���̴�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Vertex Buffer�� OpenGL�� �ѱ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// ���̴� ���� �� ������
	GLuint programID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");

	// �ݺ��� ���鼭 ������ ����
	do{
		// ȭ�� Ŭ����
		// �÷�, ���� ���� Ŭ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ���̴� ���
		glUseProgram(programID);

		// ������ ù��° �Ӽ��� : ���ؽ�
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,				// 0��° �Ӽ� - ���̴��� ���̾ƿ��� ������Ѵ�
			3,				// ���ؽ� ũ��
			GL_FLOAT,		// ���ؽ� Ÿ��
			GL_FALSE,		// ����ȭ ����
			0,				// ���� ��ұ����� ����
			(void*)0		// �ε��� ������ �ű�� ��
		);

		// 0�� ���ؽ����� �� 3���� ���ؽ��� �׸���
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		// ���� ��ȯ - ����ü��
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// escŰ�� �������� �ݺ��� ����
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// ���ؽ� ����, ���ؽ� �迭 ����
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	// ���̴� ����
	glDeleteProgram(programID);
	
	// ������ �ݰ� GLFW �Ҹ��Ų��
	glfwTerminate();

	return 0;
}

