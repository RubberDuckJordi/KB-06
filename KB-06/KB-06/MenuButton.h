#ifndef _RESOURCE_MENUBUTTON_H_
#define _RESOURCE_MENUBUTTON_H_

#include <string>

namespace pengine
{
	enum MenuButtonFuction
	{
		EXIT, BACK, SELECT, SCENE
	};

	struct MenuButton
	{
		MenuButtonFuction function;
		std::string name;
		int top;
		int bottom;
		int left;
		int right;
		int page;
	};
}
#endif