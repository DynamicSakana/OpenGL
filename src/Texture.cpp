#define STB_IMAGE_IMPLEMENTATION
#include <include/stb_image.h>
#include "include/Texture.h"
#include "include/Error.h"

Texture::Texture(const std::string& path, unsigned int texUnit) {
	m_texUnit = texUnit;
	// 读取图片
	int channel;
	stbi_set_flip_vertically_on_load(true);	// 反转y轴	
	unsigned char* data;
	data = stbi_load(path.c_str(), &m_width, &m_height, &channel, STBI_rgb_alpha);
	// 生成纹理对象并绑定
	CALL(glGenTextures(1, &m_texture));
	CALL(glActiveTexture(GL_TEXTURE0 + texUnit));
	CALL(glBindTexture(GL_TEXTURE_2D, m_texture));
	// 传输纹理数据
	// 参数列表
	CALL(glTexImage2D(
		GL_TEXTURE_2D,		// 纹理类型
		0,					// mipmap等级
		GL_RGBA,			// 纹理颜色格式：RGB或者RGBA
		m_width,			// 图片宽度
		m_height,			// 图片高度
		0,					// 无用参数，直接写0
		GL_RGBA,			// 图片颜色格式：RGB或者RGBA
		GL_UNSIGNED_BYTE,	// 图片数据RGBA的值数据通道类型
		data				// 图片数据
	));
	// 自动生成各级mipmap纹理
	CALL(glGenerateMipmap(GL_TEXTURE_2D));
	// 清理cpu端数据
	stbi_image_free(data);
	// 纹理过滤	GL_LINEAR：生成新的像素点 GL_NEAREST：选择最近的像素点
	// 若绘制的时候纹理被收缩，使用 GL_TEXTURE_MIN_FILTER
	// 若绘制的时候纹理被拉伸，使用 GL_TEXTURE_MAG_FILTER
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// 设置wrapper
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// u方向的参数（横向）
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));	// v方向的参数（纵向）
}

Texture::~Texture() {
	if (m_texture)
		CALL(glDeleteTextures(1, &m_texture));
}

void Texture::BindTexture() {
	// 先绑定到当前的纹理单元，再去修改当前的纹理对象，因为GL状态机在调用这个函数的时候不一定绑定着这个Texture对象
	CALL(glActiveTexture(GL_TEXTURE0 + m_texUnit));
	CALL(glBindTexture(GL_TEXTURE_2D, m_texture));
}

unsigned int Texture::GetTextureUnit() { return m_texUnit; }
int Texture::GetWidth() const { return m_width; }
int Texture::GetHeight() const { return m_height; }