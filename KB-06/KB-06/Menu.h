#ifndef _PENGINE_MENU_H_
#define _PENGINE_MENU_H_

#include "MenuButton.h"
#include <vector>

namespace pengine
{
	class Menu
	{
	public:
		Menu();
		~Menu();
		void addButton(MenuButtonFuction function, std::string name, int top, int bottom, int left, int right, int page);
		void click(int x, int y);

	protected:
		std::vector<MenuButton> buttons;
	};
}
#endif
