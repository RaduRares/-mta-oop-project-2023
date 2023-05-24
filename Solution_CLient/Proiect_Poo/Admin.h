#pragma once
#include <wx/wx.h>
#include <string>
class Admin :public wxFrame
{

public:
	Admin(const wxString& title);
	wxPanel* panel = nullptr;
	wxChoice* ch = nullptr;
	wxGauge* gauge = nullptr;
	wxButton* button_Admin = nullptr;
	
	wxStaticText* staticText1 = nullptr;
	wxStaticText* staticText11 = nullptr;
private:
	void OnButtoninsert(wxCommandEvent& evt);
	void OnButtonupdate(wxCommandEvent& evt);
	void OnButtondelete(wxCommandEvent& evt);
	void OnButtonAfis(wxCommandEvent& evt);
	
	//void OnClose(wxCommandEvent& evt);
	//wxDECLARE_EVENT_TABLE();
};

