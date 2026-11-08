#pragma once
#include <glad/gl.h>
#include <string>

class Texture {
private:
    GLuint textureID;

public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(GLuint unit = 0) const;

    GLuint getID() const { return textureID; }
};