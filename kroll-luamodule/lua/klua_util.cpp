/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "lua_module.h"
#include "debug.h"



namespace kroll
{
	int KLuaUtil::toLua( lua_State *L, SharedValue obj )
	{
		if( !obj.isNull() )
		{
			if( obj->IsBool() )
			{						
				debug( "KLuaUtil::toLua: IsBool\r\n" );
				lua_pushboolean( L, obj->ToBool() );
				
			}
			else if(    obj->IsNumber() 
					 || obj->IsInt()
					 || obj->IsDouble() )
			{
				debug( "KLuaUtil::toLua: IsNumber\r\n" );
				lua_pushnumber( L, obj->ToDouble() );
				
			}				
			else if( obj->IsString() )
			{
				debug( "KLuaUtil::toLua: IsString\r\n" );
				lua_pushstring( L, obj->ToString() );
				
			}
			else if(    obj->IsList()
					 || obj->IsObject() 
					 || obj->IsMethod() )
			{
				debug( "KLuaUtil::toLua: IsObject\r\n" );
				KLuaObjectProxy::New( L, obj );

			}
			else if(    obj->IsNull()
					 || obj->IsUndefined() )
			{
				debug( "KLuaUtil::toLua: IsNull\r\n" );
				lua_pushnil( L );
				
			}
			else
			{
				debug( "unhandled type\r\n" );
				lua_pushnil( L );
					
			} // if
		}
		else
		{
			debug( "obj ptr is null\r\n" );
			lua_pushnil( L );
				
		} // if
		return( 1 );
	
	} // KLuaUtil::toLua( func )
	
	
	
	SharedValue KLuaUtil::toKroll( lua_State *L )
	{
		SharedValue retVal;
		if( lua_isnoneornil( L, -1 ) )
		{
			retVal = kroll::Value::NewNull();
			
		} 
		if( lua_isboolean( L, -1 ) )
		{
			retVal = kroll::Value::NewBool( lua_toboolean( L, -1 ) );
			
		}
		else if( lua_isnumber( L, -1 ) )
		{
			debug( "making number: %f\r\n", lua_tonumber( L, -1 ) );
			retVal = kroll::Value::NewDouble( lua_tonumber( L, -1 ) );
			
		}
		else if( lua_isstring( L, -1 ) )
		{
			debug( "making string: %s\r\n", lua_tostring( L, -1 ) );
			retVal = kroll::Value::NewString( lua_tostring( L, -1 ) );
			
		}
		else if(    lua_istable( L, -1 ) 
				 || lua_isfunction( L, -1 ) )
		{
			debug( "making function\r\n" );
			retVal = Value::NewMethod( new KLuaMethod( L ) );
			
		}
		else
		{
			debug( "unhandled type: %s\r\n", lua_typename( L, lua_type( L, -1 ) ) );
			
		} // if
		return( retVal );
	
	} // KLuaUtil::toKroll( func )
}
