#pragma once
#include<d3dcompiler.h>
#include<string>
struct FXCCompileParams
{
	std::wstring shaderFileName;
	std::string entryPoint;
	std::string target;
	UINT flags1;
	UINT flags2;
	ID3DBlob** compiledCode;
	ID3DBlob** errorMsgs;
};
class FXShaderCompiler
{
public:
	static void CompileShader(FXCCompileParams fxcCompileParams);
};