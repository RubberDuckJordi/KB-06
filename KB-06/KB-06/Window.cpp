#include <windows.h>
#include "Window.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

Window::Window::Window()
{
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();

	//Set the default data for the window class.
	//These can be reset in the derived class's constructor.
	_WndClass.cbSize = sizeof(_WndClass);
	_WndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;;
	_WndClass.lpfnWndProc = BaseWndProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = NULL;
	_WndClass.hIcon = NULL;
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	_WndClass.lpszMenuName = NULL;
	_WndClass.hIconSm = NULL;

	_dwExtendedStyle = NULL;
	_dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_pszClassName = L"Window";
	_pszTitle = L"Default title, go set it!";
};

Window::Window::~Window()
{
	//logger->Log(Logger::Logger::INFO, "Destructed window");
	//Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	//delete _hwnd;
};

void Window::Window::SetTitle(char* title)
{
	size_t origsize = strlen(title) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, title, _TRUNCATE);

	_pszTitle = wcstring;
	SetWindowText(_hwnd, wcstring);

//	delete[] wcstring;
}

LRESULT Window::Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	std::list<WindowListener*>::iterator listenersIt;

	switch (msg)
	{
	case WM_ACTIVATE:
		
		for (listenersIt = windowListeners.begin(); listenersIt != windowListeners.end(); ++listenersIt)
		{
			if (wParam == WA_INACTIVE)
			{
				(*listenersIt)->OnWindowFocusLost(this);
			}
			else
			{
				(*listenersIt)->OnWindowFocusGained(this);
			}
		}
		break;
	case WM_PAINT:
		render(NULL);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		state = closed;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		Resize();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
};

void Window::Window::Resize()
{
	RECT rect;
	if (GetWindowRect(_hwnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		//renderer->setRenderSize(width, height);
	}
};

void Window::Window::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
};

HWND Window::Window::Create(int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance)
{
	_WndClass.lpszClassName = _pszClassName;
	_WndClass.hInstance = hInstance;

	//If we're already registered, this call will fail.
	RegisterClassEx(&_WndClass);

	_hwnd = CreateWindowEx(_dwExtendedStyle, _pszClassName, _pszTitle, _dwStyle, x, y, nWidth, nHeight, hParent, hMenu, hInstance, (void*)this);
	state = normal;
	return _hwnd;
};

LRESULT CALLBACK Window::Window::BaseWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//A pointer to the object is passed in the CREATESTRUCT
	if (msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA,
			(LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
	}

	//Retrieve the pointer
	Window *pObj = (Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	//Filter message through child classes
	if (pObj)
	{
		return pObj->WindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
};

void Window::Window::render(Scene::Scene *scene)
{
	if (scene)
	{
		//scene->updateEntities();
	}
	RECT rect;
	HDC hDC = GetDC(_hwnd);
	PAINTSTRUCT PaintStruct;
	BeginPaint(_hwnd, &PaintStruct);
	GetClientRect(_hwnd, &rect);
	DrawText(hDC, L"Hello, screen that is damn hard to get!", 39, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndPaint(_hwnd, &PaintStruct);
	ReleaseDC(_hwnd, hDC);
	//renderer->Render(_hwnd, scene);
};

HWND Window::Window::GetHWND()
{
	return _hwnd;
}

Window::WindowState Window::Window::GetWindowState()
{
	return state;
}

void Window::Window::AddWindowListener(WindowListener* p_windowListener)
{
	if (p_windowListener != NULL)
	{
		windowListeners.push_back(p_windowListener);
	}
}

void Window::Window::RemoveWindowListener(WindowListener* p_windowListener)
{
	if (p_windowListener != NULL)
	{
		windowListeners.remove(p_windowListener);
	}
}

void Window::Window::ClearWindowListeners()
{
	windowListeners.clear();
}