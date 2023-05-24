#undef UNICODE

#define WIN32_LEAN_AND_MEAN



#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
 #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>

#include "DAL.h"

using namespace std;


int main() {
    //std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=aut;Trusted_Connection=yes;";
   // //cout << "ddd";
   //// system("pause");
   //
   // DAL db(connection_string);

   // // Create a new user
   ///* User newUser{ 1, "John Doeeee", "johndoeeee@example.com" };
   // if (db.createUser(newUser)) {
   //     std::cout << "User created successfully.\n";
   // }
   // else {
   //     std::cout << "Error creating user.\n";
   // }*/

   // // Fetch user by ID
   // User fetchedUser = db.getUserById(0);
   // std::cout << "Fetched user: " << fetchedUser.id << ", " << fetchedUser.username << ", " << fetchedUser.email << '\n';

   // // Update user
   // fetchedUser.username = "JQke DAAA";
   // fetchedUser.email = "jQQQdoA@example.com";
   // if (db.updateUser(fetchedUser)) {
   //     std::cout << "User updated successfully.\n";
   // }
   // else {
   //     std::cout << "Error updating user.\n";
   // }

   // // Fetch users by email
   // std::vector<User> users = db.getUsersByEmail("janedoe@example.com");
   // for (const auto& user : users) {
   //     std::cout << "User found: " << user.id << ", " << user.username << ", " << user.email << '\n';
   // }

   // // Delete user
   // if (db.deleteUser(1)) {
   //     std::cout << "User deleted successfully.\n";
   // }
   // else {
   //     std::cout << "Error deleting user.\n";
   // }
    //std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=aut;Trusted_Connection=yes;";

    //DAL db(connection_string);

    //// Afișează toate înregistrările din tabel
    //std::vector<User> users = db.getAllUsers();
    //for (const auto& user : users) {
    //    std::cout << "User: " << user.id << ", " << user.username << ", " << user.email << '\n';
    //}
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;
    int z = 0,g=0;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult =::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    while (true) {
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        // Receive until the peer shuts down the connection
        do {
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                printf("Bytes received: %d\n", iResult);
                printf("Bytes received: %s\n", recvbuf);
                //    cout <<"serializat:"<< recvbuf << endl;
                //if (z == 0) {

                   /* std::string str(recvbuf);
                    std::string json = "print";
                    User persoanaDeserializata;
                    persoanaDeserializata.Deserialize(json);*/
                    cout << "fff";
                    if (z == 0 && strcmp(recvbuf,"print")!=0) {
                        User U = dezerealizeaza_user(recvbuf);
                        // //// Verificare rezultat
                        // //std::cout << "Nume: " << persoanaDeserializata.nume << std::endl;
                        // //std::cout << "PASSword: " << persoanaDeserializata.password << std::endl;
                        if (gasire_elemente_baza(U.username, U.password) == 1 && U.username!= U.password)
                            //
                            strcpy_s(recvbuf, "ATI REUSIT,AI FOST GASIT");
                        else  strcpy_s(recvbuf, "NU ATI FOST GASIT,INCERCATI AGAIN");
                       
                    }

                  



                    if (strcmp(recvbuf, "ATI REUSIT,AI FOST GASIT") == 0)
                        z = 22;
                      
                    if (strcmp(recvbuf, "Simularea 1") == 0)
                    {
                        g = 1;

                    }

                    if (strcmp(recvbuf, "Simularea 2") == 0)
                    {
                        g = 2;

                    }

                    if (strcmp(recvbuf, "Simularea 3") == 0)
                    {
                        g = 3;

                    }


                    if (g == 1) {
                    //    cout << "sunrttt in simulAAAAAAAAAAAAAAAAAAAAAAAare:g=1";
                        if (deserializare_tip_operatie(recvbuf) == 2)
                        {
                      //      cout << "qqqqqq sAAAAAAAAAAAAAAAAAAAimulare g=1";
                            citire_simulare1(recvbuf);

                        }


                    }

                    if (g == 2) {
                       
                        run_Simularea2(recvbuf);
                        cout<<"SUNT IN Simualare2";

                       citire_simulare2(recvbuf);



                    }

                    if (g == 3) {

                        run_Simularea3(recvbuf);
                        citire_simulare3(recvbuf);


                        cout << "Simualare3";

                    }




                   /* if (deserializare_tip_operatie(recvbuf) == 2)
                    {
                        citire_simulare1(recvbuf);

                    }*/

                    if (strcmp(recvbuf, "print") == 0) {

                        //   userinfile();
                        citire_simulare5(recvbuf);
                        cout << recvbuf << " FFFFF";

                    }
                   



                
                // Echo the buffer back to the sender
                iSendResult = send(ClientSocket, recvbuf, iResult, 0);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf("Bytes sent: %d\n", iSendResult);
            }
            else if (iResult == 0)
                printf("Connection closing...\n");
            else {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
        } while (iResult > 0);

        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        // cleanup
        closesocket(ClientSocket);
    }
   // system("pause");
    
    
    return 0;
}


