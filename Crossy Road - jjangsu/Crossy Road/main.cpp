// ǥ�� ��� ����
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};



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
	GLFWwindow* window; // (�ļ��Ǵ� �ڵ带 ����, �� ������ ����(Global)�Դϴ�.)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);


	if (window == NULL) {
		fprintf(stderr, "GLFW �����츦 ���µ� �����߽��ϴ�. Intel GPU �� ����Ѵٸ�, 3.3 ������ ���� �ʽ��ϴ�. 2.1 ������ Ʃ�丮���� �õ��ϼ���.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // GLEW �ʱ�ȭ
	glewExperimental = true; // �ھ� ���������� ���� �ʿ���
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// �ٸ� OpenGL ȣ���� �Ͼ�� ��, �� �� â�� �������� �� (= OpenGL ���ؽ�Ʈ�� ������ ��) �ѹ� �̺κ��� �������ּ���.
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	// ���۸� �ϳ� �����մϴ�. vertexbuffer �� ��� �ĺ��ڸ� �ֽ��ϴ�
	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� �츮�� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�̴ϴ�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// �츮�� ���ؽ����� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	// �ؿ��� Escape Ű�� �������� ���� ������ �� �ֵ��� �� ��
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
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
		// �ﰢ�� �׸���!
		glDrawArrays(GL_TRIANGLES, 0, 3); // ���ؽ� 0���� �����ؼ�; �� 3���� ���ؽ��� -> �ϳ��� �ﰢ��
		glDisableVertexAttribArray(0);

		// ���۵��� ��ü
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ���� ESC Ű�� ���������� Ȥ�� â�� �������� üũ üũ
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}