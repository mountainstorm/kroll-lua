/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _LUA_API_H_
#define _LUA_API_H_

#if defined(OS_OSX) || defined(OS_LINUX)
#define EXPORT __attribute__((visibility("default")))
#define KROLL_LUA_API EXPORT
#elif defined(OS_WIN32)
# ifdef KROLL_LUA_API_EXPORT
#  define KROLL_LUA_API __declspec(dllexport)
# else
#  define KROLL_LUA_API __declspec(dllimport)
# endif
#endif

#endif /* _LUA_API_H_ */
