#include "include/LoginPanel.hpp"
#include "include/MainFrame.hpp"

LoginPanel::LoginPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    wxBoxSizer* base = new wxBoxSizer(wxVERTICAL);
    wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    SetFont(myFont);

    SetBackgroundColour(wxColor(1,56,128,255));

    wxStaticText* Header = new wxStaticText(this, wxID_ANY, "LOG IN");
    Header->SetFont(Header->GetFont().Scale(3));
    Header->SetBackgroundColour(wxColor(128,156,192,255));
    
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

    ::wxInitAllImageHandlers();
    bg = new wxImage("data/Background.png", wxBITMAP_TYPE_PNG);

    if (!bg->IsOk())
    {
        wxMessageBox("error loading image");
    }
    this->Bind(wxEVT_PAINT, &LoginPanel::drawBG, this);
}

void LoginPanel::login(wxEvent& evt)
{
    static_cast<MainFrame*>(this->GetParent())->login(userID->GetValue(), password->GetValue());
}

void LoginPanel::drawBG(wxPaintEvent& evt)
{
    wxBitmap* img = new wxBitmap(bg->Scale(600, 600, wxIMAGE_QUALITY_NORMAL));
    dc = new wxPaintDC(this);
    dc->DrawBitmap(*img, this->GetSize().GetWidth() / 2 - 300, this->GetSize().GetHeight() / 2 - 300); 
}

