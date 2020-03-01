#include "Camera.h"
#include "Input.h"
#include "Graphics.h"

void CAMERA::Update()
{
	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 camera_pos(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z); // カメラ位置
	D3DXVECTOR3 eye_pos(m_EyePos.x, m_EyePos.y, m_EyePos.z);// 注視点
	D3DXVECTOR3 up_vector(m_CameraUp.x, m_CameraUp.y, m_CameraUp.z);	// カメラの向き;

	D3DXMatrixLookAtLH(&m_MatView,
		&camera_pos,				// カメラ座標
		&eye_pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル

	GetD3DDevice()->SetTransform(D3DTS_VIEW, &m_MatView);
	//ビュー座標変換用の行列算出 end

	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	GetD3DDevice()->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	// 視錐台の作成
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		1.1f,				// near
		2000.0f);			// far
	GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	//射影座標変換用の行列算出 end
}

void CAMERA::Move()
{
	// カメラの前向きベクトルを出す
	D3DXVECTOR3 forward;
	forward = m_EyePos - m_CameraPos;

	// ベクトルの正規化
	D3DXVec3Normalize(&forward, &forward);
	//forward.y = 0.0f;

	// カメラの左向きのベクトル
	// 前向きのベクトルに直角なベクトルを算出する
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

	m_Velocity.x = forward.x * m_Speed;
	m_Velocity.z = forward.z * m_Speed;

#pragma region カメラの移動
	// 前
	if (GetKey(W_KEY)) {
		m_CameraPos.x += forward.x * m_Speed;
		m_CameraPos.y += forward.y * m_Speed;
		m_CameraPos.z += forward.z * m_Speed;
	}
	// 後
	if (GetKey(S_KEY)) {
		m_CameraPos.x -= forward.x * m_Speed;
		m_CameraPos.z -= forward.z * m_Speed;
	}
	// 左
	if (GetKey(A_KEY)) {
		m_CameraPos.x -= left.x * m_Speed;
		m_CameraPos.z += left.z * m_Speed;
	}
	// 右
	if (GetKey(D_KEY)) {
		m_CameraPos.x += left.x * m_Speed;
		m_CameraPos.z -= left.z * m_Speed;
	}

#pragma endregion

}

D3DXVECTOR3 CAMERA::GetCameraForward()
{
	return D3DXVECTOR3();
}

void CAMERA::MouseRotate()
{
	SetCursorPos(960, 540);

	m_Yaw -= (GetMousePos().X - 960) / 1920 * 50;
	m_Pitch -= (GetMousePos().Y - 540) / 1080 * 20;
	if (m_Pitch > 90.0f) { m_Pitch = 180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }

	m_EyePos.x = m_CameraPos.x + cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_EyePos.y = m_CameraPos.y + sinf(D3DXToRadian(m_Pitch));
	m_EyePos.z = m_CameraPos.z + sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}
