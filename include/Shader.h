#pragma once
#include <include/glAPI.h>
#include <include/compile.h>

#ifdef DEBUG
#define ASSERT(func) assert(func);
#else
#define ASSERT(func)
#endif

class Shader {
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void BeginUse() const;		// 开始使用该着色器
	void StopUse() const;		// 结束使用该着色器
	GLuint GetProgram() const;	// 获取着色器编号

	void SetUniform(const std::string&, float) const;
private:
	// 生成shader可执行程序
	inline void GenShader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	inline bool CompileShader(GLint shader);	// 代码编译并检查错误
	inline void LinkShader(GLint vShader, GLint fShader);
	GLuint m_program;
};