#pragma once
//2  compilers for dx one is fxc and other is dxc
#define USEDXSHADERCOMPILER 0 
#define SKIPSHADEROPTIMIZATION 1
#include"FXShaderCompiler.h"
#include"DX11Shader.h"

class DXShaderCompiler
{
public:
	static void CompileShader(DX11Shader& shader);
};