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
void DX11Shader::Init(ComPtr<ID3D11Device> device,std::wstring shaderName, ShaderType type, std::string entryPoint)
{
	m_shaderSourceFileName = shaderName;
	m_shaderType = type;
	m_entryPoint = entryPoint;
	//compile shader
	DXShaderCompiler::CompileShader(*this);
	if(m_compiledCode.Get() != nullptr)
	{
		//create shader interface based on type
		switch (m_shaderType)
		{
			case ShaderType::VS:
				DXASSERT(device->CreateVertexShader(m_compiledCode->GetBufferPointer(), m_compiledCode->GetBufferSize(), nullptr, vs.GetAddressOf()));
				break;
			case ShaderType::PS:
				DXASSERT(device->CreatePixelShader(m_compiledCode->GetBufferPointer(), m_compiledCode->GetBufferSize(), nullptr, ps.GetAddressOf()));
				break;
			case ShaderType::CS:
				DXASSERT(device->CreateComputeShader(m_compiledCode->GetBufferPointer(), m_compiledCode->GetBufferSize(), nullptr, cs.GetAddressOf()));
				break;
			default:
				assert(false);
				break;
		}
	}
	else
	{

		assert(false);
	}

}