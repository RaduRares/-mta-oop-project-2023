#include "FourthFrame.h"

FourthFrame::FourthFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title)
{
    SetSize(wxSize(400, 300));
    SetMinSize(wxSize(400, 300));



    // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the title
    wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "Simulation 2", wxPoint(10, 10));
    wxFont titleFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    titleLabel->SetFont(titleFont);

    // Create the PC1 text and text control
    wxStaticText* pc1Label = new wxStaticText(panel, wxID_ANY, "PC1:", wxPoint(10, 50));
    pc1TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 50));

    // Create the PC2 text and text control
    wxStaticText* pc2Label = new wxStaticText(panel, wxID_ANY, "PC2:", wxPoint(10, 80));
    pc2TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 80));
  
    wxStaticText* pc3Label = new wxStaticText(panel, wxID_ANY, "PC3:", wxPoint(10, 110));
    pc3TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 110));

    // Create the PC4 text and text control
    wxStaticText* pc4Label = new wxStaticText(panel, wxID_ANY, "PC4:", wxPoint(10, 140));
    pc4TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(70, 140));

    // Create the router text
    wxStaticText* routerLabel = new wxStaticText(panel, wxID_ANY, "Router:", wxPoint(200, 50));
    routerTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(260,50));

    wxStaticText* routerLabel2 = new wxStaticText(panel, wxID_ANY, "Router2:", wxPoint(200, 110));
    router2TextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(260, 110));
    // Create the start simulation button
    wxButton* startSimulationButton = new wxButton(panel, wxID_ANY, "Start Simulation", wxPoint(10, 200));
    startSimulationButton->Bind(wxEVT_BUTTON, &FourthFrame::OnStartSimulationButtonClicked, this);

    // Create the connection description text control
    connectionDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 225), wxSize(400, 160), wxTE_MULTILINE | wxTE_READONLY);




    // Set the panel as the main sizer for the frame
    panel->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    wxButton* hintButton = new wxButton(panel, wxID_ANY, "Hint", wxPoint(10,400));
    hintButton->Bind(wxEVT_BUTTON, &FourthFrame::OnHintButtonClicked, this);

    wxButton* close = new wxButton(panel, wxID_ANY, "CLOSE", wxPoint(700, 10));
    close->Bind(wxEVT_BUTTON, &FourthFrame::OnCloseButtonClick, this);
 
    /*wxButton* nextFrame = new wxButton(panel, wxID_ANY, "NEXT SIMULATION", wxPoint(135, 135));

    nextFrame->Bind(wxEVT_BUTTON, &FourthFrame::OnConnect, this);*/
}

