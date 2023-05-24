#pragma once
#include<wx\wx.h>
#include"PC.h"
#include"Switch.h"
#include"Router.h"
#include <wx/socket.h>
#include <wx/tokenzr.h>
#include<fstream>
#include<iostream>
#include"FourthFrame.h"
class SecondFrame : public wxFrame
{
public:
    SecondFrame(const wxString& title);

    FourthFrame* fourthFrame;
    void OnConnect(wxCommandEvent& event);
private:

    wxTextCtrl* pc1TextCtrl;
    wxTextCtrl* pc2TextCtrl;
    wxTextCtrl* connectionDescriptionTextCtrl;
    wxTextCtrl* routerTextCtrl;
    void OnStartSimulationButtonClicked(wxCommandEvent& event) {
        wxString pc1IP = pc1TextCtrl->GetValue();
        wxString pc2IP = pc2TextCtrl->GetValue();
        wxString routerIP = routerTextCtrl->GetValue();

        // Perform the simulation using the PC IP addresses
        wxString connectionDescription = PerformSimulation(pc1IP, pc2IP,routerIP);

        // Display the connection description
        connectionDescriptionTextCtrl->SetValue(connectionDescription);
    }

    wxString PerformSimulation(const wxString& pc1IP, const wxString& pc2IP,const wxString& routerIP) {
        fstream file;

        file.open("Log.txt", std::ios::out | std::ios::app);
       
        wxString connectionDescription;
       int contor = 0;
       wxString routerSubnetMask = "255.255.255.0";
            if (IsValidIPAddress(pc1IP)==0 || IsValidIPAddress(pc2IP)==0 || IsValidIPAddress(routerIP) == 0) {
                // Display error message if IP addresses are not in the expected format
                connectionDescription="Invalid IP address format. Please enter IP addresses in the format X.X.X.X";
                 return connectionDescription;
            }
            if (IsSameNetwork(pc1IP, routerIP, routerSubnetMask)) {
                connectionDescription += "PC1 (IP: " + pc1IP + ") este conectat la Router (IP: " + routerIP + ").\n";
                contor++;
            }
            else {
                connectionDescription += "PC1 (IP: " + pc1IP + ") NU este în aceeași rețea cu Routerul (IP: " + routerIP + ").\n";
            }

            // Verificarea dacă PC2 și routerul sunt în aceeași rețea
            if (IsSameNetwork(pc2IP, routerIP, routerSubnetMask)) {
                connectionDescription += "PC2 (IP: " + pc2IP + ") este conectat la Router (IP: " + routerIP + ").\n";
                contor++;
            }
            else {
                connectionDescription += "PC2 (IP: " + pc2IP + ") NU este în aceeasi retea cu Routerul (IP: " + routerIP + ").\n";
            }
            if (contor = 2)
            {
                connectionDescription += " PC1(IP : " + pc1IP + ")este conectat la Switch.\nSwitch este conectat la Router(IP : " + pc2IP + ")prin intermediul portului Ethernet.\nPC2(IP: " + routerIP + ") este conectat la Switch.\nSwitch-ul facilitează conectivitatea între PC2 și Router prin intermediul portului Ethernet.\nConfiguratia retelei:\n";
                    connectionDescription += "- Adresa IP a PC1 : " + pc1IP+"\n";
                connectionDescription += "- Adresa IP a PC2 : " + pc2IP + "\n";
                connectionDescription += "- Adresa IP a Routerului : "+routerIP + "\n";
                connectionDescription += "- Mască de retea : 255.255.255.0";

                connectionDescription +="Aceasta configuratie permite rutarea traficului între PC1 și PC2 prin intermediul Routerului, permitandu - le sa comunice intre ele si sa acceseze resursele din retea.";
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
        hintMessage += "Router: 192.168.1.1 ";

        // Display the hint message
        wxMessageBox(hintMessage, "Hint", wxOK | wxICON_INFORMATION);
    }
    bool IsValidIPAddress(wxString a)
    {
        int contor = 0;
        for (int i = 0; i < a.length(); i++)
            if(a[i] == '.') contor++;
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