#include"DXShaderCompiler.h"
DX11Shader::DX11Shader()
	:m_shaderType(ShaderType::UNKNOWN),
	m_shaderSourceFileName(L"")
{}
DX11Shader::DX11Shader(std::wstring shaderName,ShaderType type)
	:m_shaderType(type),
	m_shaderSourceFileName(shaderName)
{

}
DX11Shader::~DX11Shader()
{

}
void DX11Shader::Init(std::wstring shaderName, ShaderType type, std::string entryPoint)
{
	m_shaderSourceFileName = shaderName;
	m_shaderType = type;
	m_entryPoint = entryPoint;
	//compile shader
	DXShaderCompiler::CompileShader(*this);

}