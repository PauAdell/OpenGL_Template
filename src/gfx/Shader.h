#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
    unsigned int ID;

    // Loads, compiles, links
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, const glm::vec3& value) const;
    void setVec4(const std::string &name, const glm::vec4& value) const;
    void setMat4(const std::string &name, const glm::mat4& mat) const;

private:
    static std::string readFile(const std::string& path);
    static unsigned int compileStage(GLenum type, const std::string& source, const std::string& debugName);
    static void linkProgram(unsigned int program, unsigned int vs, unsigned int fs);
};
