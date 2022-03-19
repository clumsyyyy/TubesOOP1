#include "headers/exception.hpp"

namespace Lib {
	BaseException::BaseException() {
		this->name = "BASE";
	}

	BaseException::BaseException(string name) {
		this->name = name;
	}

	AddException::AddException(string name) : BaseException(name) { }

	void AddException::printMessage() {
		cout << "[ADD-EXC] Item " << name << " doesn't exist!" << endl;
	}

	CraftingException::CraftingException(bool tool) {
		this->tool = tool;
	};

	void CraftingException::printMessage() {
		if (tool) {
			cout << "[CRF-EXC] Can't craft more than two tools!" << endl;
		} else {
			cout << "[CRF-EXC] Recipe not found!" << endl;
		}
	}

	UseException::UseException(string name) : BaseException(name) {}

	void UseException::printMessage() {
		cout << "[USE-EXC] Couldn't use a Non-Tool item! ("
			<< name << ")\nUse command 'DISCARD' to use nontool items.\n" << endl;
	}

	MoveException::MoveException(string name) : BaseException(name) {}

	void MoveException::printMessage(){
		cout << "[MOV-EXC] ";
		if(this->name == "VOID"){
			cout << "You are trying to move the void...\n";
		}else if(this->name == "INVALID"){
			cout << "You move an invalid slot!\n";
		}else if(this->name == "INVALIDDEST"){
			cout << "You entered an invalid destination slot!\n";
		}else if(this->name == "DOUBLETYPEDEST"){
			cout << "You can only move the item to one type of slot!\n";
		}else if(this->name == "MOVETO2INV"){
			cout << "You can only move this item to 1 inventory slot\n";
		}else if(this->name == "CRAFTTOCRAFT"){
			cout << "You can't move item from crafting slot to another crafting slot.\n";
		}else if(this->name == "DIFFTYPE"){
			cout << "The item you are trying to move to is not of the same type!\n";
		}else if(this->name == "FULL"){
			cout << "The slot is full, you can't move it there!\n";
		}else if(this->name == "TOOL"){
			cout << "There's a tool already here!\n";
		}else if(this->name == "NOTENOUGH"){
			cout << "You don't have enough item to move\n";
		}else if(this->name == "INVALIDSLOT"){
			cout << "Invalid slot count\n";
		}
	}

	InvException::InvException(string name) : BaseException(name) {}

	void InvException::printMessage() {
		cout << "[INV-EXC] ";
		if (this->name == "INVALID") {
			cout << "Invalid index! Index ranges from 0-26" << endl;
		}
		else if (this->name == "FULL") {
			cout << "Inventory full!" << endl;
		}
		else if (this->name == "EMPTY") {
			cout << "This slot is empty; couldn't discard anything!" << endl;
		}
	}

	TableException::TableException(string name) : BaseException(name) {}

	void TableException::printMessage() {
		cout << "[TAB-EXC] ";
		if (this->name == "INVALID") {
			cout << "Invalid index! Index ranges from 0-9" << endl;
		}
		else if (this->name == "OCCUPIED") {
			cout << "This slot is already occupied!" << endl;
		}
		else if (this->name == "FULL") {
			cout << "This slot has reached its maximum capacity!" << endl;
		}
		else if (this->name == "EMPTY") {
			cout << "This slot is empty; couldn't discard anything!" << endl;
		}
	}
}
