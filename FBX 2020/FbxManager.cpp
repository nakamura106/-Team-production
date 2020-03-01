#include "FbxManager.h"

FbxManagera::FbxManagera()
{
	if (m_Fbx == nullptr)
	{
		m_Fbx = new Fbx();
	}
}

FbxManagera::~FbxManagera()
{
	if (m_Fbx != nullptr)
	{
		delete m_Fbx;
		m_Fbx = nullptr;
	}
}

FBXMeshData FbxManagera::LoadFbxMesh(const char* pFilename_)
{
	return m_Fbx->LoadFbx(pFilename_);
}

void FbxManagera::ReleaseFbxMesh(FBXMeshData* pData_)
{
	if (pData_ == nullptr) { return; }
	m_Fbx->ReleaseFbxMesh(pData_);
}

void FbxManagera::DrawFbx(FBXMeshData* pMeshData)
{
	if (pMeshData == nullptr) { return; }
	m_Fbx->RenderFbxMesh(pMeshData);
}

void FbxManagera::Animation(FBXMeshData* pData_, float sec_)
{
	if (pData_ == nullptr) { return; }
	m_Fbx->Animate(pData_, sec_);
}

void FbxManagera::ResetAnimation(FBXMeshData* pData_)
{
	if (pData_ == nullptr) { return; }
	m_Fbx->ResetAnimate(pData_);
}
