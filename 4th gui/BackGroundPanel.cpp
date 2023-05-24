#include "BackGroundPanel.h"

wxBEGIN_EVENT_TABLE(BackgroundPanel, wxPanel)
EVT_ERASE_BACKGROUND(BackgroundPanel::OnEraseBackground)
EVT_PAINT(BackgroundPanel::OnPaint)
wxEND_EVENT_TABLE()