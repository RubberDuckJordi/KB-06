#ifndef _SCENELIST_H_
#define _SCENELIST_H_

#include <string>

namespace Resource
{
	struct SceneDefinition
	{
		std::string title;
		std::string filePath;
		std::string picturePath;
		int difficulty;
	};
}
#endif