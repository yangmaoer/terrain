#version 330 core

// Transformation matrix from world space to light clip space.
uniform mat4 lightViewProjection;

// Texture 0. Defined by glActiveTexture and passed by glUniform1i.
uniform sampler2D heightMapTex;

// Vertices 2D position in world space.
// First input buffer. Defined here, retrieved in C++ by glGetAttribLocation.
layout(location = 0) in vec2 vertexPosition2DWorld;

// Vertex position (mandatory output).
out gl_PerVertex {
    vec4 gl_Position;
};


void main() {

    // World (triangle grid) coordinates are (-1,-1) x (1,1).
    // Texture (height map) coordinates are (0,0) x (1,1).
    vec2 UV = (vertexPosition2DWorld + 1.0) / 2.0;
    float height = texture2D(heightMapTex, UV).r;

    // 3D vertex position : X and Y from vertex array, Z from heightmap texture.
    vec3 vertexPosition3DWorld = vec3(vertexPosition2DWorld.xy, height);

    // View matrix transforms from world space to camera space.
    // Projection matrix transforms from camera space to clip space (homogeneous space).
    gl_Position = lightViewProjection * vec4(vertexPosition3DWorld, 1.0);

}
