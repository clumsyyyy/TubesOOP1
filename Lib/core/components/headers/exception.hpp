#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include <iostream>
#include "item.hpp"
namespace Lib {
	using namespace std;

	class BaseException {
	protected:
		string name;
	public:
		BaseException();
		BaseException(string);
		virtual void printMessage() = 0;
	};

	class AddException : public BaseException {
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
	public:
		UseException(string);
		void printMessage();

	};

	class MoveException : public BaseException {
	public:
		MoveException(string);
		void printMessage();

	};

	class InvException : public BaseException {
	public:
		InvException(string);
		void printMessage();
	};

	class TableException : public BaseException {
	public:
		TableException(string);
		void printMessage();
	};
}
#endif