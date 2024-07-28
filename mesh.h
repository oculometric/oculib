#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "vertex.h"

using namespace std;

// TODO: support for per-corner UVs and normals

class OLMesh
{
public:
    vector<OLVertex> vertices;
    vector<uint16_t> indices;

    inline void loadOBJ(const char* path);
    inline void loadFBX(const char* path);
    inline void loadSTL(const char* path);
    inline void loadGLTF(const char* path);

public:
    inline OLMesh()
    {
        vertices.clear();
        indices.clear();
    }

    inline OLMesh(const char* path)
    {
        vertices.clear();
        indices.clear();

        // TODO: switch on different file types
        loadOBJ(path);
    }

    void combine(const OLMesh& other);

};

struct OLFaceCornerInfo { uint16_t vert; uint16_t uv; uint16_t vn; };

inline OLFaceCornerInfo splitOBJFaceCorner(string str)
{ // TODO: make this less jank
    OLFaceCornerInfo fci = { 0,0,0 };
    size_t first_break_ind = str.find('/');
    if (first_break_ind == string::npos) return fci;
    fci.vert = stoi(str.substr(0, first_break_ind)) - 1;
    size_t second_break_ind = str.find('/', first_break_ind + 1);
    if (second_break_ind != first_break_ind + 1)
        fci.uv = stoi(str.substr(first_break_ind + 1, second_break_ind - first_break_ind)) - 1;
    fci.vn = stoi(str.substr(second_break_ind + 1, str.find('/', second_break_ind + 1) - second_break_ind)) - 1;

    return fci;
}

inline void OLMesh::loadOBJ(const char* path)
{
    ifstream file;
    file.open(path);
    if (!file.is_open())
    {
        cout << "unable to open OBJ file " << path << endl;
        return;
    }

    vector<OLVector3f> tmp_vertices;
    vector<uint16_t> tmp_indices;
    vector<OLVector2f> tmp_uvs;
    vector<OLVector3f> tmp_vnorms;

    string type;
    OLVector3f tmp3;
    OLVector2f tmp2;

    while (!file.eof())
    {
        file >> type;
        if (type == "v")
        {
            // read vertex position
            file >> tmp3.x;
            file >> tmp3.y;
            file >> tmp3.z;
            tmp_vertices.push_back(tmp3);
        }
        else if (type == "vn")
        {
            // read vertex normal
            file >> tmp3.x;
            file >> tmp3.y;
            file >> tmp3.z;
            tmp_vnorms.push_back(tmp3);
        }
        else if (type == "vt")
        {
            // read vertex uv
            file >> tmp2.x;
            file >> tmp2.y;
            tmp_uvs.push_back(tmp2);
        }
        else if (type == "f")
        {
            // TODO: read arbitrary length face
            // read triangle
            string indices;

            // first vert
            file >> indices;
            OLFaceCornerInfo fci_0 = splitOBJFaceCorner(indices);

            // second vert
            file >> indices;
            OLFaceCornerInfo fci_1 = splitOBJFaceCorner(indices);

            // third vert
            file >> indices;
            OLFaceCornerInfo fci_2 = splitOBJFaceCorner(indices);

            tmp_indices.push_back(fci_0.vert);
            tmp_indices.push_back(fci_1.vert);
            tmp_indices.push_back(fci_2.vert);
        }
        // skip to next line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (uint16_t vertex = 0; vertex < tmp_vertices.size(); vertex++)
    {
        vertices.push_back(OLVertex{ tmp_vertices[vertex], tmp_vertices[vertex] });
    }

    indices = tmp_indices;
}