#include "include/AdminPanel.hpp"
#include "include/InputDialog.hpp"

AdminPanel::AdminPanel(wxFrame * parent, dt::CustomParser* mahasiswa, dt::CustomParser* dosen, dt::CustomParser* tendik) : wxPanel(parent, wxID_ANY)
{
    SetBackgroundColour(wxColor(128,156,192,255));
    wxBoxSizer* sizerBase = new wxBoxSizer(wxVERTICAL);

    list = new wxListView(this, wxID_ANY, wxDefaultPosition);

    list->Bind(wxEVT_SIZE, &AdminPanel::onListResize, this);

    wxButton * ok = new wxButton(this, wxID_ANY, "Add", wxDefaultPosition, wxSize(75, -1));
    wxButton * detail = new wxButton(this, wxID_ANY, "Detail", wxDefaultPosition, wxSize(75, -1));
    wxButton * deleteDt = new wxButton(this, wxID_ANY, "Delete", wxDefaultPosition, wxSize(75, -1));


    wxArrayString jenis;
    jenis.Add("Mahasiswa");
    jenis.Add("Dosen");
    jenis.Add("Tendik");

    jenisCtrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, jenis);

    ok->Bind(wxEVT_BUTTON,&AdminPanel::Add, this);
    detail->Bind(wxEVT_BUTTON, &AdminPanel::detailClicked, this);
    jenisCtrl->Bind(wxEVT_CHOICE, &AdminPanel::onChoiceUpdate, this);
    deleteDt->Bind(wxEVT_BUTTON, &AdminPanel::deleteData, this);

    jenisCtrl->Select(0);

    wxBoxSizer * sizerBottom = new wxBoxSizer(wxHORIZONTAL);

    sizerBottom->Add(jenisCtrl, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
    sizerBottom->Add(detail, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
    sizerBottom->Add(ok, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);
    sizerBottom->Add(deleteDt, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, 10);


    sizerBase->Add(sizerBottom, 0, wxEXPAND);

    sizerBase->Add(list, 1, wxEXPAND | wxALL, 10);

    this->SetSizerAndFit(sizerBase);
    // sizerBase->SetMinSize(parent->GetSize());

    this->mahasiswa = mahasiswa;
    this->dosen = dosen;
    this->tendik = tendik;

    currentParser = mahasiswa;

    listUpdate(*mahasiswa, std::vector<std::string>{"NRP", "Nama", "Jurusan"});
}

void AdminPanel::onListResize(wxEvent& evt)
{
    list->SetColumnWidth(0, list->GetSize().GetWidth() * 0.2 > 200 ? 200 : list->GetSize().GetWidth() * 0.2);
    list->SetColumnWidth(2, list->GetSize().GetWidth() * 0.3 > 300 ? 300 : list->GetSize().GetWidth() * 0.3);
    list->SetColumnWidth(1, list->GetSize().GetWidth() - list->GetColumnWidth(0) - list->GetColumnWidth(2));
}

void AdminPanel::Add(wxEvent& evt)
{
    InputDialog * input = new InputDialog(this, currentParser->get().at(0));
    int res = input->ShowModal();

    if (res == wxID_OK)
    {
        dt::Entity et = input->GetEntity();
        // for (const auto & val : et.getDt()) 
        // {
        //     wxMessageBox(val.type + " " + val.value);
        // } 
        currentParser->add(et);
        currentParser->update();

        std::vector<std::string> str;
        for (const auto & s : showLabel[jenisCtrl->GetSelection()])
        {
            str.push_back(et.get(s));
        }
        addToList(list->GetItemCount(), str);
    }

}

void AdminPanel::deleteData(wxEvent& evt)
{
    currentParser->deleteData(list->GetFirstSelected());
    currentParser->update();
    listUpdate(*currentParser, showLabel[jenisCtrl->GetSelection()]);
}

void AdminPanel::detailClicked(wxEvent& evt)
{
    int index = list->GetFirstSelected(); 
    // wxMessageBox("1");
    if (index < 0)
    {
        wxMessageDialog dialog(this,"Pilih terlebih dahulu", "Detail");
        dialog.ShowModal();
        return;
    }
    // wxMessageBox("2");
    std::string namaIndex = currentParser->get().at(index).get("Nama");
    dt::Entity* et = &(currentParser->find("Nama", namaIndex)); 
    DetailDialog dialog(this, *et);
    dialog.ShowModal();

    currentParser->update();
    listUpdate(*currentParser, showLabel.at(jenisCtrl->GetSelection()));
}

void AdminPanel::onChoiceUpdate(wxEvent& evt)
{
    int select = jenisCtrl->GetSelection();
    // wxMessageBox(std::to_string(select));
    std::vector<std::string> str;

    switch (select)
    {
        case 0 :
            currentParser = mahasiswa;
            break;
        case 1 :
            currentParser = dosen;
            break;
        case 2 :
            currentParser = tendik;
            break;
    }

    listUpdate(*currentParser, showLabel[select]);
}

void AdminPanel::listUpdate(dt::CustomParser &customParser, std::vector<std::string> str)
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

void AdminPanel::addToList(int index, std::vector<std::string> str)
{
    list->InsertItem(index, str[0]);
    for (int i = 1; i < str.size(); i++)
    {
        list->SetItem(index, i, str[i]);
    }
}

