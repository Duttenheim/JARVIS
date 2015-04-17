#pragma once
//------------------------------------------------------------------------------
/**
	@file core/singleton.h

	Singleton macros.

	(C) 2015 See the LICENSE file.
*/

#define __SingletonDecl(type) \
	public: \
	template<class... ARGS> \
	static type* Create(ARGS&&... args) \
	{ \
		j_assert(type::singleton == nullptr); \
		type* obj = new type(args...); \
		return obj; \
	} \
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
	singleton = this;

#define __SingletonDtor() \
	singleton = nullptr;