#ifndef DRAWBUFFER_H_
#define DRAWBUFFER_H_

#include "Graphics.h"

// 頂点バッファの生成
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size);
// インデックスバッファの生成
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size);



#endif