#include "include/MainFrame.hpp"
#include "include/CustomParser.hpp"
#include <iostream>
#include <vector>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this); 
    // panel->SetBackgroundColour("blue");
   
    wxBoxSizer* sizerBase = new wxBoxSizer(wxVERTICAL);

    list = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 400));
    
    mahasiswa.setSource("data/mahasiswa");
    mahasiswa.load();

    listUpdate(mahasiswa);

    list->Bind(wxEVT_SIZE, &MainFrame::onListResize, this);

    wxButton * ok = new wxButton(panel, wxID_ANY, "OK", wxDefaultPosition, wxSize(100, 50));
    wxButton * no = new wxButton(panel, wxID_ANY, "NO", wxDefaultPosition, wxSize(100, 50));

    ok->Bind(wxEVT_BUTTON, &MainFrame::okbt, this);

    wxBoxSizer * sizerCenter = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * sizerBottom = new wxBoxSizer(wxHORIZONTAL);


    sizerBase->Add(list, 1, wxEXPAND | wxALL, 10);

    sizerBottom->Add(ok, 0, wxALIGN_LEFT | wxALL, 10);
    sizerBottom->Add(no, 0, wxALIGN_LEFT | wxALL, 10);

    sizerBase->Add(sizerBottom, 0, wxEXPAND);
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
    listUpdate(mahasiswa);
}

void MainFrame::listUpdate(dt::CustomParser &customParser)
{
    list->ClearAll();
    list->AppendColumn("NRP", wxLIST_FORMAT_LEFT);
    list->AppendColumn("NAMA", wxLIST_FORMAT_LEFT);
    list->AppendColumn("SajaTes", wxLIST_FORMAT_LEFT);

    list->SetColumnWidth(0, list->GetSize().GetWidth() * 0.2 > 200 ? 200 : list->GetSize().GetWidth() * 0.2);
    list->SetColumnWidth(2, list->GetSize().GetWidth() * 0.3 > 300 ? 300 : list->GetSize().GetWidth() * 0.3);
    list->SetColumnWidth(1, list->GetSize().GetWidth() - list->GetColumnWidth(0) - list->GetColumnWidth(2));
    
    std::vector<dt::Entity> data = customParser.get(); 
    
    for (int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> vec;

        vec.push_back(data[i].get("nrp"));
        vec.push_back(data[i].get("nama"));
        vec.push_back(data[i].get("jurusan"));

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

