#include "App.h"
#include"MainFrame.h"


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Packet Tracer-App");
    mainFrame->SetClientSize(700, 450);
   
    mainFrame->Show();
    return true;
}
