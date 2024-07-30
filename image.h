#pragma once

#include <stddef.h>
#include <string>
#include "vector2.h"

using namespace std;

class OLImage
{
private:
    OLVector2<size_t> size;
    void* data;

public:
    OLImage() = delete;

    OLImage(size_t image_width, size_t image_height);
    OLImage(size_t image_width, size_t image_height, void* image_data);
    OLImage(string texture_file);

    OLImage(OLImage& other) = delete;
    OLImage(OLImage&& other) = delete;
    OLImage operator=(OLImage& other) = delete;
    OLImage operator=(OLImage&& other) = delete;

    void* getData();
    OLVector2<size_t> getSize();

    ~OLImage();
};