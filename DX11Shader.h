#pragma once
#include<d3dcompiler.h>
#include<string>
#include"DX11Common.h"

enum class ShaderType
{
	UNKNOWN,
	VS,
	PS,
	CS
};
class DX11Shader
{
public:
	DX11Shader();
	DX11Shader(std::wstring shaderName,ShaderType type);
	~DX11Shader();
	void Init(ComPtr<ID3D11Device> device,std::wstring shaderName, ShaderType type,std::string entryPoint);
	ComPtr<ID3DBlob>& GetCompiledCode(){ return m_compiledCode; }
	ComPtr<ID3DBlob>& GetErrorMsgs(){ return m_compileErrorMsgs; }
	std::wstring GetShaderSourceFileName() const { return m_shaderSourceFileName; }
	ShaderType GetShaderType() const { return m_shaderType; }
	std::string GetEntryPoint() const { return m_entryPoint; }
	ComPtr<ID3DBlob> GetCompiledCode() const { return m_compiledCode; }
	ComPtr<ID3D11VertexShader> GetVertexShader();
	ComPtr<ID3D11PixelShader> GetPixelShader();
	ComPtr<ID3D11ComputeShader> GetComputeShader();
private:
	ShaderType m_shaderType;
	std::wstring m_shaderSourceFileName;
	std::string m_entryPoint;
	ComPtr<ID3DBlob> m_compiledCode;
	ComPtr<ID3DBlob> m_compileErrorMsgs;
	//shaderinterface used based on type
	ComPtr<ID3D11VertexShader> vs;
	ComPtr<ID3D11PixelShader> ps;
	ComPtr<ID3D11ComputeShader> cs;
	void GetShaderCommon();
	
};
