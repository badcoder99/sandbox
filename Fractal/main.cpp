#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <d3d9.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#include "Globals.h"
#include "Render.h"

#define ESC_KEY         (0x1B)
#define PTS_PER_LINE    (2)
#define VERTEX_FORMAT   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define TIMER_ID        (1001)

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "user32.lib")

LPDIRECT3D9 D3D;
LPDIRECT3DDEVICE9 Device;
LPDIRECT3DVERTEXBUFFER9 Buffer = NULL;
UINT BufferSize = 0;

LARGE_INTEGER Frequency{};

bool Paused = false;

void InitD3D(HWND hWnd);
void LoadGraphics(); 
void RenderFrame();
void UpdateFrame();
void DestroyD3D();

VOID CALLBACK TimerProc(HWND hWnd, UINT msg, UINT idTimer, DWORD dwTime) {
      UpdateFrame();
}

void ShowValue(HWND hWnd, int value) {
   char buf[80];
   string str = to_string(value);
   for (int i = 0; i < str.length(); ++i) {
      buf[i] = str[i];
   }
   buf[str.length()] = '\0';
   MessageBox(hWnd, buf, NULL, MB_OK);
} 

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
   switch(msg) {
   case WM_KEYDOWN:
      switch(wParam) {
      case VK_RIGHT:
         ++SIDES;
         break;

      case VK_LEFT:
         SIDES = max(3, SIDES - 1);
         break;
      
      case VK_UP:
         ++DEGREE;
         break;
   
      case VK_DOWN:
         DEGREE = max(1, DEGREE - 1);
         break;
      }
      break;

   case WM_CHAR:
      switch (wParam) {
      case ESC_KEY:
         PostQuitMessage(0);
         break;

      case VK_SPACE:
         Paused = !Paused;
         break;
   
      }
      break;
 
   case WM_CLOSE:
      DestroyWindow(hWnd);
      break;

   case WM_DESTROY:
      KillTimer(hWnd, TIMER_ID);
      DestroyD3D();
      PostQuitMessage(0);
      break;
   
   default: 
      return DefWindowProc(hWnd, msg, wParam, lParam);
   }
   
   return 0;
}

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE, LPSTR lpCmd, int nCmd) {
   HWND hWnd;
   WNDCLASSEX wc;

   QueryPerformanceFrequency(&Frequency);
   ZeroMemory(&wc, sizeof(WNDCLASSEX));

   wc.cbSize = sizeof(WNDCLASSEX);
   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = WndProc;
   wc.hInstance = hIns;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.lpszClassName = "WindowClass";
   RegisterClassEx(&wc);
   hWnd = CreateWindowEx(NULL, "WindowClass", "Fractal", 
      WS_BORDER | WS_VISIBLE | WS_SYSMENU,
      0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hIns, NULL);

   ShowWindow(hWnd, nCmd);
   InitD3D(hWnd);
   SetTimer(hWnd, TIMER_ID, 1000 / FRAME_RATE, (TIMERPROC)TimerProc);
   
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   return msg.wParam;
}

void InitD3D(HWND hWnd) {
   D3D = Direct3DCreate9(D3D_SDK_VERSION);

   D3DPRESENT_PARAMETERS d3dpp;
   ZeroMemory(&d3dpp, sizeof(d3dpp));
   
   d3dpp.Windowed = TRUE;
   d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
   d3dpp.hDeviceWindow = hWnd;
   d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
   d3dpp.BackBufferWidth = SCREEN_WIDTH;
   d3dpp.BackBufferHeight = SCREEN_HEIGHT;

   D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
      D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Device);
   
}

void UpdateFrame() {
   static LARGE_INTEGER lastUpdate{};
   LARGE_INTEGER thisUpdate;
   QueryPerformanceCounter(&thisUpdate);
   if (lastUpdate.QuadPart && !Paused) {
      double secs = static_cast<double>(thisUpdate.QuadPart - lastUpdate.QuadPart);
      secs /= Frequency.QuadPart; 
      secs = fabs(secs);
      THETA -= static_cast<float>(secs * THETA_PER_SEC);
      while (THETA < 0) {
         THETA += PI * 2;
      }
      RATIO_THETA += static_cast<float>(secs * RATIO_PER_SEC);
      while (RATIO_THETA >= PI * 2) {
         RATIO_THETA -= PI * 2;
      }
      RATIO = sin(RATIO_THETA);
      IN_RATIO = RATIO / AU;  
      LoadGraphics();
      RenderFrame();
   }
   lastUpdate = thisUpdate;
}

void LoadGraphics() {
   if (Buffer) {
      Buffer->Release();
      Buffer = NULL;
   }

   vector<Vertex> v = GetPts();
   BufferSize = v.size();
   UINT bytes = BufferSize * sizeof(Vertex);
   
   Device->CreateVertexBuffer(bytes, 0, VERTEX_FORMAT,
      D3DPOOL_MANAGED, &Buffer, NULL);

   VOID* ptr;  
   Buffer->Lock(0, 0, (void**)&ptr, 0);
   memcpy(ptr, v.data(), bytes);
   Buffer->Unlock();
}

void RenderFrame() {
   Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1, 0);
   Device->BeginScene();
   Device->SetFVF(VERTEX_FORMAT);
   Device->SetStreamSource(0, Buffer, 0, sizeof(Vertex));
   Device->DrawPrimitive(D3DPT_LINELIST, 0, BufferSize / PTS_PER_LINE);
   Device->EndScene();
   Device->Present(NULL, NULL, NULL, NULL);
}

void DestroyD3D() {
    Buffer->Release();
    Device->Release();
    D3D->Release();
}

