
#ifndef __vertices_camera_pictorial_h__
#define __vertices_camera_pictorial_h__

#include "vertices.h"

class VerticesCameraPictorial : public Vertices {

public:

    /// Generate the vertices.
    void generate();

    /// Bind the vertex attribute to the VBO (retained in VAO state).
    void bind(unsigned int vertexAttribID) const;

    /// Draw the scene.
    void draw() const;

    /// Delete the buffers.
    void clean();

};

#endif /* __vertices_camera_pictorial_h__ */