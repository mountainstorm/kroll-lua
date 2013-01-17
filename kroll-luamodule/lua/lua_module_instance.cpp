/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "lua_module.h"

namespace kroll
{
	LuaModuleInstance::LuaModuleInstance(Host *host, std::string path) :
		Module(host, path ), path(path)
	{
	}

	LuaModuleInstance::~LuaModuleInstance()
	{
	}

	const char* LuaModuleInstance::GetName() 
	{ 
		return path.c_str(); 
	}

	void LuaModuleInstance::Initialize () 
	{
	}

	void LuaModuleInstance::Destroy () 
	{
	}
}

