// ǥ�� ��� ����
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window; // (�ļ��Ǵ� �ڵ带 ����, �� ������ ����(Global)�Դϴ�.)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW �ʱ�ȭ ����\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x ��Ƽ���ϸ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 �� �� �̴ϴ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS �� ��� ������; �� �ʿ��� �κ��� �ƴ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //���� OpenGL�� ������ �ʾƿ�

	// ��â�� ����, OpenGL ���ؽ�Ʈ�� ����
	window = glfwCreateWindow(1024, 768, "openGL Tutorial", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW �����츦 ���µ� �����߽��ϴ�. Intel GPU �� ����Ѵٸ�, 3.3 ������ ���� �ʽ��ϴ�. 2.1 ������ Ʃ�丮���� �õ��ϼ���.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLEW �ʱ�ȭ
	glewExperimental = true; // �ھ� ���������� ���� �ʿ���
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// �ؿ��� Escape Ű�� �������� ���� ������ �� �ֵ��� �� ��
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	// Hide the mouse and enable unlimited mouvement
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	// �ٸ� OpenGL ȣ���� �Ͼ�� ��, �� �� â�� �������� �� (= OpenGL ���ؽ�Ʈ�� ������ ��) �ѹ� �̺κ��� �������ּ���.
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// ���̴��鿡�� �츮�� GLSL ���α׷��� �����ϰ� �������ϱ�
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	GLuint Texture = loadDDS("uvtemplate.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	
	static const GLfloat g_vertex_buffer_data[] = {
   -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};

	// ���� �� �ΰ��� UV ��ǥ. Blender���� �����Ǿ����ϴ�. �� �̰� ������ �ϴ� ���� ���̴ϴ�. 
	static const GLfloat g_uv_buffer_data[] = {
		 0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
	};

	GLuint vertexbuffer;
	// ���۸� �ϳ� �����մϴ�. vertexbuffer �� ��� �ĺ��ڸ� �ֽ��ϴ�
	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� �츮�� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�̴ϴ�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// �츮�� ���ؽ����� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �츮�� ���̴��� ����ϱ�
		glUseProgram(programID);

		computeMatricesFromInputs();	// Ű����� ���콺, �׸��� Projection ��İ� View ����� ����� ����ϰ� �־��
		glm::mat4 ProjectionMatrix = getProjectionMatrix();	//����� Projection ����� �����ֱ⸸ �մϴ�
		glm::mat4 ViewMatrix = getViewMatrix();				// ����� View ����� �����ֱ⸸ �մϴ�.
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
			3,                  // ũ��(size)
			GL_FLOAT,           // Ÿ��(type)
			GL_FALSE,           // ����ȭ(normalized)?
			0,                  // ���� ��� ���� ����(stride)
			(void*)0            // �迭 ������ ������(offset; �ű�� ��)
		);

		// 2nd attribute buffer : texture
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,      // ũ��� 2!! ���� �߿�    // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// �ﰢ�� �׸���!
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);  // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// ���۵��� ��ü
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}