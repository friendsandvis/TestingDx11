#pragma once
#include"DX11Common.h"
//#define UPDATECAMERAVECTORTECHNIQUE_UPDATETARGETPOSITION
/*
* two techniques used to update camera vectors with Pitch and yaw angles.
* 1. old does not update target position where pitch and yaw vector are used to calculate forwardvector directly by using sin & cos(target position is ignored)
* 2. new where pitch & yaw are used to rotate previous camera vectors along CX & Y axis,target position is updated.
* do note both varients use different way of interpreting mouse X,Y offset 1 as pitch yaw change directly and other with actual rotations.
*/
class DXCamera
{
public:
	DXCamera();
	XMMATRIX GetViewMat();
	XMMATRIX GetProjectionMat(bool ortho = false);
	void SetCamPos(XMVECTOR camPos)
	{
		m_camerapos = camPos;
	}
	void SetCamTargetPos(XMVECTOR camTargetPos)
	{
		m_cameraTargetpos = camTargetPos;
	}
	void SetNearPlane(float nearPlane)
	{
		m_NearPlane = nearPlane;
	}
	void SetFarPlane(float farPlane)
	{
		m_FarPlane = farPlane;
	}
	void SetFovDegree(float fov_degree)
	{
		m_Fov_degree = fov_degree;
	}
	float GetFovDegree() const
	{
		return m_Fov_degree;
	}

	XMVECTOR GetCamPos() const
	{
		return m_camerapos;
	}
	XMVECTOR GetCamTargetPos() const
	{
		return m_cameraTargetpos;
	}

	XMVECTOR GetCamRight()
	{

		return m_rightDir;
	}

	XMVECTOR GetCamForward()
	{

		return m_forwardDir;
	}

	void SetAspectRatio(float viewWidth, float viewHeight);
	void Reset(XMVECTOR camPos, XMVECTOR camTargetPos, float viewWidth, float viewHeight, float nearPlane, float farPlane);
	void UpdateCameraVectors(float pitch, float yaw);
private:
	XMVECTOR m_camerapos;
	XMVECTOR m_cameraTargetpos;
	XMVECTOR m_upDir;
	XMVECTOR m_forwardDir, m_rightDir;
	float m_NearPlane;
	float m_FarPlane;
	float m_ViewWidth;
	float m_ViewHeight;
	float m_Aspectratio;
	float m_Fov_degree;
};