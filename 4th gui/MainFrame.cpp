#define CRT_SECURE_NO_WARNINGS
#include "MainFrame.h"
#include <wx/wx.h>
#include<vector>
#include<string>
#include <iostream>
#include<ws2tcpip.h>
#include <json/json.h>
#include <wx/sizer.h>
#include <wx/dcclient.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/dcclient.h>
#include <wx/image.h>
#include<json/json.h>
#include"MyPanel.h"


void call_server(string userInput, char buf[4096]) {

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

    // Resolve the server address and port
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

wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_PAINT(MyPanel::OnPaint)
EVT_ERASE_BACKGROUND(MyPanel::EraseBackground)
wxEND_EVENT_TABLE()



MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title)
{ //BackgroundPanel* panel = new BackgroundPanel(this);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
   // wxBitmap image("kisspng-imagine.png", wxBITMAP_TYPE_PNG);
	 nameLabel = new wxStaticText(panel, wxID_ANY, "Userame:", wxPoint(70,200));
	 nameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150,200), wxSize(200, -1));
    
     SetBackgroundColour(wxColour(135, 206, 250));
	passwordLabel = new wxStaticText(panel, wxID_ANY, "Password:", wxPoint(70,250));
passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150,250), wxSize(200, -1), wxTE_PASSWORD);
wxStaticText* titleLabel = new wxStaticText(panel, wxID_ANY, "Paket Tracer", wxPoint(250,100));
wxFont titleFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
titleLabel->SetFont(titleFont);
wxButton* connectButton = new wxButton(panel, wxID_ANY, "CONNECT", wxPoint(150, 350));
connectButton->Bind(wxEVT_BUTTON, &MainFrame::OnConnect, this);



termsText = new wxStaticText(panel, wxID_ANY, "", wxPoint(10, 40), wxDefaultSize);
termsCheckbox = new wxCheckBox(panel, wxID_ANY, "Terms and Conditions", wxPoint(70, 300));
termsCheckbox->Bind(wxEVT_CHECKBOX, &MainFrame::OnTermsCheckboxClicked, this);

wxButton* signIn = new wxButton(panel,wxID_ANY,"SIGN IN ",wxPoint(300,350));
signIn->Bind(wxEVT_BUTTON, &MainFrame::OnSignIn, this);
// Convert JSON object to string

//call_server(jsonStr, " ");

wxButton* Admin = new wxButton(panel, wxID_ANY, "ADMIN", wxPoint(450,350));
Admin->Bind(wxEVT_BUTTON, &MainFrame::CheckAdmin, this);

wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
MyPanel* panell = new MyPanel(this);
sizer->Add(panel, 1, wxEXPAND);
SetSizerAndFit(sizer);
}

void MainFrame::OnConnect(wxCommandEvent& event)
{
    wxString username = nameTextCtrl->GetValue();
    wxString password = passwordTextCtrl->GetValue();

    string username1 = username.ToStdString();
    string password1 = password.ToStdString();
    jsonData["nume"] = username1;
    jsonData["password"] = password1;
    std::string jsonString = jsonData.toStyledString();
    wxMessageBox(jsonString);

    if (MainFrame::CheckCredential(username,password) && termsAccepted == true)
    {
        
        secondFrame = new SecondFrame("Second Frame");    secondFrame->SetClientSize(800,600);
        secondFrame->Show(true);
        // Navigate to the second page
       // wxMessageBox("Login successful! Navigating to the second page.");
        // Add your code to navigate to the second page here
        Hide();
    }
    else if (termsAccepted == false)
    {
        wxMessageBox("Accepta termenii si conditiile" );
    }
    else
    {
        wxMessageBox("Invalid username or password. Please try again.");
    }
}

bool MainFrame::CheckCredential(const wxString& username1, const wxString& password1)
{

    std::ifstream inputFile("credentials.txt");

    try{
    // Iterate over the JSON objects in the file
        string line;
    while (std::getline(inputFile, line)) {
        std::string storedUsername = line.substr(0, line.find(','));
        std::string storedPassword = line.substr(line.find(',') + 1);
     

        // Check if the username and password match
        if (storedUsername == username1 && storedPassword == password1) {
            inputFile.close(); // Close the input file stream
            return true; // Credentials match
        }
    
    }

    inputFile.close(); // Close the input file stream
    }
    catch (const std::exception& e) {
        wxMessageBox(e.what());
    }
    return false; // Credentials not found
    }

void MainFrame::CheckAdmin(wxCommandEvent& event)
{
    wxString username1 = nameTextCtrl->GetValue();
    wxString password1 = passwordTextCtrl->GetValue();

    string username = username1.ToStdString();
    string password = password1.ToStdString();
   
    if (username == "admin" && password == "admin")
    {
        std::ifstream inputFile("credentials.txt");

        //Iterate over the JSON objects in the file
        string line;
        string message;
        while (std::getline(inputFile, line)) {
            message = message + line+' + ';
          
        }  wxMessageBox(message);
    }
    else {
        wxMessageBox("Username sau parola gresita");
        return;
    }
  
}


void MainFrame::OnTermsCheckboxClicked(wxCommandEvent& event)
{
    termsAccepted = true;
    if (termsCheckbox->IsChecked())
    {
        // Create and show the new frame
        ThirdFrame* thirdFrame = new ThirdFrame("");
        thirdFrame->Show();
    }
}


void MainFrame::OnSignIn(wxCommandEvent& event)
{
    if (termsAccepted == false)
    {
        wxMessageBox("Accepta termenii si conditiile.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString username = nameTextCtrl->GetValue();
    wxString password = passwordTextCtrl->GetValue();
    string username1 = username.ToStdString();
    string password1 = password.ToStdString();
    for (int i = 0; i < username1.size(); i++)
        if (username1[i] == ',')
        {
            wxMessageBox("Username neadecvat, nu folosi caractere de tip ,");
            return;
        }
    for (int i = 0; i < password1.size(); i++)
        if (password1[i] == ',')
        {
            wxMessageBox("Parola neadecvata, nu folosi caractere de tip ,");
            return;
        }
    // Create a JSON object and set the username and password values

    if (username1.empty() || password1.empty()) {

        wxMessageBox("Username sau parola invalide.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    jsonData["nume"] = username1;
    jsonData["password"] = password1;
    
  
    // Serialize the JSON object to a string
    std::string jsonString = jsonData.toStyledString();
  wxMessageBox(jsonString);

  char buf[4096];

  //call_server(jsonString, buf);
 // wxMessageBox(buf);
    std::ofstream outputFile("userdata.json", std::ios::app);
    std::ofstream outputFileString("credentials.txt", std::ios::app);

    // daca persoana este deja inregistrata, nu se mai poate inregistra odata
    std::ifstream inputFile("credentials.txt");

     //Iterate over the JSON objects in the file
    string line;
    while (std::getline(inputFile, line)) {
        std::string storedUsername = line.substr(0, line.find(','));
        std::string storedPassword = line.substr(line.find(',') + 1);


        // Check if the usernameand password match
        if (storedUsername == username1 && storedPassword == password1) {
            inputFile.close(); // Close the input file stream
            wxMessageBox("Acest cont deja exista");
            return; // Credentials match
        }

    }

    inputFile.close(); // Close the input file stream
    wxMessageBox("Ai fost inregistrat,incearca sa te conectezi");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
    }
    if (outputFileString.is_open())
    {
        outputFileString << username1 << "," << password1 << endl;
        outputFile.close();
    }
}


    // Clear the text controls
