#ifndef _PENGINE_WINDOWLISTENER_H_
#define _PENGINE_WINDOWLISTENER_H_

#include "Window.h"

namespace pengine
{
	class Window;

	class WindowListener
	{
	public:
		virtual void OnWindowFocusGained(Window* window) = 0;
		virtual void OnWindowFocusLost(Window* window) = 0;
		virtual void OnWindowCreated(Window* window) = 0;
	};
}
#endif