#ifndef __Vertex__
#define __Vertex__


#include <D3D11.h>
#include <xnamath.h>

struct Vertex
{
	XMFLOAT4 Pos;
	XMFLOAT4 Normal;
	XMFLOAT2 Texture0;
	XMFLOAT2 Texture1;    
};

#endif //__Vertex__