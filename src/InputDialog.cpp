#include "include/InputDialog.hpp"

InputDialog::InputDialog(wxWindow *parent, dt::Entity data, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* base = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton * b = new wxButton( panel, wxID_OK, _("Submit"), wxDefaultPosition, wxDefaultSize);
	wxButton * c = new wxButton( panel, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize );

    wxFlexGridSizer* grid = new wxFlexGridSizer(2, wxSize(5, 5));
    grid->AddGrowableCol(1, 2);
    grid->AddGrowableCol(0, 1);

    panel->SetBackgroundColour(wxColor(128,156,192,255));

    for (const auto & dt : data.getDt())
    {
        wxStaticText* label = new wxStaticText(panel, wxID_ANY, dt.type);
        grid->Add(label, 0, wxALIGN_LEFT);

        wxTextCtrl* inputField = new wxTextCtrl(panel, wxID_ANY);
        inputField->SetHint(dt.type);
        VectInputField.push_back(inputField);

        grid->Add(inputField, 1, wxEXPAND);
    }

    buttonSizer->Add(b, 0, wxRIGHT | wxALIGN_CENTER, 20);
    buttonSizer->Add(c, 0, wxLEFT | wxALIGN_CENTER);

    base->Add(grid, 1, wxEXPAND | wxALL, 20);
    base->AddStretchSpacer();
    base->Add(buttonSizer, 0, wxEXPAND | wxALL, 20);

    panel->SetSizerAndFit(base);
}

dt::Entity InputDialog::GetEntity()
{
    dt::Entity et;

    for (const auto& inp : VectInputField)
    {
        et.add(inp->GetHint(), inp->GetValue());
    }

    return et;
}