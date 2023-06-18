#include <wx/wx.h>
#include "CustomParser.hpp"
#include "DetailDialog.hpp"
#include <wx/listctrl.h>

class AdminPanel : public wxPanel
{
    private :
        wxListView* list;
        wxChoice* jenisCtrl;

        dt::CustomParser* mahasiswa;
        dt::CustomParser* dosen;
        dt::CustomParser* tendik;

        std::vector<std::vector<std::string>> showLabel = {{"NRP", "Nama", "Jurusan"}, {"NIM", "Nama"}, {"NIM", "Nama"}};

        dt::CustomParser* currentParser;
    public :
        AdminPanel(wxFrame* parent, dt::
        CustomParser* mahasiswa, dt::CustomParser* dosen, dt::CustomParser* tendik);
        void onListResize(wxEvent& evt);
        void listUpdate(dt::CustomParser& customParser, std::vector<std::string> str);
        void addToList(int index, std::vector<std::string> str);
        void Add(wxEvent& evt);
        void onChoiceUpdate(wxEvent& evt);
        void detailClicked(wxEvent& evt);
        void deleteData(wxEvent& evt);
};