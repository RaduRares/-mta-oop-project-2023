#include "SecondFrame.h"

SecondFrame::SecondFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title)
{// Set the frame size and layout
    SetSize(wxSize(400, 300));
    SetMinSize(wxSize(400, 300));
  
 
   
    // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the title
    wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "Simulation 1", wxPoint(10, 10));
    wxFont titleFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    titleLabel->SetFont(titleFont);

    // Create the PC1 text and text control
    wxStaticText* pc1Label = new wxStaticText(panel, wxID_ANY, "PC1:", wxPoint(10, 50));
    pc1TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 50));

    // Create the PC2 text and text control
    wxStaticText* pc2Label = new wxStaticText(panel, wxID_ANY, "PC2:", wxPoint(10, 80));
    pc2TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 80));

    // Create the router text
    wxStaticText* routerLabel = new wxStaticText(panel, wxID_ANY, "Router:", wxPoint(10, 110));
    routerTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 110));


    // Create the start simulation button
    wxButton* startSimulationButton = new wxButton(panel, wxID_ANY, "Start Simulation", wxPoint(10, 135));
    startSimulationButton->Bind(wxEVT_BUTTON, &SecondFrame::OnStartSimulationButtonClicked, this);

    // Create the connection description text control
    connectionDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 160), wxSize(380, 130), wxTE_MULTILINE | wxTE_READONLY);




    // Set the panel as the main sizer for the frame
    panel->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
   wxButton*  hintButton = new wxButton(panel, wxID_ANY, "Hint", wxPoint(150, 300));
       hintButton->Bind(wxEVT_BUTTON, &SecondFrame::OnHintButtonClicked, this);

       wxButton* close = new wxButton(panel, wxID_ANY, "CLOSE", wxPoint(700,10));
     close->Bind(wxEVT_BUTTON, &SecondFrame::OnCloseButtonClick, this);

     wxButton* nextFrame = new wxButton(panel, wxID_ANY, "NEXT SIMULATION", wxPoint(135, 135));
   
    nextFrame->Bind(wxEVT_BUTTON, &SecondFrame::OnConnect, this);
}

void SecondFrame::OnConnect(wxCommandEvent& event)
{
 fourthFrame= new FourthFrame("Second Simulation");    fourthFrame->SetClientSize(800, 600);
    fourthFrame->Show(true);
    Hide();

}
