#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);									// 4x ��Ƽ�������
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);							// ������ ������¡ ��� �¿��� ����
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
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}

	// �� �������� OpenGL context�� �����Ѵ�
	glfwMakeContextCurrent(window);

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

	// �ݺ��� ���鼭 ������ ����
	do{
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !

		// ���� ��ȯ - ����ü��
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// escŰ�� �������� �ݺ��� ����
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// ������ �ݰ� GLFW �Ҹ��Ų��
	glfwTerminate();

	return 0;
}

