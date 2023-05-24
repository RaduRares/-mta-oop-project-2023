#include "ThirdFrame.h"

ThirdFrame::ThirdFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title)
{
	SetSize(wxSize(400, 300));
	SetMinSize(wxSize(400, 300));
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	wxButton* close = new wxButton(panel, wxID_ANY, "CLOSE", wxPoint(150,190));
	close->Bind(wxEVT_BUTTON, &ThirdFrame::OnCloseButtonClick, this);
	wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "TERMENII SI CONDITIILE", wxPoint(120, 20));
	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Permite utilizatorilor sa proiecteze topologii de retea.\n Utilizatorii pot simula switch-uri Cisco si routere.", wxPoint(50, 50));
}
