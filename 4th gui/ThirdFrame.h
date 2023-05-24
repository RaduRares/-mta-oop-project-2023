
#include<wx/wx.h>
#include<iostream>
class ThirdFrame :public wxFrame
{public:
	ThirdFrame(const wxString& title);
private:
    void OnCloseButtonClick(wxCommandEvent& event)
    {
        this->Hide(); // Hide the current frame
      
    }

};

