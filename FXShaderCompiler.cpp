#include"FXShaderCompiler.h"
#include"DX11Common.h"
#pragma comment(lib,"d3dcompiler.lib")
void FXShaderCompiler::CompileShader(FXCCompileParams fxcCompileParams)
{
	HRESULT res = (D3DCompileFromFile(fxcCompileParams.shaderFileName.c_str(), nullptr, nullptr, fxcCompileParams.entryPoint.c_str(), fxcCompileParams.target.c_str(), fxcCompileParams.flags1, fxcCompileParams.flags2, fxcCompileParams.compiledCode, fxcCompileParams.errorMsgs));
	ID3DBlob* errorBlob = (*fxcCompileParams.errorMsgs);
	const char* errorMsg;
	if(errorBlob != nullptr)
	{
		errorMsg = reinterpret_cast<const char*>(errorBlob->GetBufferPointer());
		assert(false);
	}
}