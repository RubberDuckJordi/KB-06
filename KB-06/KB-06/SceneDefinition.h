#ifndef _PENGINE_SCENEDEFINITION_H_
#define _PENGINE_SCENEDEFINITION_H_

#include <string>

namespace pengine
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