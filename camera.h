#pragma once

#include "matrix4.h"
#include "vector3.h"
#include "object.h"

class OLCamera : public OLObject
{
public:
	float near_clip = 0.1f;
	float far_clip = 100.0f;
	float horizontal_fov = 120.0f;
	float aspect_ratio = 4.0 / 3.0;

private:

public:
	OLMatrix4f getProjectionMatrix();
	static OLMatrix4f projectionMatrix(float near_clip_plane, float far_clip_plane, float horizontal_fov_degrees, float aspect_ratio);
};