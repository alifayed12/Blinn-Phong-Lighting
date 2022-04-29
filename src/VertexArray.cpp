#include "VertexArray.hpp"

#include <iostream>

VertexArray::VertexArray()
	: m_Stride(0)
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddLayout(unsigned int count)
{
	m_Elements.push_back( { count } );

	m_Stride += sizeof(float) * count;
}

void VertexArray::SetLayout()
{
	unsigned int offset = 0;
	for (int i = 0; i < m_Elements.size(); i++)
	{
		const auto element = m_Elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, GL_FLOAT, GL_FALSE, m_Stride, (const void*) offset);

		offset += sizeof(float) * element.count;
	}
}


