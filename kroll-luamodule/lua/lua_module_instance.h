/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _LUA_MODULE_INSTANCE_H_
#define _LUA_MODULE_INSTANCE_H_

#include "lua_api.h"

namespace kroll
{
	class LuaModuleInstance : public Module
	{
	public:
		LuaModuleInstance(Host *host, std::string path);
	protected:
		virtual ~LuaModuleInstance();
	public:
		const char* GetName();
		void Initialize ();
		void Destroy ();
	private:
		std::string path;
        DISALLOW_EVIL_CONSTRUCTORS(LuaModuleInstance);
	};
}

#endif
