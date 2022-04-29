#include "Cube.hpp"

#include "Texture.hpp"

#include "glm/gtc/matrix_transform.hpp"

Cube::Cube(const void* vertices, uint32_t verticesSize, const void* indices, uint32_t indicesCount, const glm::vec3& position, const std::string& shaderPath, size_t textureCount)
	: m_Position(position), m_VAO(), m_VBO(vertices, verticesSize), m_EBO(indices, indicesCount), m_Shader(shaderPath)
{
	m_Textures.reserve(textureCount);
	Unbind();
}

void Cube::Bind()
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_EBO.Bind();
	m_Shader.Bind();
}

void Cube::Unbind()
{
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
	m_Shader.Unbind();
}

void Cube::AddLayout(int32_t size)
{
	m_VAO.AddLayout(size);
}

void Cube::SetLayout()
{
	m_VAO.SetLayout();
}

void Cube::SetTexture(const std::string& filePath, const std::string& uniformName, unsigned int slot)
{
	m_Textures.emplace_back(filePath);
	m_Shader.SetUniform1i(uniformName, slot);
}

void Cube::UpdateMVP(const glm::mat4& perspective, const glm::mat4& view, const glm::mat4& model)
{
	m_Shader.SetUniformMat4("u_MVP", perspective * view * model);
}

glm::mat4 Cube::GetModelMatrix() const
{
	return glm::translate(glm::mat4(1.0f), m_Position);
}

Shader& Cube::GetShader()
{
	return m_Shader;
}

const std::vector<Texture>& Cube::GetTextures() const
{
	return m_Textures;
}

unsigned int Cube::GetIndicesCount() const
{
	return m_EBO.GetCount();
}