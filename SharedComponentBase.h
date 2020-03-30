#pragma once
#include "Misc.h"

class SharedComponentBase
{
	virtual std::size_t hash_code() = 0;
};
