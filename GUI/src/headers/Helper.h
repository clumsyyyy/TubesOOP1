#pragma once
#ifndef __HELPER_H
#define __HELPER_H
#include <string>
#include <msclr\marshal_cppstd.h>

namespace GUI {
	using namespace System;

	template <typename T>
	inline String^ to_str(T obj) {
		return msclr::interop::marshal_as<String^>(std::to_string(obj));
	}

	template <typename T1, typename T2>
	inline T1 to(T2 obj) {
		return static_cast<T1>(obj);
	}

	template <>
	inline String^ to(std::string str) {
		return msclr::interop::marshal_as<String^>(str);
	}

	template <>
	inline std::string to(String^ str) {
		return msclr::interop::marshal_as<std::string>(str);
	}

	template <>
	inline int to(Decimal dec) {
		return Decimal::ToInt32(dec);
	}

	template <>
	inline long long to(Decimal dec) {
		return Decimal::ToInt64(dec);
	}
}

#endif
