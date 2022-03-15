#include "core/all_headers.hpp"
#include "headers/Main.h"

namespace GUI {
	System::Void Main::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		MessageBox::Show("Yay clicked!");
	}
}
