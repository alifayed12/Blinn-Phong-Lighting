#pragma once

#include "glm/glm.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#include <vector>
#include <memory>

class Texture;

class Cube
{
private:
	glm::vec3 m_Position;

	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_EBO;
	Shader m_Shader;

	std::vector<Texture> m_Textures;
public:
	Cube(const void* vertices, uint32_t verticesSize, const void* indices, uint32_t indicesCount, const glm::vec3& position, const std::string& shaderPath, size_t textureCount = 5);
	~Cube() = default;

	void Bind();
	void Unbind();

	void AddLayout(int32_t size);
	void SetLayout();
	void SetTexture(const std::string& filePath, const std::string& uniformName, unsigned int slot);
	void UpdateMVP(const glm::mat4& perspective, const glm::mat4& view, const glm::mat4& model);

	glm::mat4 GetModelMatrix() const;

	Shader& GetShader();
	const std::vector<Texture>& GetTextures() const;

	unsigned int GetIndicesCount() const;
};

