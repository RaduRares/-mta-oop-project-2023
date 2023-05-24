#pragma once





#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "User.h"
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <nanodbc.h>



using namespace std;

class DAL {
private:
    nanodbc::connection conn;

    void disconnect();
public:
        DAL(const string connectionString) : conn(connectionString) {}
        ~DAL(){}

        bool createUser(const User& user);
        User getUserById(int id);
        bool updateUser(const User& user);
        bool deleteUser(int id);
        vector<User> getUsersByEmail(const std::string& email);
        std::vector<User> getAllUsers();
};

int gasire_elemente_baza(string a,string b);
int deserializare_tip_operatie(char s[]);

void citire_simulare1(char s[]);
void citire_simulare2(char s[]);
void citire_simulare3(char s[]);
void citire_simulare4(char s[]);
void citire_simulare5(char s[]);
User dezerealizeaza_user(char s[]);

void userinfile();

void run_Simularea2(char s[]);
void run_Simularea3(char s[]);



