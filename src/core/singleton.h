#pragma once
//------------------------------------------------------------------------------
//	@file core/singleton.h
//
//	Singleton macros.
//
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#define __SingletonDecl(type) \
	public: \
	static type* Instance() \
	{ \
		j_assert(type::singleton != nullptr); \
		return type::singleton; \
	} \
	private: \
		static type* singleton;

#define __SingletonDef(type) \
	type* type::singleton = nullptr;

#define __SingletonCtor() \
    j_assert(singleton == nullptr); \
	singleton = this;

#define __SingletonDtor() \
    j_assert(singleton != nullptr); \
	singleton = nullptr;