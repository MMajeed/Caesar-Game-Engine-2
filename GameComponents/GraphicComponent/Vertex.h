#ifndef __Vertex__
#define __Vertex__

#include "Linker.h"

#include <D3D11.h>
#include <xnamath.h>

struct Vertex
{
	XMFLOAT4 Pos;
	XMFLOAT4 Normal;
	XMFLOAT2 Texture;   
};

#endif //__Vertex__