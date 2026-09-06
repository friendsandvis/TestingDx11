#include"DXCamera.h"

void DXCamera::SetAspectRatio(float viewWidth, float viewHeight)
{
	m_ViewWidth = viewWidth;
	m_ViewHeight = viewHeight;
	m_Aspectratio = viewWidth / viewHeight;
}

DXCamera::DXCamera()
{
	m_camerapos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_cameraTargetpos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_forwardDir = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_rightDir = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_Aspectratio = 0.0f;
	m_Fov_degree = 45.0f;
	m_FarPlane = 0.0f;
	m_NearPlane = 0.0f;
	m_ViewWidth = 0.0f;
	m_ViewHeight = 0.0f;
}
XMMATRIX DXCamera::GetProjectionMat(bool ortho)
{
	if (ortho)
	{
		return DirectX::XMMatrixOrthographicLH(m_ViewWidth,m_ViewHeight, m_NearPlane, m_FarPlane);
	}
	else
	{
		return XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov_degree), m_Aspectratio, m_NearPlane, m_FarPlane);
	}
}

XMMATRIX DXCamera::GetViewMat()
{
#ifdef UPDATECAMERAVECTORTECHNIQUE_UPDATETARGETPOSITION
	return DirectX::XMMatrixLookAtLH(m_camerapos, m_cameraTargetpos, m_upDir);
#else
	XMVECTOR focusPos = m_camerapos + m_forwardDir;
	return XMMatrixLookAtLH(m_camerapos, focusPos , m_upDir);
#endif // UPDATECAMERAVECTORTECHNIQUE_UPDATETARGETPOSITION
}

void DXCamera::Reset(XMVECTOR camPos, XMVECTOR camTargetPos, float viewWidth, float viewHeight, float nearPlane, float farPlane)
{
	m_camerapos = camPos;
	m_cameraTargetpos = camTargetPos;
	m_ViewWidth = viewWidth;
	m_ViewHeight = viewHeight;
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
	SetAspectRatio(viewWidth, viewHeight);
	m_forwardDir = XMVector3Normalize(m_cameraTargetpos - m_camerapos);
	m_rightDir = XMVector3Cross(m_upDir, m_forwardDir);
}

void DXCamera::UpdateCameraVectors(float pitch, float yaw)
{
	double pitchinrads = (double)XMConvertToRadians(pitch);
	double yawinrads = (double)XMConvertToRadians(yaw);
#ifdef UPDATECAMERAVECTORTECHNIQUE_UPDATETARGETPOSITION
	XMVECTOR camToTargetVec = m_cameraTargetpos - m_camerapos;
	float camToTargetVecDistance = 0.0f;
	XMVECTOR camToTargetVecDistanceVec = XMVector3Length(camToTargetVec);
	XMStoreFloat(&camToTargetVecDistance, camToTargetVecDistanceVec);
	camToTargetVec = XMVector3Normalize(camToTargetVec);
	XMMATRIX xaxisrotation = XMMatrixRotationX(pitchinrads);
	camToTargetVec = XMVector4Transform(camToTargetVec, xaxisrotation);
	XMMATRIX yaxisrotation = XMMatrixRotationY(yawinrads);
	camToTargetVec = XMVector4Transform(camToTargetVec, yaxisrotation);
	XMVECTOR camToTargetVecResultant = camToTargetVec * camToTargetVecDistance;
	m_cameraTargetpos = m_camerapos + camToTargetVecResultant;
	m_forwardDir = XMVector3Normalize(m_cameraTargetpos - m_camerapos);
	m_rightDir = XMVector3Cross(m_upDir, m_forwardDir);
#else
	double x = cos(yawinrads) * cos(pitchinrads);
	float xF = static_cast<float>(x);
	double y = sin(pitchinrads);
	float yF = static_cast<float>(y);
	double z = sin(yawinrads) * cos(pitchinrads);
	float zF = static_cast<float>(z);
	XMVECTOR newforward = XMVectorSet(xF, yF, zF, 0.0f);
	XMFLOAT4 newForwardExtract;
	XMStoreFloat4(&newForwardExtract, newforward);
	newforward = XMVector3Normalize(newforward);
	m_forwardDir = newforward;
	m_rightDir = XMVector3Cross(m_upDir, m_forwardDir);
#endif // UPDATECAMERAVECTORTECHNIQUE_UPDATETARGETPOSITION
}