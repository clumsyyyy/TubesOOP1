#include "headers/Main.h"

namespace GUI {
    using namespace System;
    using namespace System::Windows::Forms;
    [STAThread]
    int main(array<System::String^>^ args)
    {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Application::Run(gcnew Main());
        return 0;
    }
}