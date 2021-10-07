#pragma once

#ifdef SALT_WINDOWS
	#ifdef SALT_LIB
		#define SALT_API __declspec(dllexport)
	#else
		#define SALT_API __declspec(dllimport)
	#endif
#else
	#define SALT_API
#endif