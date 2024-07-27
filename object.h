#pragma once

#include "vector3.h"
#include "matrix4.h"

class OLObject
{
public:
	OLVector3f local_position;
	OLVector4f local_rotation;
	OLVector3f local_scale;

private:

public:
	OLMatrix4f getLocalTransform()
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

		return stretch * rotation * translation;
	}

	static OLMatrix4f objectMatrix(const OLVector3f& position, const OLVector3f& right, const OLVector3f& up, const OLVector3f& back, const OLVector3f& scale)
	{
		OLMatrix4f translation
		{
			1.0f, 0.0f, 0.0f, position.x,
			0.0f, 1.0f, 0.0f, position.y,
			0.0f, 0.0f, 1.0f, position.z,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		OLMatrix4f rotation
		{
			right.x, up.x, back.x, 0.0f,
			right.y, up.y, back.y, 0.0f,
			right.z, up.z, back.z, 0.0f,
			0.0f,    0.0f, 0.0f,   1.0f
		};

		OLMatrix4f stretch
		{
			scale.x, 0.0f,    0.0f,    0.0f,
			0.0f,    scale.y, 0.0f,    0.0f,
			0.0f,    0.0f,    scale.z, 0.0f,
			0.0f,    0.0f,    0.0f,    1.0f
		};

		OLMatrix4f transform = stretch * rotation * translation;
		return transform;
	}
};