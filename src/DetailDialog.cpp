#include "include/DetailDialog.hpp"

DetailDialog::DetailDialog(wxWindow *parent, dt::Entity& entity, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* baseSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<wxStaticText*> txtVector;
    this->SetFont(this->GetFont().Scale(1.5));

    for (const auto& data : entity.getDt())
    {
        std::string str = data.type + "\t: " + data.value;
        txtVector.push_back(new wxStaticText(panel, wxID_ANY, str));
        baseSizer->Add(txtVector.back(), 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    }

    panel->SetSizerAndFit(baseSizer);
}