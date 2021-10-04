set(SOURCE_FILES BubbleApp.cpp)
set(HEADER_FILES Bubble.h BubbleApp.h BubbleUtils.h)
add_library(bubble_lib SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_precompile_headers(bubble_lib PRIVATE pch.h)