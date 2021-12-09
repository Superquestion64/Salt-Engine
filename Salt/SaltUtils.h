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

#ifdef SALT_DEBUG
	#define SALT_LOG(x) std::cout<<x<<std::endl; 
#else
	#define SALT_LOG(x)
#endif