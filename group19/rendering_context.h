
#ifndef __rendering_context_h__
#define __rendering_context_h__

/// Forward declarations (no header includes) (namespace pollution, build time).
class Vertices;

/// @brief OpenGL wrapper class template
class RenderingContext {

public:

    /// Common methods of all RenderingContext.
    void clean();

protected:

    /// Common methods of all RenderingContext.
    RenderingContext(unsigned int width, unsigned int height);
    void init(Vertices* vertices, const char* vshader, const char* fshader, const char* vertexAttribName, int frameBufferID);
    void draw() const;

    /// Helper function.
    void set_texture(unsigned int textureIndex, int textureID, const char* uniformName, unsigned int target);

    /// Common properties of all RenderingContext.
    const unsigned int _width, _height;
    unsigned int _programID;

    /// Pointer : vertices object can be shared between RenderingContext.
    Vertices* _vertices;

private:

    /// Common properties of all RenderingContext.
    unsigned int _frameBufferID;

    /// Textures.
    struct texture {
        int ID;
        unsigned int target;
    };
    static const int _nTextures = 20;
    struct texture _textures[_nTextures];

};

#endif /* __rendering_context_h__ */
