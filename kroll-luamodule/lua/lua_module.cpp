/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include <iostream>
#include <signal.h>
#include "lua_module.h"
#include "debug.h"


namespace kroll
{
	KROLL_MODULE(LuaModule);

	LuaModule *LuaModule::_instance = NULL;
	void LuaModule::Initialize()
	{	
		debug( "LuaModule::Initialize\r\n" );		
		
		// open and init a lua state
		this->_L = lua_open();
		luaL_openlibs( this->_L );	
		
		LuaModule::_instance = this;
		this->InitializeBinding();
		host->AddModuleProvider( this );
	}

	void LuaModule::Stop()
	{
		debug( "LuaModule::Stop\r\n" );
		
		SharedKObject global = this->host->GetGlobalObject();
		global->Set( "lua", Value::Undefined );
		this->_binding->Set( "evaluate", Value::Undefined );
		this->_binding = NULL;
	
		lua_close( this->_L );
		
		LuaModule::_instance = NULL;
	}

	void LuaModule::InitializeBinding()
	{
		debug( "LuaModule::InitializeBinding\r\n" );
		
		SharedKObject global = this->host->GetGlobalObject();
		this->_binding = new StaticBoundObject();
		global->Set( "Lua", Value::NewObject( this->_binding) );

		SharedKMethod evaluator = new LuaEvaluator();
		this->_binding->Set( "evaluate", Value::NewMethod( evaluator ) );

		this->globalObject = Value::NewObject( global );
		if( KLuaUtil::toLua( this->_L, this->globalObject ) == 1 )
		{
			lua_setfield( this->_L, LUA_GLOBALSINDEX, "kroll" );  
			debug( "LuaModule::InitializeBinding: success\r\n" );
		
		} // if
	}
	
	const static std::string lua_suffix = "module.lua";
	bool LuaModule::IsModule(std::string& path)
	{	
		return( path.substr( path.length() - lua_suffix.length() ) == lua_suffix );
	}

	Module *LuaModule::CreateModule(std::string& path)
	{
		debug( "LuaModule::CreateModule\r\n" );
		
		if( luaL_dofile( this->_L, path.c_str() ) )
		{
			debug( "LuaModule::CreateModule: error\r\n%s\r\n", lua_tostring( this->_L, -1 ) );

		}
		else
		{
			debug( "LuaModule::CreateModule: success\r\n" );
			
		} // if	
		return new LuaModuleInstance( this->host, path );
	}

}
