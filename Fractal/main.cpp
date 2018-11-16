#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>

#include <vector>
using namespace std;

#include "Globals.h"
#include "Render.h"

#define ESC_KEY         (0x1B)
#define PTS_PER_LINE    (2)
#define VERTEX_FORMAT   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "user32.lib")

LPDIRECT3D9 D3D;
LPDIRECT3DDEVICE9 Device;
LPDIRECT3DVERTEXBUFFER9 Buffer = NULL;
UINT BufferSize = 0;

void InitD3D(HWND hWnd);
void InitGraphics(); 
void RenderFrame();
void DestroyD3D();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
   switch(msg) {
   case WM_CHAR:
      switch (wParam) {
      case ESC_KEY:
         PostQuitMessage(0);
         break;
      }
      break;
 
   case WM_CLOSE:
      DestroyWindow(hWnd);
      break;

   case WM_DESTROY:
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
   
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      RenderFrame();
   }
   
   DestroyD3D();
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

   InitGraphics();
}

void InitGraphics() {
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

