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
	OLMatrix4f getLocalTransform();
	static OLMatrix4f objectMatrix(const OLVector3f& position, const OLVector3f& right, const OLVector3f& up, const OLVector3f& back, const OLVector3f& scale);
};