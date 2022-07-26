#pragma once

#include "Jerboa/Debug.h"

namespace Jerboa
{
	/* A class T inheriting Singleton<T> add the following properties
		* Makes it uncopyable and unmovable
		* Asserts if more than one instance exists 
	*/
	template<class T>
    class Singleton
    {
	protected:
		Singleton()
		{
			JERBOA_ASSERT(!sm_InstanceExists, "An active instance of '" + std::string(typeid(T).name()) + "' already exists. There can't be more than one.");
			sm_InstanceExists = true;
		}

		~Singleton()
		{
			sm_InstanceExists = false;
		}

		Singleton(const Singleton&) = delete;
		Singleton(const Singleton&&) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(const Singleton&& other) = delete;
	private:
		static inline bool sm_InstanceExists = false;
    };
}