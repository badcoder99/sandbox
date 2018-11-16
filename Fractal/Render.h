#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

#include "Globals.h"

struct Vertex {
   float x, y, z;
   DWORD color;
};

struct Point {
   float x, y;
};

float GetX(float x);
float GetY(float y);
Point GetC(Point A, Point B);
Point GetD(Point A, Point B, bool in = false);

void SubPolygon(Point A, Point B, int degree, bool in = false);
void BasePolygon();
vector<Vertex> GetPts();


