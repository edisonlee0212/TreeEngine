#include "Shader.h"
#include "FileSystem.h"
Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath) : SharedComponentBase()
{
    _VertexShaderCodes.push_back("#version 420 core");
    _FragmentShaderCodes.push_back("#version 420 core");
    _GeometryShaderCodes.push_back("#version 420 core");
    AppendVertexShaderCode(FileSystem::GetPath("Shaders/Include/Camera.inc"));
    AppendFragmentShaderCode(FileSystem::GetPath("Shaders/Include/Camera.inc"));
    AppendFragmentShaderCode(FileSystem::GetPath("Shaders/Include/Material.inc"));
    AppendFragmentShaderCode(FileSystem::GetPath("Shaders/Include/Lighting/DirectionalLight.inc"));
    AppendFragmentShaderCode(FileSystem::GetPath("Shaders/Include/Lighting/PointLight.inc"));
    AppendFragmentShaderCode(FileSystem::GetPath("Shaders/Include/Lighting/SpotLight.inc"));
    AppendFragmentShaderCode(fragmentPath);
    AppendVertexShaderCode(vertexPath);

    if (!geometryPath._Equal(""))
    {
        AppendGeometryShaderCode(geometryPath);
    }

    
    CompileShader();
}

void Shader::AppendFragmentShaderCode(std::string path) {
    _FragmentShaderCodes.push_back(FileSystem::LoadFileAsString(path));
}

void Shader::AppendVertexShaderCode(std::string path) {
    _VertexShaderCodes.push_back(FileSystem::LoadFileAsString(path));
}

void Shader::AppendGeometryShaderCode(std::string path) {
    _GeometryShaderCodes.push_back(FileSystem::LoadFileAsString(path));
}

void Shader::CompileShader() {
    std::string vertexCode = "";
    std::string fragmentCode = "";
    std::string geometryCode = "";

    for (auto i : _VertexShaderCodes) vertexCode += i + "\n";
    for (auto i : _FragmentShaderCodes) fragmentCode += i + "\n";
    if (_GeometryShaderCodes.size() > 1) for (auto i : _GeometryShaderCodes) geometryCode += i + "\n";

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if (_GeometryShaderCodes.size() > 1)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (_GeometryShaderCodes.size() > 1)
        glAttachShader(ID, geometry);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (_GeometryShaderCodes.size() > 1)
        glDeleteShader(geometry);

}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            Debug::Error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            Debug::Error("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
        }
    }
}