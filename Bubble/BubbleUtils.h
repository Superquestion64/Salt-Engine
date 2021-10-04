#pragma once

#ifdef BUBBLE_WINDOWS
	#ifdef BUBBLE_LIB
		#define BUBBLE_API __declspec(dllexport)
	#else
	#define BUBBLE_API __declspec(dllimport)
	#endif
#else
#endif