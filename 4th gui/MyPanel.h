#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcclient.h>
#include <wx/image.h>
class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow* parent) : wxPanel(parent) { }

    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        RenderBackground(dc);
    }

    void RenderBackground(wxDC& dc)
    {
        wxImage background;
       // if (background.LoadFile("C:\\Users\\rares\\Desktop\\maxresdefault.png", wxBITMAP_TYPE_JPEG)) {
        //    wxBitmap bitmap(background);
          //  dc.DrawBitmap(bitmap, 0, 0);
       // }
    }

    void EraseBackground(wxEraseEvent& event)
    {
        // Do nothing to prevent flickering
    }

    wxDECLARE_EVENT_TABLE();
};

