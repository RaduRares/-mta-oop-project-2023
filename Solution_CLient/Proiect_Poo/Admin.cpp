#include "Admin.h"

#include <wx/spinctrl.h>
#include<ws2tcpip.h>



#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
using namespace std;

void call_server9(string userInput, char buf[4096]) {

    //	WSACleanup();
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
   /* if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }*/

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        // printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port  192.168.0.109    192.168.43.160
    iResult = getaddrinfo("192.168.43.160", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, userInput.c_str(), userInput.size() + 1, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    //    printf("Bytes Sent: %ld\n", iResult);

        // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, buf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();


}



Admin::Admin(const wxString& title) :wxFrame(nullptr, wxID_ANY, title)
{
    panel = new wxPanel(this);

    wxFont titleFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

   /* button_Admin = new wxButton(panel, wxID_ANY, "GO SIMULATION", wxPoint(300, 400), wxSize(200, 50));
    button_Admin->SetBackgroundColour(*wxLIGHT_GREY);
    button_Admin->Bind(wxEVT_BUTTON, &Admin::OnButtonClicked_Admin, this);*/

   

    wxButton* button_AFIS = new wxButton(panel, wxID_ANY, "PRINT USERS", wxPoint(300, 425), wxSize(200, 50));
    wxButton* button_delete = new wxButton(panel, wxID_ANY, "DELETE USER:", wxPoint(300,500), wxSize(200, 50));
    wxButton* button_update = new wxButton(panel, wxID_ANY, "UPDATE:", wxPoint(300,550), wxSize(200, 50));
    wxButton* button_insert = new wxButton(panel, wxID_ANY, "INSERT:", wxPoint(300,350), wxSize(200, 50));


    wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500,510), wxSize(100, -1));
    wxTextCtrl* textCtrl1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500,560), wxSize(100, -1));
    wxTextCtrl* textCtrl2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500,360), wxSize(100, -1));
    button_AFIS->Bind(wxEVT_BUTTON, &Admin::OnButtonAfis, this);
    button_delete->Bind(wxEVT_BUTTON, &Admin::OnButtondelete, this);
    button_update->Bind(wxEVT_BUTTON, &Admin::OnButtonupdate, this);
    button_insert->Bind(wxEVT_BUTTON, &Admin::OnButtoninsert, this);

    button_AFIS->SetBackgroundColour(*wxLIGHT_GREY);
    button_delete->SetBackgroundColour(*wxLIGHT_GREY);
    button_update->SetBackgroundColour(*wxLIGHT_GREY);
    button_insert->SetBackgroundColour(*wxLIGHT_GREY);

    wxStaticText* titleText = new wxStaticText(panel, wxID_ANY, "ADMININSTRATOR", wxPoint(280, 20));
    //wxStaticText* info = new wxStaticText(panel, wxID_ANY, "SIMULARE RETEA CONFIGURARE PENTRU:PC,ROUTER,SWITCH", wxPoint(250, 48));
    //info->SetBackgroundColour(*wxLIGHT_GREY);
    //wxStaticText* info1 = new wxStaticText(panel, wxID_ANY, "PC ARE URMATORELE CONFIGURARI:NUME PC,ADRESA IP", wxPoint(30, 70));

    //wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 86), wxSize(100, -1));
    //wxTextCtrl* textCtrl1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 86), wxSize(100, -1));

    //wxStaticText* info2 = new wxStaticText(panel, wxID_ANY, "SWITH-UL ARE URMATORELE CONFIGURARI:NUME,PORT1,PORT2,ADRESA IP", wxPoint(30, 108));

    //wxTextCtrl* textCtrl2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 125), wxSize(100, -1));
    //wxTextCtrl* textCtrl3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(140, 125), wxSize(100, -1));

    //textCtrl4 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(250, 125), wxSize(100, -1));
    //textCtrl5 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(360, 125), wxSize(100, -1));

    //wxStaticText* info3 = new wxStaticText(panel, wxID_ANY, "ROUTER-UL ARE URMATORELE CONFIGURARI:NUME,ADRESA IP", wxPoint(30, 150));

    //textCtrl6 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 170), wxSize(100, -1));
    //textCtrl7 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(140, 170), wxSize(100, -1));


    titleText->SetFont(titleFont);
    SetBackgroundColour(wxColour(135, 206, 250));

    //this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    /*button->SetBackgroundColour(*wxLIGHT_GREY);
    button->Bind(wxEVT_BUTTON, &interfata_doi::OnButtonClicked, this);*/
  //  wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(590, 205), wxSize(200, -1), wxGA_VERTICAL);
   // gauge->SetValue(50);

  //  wxStaticText* info4 = new wxStaticText(panel, wxID_ANY, "AICI VA APAREA SIMULAREA RETELEI OFERITA DE SERVER", wxPoint(150, 500));
    //info4->SetBackgroundColour(*wxLIGHT_GREY);
    //wxArrayString alegere;
    //alegere.Add("AICI VA APAREA SIMULAREA RETELEI OFERITA DE SERVER");
    /*alegere.Add("Simularea 2");
    alegere.Add("Simularea 3");*/

    //wxListBox* listbox = new wxListBox(panel, wxID_ANY, wxPoint(10, 500), wxSize(800, -1), alegere,wxLB_MULTIPLE);

//	wxRadioBox *radiobox= new wxRadioBox(panel, wxID_ANY, "RADIOBOX", wxPoint(590, 205), wxSize(200, -1),alegere);


    CreateStatusBar();
}

void Admin::OnButtoninsert(wxCommandEvent& evt)
{

    //wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(40, 500), wxSize(700, -1), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

    //textCtrl->AppendText(buf);


    //wxString values = textCtrl->GetValue();





    evt.Skip();
}
void Admin::OnButtondelete(wxCommandEvent& evt)
{






    evt.Skip();
}

void Admin::OnButtonAfis(wxCommandEvent& evt)
{

    char buf[4096];
    call_server9("print", buf);


   wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 150), wxSize(400, 100), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);

    textCtrl->AppendText(buf);
    wxLogMessage(buf);



    wxString values = textCtrl->GetValue();


    evt.Skip();
}




void Admin::OnButtonupdate(wxCommandEvent& evt)
{


  



    evt.Skip();
}