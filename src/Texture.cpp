#include "Texture.hpp"

#include "GL/glew.h"

#include "stb_image/stb_image.h"

#include <iostream>

Texture::Texture()
	: m_ID(0), m_FilePath(""), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
}

Texture::Texture(const std::string& filePath)
	: m_ID(0), m_FilePath(filePath), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	CreateTexture(m_FilePath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::CreateTexture(const std::string& filePath)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
