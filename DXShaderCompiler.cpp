#include"DXShaderCompiler.h"
#include"FXShaderCompiler.h"
void DXShaderCompiler::CompileShader(DX11Shader& shader)
{
#if USEDXSHADERCOMPILER
	//configure dx cpompiler parameters
#else
	//configure fx compiler parameters
	FXCCompileParams fxcCompileParams;
	fxcCompileParams.shaderFileName = shader.GetShaderSourceFileName();
	fxcCompileParams.entryPoint = shader.GetEntryPoint();
	//determine target profile from type of shader
	switch (shader.GetShaderType())
	{
		case ShaderType::VS:
			fxcCompileParams.target = "vs_5_0";
			break;
		case ShaderType::PS:
			fxcCompileParams.target = "ps_5_0";
			break;
		case ShaderType::CS:
			fxcCompileParams.target = "cs_5_0";
			break;
	default:
		//unsupported shader type for compilation
		assert(false);
		break;
	}
	fxcCompileParams.compiledCode = shader.GetCompiledCode().GetAddressOf();
	fxcCompileParams.errorMsgs = shader.GetErrorMsgs().GetAddressOf();
#if SKIPSHADEROPTIMIZATION
	fxcCompileParams.flags1 = D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	fxcCompileParams.flags1 = 0;
#endif//SKIPSHADEROPTIMIZATION
	fxcCompileParams.flags2 = 0;
	FXShaderCompiler::CompileShader(fxcCompileParams);
	if (ID3DBlob* errorBlob = shader.GetErrorMsgs().Get())
	{
		assert(errorBlob->GetBufferSize() == 0);
	}
#endif
}