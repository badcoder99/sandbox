#include "Render.h"

vector<Vertex> v;

void push(Point pt) { 
   float x = pt.x * cos(THETA) - pt.y * sin(THETA);
   float y = pt.y * cos(THETA) + pt.x * sin(THETA);
   v.push_back({ GetX(x), GetY(y), 0, 0, D3DCOLOR_ARGB(0, 0, 0, 0) });
}

float GetX(float x) {
   return ((x + 1.f) / 2.f) * SCREEN_WIDTH;
}

float GetY(float y) {
   return (1.f - ((y + 1.f) / 2.f)) * SCREEN_HEIGHT;
}

Point GetC(Point A, Point B) {
   float dx = (B.x - A.x) / 2;
   float dy = (B.y - A.y) / 2;
   return { A.x + dx, A.y + dy }; 
}

Point GetD(Point A, Point C, bool in) {
   float ux = C.x - A.x;
   float uy = C.y - A.y;
   float len = sqrt(powf(ux, 2) + powf(uy, 2));
   float vx;
   float vy;
   if (abs(ux) < abs(uy)) {
      vx = abs(uy) * (in ? IN_RATIO : RATIO) * (uy > 0 ^ in ? 1 : -1);
      vy = (-ux / uy) * vx;
   }
   else {
      vy = abs(ux) * (in ? IN_RATIO : RATIO) * (ux > 0 ^ in ? -1 : 1);
      vx = -(uy / ux) * vy;
   }
   return { C.x + vx, C.y + vy }; 
}

int powi(int x, int y) {
   int val = 1;
   for (int i = 0; i < y; ++i) {
      val *= x;
   }
   return val;
}

void SubPolygon(Point A, Point B, int degree, bool in) {
   if (degree >= (in ? DEGREE - 5 : DEGREE)) {
      return;
   }
    
   Point C = GetC(A, B);
   Point D = GetD(A, C, in); 
   
   SubPolygon(A, D, degree + 1, in);
   SubPolygon(D, B, degree + 1, in);
   
   push(C);
   push(D); 
   push(A);
   push(D);
   push(D);
   push(B);
} 

void BasePolygon() {
   float delta = PI * 2 / SIDES;  
   for (int i = 0; i < SIDES; ++i) {
      float theta = delta * i + delta / 2;
      Point A{ cos(theta) * RADIUS, sin(theta) * RADIUS };
      Point B{ cos(theta + delta) * RADIUS, sin(theta + delta) * RADIUS };
      push(A);
      push(B);
      SubPolygon(A, B, 1);
   }
   for (int i = 0; i < SIDES; ++i) {
      float theta = delta * i + delta / 2;
      Point A{ cos(theta) * RADIUS, sin(theta) * RADIUS };
      Point B{ cos(theta + delta) * RADIUS, sin(theta + delta) * RADIUS };
      SubPolygon(A, B, 1, true);
   }
}

vector<Vertex> GetPts() {
   v.clear();
   BasePolygon();
   return v;
}

