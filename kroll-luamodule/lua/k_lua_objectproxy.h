/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _K_LUA_OBJECTPROXY_H
#define _K_LUA_OBJECTPROXY_H



#include "lua_module.h"



#define kKLuaObjectProxy_MetaTable	"KLuaObjectProxy*"



namespace kroll
{
	class KLuaObjectProxy
	{
	public:
		static KLuaObjectProxy *KLuaObjectProxy::New( lua_State *L, SharedValue obj );
		
	private:
		KLuaObjectProxy( lua_State *L, SharedValue obj );
		virtual ~KLuaObjectProxy();

	private:
		SharedValue _obj;

		// private members used for metatable
		static int getProperty( lua_State *L );
		static int setProperty( lua_State *L );
		static int invoke( lua_State *L );
		static int gc( lua_State *L );
		
	};
}

#endif // _K_LUA_OBJECTPROXY_H
