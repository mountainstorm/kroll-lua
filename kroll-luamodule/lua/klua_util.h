/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _KLUA_UTIL_H_
#define _KLUA_UTIL_H_

namespace kroll
{

	class KROLL_LUA_API KLuaUtil
	{
	public:
		static int KLuaUtil::toLua( lua_State *L, SharedValue obj );
		static SharedValue KLuaUtil::toKroll( lua_State *L );
	};

}

#endif
