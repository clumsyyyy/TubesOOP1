#include "headers/exception.hpp"

namespace Lib {
	BaseException::BaseException() {
		this->name = "BASE";
	}

	BaseException::BaseException(string name) {
		this->name = name;
	}

	string AddException::getException(){
		string exc = "[ADD-EXC] Item " + this->name + " doesn't exist!"; 
		return exc;
	}

	AddException::AddException(string name) : BaseException(name) { }

	void AddException::printMessage() {
		cout << "[ADD-EXC] Item " << name << " doesn't exist!" << endl;
	}

	CraftingException::CraftingException(string btype) {
		this->btype = btype;
	};

	void CraftingException::printMessage() {
		if (btype == "TOOL") {
			cout << "[CRF-EXC] Can't craft more than two tools!" << endl;
		} else {
			cout << "[CRF-EXC] Recipe not found!" << endl;
		}
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
		cout << "[USE-EXC] Couldn't use a Non-Tool item! ("
			<< name << ")\nUse command 'DISCARD' to use nontool items.\n" << endl;
	}

	string UseException::getException(){
		string exc = "[USE-EXC] Couldn't use a Non-Tool item! (" + name + ")\nUse command 'DISCARD' to use nontool items.\n";
		return exc;
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
		}
		return exc;
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
	}
}
