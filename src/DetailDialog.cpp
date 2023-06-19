#include "include/DetailDialog.hpp"

DetailDialog::DetailDialog(wxWindow *parent, dt::Entity& entity, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    wxPanel* panel = new wxPanel(this);
    et = &entity;
    panel->SetBackgroundColour(wxColor(128,156,192,255));
    
    // panel->SetBackgroundColour("white");
    wxBoxSizer* baseSizer = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer* grid = new wxFlexGridSizer(3, wxSize(5, 5));
    grid->AddGrowableCol(1, 1);

    int index = 0;

    for (const auto& data : entity.getDt())
    {
        wxStaticText* t = new wxStaticText(panel, wxID_ANY, data.type);
        wxStaticText* v = new wxStaticText(panel, wxID_ANY, " : " + data.value);
        wxButton* b = new wxButton(panel, index, "EDIT");

        grid->Add(t, wxEXPAND);
        grid->Add(v, wxEXPAND);
        grid->Add(b, wxEXPAND);  

        index++; 
        b->Bind(wxEVT_BUTTON, &DetailDialog::editData, this);
        valueVector.push_back(v);
    }

    wxButton * b = new wxButton( panel, wxID_OK, _("OK"), wxDefaultPosition, wxSize(50, -1));

    baseSizer->Add(grid, 1, wxALL | wxEXPAND, 10);
    baseSizer->Add(b, 0, wxALIGN_CENTER | wxALL, 10);
    panel->SetSizerAndFit(baseSizer);
}

void DetailDialog::editData(wxEvent& evt)
{
    wxTextEntryDialog* in = new wxTextEntryDialog(this, "Nilai baru", "EDIT");
    int ok = in->ShowModal();
    std::string result = in->GetValue();
    if (ok == wxID_OK)
    {
        std::string type = et->getDt().at(evt.GetId()).type;
        et->set(type, result);
        valueVector.at(evt.GetId())->SetLabel(" : " + result);
    }
    
}

dt::Entity DetailDialog::getEt()
{
    return *et;
}