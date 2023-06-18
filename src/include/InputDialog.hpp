#pragma once

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <vector>


#include "Entity.hpp"

class InputDialog : public wxDialog
{
    private:
        std::vector<wxTextCtrl*> VectInputField;
        dt::Entity entity;

    public:
        InputDialog(wxWindow *parent, dt::Entity data, wxWindowID id = wxID_ANY, const wxString &title = "Detail", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        dt::Entity GetEntity();
};