#pragma once

#include "vector3.h"
#include "matrix4.h"

class OLObject
{
public:
	OLVector3f local_position;
	OLVector4f local_rotation = OLVector4f{ 0, 0, -1, 0 };
	OLVector3f local_scale;

private:

public:
	inline OLMatrix4f getLocalTransform()
	{
		OLMatrix4f translation
		{
			1.0f, 0.0f, 0.0f, local_position.x,
			0.0f, 1.0f, 0.0f, local_position.y,
			0.0f, 0.0f, 1.0f, local_position.z,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		OLMatrix4f rotation = toMatrix(local_rotation);

		OLMatrix4f stretch
		{
			local_scale.x, 0.0f,          0.0f,          0.0f,
			0.0f,          local_scale.y, 0.0f,          0.0f,
			0.0f,          0.0f,          local_scale.z, 0.0f,
			0.0f,          0.0f,          0.0f,          1.0f
		};

		return translation * rotation * stretch;
	}
};