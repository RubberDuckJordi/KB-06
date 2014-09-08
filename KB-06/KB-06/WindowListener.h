#ifndef __WINDOW_WINDOWLISTENER_H__
#define __WINDOW_WINDOWLISTENER_H__

#include "Window.h"

namespace Window
{
	class WindowListener
	{
	public:
		virtual void WindowClosed(Window& p_window) = 0;
		virtual void WindowOpened(Window& p_window) = 0;
	};
}

#endif