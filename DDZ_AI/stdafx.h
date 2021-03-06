// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <stdint.h>
#include "log.h"
#include "random.h"
#include "common.h"

typedef std::vector<uint8_t> CardVector;

// TODO: 在此处引用程序需要的其他头文件
extern Random CommonRandom;
extern std::default_random_engine DefaultRandomEngine;

#define VECTOR_COPY(src,des)	des.resize(src.size());\
	std::copy(src.begin(), src.end(), des.begin())

#define VECTOR_MIN_INDEX(return_variable_name,src)auto  minIndex = std::min_element(src.begin(), src.end());\
size_t return_variable_name = minIndex - src.begin()

#define VECTOR_MAX_INDEX(return_variable_name,src)auto  maxIndex = std::max_element(src.begin(), src.end());\
size_t return_variable_name = maxIndex - src.begin()

#define VECTOR_MIN_VALUE(return_variable_name,src)size_t  min = *std::min_element(src.begin(), src.end())

#define VECTOR_MAX_VALUE(return_variable_name,src)size_t  max = *std::max_element(src.begin(), src.end())

#define VECTOR_INSERT_UNIQUE(vector_variable,same_object)auto itFinder = std::find(vector_variable.begin(), vector_variable.end(), same_object);\
if (vector_variable.size() == 0 || itFinder == vector_variable.end()) {\
	vector_variable.push_back(std::move(same_object));\
}
#if _DEBUG
#define DEBUG_LOG(text) Log::InfoF(text)
#else
#define DEBUG_LOG(text)
#endif
