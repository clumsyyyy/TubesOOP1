#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include <iostream>
#include "item.hpp"
namespace Lib {
	using namespace std;

	class BaseException {
	public:
		virtual void printMessage() = 0;
	};

	class AddException : public BaseException {
	private:
		string name;
	public:
		AddException(string);
		void printMessage();
	};

	class CraftingException : public BaseException {
	private:
		bool tool;
	public:
		CraftingException(bool);
		void printMessage();
	};

	class UseException : public BaseException {
	private:
		string name;
	public:
		UseException(string);
		void printMessage();

	};
}
#endif