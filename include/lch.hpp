#pragma once

// 1-st Level Headers
#pragma warning( push )
# pragma warning (disable:4996)
#include "global_ini.hpp"
#pragma warning( pop )
#include "Singleton.hpp"
#include "StringHelper.hpp"
#include "IOHelper.hpp"
#include "LogHelper.hpp"
#include "TimeHelper.hpp"

// 2-nd Level Headers		// depends on:
#include "DirHelper.hpp"	// StringHelper
#include "ConfigHelper.hpp" // Singleton StringHelper IOHelper DirHelper

namespace helper {
using namespace IniHelper;
using namespace StringHelper;
using namespace IOHelper;
using namespace TimeHelper;

using namespace LogHelper;
using namespace DirHelper;
using namespace ConfigHelper;
}
