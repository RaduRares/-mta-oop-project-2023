#include <wx/wx.h>
#include <wx/dcbuffer.h>

class BackgroundPanel : public wxPanel
{
public:
    BackgroundPanel(wxWindow* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
    }

private:
    void OnEraseBackground(wxEraseEvent& event)
    {
        // Do not erase the background to avoid flickering
    }

    void OnPaint(wxPaintEvent& event)
    {
        wxAutoBufferedPaintDC dc(this);
        RenderBackground(dc);
    }

    void RenderBackground(wxDC& dc)
    {
        // Load the background image
        wxImage backgroundImage("poza.png", wxBITMAP_TYPE_PNG);

        if (backgroundImage.IsOk())
        {
            // Scale the background image to fit the panel size
            backgroundImage = backgroundImage.Scale(GetSize().GetWidth(), GetSize().GetHeight());

            // Draw the background image
            wxBitmap bitmap(backgroundImage);
            dc.DrawBitmap(bitmap, 0, 0);
        }
    }

    wxDECLARE_EVENT_TABLE();
};