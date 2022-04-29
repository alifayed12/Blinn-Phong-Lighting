#pragma once

#include <string>

class Texture
{
	private:
		unsigned int m_ID;
		unsigned char* m_LocalBuffer;
		std::string m_FilePath;
		int m_Width, m_Height, m_BPP;
	public:
		Texture();
		Texture(const std::string& filePath);
		~Texture();

		void CreateTexture(const std::string& filePath);

		void Bind(unsigned int slot) const;
		void Unbind() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline int GetBPP() const { return m_BPP; }
};

