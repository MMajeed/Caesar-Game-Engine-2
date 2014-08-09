#include "3DMath.h"

float Length(const XMFLOAT4& a, const XMFLOAT4& b)
{
	XMVECTOR vector1 = XMVectorSet(a.x, a.y, a.z, a.w);
	XMVECTOR vector2 = XMVectorSet(b.x, b.y, b.z, b.w);
	XMVECTOR vectorSub = XMVectorSubtract(vector1, vector2);
	XMVECTOR length = XMVector4Length(vectorSub);

	float distance = 0.0f;
	XMStoreFloat(&distance, length);
	return distance;
}