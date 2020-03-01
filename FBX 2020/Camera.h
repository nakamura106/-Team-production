#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

class CAMERA
{
public:
	CAMERA(float camera_x, float camera_y, float camera_z) :
		m_WalkSpeed(2.0f),
		m_SprintSpeed(6.0f)
	{
		m_CameraPos.x = camera_x;
		m_CameraPos.y = camera_y;
		m_CameraPos.z = camera_z;

		m_EyePos.x = 0.0f;
		m_EyePos.y = 5.0f;
		m_EyePos.z = -.0f;

		m_CameraUp.x = 0.0f;
		m_CameraUp.y = 1.0f;
		m_CameraUp.z = 0.0f;

		m_RotateSpeed = 0.05f;

		m_Yaw = 0.0f;
		m_Pitch = 0.0f;
		m_Roll = 0.0f;

		m_Speed = m_WalkSpeed;

		D3DXMatrixIdentity(&m_MatView);
	}

	// カメラ座標の更新
	void Update();

	// カメラの移動
	void Move();

	void CAMERA::MouseRotate();

	// カメラの前向きベクトルを出す
	D3DXVECTOR3 GetCameraForward();

private:
	/* カメラの移動速度 Walk */
	const float m_WalkSpeed;

	/* カメラの移動速度 Sprint */
	const float m_SprintSpeed;

	/* カメラの位置 */
	D3DXVECTOR3 m_CameraPos;

	/* 注視点 */
	D3DXVECTOR3 m_EyePos;

	/* カメラの上向きのベクトル */
	D3DXVECTOR3 m_CameraUp;

	/* カメラのビュー情報を保存する変数 */
	D3DXMATRIX m_MatView;

	/* 角度 */
	float m_Rad;

	/* 回転速度 */
	float m_RotateSpeed;

	/* X軸回転 */
	float m_Yaw;

	/* Y軸回転 */
	float m_Pitch;

	/* Z軸回転 */
	float m_Roll;

	/* スピード */
	float m_Speed;

	/* 移動速度 */
	D3DXVECTOR3 m_Velocity;

};

#endif