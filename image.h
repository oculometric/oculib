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

    OLImage(size_t image_width, size_t image_height) { /* TODO: */ };
    OLImage(size_t image_width, size_t image_height, void* image_data) { /* TODO: */ };
    OLImage(string texture_file) { /* TODO: */ };

    OLImage(OLImage& other) = delete;
    OLImage(OLImage&& other) = delete;
    OLImage operator=(OLImage& other) = delete;
    OLImage operator=(OLImage&& other) = delete;

    inline void* getData() { return data; }
    inline OLVector2<size_t> getSize() { return size; }

    ~OLImage() { /* TODO: */ };
};