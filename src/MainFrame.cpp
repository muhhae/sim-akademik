#include "include/MainFrame.hpp"
#include "include/CustomParser.hpp"
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

    wxPanel* panel = new wxPanel(this); 
    // panel->SetBackgroundColour("blue");
   
    wxBoxSizer* sizerBase = new wxBoxSizer(wxVERTICAL);

    list = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 400));

    list->Bind(wxEVT_SIZE, &MainFrame::onListResize, this);

    wxButton * ok = new wxButton(panel, wxID_ANY, "OK", wxDefaultPosition, wxSize(75, -1));
    wxButton * detail = new wxButton(panel, wxID_ANY, "Detail", wxDefaultPosition, wxSize(75, -1));

    wxArrayString jenis;
    jenis.Add("Mahasiswa");
    jenis.Add("Dosen");
    jenis.Add("Tendik");

    jenisCtrl = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, jenis);

    ok->Bind(wxEVT_BUTTON, &MainFrame::okbt, this);
    detail->Bind(wxEVT_BUTTON, &MainFrame::detailClicked, this);
    jenisCtrl->Bind(wxEVT_CHOICE, &MainFrame::onChoiceUpdate, this);

    jenisCtrl->Select(0);
    
    std::vector<std::string> str = {"NRP", "Nama", "Jurusan"};
    currentParser = mahasiswa;
    listUpdate(currentParser, str);

    wxBoxSizer * sizerCenter = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * sizerBottom = new wxBoxSizer(wxHORIZONTAL);

    sizerBottom->Add(jenisCtrl, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
    sizerBottom->Add(ok, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
    sizerBottom->Add(detail, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);

    sizerBase->Add(sizerBottom, 0, wxEXPAND);

    sizerBase->Add(list, 1, wxEXPAND | wxALL, 10);

    panel->SetSizerAndFit(sizerBase);
}

void MainFrame::onListResize(wxEvent& evt)
{
    list->SetColumnWidth(0, list->GetSize().GetWidth() * 0.2 > 200 ? 200 : list->GetSize().GetWidth() * 0.2);
    list->SetColumnWidth(2, list->GetSize().GetWidth() * 0.3 > 300 ? 300 : list->GetSize().GetWidth() * 0.3);
    list->SetColumnWidth(1, list->GetSize().GetWidth() - list->GetColumnWidth(0) - list->GetColumnWidth(2));
}

void MainFrame::okbt(wxEvent& evt)
{
    // std::string arr[] = {"NRP", "Nama", "Jurusan"};
    std::vector<std::string> str = {"NRP", "Nama"};
    listUpdate(mahasiswa, str);
}

void MainFrame::detailClicked(wxEvent& evt)
{
    int index = list->GetFirstSelected(); 
    

    if (index < 0)
    {
        wxMessageDialog dialog(this,"Pilih terlebih dahulu", "Detail");
        dialog.ShowModal();
        return;
    }

    std::string str;
    dt::Entity et = currentParser.get().at(index);
    
    for (const auto& dt : et.getDt())
    {
        str += dt.type + "\t: " + dt.value + "\n";
    }

    wxMessageDialog dialog(this, str, "Detail", wxICON_NONE);
    dialog.ShowModal();
}

void MainFrame::onChoiceUpdate(wxEvent& evt)
{
    int select = jenisCtrl->GetSelection();
    std::vector<std::string> str;

    switch (select)
    {
        case 0 :
            str = {"NRP", "Nama", "Jurusan"};
            currentParser = mahasiswa;
            break;
        case 1 :
            str = {"NIM", "Nama"};
            currentParser = dosen;
            break;
        case 2 :
            str = {"NIM", "Nama"};
            currentParser = tendik;
            break;
    }

    listUpdate(currentParser, str);
}

void MainFrame::listUpdate(dt::CustomParser &customParser, std::vector<std::string> str)
{
    list->ClearAll();

    for (int i = 0; i < str.size(); i++)
    {
        // wxMessageBox(std::to_string(str.size()));
        list->AppendColumn(str[i]);
    }

    list->SetColumnWidth(0, list->GetSize().GetWidth() * 0.2 > 200 ? 200 : list->GetSize().GetWidth() * 0.2);
    list->SetColumnWidth(2, list->GetSize().GetWidth() * 0.3 > 300 ? 300 : list->GetSize().GetWidth() * 0.3);
    list->SetColumnWidth(1, list->GetSize().GetWidth() - list->GetColumnWidth(0) - list->GetColumnWidth(2));
    
    std::vector<dt::Entity> data = customParser.get(); 
    
    for (int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> vec;

        for (int j = 0; j < str.size(); j++)
        {
            vec.push_back(data[i].get(str[j]));
        }

        addToList(i, vec);
    }

}

void MainFrame::addToList(int index, std::vector<std::string> str)
{
    list->InsertItem(index, str[0]);
    for (int i = 1; i < str.size(); i++)
    {
        list->SetItem(index, i, str[i]);
    }
}

