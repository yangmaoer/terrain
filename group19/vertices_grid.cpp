
#include "vertices_grid.h"
#include <GL/glew.h>
#include "opengp.h"


/// NxN triangle grid.
/// const is better than #define : type checked, optimized out anyway
const unsigned int N = 128;
const unsigned int nVertices = N*N;
const unsigned int nIndices = (N-1)*(N-1)*6;


/// Generate a flat and regular triangle grid. Copy vertices to GPU.
void VerticesGrid::generate() {

    /// Vertex array object (VAO).
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);

    /// Generate the vertices (line by line) : 16^2 = 256 vertices.
    vec2 vertices[nVertices];
    for(int y=0; y<N; y++) {
        for(int x=0; x<N; x++) {
            vertices[y*N+x] = vec2(float(2.0*x)/(N-1)-1, float(2.0*y)/(N-1)-1);
        }
    }

    /// Copy the vertices to GPU in a vertex buffer (VBO).
    glGenBuffers(1, _vertexBufferIDs);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferIDs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /// Indices that form the triangles.
    /// Grid of 15x15 squares : 225 squares -> 450 triangles -> 1350 indices.
    unsigned int indices[nIndices];
    for(int y=0; y<N-1; y++) {
        for(int x=0; x<N-1; x++) {
            /// Upper left triangle of the square.
            indices[y*(N-1)*6+x*6+0] = y*N + x + 0;
            indices[y*(N-1)*6+x*6+1] = y*N + x + 1;
            indices[y*(N-1)*6+x*6+2] = y*N + x + N;
            /// Lower right triangle of the square.
            indices[y*(N-1)*6+x*6+3] = y*N + x + 1;
            indices[y*(N-1)*6+x*6+4] = y*N + x + N+1;
            indices[y*(N-1)*6+x*6+5] = y*N + x + N;
        }
    }

    /// Copy the indices to GPU in an index buffer.
    glGenBuffers(1, &_elementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}


void VerticesGrid::bind(GLuint vertexAttribIDs[]) const {

    /// Vertex attribute points to data from the currently binded array buffer.
    /// The binding is part of the binded VAO state.
    glBindVertexArray(_vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferIDs[0]);
    glEnableVertexAttribArray(vertexAttribIDs[0]);
    // vec2: 2 floats per vertex for the attribute.
    glVertexAttribPointer(vertexAttribIDs[0], 2, GL_FLOAT, GL_FALSE, 0, 0);

}


void VerticesGrid::draw() const {

    /// The GL_ELEMENT_ARRAY_BUFFER binding is stored within the VAO.
    /// The GL_ARRAY_BUFFER​ binding is NOT part of the VAO state.
    /// But the vertex attribute binding to the VBO is retained.
    glBindVertexArray(_vertexArrayID);

    /// Draw the grid vertices.
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

}


void VerticesGrid::clean() {
    glDeleteBuffers(1, _vertexBufferIDs);
    glDeleteBuffers(1, &_elementBufferID);
    glDeleteVertexArrays(1, &_vertexArrayID);
}
