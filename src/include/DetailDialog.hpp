#pragma once

#include <wx/wx.h>

#include "Entity.hpp"

class DetailDialog : public wxDialog
{
    private :
        wxButton* button1;
        wxButton* button2;
    public :
        DetailDialog(wxWindow *parent, dt::Entity& entity, wxWindowID id = wxID_ANY, const wxString &title = "Detail", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

};