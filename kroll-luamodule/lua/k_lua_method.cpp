/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */


 
#include "k_lua_method.h"
#include "debug.h"



namespace kroll
{
	KLuaMethod::KLuaMethod( lua_State *L )
	: _L( NULL )
	{
		// create the thread we shall call on
		lua_State *callThread = lua_newthread( L );
		if( callThread != NULL )
		{
			lua_pop( L, 1 ); // pop off the new thread
			lua_xmove( L, callThread, 1 ); // copy the function call/object onto the new stack
			this->_L = callThread;

		} // if
	}

	KLuaMethod::~KLuaMethod()
	{
	}

	SharedValue KLuaMethod::Call( const ValueList& args )
	{
		SharedValue retVal;
		lua_State *L = ( lua_State * ) this->_L;
		
		lua_pushvalue( L, -1 ); // copy the function object so we can be called multiple times
		debug( "KLuaMethod::Call, attempting to make a lua call: %p\r\n", L );
		
		size_t i = 0;
		for( i = 0; i < args.size(); i++ )
		{	
			// covert args into Lua objects
			if( KLuaUtil::toLua( L, args[ i ] ) == 0 )
			{
				break;
				
			} // if
		} // for
		
		if( i == args.size() )
		{
			lua_call( L, args.size(), 1 );
			retVal = KLuaUtil::toKroll( L );
			
		} // if	
		
		// all done, cleanup just leaving the function call on the stack
		lua_pop( L, lua_gettop( L ) - 1 );
		return( retVal );
	}

	void KLuaMethod::Set( const char *name, SharedValue value )
	{
		debug( "KLuaMethod::Set\r\n" );
		lua_State *L = ( lua_State * ) this->_L;
		lua_pushvalue( L, -1 ); // copy the object so we can be called multiple times

		if( KLuaUtil::toLua( L, value ) == 1 )
		{
			lua_setfield( L, -2, name );
		
		} // if
		// all done, cleanup just leaving the object on the stack
		lua_pop( L, lua_gettop( L ) - 1 );
	}

	SharedValue KLuaMethod::Get( const char *name )
	{
		SharedValue retVal = Value::Undefined;
	
		debug( "KLuaMethod::Get\r\n" );
		lua_State *L = ( lua_State * ) this->_L;
		lua_pushvalue( L, -1 ); // copy the object so we can be called multiple times

		lua_getfield( L, -1, name );
		retVal = KLuaUtil::toKroll( L );		

		// all done, cleanup just leaving the object on the stack
		lua_pop( L, lua_gettop( L ) - 1 );
		return( retVal );
	}

	SharedStringList KLuaMethod::GetPropertyNames()
	{
		SharedStringList retVal = new StringList();
	
		debug( "KLuaMethod::GetPropertyNames\r\n" );
		lua_State *L = ( lua_State * ) this->_L;
		lua_pushvalue( L, -1 ); // copy the object so we can be called multiple times

		lua_pushnil( L );  /* first key */
		while( lua_next( L, -2 ) != 0 ) 
		{
			// uses 'key' (at index -2) and 'value' (at index -1)
			debug( "keyfound: %s\r\n", lua_tostring( L, -2 ) );
			retVal->push_back( new std::string( lua_tostring( L, -2 ) ) );
      		
			// removes 'value'; keeps 'key' for next iteration
			lua_pop( L, 1 );
			
     	} // while

		// all done, cleanup just leaving the object on the stack
		lua_pop( L, lua_gettop( L ) - 1 );
		return( retVal );
	}
}
