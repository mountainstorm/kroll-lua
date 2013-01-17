/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _LUA_MODULE_H
#define _LUA_MODULE_H

#include <kroll/base.h>
#include <kroll/kroll.h>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "lua_api.h"
#include "lua_evaluator.h"
#include "lua_module_instance.h"
#include "klua_util.h"

#include "k_lua_objectproxy.h"
#include "k_lua_method.h"



namespace kroll
{
	class LuaModule : public Module, public ModuleProvider
	{
		KROLL_MODULE_CLASS(LuaModule)

	public:
		virtual bool IsModule(std::string& path);
		virtual Module* CreateModule(std::string& path);
		void InitializeBinding();		
		
		virtual const char * GetDescription() 
		{ 
			return "Lua Module Loader"; 
		}

		Host* GetHost()
		{
			return host;
		}

		static LuaModule* Instance()
		{
			return _instance;
		}

		static lua_State* L()
		{
			return _instance->_L;
		}
		
	private:
		lua_State *_L;	
		SharedValue globalObject;
		
		SharedKObject _binding;
		static LuaModule *_instance;
		DISALLOW_EVIL_CONSTRUCTORS(LuaModule);
	};
}

#endif
