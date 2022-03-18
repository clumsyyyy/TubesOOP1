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
}
