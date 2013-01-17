/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _K_LUA_METHOD_H
#define _K_LUA_METHOD_H



#include "lua_module.h"



namespace kroll
{
	class KLuaMethod : public KMethod
	{
	public:
		KLuaMethod( lua_State *L );
		virtual ~KLuaMethod();

		SharedValue Call( const ValueList& args );
		virtual void Set( const char *name, SharedValue value );
		virtual SharedValue Get( const char *name );
		virtual SharedStringList GetPropertyNames();

	private:
		lua_State *_L;
		DISALLOW_EVIL_CONSTRUCTORS( KLuaMethod );
	};
}

#endif // _K_LUA_METHOD_H

