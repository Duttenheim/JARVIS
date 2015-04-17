#pragma once
//------------------------------------------------------------------------------
/**
    @file core/class.h
    
	Class macros.
	
	(C) 2015 See the LICENSE file.
*/

#define __ClassDecl(type) \
	public: \
	template<class... ARGS> \
	static type* Create(ARGS&&... args) \
	{ \
		return new type(args...); \
	}
