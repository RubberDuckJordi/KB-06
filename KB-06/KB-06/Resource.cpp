#include "stdafx.h"
#include "Resource.h"


Resource::Resource::Resource()
{
	isLoaded = false;
}


Resource::Resource::~Resource()
{
}

bool Resource::Resource::GetIsLoaded()
{
	return isLoaded;
}