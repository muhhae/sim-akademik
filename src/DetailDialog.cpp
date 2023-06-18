#include "include/DetailDialog.hpp"

DetailDialog::DetailDialog(wxWindow *parent, dt::Entity& entity, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    wxPanel* panel = new wxPanel(this);
    // panel->SetBackgroundColour("white");
    wxBoxSizer* baseSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<wxStaticText*> txtVector;

    for (const auto& data : entity.getDt())
    {
        std::string str = data.type + "\t: " + data.value;
        txtVector.push_back(new wxStaticText(panel, wxID_ANY, str));
        baseSizer->Add(txtVector.back(), 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
        txtVector.back()->SetFont(this->GetFont().Scale(1.5));
    }
    
    wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
    
    wxButton * button1 = new wxButton(panel, wxID_ANY, "Tes");
    button->Add(button1, 0, wxLEFT | wxRIGHT | wxTOP, 10);

    wxButton * button2 = new wxButton(panel, wxID_ANY, "Tes");
    button->Add(button2, 0, wxLEFT | wxRIGHT | wxTOP, 10);

    wxButton * button3 = new wxButton(panel, wxID_ANY, "Tes");
    button->Add(button3, 0, wxLEFT | wxRIGHT | wxTOP, 10);

    baseSizer->Add(button, 0, wxALIGN_CENTER);

    panel->SetSizerAndFit(baseSizer);
}