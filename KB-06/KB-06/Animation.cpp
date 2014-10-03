#include "Animation.h"
namespace pengine
{
	Animation::~Animation(void)
	{
		while (!_Scalings.empty())
		{
			delete _Scalings.back();
			_Scalings.pop_back();
		}
		while (!_Rotations.empty())
		{
			delete _Rotations.back();
			_Rotations.pop_back();
		}
		while (!_Translations.empty())
		{
			delete _Translations.back();
			_Translations.pop_back();
		}
		while (!_Matrices.empty())
		{
			delete _Matrices.back();
			_Matrices.pop_back();
		}
	}
}