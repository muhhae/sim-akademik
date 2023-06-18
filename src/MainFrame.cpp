#include "include/MainFrame.hpp"
#include "include/CustomParser.hpp"
#include "include/DetailDialog.hpp"
#include "include/AdminPanel.hpp"
#include "include/LoginPanel.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <wx/msgdlg.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    mahasiswa.setSource("data/mahasiswa");
    mahasiswa.load();
    dosen.setSource("data/dosen");
    dosen.load();
    tendik.setSource("data/tendik");
    tendik.load();

    wxMenuBar* menu = new wxMenuBar();
    wxMenu* profile = new wxMenu();
    base = new wxBoxSizer(wxVERTICAL);

    profile->Append(1, "Log Out", "", false);

    this->Bind(wxEVT_MENU, &MainFrame::logOut, this, 1);

    menu->Append(profile, "Profile");

    SetMenuBar(menu);

    panel = new LoginPanel(this);
    base->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(base);
}

void MainFrame::logOut(wxEvent& evt)
{
    wxSize sizeTemp = GetSize();
    if (panel) panel->Destroy();
    panel = new LoginPanel(this);
    base->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(base);
    this->SetSize(sizeTemp);
}

void MainFrame::login(std::string userID, std::string password)
{
    bool verified = false;

    if (tendik.find("userID", userID).get("password") == password) verified = true; 

    if (!verified) return;

    wxSize sizeTemp = GetSize();
    if (panel) panel->Destroy();
    panel = new AdminPanel(this, &mahasiswa, &dosen, &tendik);
    base->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(base);
    this->SetSize(sizeTemp);
}
