#pragma once

#include <wx/wx.h>

#include "Entity.hpp"

class DetailDialog : public wxDialog
{
    private :
        dt::Entity* et;
        std::vector<wxStaticText*> valueVector;
    public :
        void editData(wxEvent & evt);
        DetailDialog(wxWindow *parent, dt::Entity& entity, wxWindowID id = wxID_ANY, const wxString &title = "Detail", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE);
        dt::Entity getEt();
};