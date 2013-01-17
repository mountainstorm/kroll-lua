/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _LUA_EVALUATOR_H_
#define _LUA_EVALUATOR_H_

namespace kroll
{
	class LuaEvaluator : public KMethod
	{
	public:
		virtual SharedValue Call(const ValueList& args);
		virtual void Set(const char *, SharedValue);
		virtual SharedValue Get(const char *);
		virtual SharedStringList GetPropertyNames();

	private:

	};
}

#endif

