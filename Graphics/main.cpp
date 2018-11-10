#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "glu32.lib")

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <windows.h>
#include <wingdi.h>
#include <winuser.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define SCREEN_WIDTH 	(500)
#define SCREEN_HEIGHT	(500)
#define SCREEN_BITS	(32)

HDC hdc;

void Draw(), DrawCube();
void Render();
void InitPixelFormat(HDC hdc);
int APIENTRY WinMain(HINSTANCE ins, HINSTANCE prev, LPSTR lpCmd, int nCmd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HGLRC hrc;
	int width, height;

	switch(msg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		InitPixelFormat(hdc);
		hrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hrc);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		gluPerspective(54, (GLfloat)width / height, 1, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}			

int APIENTRY WinMain(HINSTANCE ins, HINSTANCE prev, LPSTR lpCmd, int nCmd) {
	HWND hwnd;
	MSG msg;

	WNDCLASSEX wnd = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, ins, 
		NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, "DefaultClass",
		LoadIcon(NULL, IDI_WINLOGO)
	};
	RegisterClassEx(&wnd);
	hwnd = CreateWindowEx(
		0, "DefaultClass", "Graphics Project", 
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
		NULL, NULL, ins, NULL
	);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		Render();
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam; 
}

void InitPixelFormat(HDC hdc) {
	int n;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0
	};
	
	n = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, n, &pfd);
}

void Draw() {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(1, 2, 0);
	glScalef(2, 2, 2);
	DrawCube();
	glPopMatrix();	
}

void DrawCube() {
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, -1);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(0, -1, -1);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 0);
	glEnd();
	glPopMatrix();	
}

void Render() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, -30);
	glRotatef(0, 0, 1, 0);
	Draw();
	glPopMatrix();
	glFlush();
	SwapBuffers(hdc);		
}

