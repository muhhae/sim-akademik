#include "include/LoginPanel.hpp"
#include "include/MainFrame.hpp"

LoginPanel::LoginPanel(wxFrame* parent) : wxPanel(parent)
{
    wxBoxSizer* base = new wxBoxSizer(wxVERTICAL);
    wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    SetFont(myFont);

    wxStaticText* Header = new wxStaticText(this, wxID_ANY, "LOG IN");
    Header->SetFont(Header->GetFont().Scale(3));
    
    userID = new wxTextCtrl(this, wxID_ANY);
    password = new wxTextCtrl(this, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    userID->SetHint("User ID");
    password->SetHint("password");

    wxButton* loginButton = new wxButton(this, wxID_ANY, "LOGIN");
    loginButton->Bind(wxEVT_BUTTON, &LoginPanel::login, this);

    base->AddStretchSpacer();
    base->Add(Header, 0, wxALIGN_CENTER | wxALL, 5);
    base->Add(userID, 0, wxALIGN_CENTER | wxALL, 5);
    base->Add(password, 0, wxALIGN_CENTER | wxALL, 5);
    base->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 5);
    base->AddStretchSpacer();

    this->SetSizerAndFit(base);
}

void LoginPanel::login(wxEvent& evt)
{
    static_cast<MainFrame*>(this->GetParent())->login(userID->GetValue(), password->GetValue());
}

