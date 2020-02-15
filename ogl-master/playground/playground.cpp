// 표준 헤더 포함
#include <stdio.h>
#include <stdlib.h>

// GLEW 포함 - The OpenGL Extension Wrangler Library
// OpenGL은 하나의 라이브러리로 구성된 것이 아니여서
// GLEW 같은 라이브러리의 도움을 받아 프로젝트에 연결할 수 있다
#include <GL/glew.h>

// GLFW 포함
// 윈도우, 키보드 제어
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM 포함
// 수학 기능을 위한 헤더
#include <glm/glm.hpp>
using namespace glm;

// 쉐이더 사용을 위한 헤더 추가
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

	/// 윈도우 생성

	glfwWindowHint(GLFW_SAMPLES, 4);									// 4x 안티엘리어싱
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// 윈도우 리사이징 기능 온오프 여부
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
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// 그 윈도우의 OpenGL context를 생성한다
	glfwMakeContextCurrent(window);
	
	// 코어 프로파일을 위해 필요함
	glewExperimental = true;

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

	/// 화면 작업 완료 후 진행
	// Vertex Array 객체 생성
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);

	// Bind - 메모리를 쓰겠다는 뜻
	// glBindBuffer 같은 것을 호출하면 해당 내용이 이 VertexArray에 저장된다
	// 인덱스 개념
	glBindVertexArray(VertexArrayID);

	// 세 개의 Vertex를 표현하는 세 벡터 배열
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,		// 좌하단
		1.0f, -1.0f, 0.0f,		// 우하단
		0.0f, 1.0f, 0.0f,		// 상단
	};

	// vertex 데이터를 GPU로 전송 -  Vertex Buffer Object(VBO)
	// Vertex Buffer 객체 생성
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	// Vertex Buffer를 사용할 것이다
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Vertex Buffer를 OpenGL로 넘긴다
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 쉐이더 생성 후 컴파일
	GLuint programID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");

	// 반복문 돌면서 렌더링 진행
	do{
		// 화면 클리어
		// 컬러, 깊이 버퍼 클리어
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 쉐이더 사용
		glUseProgram(programID);

		// 버퍼의 첫번째 속성값 : 버텍스
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,				// 0번째 속성 - 쉐이더의 레이아웃과 맞춰야한다
			3,				// 버텍스 크기
			GL_FLOAT,		// 버텍스 타입
			GL_FALSE,		// 정규화 여부
			0,				// 다음 요소까지의 간격
			(void*)0		// 인덱스 버퍼의 옮기는 값
		);

		// 0번 버텍스부터 총 3개의 버텍스로 그린다
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		// 버퍼 교환 - 스왑체인
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// esc키가 눌려지면 반복문 종료
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// 버텍스 버퍼, 버텍스 배열 정리
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	// 쉐이더 정리
	glDeleteProgram(programID);
	
	// 윈도우 닫고 GLFW 소멸시킨다
	glfwTerminate();

	return 0;
}

