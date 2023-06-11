#include "include/DetailDialog.hpp"

DetailDialog::DetailDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* baseSizer = new wxBoxSizer(wxVERTICAL);

    panel->SetBackgroundColour("yellow");

    button1 = new wxButton(panel, wxID_ANY, "Tombol 1");
    button2 = new wxButton(panel, wxID_ANY, "Tombol 2");

    baseSizer->Add(button1, 0, wxALL, 10); 
    baseSizer->Add(button2, 0, wxALL, 10);

    panel->SetSizerAndFit(baseSizer);
}