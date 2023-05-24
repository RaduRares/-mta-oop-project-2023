#pragma once
#include<wx\wx.h>
#include<wx\wx.h>
#include"PC.h"
#include"Switch.h"
#include"Router.h"
#include <wx/socket.h>
#include <wx/tokenzr.h>
#include<fstream>
#include<iostream>
class FourthFrame :public wxFrame
{
public:
	FourthFrame(const wxString& title);


private:

    wxTextCtrl* pc1TextCtrl;
    wxTextCtrl* pc2TextCtrl;
    wxTextCtrl* pc3TextCtrl;
    wxTextCtrl* pc4TextCtrl;
    wxTextCtrl* connectionDescriptionTextCtrl;
    wxTextCtrl* routerTextCtrl;
    wxTextCtrl* router2TextCtrl;
    void OnStartSimulationButtonClicked(wxCommandEvent& event) {
        wxString pc1IP = pc1TextCtrl->GetValue();
        wxString pc2IP = pc2TextCtrl->GetValue();
        wxString routerIP = routerTextCtrl->GetValue();
        wxString pc3IP = pc3TextCtrl->GetValue();
        wxString pc4IP = pc4TextCtrl->GetValue();
        wxString routerIP2 = router2TextCtrl->GetValue();
        // Perform the simulation using the PC IP addresses
        wxString connectionDescription = PerformSimulation(pc1IP, pc2IP,pc3IP,pc4IP, routerIP,routerIP2);

        // Display the connection description
        connectionDescriptionTextCtrl->SetValue(connectionDescription);
    }

