/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "k_lua_objectproxy.h"
#include "debug.h"



KLuaObjectProxy *KLuaObjectProxy::New( lua_State *L, SharedValue obj )
{
	return( new( lua_newuserdata( L, sizeof( KLuaObjectProxy ) ) ) KLuaObjectProxy( L, obj ) );

} // KLuaObjectProxy::New( func )



KLuaObjectProxy::KLuaObjectProxy( lua_State *L, SharedValue obj )
: _obj( obj)
{
	if( luaL_newmetatable( L, kKLuaObjectProxy_MetaTable ) == 1 )
	{
		// create new metatable
		lua_pushcfunction( L, KLuaObjectProxy::getProperty );
		lua_setfield( L, -2, "__index" );
		lua_pushcfunction( L, KLuaObjectProxy::setProperty );
		lua_setfield( L, -2, "__newindex" );
		lua_pushcfunction( L, KLuaObjectProxy::invoke );
		lua_setfield( L, -2, "__call" );
		lua_pushcfunction( L, KLuaObjectProxy::gc );
		lua_setfield( L, -2, "__gc" );

	} // if
  	lua_setmetatable( L, -2 );

} // KLuaObjectProxy::KLuaObjectProxy( func )



KLuaObjectProxy::~KLuaObjectProxy()
{
} // KLuaObjectProxy::~KLuaObjectProxy( func )



int KLuaObjectProxy::getProperty( lua_State *L )
{
	int retVal = 0;
	if(    ( lua_gettop( L ) == 2 )
		&& ( lua_isuserdata( L, -2 ) )
		&& ( lua_isstring( L, -1 ) ) )	
	{
		KLuaObjectProxy *self = ( KLuaObjectProxy * ) luaL_checkudata( L, 1, kKLuaObjectProxy_MetaTable );
		
		debug( "KLuaUtil::getProperty: %s\r\n", lua_tostring( L, 2 ) );
		SharedValue childObj = self->_obj->ToObject()->Get( lua_tostring( L, 2 ) );
		retVal = KLuaUtil::toLua( L, childObj );

	}
	else
	{
		debug( "KLuaObjectProxy::getProperty, invalid parameters\r\n" );
		
	} // if
	return( retVal );

} // KLuaObjectProxy::getProperty( func )



int KLuaObjectProxy::setProperty( lua_State *L )
{
	if(    ( lua_gettop( L ) == 3 )
		&& ( lua_isuserdata( L, 1 ) )
		&& ( lua_isstring( L, 2 ) ) )	
	{
		KLuaObjectProxy *self = ( KLuaObjectProxy * ) luaL_checkudata( L, 1, kKLuaObjectProxy_MetaTable );
		
		debug( "KLuaUtil::setProperty: %s\r\n", lua_tostring( L, 2 ) );
		self->_obj->ToObject()->Set( lua_tostring( L, 2 ), KLuaUtil::toKroll( L ) );
		
	}
	else
	{
		debug( "KLuaObjectProxy::setProperty, invalid parameters\r\n" );
		
	} // if
	return( 0 );
	
} // KLuaObjectProxy::setProperty( func )



int KLuaObjectProxy::invoke( lua_State *L )
{
	int retVal = 0;
	
	debug( "KLuaObjectProxy::invoke\r\n" );
	size_t noArgs = lua_gettop( L );
	if( noArgs >= 1 )
	{
		KLuaObjectProxy *self = ( KLuaObjectProxy * ) luaL_checkudata( L, 1, kKLuaObjectProxy_MetaTable );

		// work backwards so as we convert the top of the stack
		ValueList args;
		size_t n = 0;
		for( n = noArgs; n > 1; n-- )
		{
			args.push_back( KLuaUtil::toKroll( L ) );
			lua_pop( L, 1 );
			
		} // for	
		KLuaUtil::toLua( L, self->_obj->ToMethod()->Call( args ) );

	}
	else
	{
		debug( "invalidParameters: %u\r\n", lua_gettop( L ) );
		
	} // if	

	if( retVal == 0 )
	{
		lua_pushnil( L ); // on error
		
	} // if
	debug( "KLuaObjectProxy::invoke, done!\r\n" );
	return( retVal );
	
} // KLuaObjectProxy::invoke( func )



int KLuaObjectProxy::gc( lua_State *L )
{
	debug( "KLuaObjectProxy::gc\r\n" );
	KLuaObjectProxy *self = ( KLuaObjectProxy * ) luaL_checkudata( L, 1, kKLuaObjectProxy_MetaTable );
	self->~KLuaObjectProxy();
	return( 0 );
	
} // KLuaObjectProxy::gc( func )
