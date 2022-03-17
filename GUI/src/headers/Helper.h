#pragma once
#ifndef __HELPER_H
#define __HELPER_H
#include <string>

namespace GUI {
	using namespace System;

	template <typename T>
	inline String^ to_cs_str(T obj) {
		return gcnew String(std::to_string(obj).c_str());
	}

	template <>
	inline String^ to_cs_str<std::string>(std::string str) {
		return gcnew String(str.c_str());
	}
}

#endif
