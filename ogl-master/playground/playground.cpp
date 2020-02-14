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

	glfwWindowHint(GLFW_SAMPLES, 4);									// 4x 안티엘리어싱
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);							// 윈도우 리사이징 기능 온오프 여부
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL 3.3을 사용한다
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS X 에서는 이것을 추가해야 코드가 성공적으로 작동할 것입니다.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 이전 OpenGL 버전은 지원하지 않겠다

	// 윈도우를 열고
	window = glfwCreateWindow(
		1024,				// 창 너비
		768,				// 창 높이
		"Playground",		// 창의 이름
		NULL,
		NULL);

	// 윈도우 생성 실패했을 시 에러메시지 출력 후 종료
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}

	// 그 윈도우의 OpenGL context를 생성한다
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// 입력 셋팅
	// 키 눌리고 때는 동작을 감지한다
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// 화면 클리어
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// 반복문 돌면서 렌더링 진행
	do{
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !

		// 버퍼 교환 - 스왑체인
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// esc키가 눌려지면 반복문 종료
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// 윈도우 닫고 GLFW 소멸시킨다
	glfwTerminate();

	return 0;
}

