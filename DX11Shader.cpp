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
ComPtr<ID3D11VertexShader> DX11Shader::GetVertexShader()
{
	assert(m_shaderType == ShaderType::VS);
	return vs;
}
ComPtr<ID3D11PixelShader> DX11Shader::GetPixelShader()
{
	assert(m_shaderType == ShaderType::PS);
	return ps;
}
ComPtr<ID3D11ComputeShader> DX11Shader::GetComputeShader()
{
	assert(m_shaderType == ShaderType::CS);
	return cs;
}