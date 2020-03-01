#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_
#include "FBX.h"

class FbxManagera
{
public:
	FbxManagera();

	~FbxManagera();

	FBXMeshData LoadFbxMesh(const char* pFilename);

	void ReleaseFbxMesh(FBXMeshData* pMeshData);

	void DrawFbx(FBXMeshData* pMeshData);

	void Animation(FBXMeshData* pData_, float sec_);

	void ResetAnimation(FBXMeshData* pData_);
private:
	Fbx* m_Fbx;
};
#endif
