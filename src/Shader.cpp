#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "include/Error.h"
#include "include/Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath) {
	using namespace std;
	string vertSrcCode;
	string fragSrcCode;
	ifstream vertFile;
	ifstream fragFile;
	// 读取文件异常时抛出异常
	vertFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		vertFile.open(vertPath);
		fragFile.open(fragPath);
		stringstream vertShaderStream, fragShaderStream;
		vertShaderStream << vertFile.rdbuf();
		fragShaderStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();

		vertSrcCode = vertShaderStream.str();
		fragSrcCode = fragShaderStream.str();
	}
	catch (ifstream::failure& error) {
		std::cout << "[Error]: Shader file error" << error.what() << "\n";
	}

	GenShader(vertSrcCode.c_str(), fragSrcCode.c_str());
}

inline void Shader::GenShader(const char* vertSrcCode, const char* fragSrcCode) {
	// 创建shader程序
	GLuint vShader, fShader;
	vShader = CALL(glCreateShader(GL_VERTEX_SHADER));
	fShader = CALL(glCreateShader(GL_FRAGMENT_SHADER));

	// 传入shader代码到源代码编译器
	CALL(glShaderSource(vShader, 1, &vertSrcCode, NULL));
	CALL(glShaderSource(fShader, 1, &fragSrcCode, NULL));

	// 代码编译并检查代码编译结果
	ASSERT(CompileShader(vShader));
	ASSERT(CompileShader(fShader));

	LinkShader(vShader, fShader);
	
	// 清理中间编译产物 vShader和fShader
	CALL(glDeleteShader(vShader));
	CALL(glDeleteShader(fShader));
}

inline bool Shader::CompileShader(GLint shader) {
	// 代码编译并检查代码编译结果
	CALL(glCompileShader(shader));
	GLint compileStatus;
	// 获取代码编译结束状态
	CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus) {
		return true;
	}
	else {
		char infoLog[1024];	// 错误日志
		CALL(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
		// 将vShader的编译错误储存到长度为1024个字节的char数组infoLog中
		std::cout << "[Error]: shader compile error\n" << infoLog << "\n";
		return false;
	}
}

inline void Shader::LinkShader(GLint vShader, GLint fShader) {
	// 链接两个shader程序
	// 创建shaders program盒子
	m_program = CALL(glCreateProgram());
	GLint compileStatus;
	// 将编译好的两个shader放入这个盒子
	CALL(glAttachShader(m_program, vShader));
	CALL(glAttachShader(m_program, fShader));
	// 将这两个shader链接形成可执行程序
	CALL(glLinkProgram(m_program));
	// 获取代码编译结束状态
	CALL(glGetProgramiv(m_program, GL_LINK_STATUS, &compileStatus));
	if (compileStatus == 0) {
		char infoLog[1024];	// 错误日志
		CALL(glGetProgramInfoLog(m_program, 1024, NULL, infoLog));
		// 将program的链接错误储存到长度为1024个字节的char数组infoLog中
		std::cout << "[Error]: shader link error\n" << infoLog << "\n";
		assert(false);
	}
}

Shader::~Shader() { }

void Shader::BeginUse() const { CALL(glUseProgram(m_program)); }
void Shader::StopUse() const { CALL(glUseProgram(0)); }
GLuint Shader::GetProgram() const { return m_program; }

void Shader::SetUniform(const std::string& name, float value) const {
	// 通过名称获取uniform变量的位置
	GLuint location = CALL(glGetUniformLocation(m_program, name.c_str()));
	// 通过location更新uniform变量的值
	CALL(glUniform1f(location, value));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z) const {
	// 通过名称获取uniform变量的位置
	GLuint location = CALL(glGetUniformLocation(m_program, name.c_str()));
	// 通过location更新uniform变量的值
	CALL(glUniform3f(location, x, y, z));
}

void Shader::SetUniform(const std::string& name, int value) const {
	// 通过名称获取uniform变量的位置
	GLuint location = CALL(glGetUniformLocation(m_program, name.c_str()));
	// 通过location更新uniform变量的值
	CALL(glUniform1i(location, value));
}

void Shader::SetSample(const std::string& textureName, unsigned int texUnit) {
	// 通过名称获取uniform变量的位置
	GLuint location = CALL(glGetUniformLocation(m_program, textureName.c_str()));
	// 通过location更新uniform变量的值
	CALL(glUniform1i(location, texUnit));
}