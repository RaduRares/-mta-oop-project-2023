#pragma once
#include <wx/wx.h>
#include <fstream>
#include"SecondFrame.h"
#include"ThirdFrame.h"

#include"BackGroundPanel.h"
#include <json/json.h>
#include"MyPanel.h"
using namespace std;
class MainFrame :public wxFrame
{
public:
	MainFrame(const wxString& title);
	void OnConnect(wxCommandEvent& event);
	

private:
	wxPanel* panel;
	wxStaticText* nameLabel;
	wxTextCtrl* nameTextCtrl;
	wxStaticText* usernameLabel;
	wxTextCtrl* usernameTextCtrl;
	wxStaticText* passwordLabel;
	wxTextCtrl* passwordTextCtrl;
	wxStaticText* titlelabel;
	SecondFrame* secondFrame;
	wxCheckBox* termsCheckbox;
	wxStaticText* termsText;
	bool termsAccepted = false;
	Json::Value jsonData;
public:
	void OnTermsCheckboxClicked(wxCommandEvent& event);
	void transmitere_parsare(const wxString&name,const wxString &password);
	void OnSignIn(wxCommandEvent& event);
	bool CheckCredential(const wxString& username1, const wxString& password1);
	void CheckAdmin(wxCommandEvent& event);
};