    void GoBack(wxCommandEvent& event);
    wxString PerformSimulation(const wxString& pc1IP, const wxString& pc2IP,const wxString& pc3IP,const wxString& pc4IP, const wxString& routerIP,wxString& routerIP2) {
        fstream file;

        file.open("Log.txt", std::ios::out | std::ios::app);

        wxString connectionDescription;
        int contor = 0,contor2=0;
        wxString routerSubnetMask = "255.255.255.0";
        if (IsValidIPAddress(pc1IP) == 0 || IsValidIPAddress(pc2IP) == 0 || IsValidIPAddress(routerIP) == 0 || IsValidIPAddress(pc3IP) == 0 || IsValidIPAddress(routerIP2) == 0 || IsValidIPAddress(pc4IP) == 0) {
            // Display error message if IP addresses are not in the expected format
            connectionDescription = "Invalid IP address format. Please enter IP addresses in the format X.X.X.X";
            return connectionDescription;
        }
        if (IsSameNetwork(pc1IP, routerIP, routerSubnetMask)) {
            connectionDescription += "PC1 (IP: " + pc1IP + ") este conectat la Router (IP: " + routerIP + ").\n";
            contor++;
        }
        else {
            connectionDescription += "PC1 (IP: " + pc1IP + ") NU este în aceeași rețea cu Routerul (IP: " + routerIP + ").\n";
        }
        if (IsSameNetwork(pc3IP, routerIP2, routerSubnetMask)) {
            connectionDescription += "PC3 (IP: " + pc3IP + ") este conectat la Router (IP: " + routerIP2 + ").\n";
            contor2++;
        }
        else {
            connectionDescription += "PC3 (IP: " + pc1IP + ") NU este în aceeași rețea cu Routerul2 (IP: " + routerIP2 + ").\n";
        }
        if (IsSameNetwork(pc4IP, routerIP2, routerSubnetMask)) {
            connectionDescription += "PC4 (IP: " + pc4IP + ") este conectat la Router2 (IP: " + routerIP2 + ").\n";
            contor2++;
        }
        else {
            connectionDescription += "PC4 (IP: " + pc4IP + ") NU este în aceeași rețea cu Routerul2 (IP: " + routerIP2 + ").\n";
        }
        // Verificarea dacă PC2 și routerul sunt în aceeași rețea
        if (IsSameNetwork(pc2IP, routerIP, routerSubnetMask)) {
            connectionDescription += "PC2 (IP: " + pc2IP + ") este conectat la Router (IP: " + routerIP + ").\n";
            contor++;
        }
        else {
            connectionDescription += "PC2 (IP: " + pc2IP + ") NU este în aceeasi retea cu Routerul (IP: " + routerIP + ").\n";
        }
        if (contor==2 && contor2==2)
        {
            connectionDescription += "Dorim sa transmitem un mesaj de la PC1 la PC3,ele fiind in alte retele diferite\n";
            connectionDescription += "Nu exista o conexiune directa între reteaua PC1 și rețeaua PC3.\n";
            connectionDescription += "Pentru a permite comunicarea intre cele două retele, puteti configura o rutare între Routerul 1 și Routerul 2.\n\n";
            connectionDescription += "Traseul adresei IP de la PC1 la PC3 este urmatorul:\n";
            connectionDescription += "1. PC1 trimite pachetul către adresa IP a Routerului 1.\n";
            connectionDescription += "2. Routerul 1 primeste pachetul de la PC1 si realizează o verificare in tabela sa de rutare pentru a determina urmatorul hop.\n";
            connectionDescription += "3. Routerul 1 gaseste o ruta catre reteaua PC3 și impacheteaza pachetul cu adresa IP a Routerului 2 ca destinatie.\n";
            connectionDescription += "4. Pachetul este trimis către Routerul 2 prin intermediul cablului Ethernet care leaga cele două routere.\n";
            connectionDescription += "5. Routerul 2 primește pachetul și realizează o verificare in tabela sa de rutare pentru a determina următorul hop catre rețeaua PC3.\n";
            connectionDescription += "6. Routerul 2 identifica că adresa IP a PC3 se afla in rețeaua sa locală si trimite pachetul direct către adresa IP a PC3.\n";
            connectionDescription += "7. PC3 primeste pachetul de la Routerul 2 si il proceseaza, permitand comunicarea intre PC1 și PC3.\n\n";
            outfile << connectionDescription;
            outfile.close();
        }

        /* wxString pc1IP = pc1TextCtrl->GetValue();
         wxString pc2IP = pc2TextCtrl->GetValue();
         wxString routerIP = routerTextCtrl->GetValue();*/

         /* wxString connectionDescription;*/

          // Descrierea conexiunii PC1 - Switch
          //connectionDescription += "PC1 (IP: " + pc1IP + ") este conectat la Switch.\n";

          //// Descrierea conexiunii PC2 - Switch
          //connectionDescription += "PC2 (IP: " + pc2IP + ") este conectat la Switch.\n";

          //// Descrierea conexiunii Switch - Router
          //connectionDescription += "Switch este conectat la Router (IP: " + routerIP + ").\n";

          // ...

          // Afișarea descrierii într-un câmp de text sau într-o fereastră de mesaj
          //wxMessageBox(connectionDescription, "Descriere simulare", wxOK | wxICON_INFORMATION);


        connectionDescriptionTextCtrl->SetValue(connectionDescription);


        return connectionDescription;
    }
    void OnHintButtonClicked(wxCommandEvent& event) {
        wxString hintMessage = "Hint:\n";
        hintMessage += "PC1: 192.168.1.10\n";
        hintMessage += "PC2: 192.168.1.20\n";
        hintMessage += "Router: 192.168.1.1\n\n";
        hintMessage += "PC3:192.168.2.20\n";
        hintMessage += "PC3:192.168.2.30\n";
        hintMessage += "Router2:192.168.2.1\n";
        // Display the hint message
        wxMessageBox(hintMessage, "Hint", wxOK | wxICON_INFORMATION);
    }
    bool IsValidIPAddress(wxString a)
    {
        int contor = 0;
        for (int i = 0; i < a.length(); i++)
            if (a[i] == '.') contor++;
        if (contor != 3)
            return false;

        else true;
    }


    bool IsSameNetwork(const wxString& ip1, const wxString& ip2, const wxString& subnetMask)
    {
        wxStringTokenizer tkn1(ip1, ".");
        wxStringTokenizer tkn2(ip2, ".");
        wxStringTokenizer tknSubnet(subnetMask, ".");
        wxString routerSubnetMask = "255.255.255.0";
        // Verificăm fiecare parte a adreselor IP și măștii de subrețea
        while (tkn1.HasMoreTokens() && tkn2.HasMoreTokens() && tknSubnet.HasMoreTokens())
        {
            wxString part1 = tkn1.GetNextToken();
            wxString part2 = tkn2.GetNextToken();
            wxString subnetPart = tknSubnet.GetNextToken();

            long ipPart1, ipPart2, subnetPartValue;
            part1.ToLong(&ipPart1);
            part2.ToLong(&ipPart2);
            subnetPart.ToLong(&subnetPartValue);

            // Verificăm dacă adresele IP sunt în aceeași rețea
            if ((ipPart1 & subnetPartValue) != (ipPart2 & subnetPartValue))
            {
                return false;
            }
        }

        return true;
    }
    std::ofstream outfile;
    void OnCloseButtonClick(wxCommandEvent& event)
    {
        this->Close();
    }
}; 