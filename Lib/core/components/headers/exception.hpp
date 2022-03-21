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
		virtual string getException() = 0;
		virtual void printMessage() = 0;
	};

	class AddException : public BaseException {
	public:
		AddException(string);
		void printMessage();
		string getException();
	};

	class CraftingException : public BaseException {
	private:
		string btype;
	public:
		CraftingException(string);
		void printMessage();
		string getException();
	};

	class UseException : public BaseException {
	public:
		UseException(string);
		void printMessage();
		string getException();

	};

	class MoveException : public BaseException {
	public:
		MoveException(string);
		void printMessage();
		string getException();

	};

	class InvException : public BaseException {
	public:
		InvException(string);
		void printMessage();
		string getException();
	};

	class TableException : public BaseException {
	public:
		TableException(string);
		void printMessage();
		string getException();
	};
}
#endif