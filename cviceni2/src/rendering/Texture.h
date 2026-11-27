/**
 * @file Texture.h
 * @brief Class representing an OpenGL 2D texture loaded from an image file.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
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
