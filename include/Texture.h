#pragma once
#include <include/glAPI.h>
#include <string>
class Texture {
public:
	Texture(const std::string& path, unsigned int texUnit);
	~Texture();

	void BindTexture();
	unsigned int GetTextureUnit();	// 返回该Texture绑定的纹理单元

private:
	GLuint m_texture;		// 该texture的编号
	int m_width;			// texture的宽
	int m_height;			// texture的高
	unsigned int m_texUnit;	// 该texture绑定的纹理单元
};