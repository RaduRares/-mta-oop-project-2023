#pragma once
#include<wx/wx.h>
class PC {
public:
    PC(const wxString& ipAddress) : ipAddress(ipAddress) {}

    wxString GetIPAddress() const {
        return ipAddress;
    }

private:
    wxString ipAddress;
};