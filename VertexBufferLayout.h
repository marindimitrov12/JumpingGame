#pragma once
#include <vector>
#include <glad/glad.h>

struct VertextBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	
	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type) 
		{
		case GL_FLOAT:return 4;
		case GL_UNSIGNED_INT:return 4;
		case GL_UNSIGNED_BYTE:return 1;
		
		}
		return 0;
	}
};
class VertexBufferLayout
{
private:
	std::vector<VertextBufferElement>m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) 
	{
	}
	template<typename T>

	void Push(unsigned int count)
	{
		static_assert(false,"must use correct specialization");
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += count*VertextBufferElement::GetSizeOfType(GL_FLOAT);
		
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
		m_Stride += count*VertextBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	
	inline const std::vector<VertextBufferElement>GetElements() const& { return m_Elements; }
	inline unsigned int GetStride()const { return m_Stride; }

};
