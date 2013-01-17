/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "lua_module.h"
#include "debug.h"


SharedValue LuaEvaluator::Call(const ValueList& args)
{
	debug( "LuaEvaluator::Call: %u\r\n", (unsigned int) args.size() );

	if( 	args.size() != 3
		|| !args.at( 1 )->IsString()
		|| !args.at( 2 )->IsObject() )
	{
		return Value::Undefined;
	}
	
	SharedStringList s = args.at( 2 )->ToObject()->GetPropertyNames();
	for( size_t i = 0; i < s->size(); i++ )
	{
		debug( "toplevel: %s\r\n", s->at(i)->c_str() );
	}
	
	lua_State *L = LuaModule::L();
	if( KLuaUtil::toLua( L, args.at( 2 ) ) == 1 )
	{
		lua_setfield( L, LUA_GLOBALSINDEX, "current" );  
		if( luaL_dostring( L, args.at( 1 )->ToString() ) == 1 )
		{
			debug( "LuaEvaluator::Call: error\r\n%s\r\n", lua_tostring( L, -1 ) );

		}
		else
		{
			debug( "LuaEvaluator::Call: success\r\n" );
			
		} // if	
	} // if	
	return Value::Undefined;
}

void LuaEvaluator::Set(const char *name, SharedValue value)
{
}

SharedValue LuaEvaluator::Get(const char *name)
{
	return Value::Undefined;
}

SharedStringList LuaEvaluator::GetPropertyNames()
{
	return SharedStringList();
}
