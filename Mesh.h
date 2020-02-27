#ifndef MESH_H
#define MESH_H
#include <glad/include/glad/glad.h>
class Mesh : public ComponentBase {
public:
	Mesh(int vertexAmount, float * vertices) : _VertexAmount(vertexAmount), _Vertices(vertices){
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
	}
	~Mesh() {
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
	}
	unsigned int _VAO, _VBO;
	int _VertexAmount;
	float* _Vertices;
};
#endif MESH_H
