#include "Graphics.h"
#include "Window.h"
#include "FBX.h"

#define	TEXTURE_MAX	1000

static LPDIRECT3D9 g_Interface;
static LPDIRECT3DDEVICE9 g_Device;

struct LoadedTextureInfo
{
	char		filename[MAX_PATH];
	int			count;
	TEXTURE_DATA texData;
};

static LoadedTextureInfo g_loadedTextures[TEXTURE_MAX] = {};



bool InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false)
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}

	return true;
}

bool CreateGraphicsInterface()
{
	// インターフェース作成
	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_Interface == NULL)
	{
		return false;
	}

	return true;
}

bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param)
{
	present_param->BackBufferCount = 1;
	present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	present_param->Windowed = true;
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_param->EnableAutoDepthStencil = true;
	present_param->MultiSampleType = D3DMULTISAMPLE_NONE;
	present_param->MultiSampleQuality = 0;

	// デプスとステンシルバッファのフォーマット設定
	present_param->AutoDepthStencilFormat = D3DFMT_D24S8;

	// もしフルスクリーンなら
	if (present_param->Windowed == false)
	{
		present_param->BackBufferWidth = 1920.0f;
		present_param->BackBufferHeight = 1080.0f;

		present_param->FullScreen_RefreshRateInHz = 60.0f;
	}

	if (FAILED(g_Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&g_Device)))
	{
		return false;
	}

	return true;
}

bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param->BackBufferWidth;
	view_port.Height = present_param->BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(g_Device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void ReleaseGraphics()
{
	g_Device->Release();
	g_Interface->Release();
}

// 描画ステートの設定
void SetRenderMode(ERenderMode mode_, bool enableAlpa_)
{
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// αが無向な場合入力されたカラーをそのまま使う
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpa_)
	{
		// αが有効な場合はα値をカラーに影響させる
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// αテストでα値が0の場合は描画をしないように設定
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// αブレンドとαテストの有無を設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpa_);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpa_);


	switch (mode_)
	{
	case Normal:
		// αが有効 : (SrcColor * 1)  + (DestColor * 0)
		// αが無効 : (SrcColor * α) + (DestColor * (1 - α))
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case Add:
		// αが有効：(SrcColor * 1) + (DestColor * 1)
		// αが無効：(SrcColor * α) + (DestColor * 1)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Subtract:
		// αが有効：(DestColor * 1) - (SrcColor * 1)
		// αが無効：(DestColor * 1) - (SrcColor * α)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Multiple:
		// 共通 : (SrcColor * 0) + (DestColor * SrcColor
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	default:
		break;
	}
}

void DrawStart()
{
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	g_Device->BeginScene();
}

void DrawEnd()
{
	g_Device->EndScene();
	g_Device->Present(NULL, NULL, NULL, NULL);
}

//static const TEXTURE_DATA* LoadTexture(const char* file_name)
//{
//	for (int i = 0; i < TEXTURE_MAX; i++)
//	{
//		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
//		if (pInfo->count == 0) continue;
//
//		if (strcmp(pInfo->filename, file_name) == 0)
//		{
//			pInfo->count++;
//			return &pInfo->texData;
//		}
//	}
//
//	for (int i = 0; i < TEXTURE_MAX; i++)
//	{
//		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
//		if (pInfo->count != 0) continue;
//
//		IDirect3DTexture9* pTexture;
//		D3DXIMAGE_INFO info;
//		// ファイルからテクスチャーを生成する
//		HRESULT hr = D3DXCreateTextureFromFileExA(
//			GetD3DDevice(),	// Direct3DDevice
//			file_name,				// ファイル名
//			D3DX_DEFAULT,			// 横幅(D3DX_DEFAULTでファイルから判定)
//			D3DX_DEFAULT,			// 高さ(D3DX_DEFAULTでファイルから判定)
//			1,						// ミップマップの数
//			0,						// 使用用途
//			D3DFMT_A8R8G8B8,		// フォーマット
//			D3DPOOL_MANAGED,		// メモリの管理設定
//			D3DX_FILTER_NONE,		// フィルター設定
//			D3DX_DEFAULT,			// ミップマップフィルターの設定
//			0x00000000,				// カラーキー
//			&info,					// 画像情報
//			NULL,					// パレットデータ
//			&pTexture);				// 生成したテクスチャーの格納先
//		if (SUCCEEDED(hr))
//		{
//			D3DSURFACE_DESC desc;
//			// 生成したテクスチャーの情報を取得
//			pTexture->GetLevelDesc(0, &desc);
//			// テクスチャー情報の設定
//			pInfo->texData.Texture = pTexture;
//			pInfo->texData.srcWidth = info.Width;
//			pInfo->texData.srcHeight = info.Height;
//			pInfo->texData.Width = desc.Width;
//			pInfo->texData.Height = desc.Height;
//
//			return &pInfo->texData;
//		}
//		break;
//	}
//	return NULL;
//}
// テクスチャーの読み込み
bool LoadTexture(const char* file_name,TEXTURE_DATA* texture)
{
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_Device,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture->Texture)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture->Texture->GetLevelDesc(0, &desc)))
		{
			texture->Texture->Release();
			texture->Texture = NULL;
			return false;
		}
		texture->Width = (float)desc.Width;
		texture->Height = (float)desc.Height;
	}
	return true;
}

//bool LoadTexture(const char* pFileName, TEXTURE_DATA* pOut)
//{
//	if (pOut == NULL) return false;
//
//	const TEXTURE_DATA* pData = LoadTexture(pFileName);
//	if (pData == NULL) return false;
//
//	*pOut = *pData;
//	return true;
//}
//背景用

// テクスチャーの解放
void ReleaseTexture(TEXTURE_DATA* pTextureData)
{
	if (pTextureData == NULL) return;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (pInfo->texData.Texture == pTextureData->Texture)
		{
			pInfo->count--;
			if (pInfo->count == 0)
			{
				ZeroMemory(pInfo, sizeof(*pInfo));

				SAFE_RELEASE(pTextureData->Texture);
			}
		}
	}
}

const LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_Device;
}

void SetLight()
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction.x = 0.0f;
	light.Direction.y = -0.5f;
	light.Direction.z = 0.2f;
	light.Diffuse.a = 1.0f;
	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;
	light.Ambient.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec_direction);
	light.Range = 200.0f;
	g_Device->SetLight(0, &light);
	g_Device->LightEnable(0, true);
	g_Device->SetRenderState(D3DRS_LIGHTING, true);
}
