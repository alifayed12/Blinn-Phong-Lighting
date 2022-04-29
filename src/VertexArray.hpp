#pragma once

#include "GL/glew.h"

#include <vector>

struct Element
{
	unsigned int count;
};

class VertexArray
{
	private:
		unsigned int m_ID;
		unsigned int m_Stride;
		std::vector<Element> m_Elements;
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddLayout(unsigned int count);
		void SetLayout();
};

