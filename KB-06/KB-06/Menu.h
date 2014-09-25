#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "MenuButton.h"
#include <vector>

namespace Scene
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
