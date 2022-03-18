#include "headers/exception.hpp"

namespace Lib {
	AddException::AddException(string name) {
		this->name = name;
	}

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

	UseException::UseException(string name) {
		this->name = name;
	}

	void UseException::printMessage() {
		cout << "[USE-EXC] Couldn't use a Non-Tool item! )"
			<< name << ")\nUse command 'DISCARD' to use nontool items.\n" << endl;
	}
		MoveException::MoveException(string name){
		this->name = name;
	}
	void MoveException::printMessage(){
		
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
}
