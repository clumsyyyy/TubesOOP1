#include "headers/exception.hpp"

namespace Lib {
	BaseException::BaseException() {
		this->name = "BASE";
	}

	BaseException::BaseException(string name) {
		this->name = name;
	}

	string AddException::getException(){
		if (btype == "INVALID") {
			return "[ADD-EXC] Item " + name + " doesn't exist!\n";
		}
		else if (btype == "OVERCAP") {
			return "[ADD-EXC] Quantity exceeded current capacity!";
		}
		return "";
	}

	AddException::AddException(string name, string btype) : BaseException(name) { 
		this->btype = btype;
	}

	void AddException::printMessage() {
		cout << getException();
	}

	CraftingException::CraftingException(string btype) {
		this->btype = btype;
	};

	void CraftingException::printMessage() {
		cout << getException();
	}
	string CraftingException::getException(){
		string exc = "[CRF-EXC]";
		if (btype == "TOOL") {
			exc = "[CRF-EXC] Can't craft more than two tools!\n";
			return  exc;
		} else {
			exc = "[CRF-EXC] Recipe not found!\n";
			return exc;
		}
	}

	UseException::UseException(string name) : BaseException(name) {}

	void UseException::printMessage() {
		cout << getException();
	}

	string UseException::getException(){
		string exc = "[USE-EXC] Couldn't use a Non-Tool item! (" + name + ")\nUse command 'DISCARD' to use nontool items.\n";
		return exc;
	}

	MoveException::MoveException(string name) : BaseException(name) {}

	void MoveException::printMessage(){
		cout << getException();
	}

	string MoveException::getException(){
		string exc = "[MOV-EXC] ";
		if(this->name == "VOID"){
			return exc + "You are trying to move the void...\n";
		}else if(this->name == "INVALID"){
			return exc + "You move an invalid slot!\n";
		}else if(this->name == "INVALIDDEST"){
			return exc + "You entered an invalid destination slot!\n";
		}else if(this->name == "DOUBLETYPEDEST"){
			return exc + "You can only move the item to one type of slot!\n";
		}else if(this->name == "MOVETO2INV"){
			return exc + "You can only move this item to 1 inventory slot\n";
		}else if(this->name == "CRAFTTOCRAFT"){
			return exc + "You can't move item from crafting slot to another crafting slot.\n";
		}else if(this->name == "DIFFTYPE"){
			return exc + "The item you are trying to move to is not of the same type!\n";
		}else if(this->name == "FULL"){
			return exc + "The slot is full, you can't move it there!\n";
		}else if(this->name == "TOOL"){
			return exc + "There's a tool already here!\n";
		}else if(this->name == "NOTENOUGH"){
			return exc + "You don't have enough item to move\n";
		}else if(this->name == "INVALIDSLOT"){
			return exc + "Invalid slot count\n";
		}else if(this->name == "INVALIDSLOTCOMMAND"){
			return exc + "Invalid move slot command\n";
		}
		return exc;
	}

	InvException::InvException(string name) : BaseException(name) {}

	void InvException::printMessage() {
		cout << getException();
	}

	string InvException::getException(){
		string exc = "[INV-EXC] ";
		if (this->name == "INVALID") {
			return exc + "Invalid index! Index ranges from 0-26\n";
		}
		else if (this->name == "FULL") {
			return exc + "Inventory full!\n";
		}
		else if (this->name == "EMPTY") {
			return exc + "This slot is empty; couldn't discard anything!\n";
		}
		else if (this->name == "OVER") {
			return exc + "You're attempting to discard more than the available quantity!\n";
		}
		return "";
	}

	TableException::TableException(string name) : BaseException(name) {}

	void TableException::printMessage() {
		cout << getException();
	}

	string TableException::getException(){
		string exc = "[TAB-EXC] ";
		if (this->name == "INVALID") {
			return exc + "Invalid index! Index ranges from 0-9\n";
		}
		else if (this->name == "OCCUPIED") {
			return exc + "This slot is already occupied!\n";
		}
		else if (this->name == "FULL") {
			return exc + "This slot has reached its maximum capacity!\n";
		}
		else if (this->name == "EMPTY") {
			return exc + "This slot is empty; couldn't discard anything!\n";
		}
		return "";
	}
}
