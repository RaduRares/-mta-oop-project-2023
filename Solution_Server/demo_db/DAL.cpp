#include "DAL.h"
#include "Simulare1.h"
#include "Simulare2.h"
#include <string>





void citire_simulare5(char s[]) {

    std::ifstream inputFile("users.txt");
    std::string fileContent;

    if (inputFile.is_open()) {
        // Citeste continutul fisierului linie cu linie
        std::cout << "Continutul fisierului:\n";
        while (std::getline(inputFile, fileContent)) {
            std::cout << fileContent << std::endl;
        }
        strcpy(s, fileContent.c_str());
        // Verifica daca citirea a fost cu succes
        if (!inputFile.eof()) {
            std::cout << "Eroare la citirea fisierului." << std::endl;
        }

        // Inchide fisierul
        inputFile.close();
    }
    else {
        std::cout << "Nu s-a putut deschide fisierul." << std::endl;
    }


}











void citire_simulare4(char s[]) {

    std::ifstream inputFile("users.txt");
    std::string fileContent;

    if (inputFile.is_open()) {
        // Obține lungimea fișierului
        inputFile.seekg(0, std::ios::end);
        std::streampos fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        // Alocă suficient spațiu în string pentru conținutul fișierului
        fileContent.resize(fileSize);

        // Citește conținutul fișierului în string
        inputFile.read(&fileContent[0], fileSize);


        strcpy(s, fileContent.c_str());
        
        // Verifică dacă citirea a fost cu succes
        if (inputFile) {
            std::cout << "Continutul fisierului:\n";
            std::cout << fileContent;
        }
        else {
            std::cout << "Eroare la citirea fisierului.";
        }

        // Închide fișierul
        inputFile.close();
    }
    else {
        std::cout << "Nu s-a putut deschide fisierul.";
    }


}




void userinfile() {

    std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=POO;Trusted_Connection=yes;";
    fstream f("users.txt", ios::out);
    DAL db(connection_string);
    int ok = 0;
    // Afișează toate înregistrările din tabel
    std::vector<User> users = db.getAllUsers();
    for (const auto& user : users) {
        f << "->User: " << user.username << ", " << user.password ;
       
    }

    f.close();
}






int gasire_elemente_baza(string a,string b) {

    std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=POO;Trusted_Connection=yes;";
    
   DAL db(connection_string);
   int ok = 0;
   // Afișează toate înregistrările din tabel
   std::vector<User> users = db.getAllUsers();
   for (const auto& user : users) {
     //  std::cout << "User: " << user.id << ", " << user.username << ", " << user.password << '\n';
       if (user.username == a && user.password == b)
       {
           ok = 1;

       }


   }

   return ok;
}

  

bool DAL::createUser(const User& user) {
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO myusers (username, password) VALUES (?, ?);
        )");

    
    stmt.bind(0, user.username.c_str());
    stmt.bind(1, user.password.c_str());
    nanodbc::result rez = stmt.execute();

    return rez.has_affected_rows();
}

User DAL::getUserById(int id) {
    User user;
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
        SELECT id, username, password FROM myusers WHERE id = ?;
    )");
    stmt.bind(0, &id);

    nanodbc::result result = stmt.execute();
    
    const short columns = result.columns();
    cout << "\nDisplaying " << result.rowset_size() << " rows "
        << "(" << result.rowset_size() << " fetched at a time):" << endl;

    // show the column names
    cout << "row\t";
    for (short i = 0; i < columns; ++i)
        cout << result.column_name(i) << "\t";
    cout << endl;

    if (result.next()) {
        user.id = result.get<int>(0);
        user.username = result.get<std::string>(1);
        user.password = result.get<std::string>(2);
    }

    return user;
}

bool DAL::updateUser(const User& user) {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            UPDATE myusers SET username = ?, password = ? WHERE id = ?;
        )");

        stmt.bind(0, user.username.c_str());
        stmt.bind(1, user.password.c_str());
        stmt.bind(2, &user.id);

        nanodbc::result rez = stmt.execute();

        return rez.has_affected_rows();
    }

bool DAL::deleteUser(int id) {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            DELETE FROM myusers WHERE id = ?;
        )");

        stmt.bind(0, &id);

        nanodbc::result rez = stmt.execute();

        return rez.has_affected_rows();
    }

vector<User> DAL::getUsersByEmail(const std::string& email) 
{
        std::vector<User> users;
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT id, username, password FROM myusers WHERE email LIKE ?;
        )");

        std::string email_pattern = "%" + email + "%";
        stmt.bind(0, email_pattern.c_str());

        nanodbc::result result = stmt.execute();

        while (result.next()) {
            User user;
            user.id = result.get<int>(0);
            user.username = result.get<std::string>(1);
            user.password = result.get<std::string>(2);
            users.push_back(user);
        }

        return users;
    }



void DAL::disconnect() {
    if (conn.connected()) {
        conn.disconnect();
        conn.deallocate();
    }
}

std::vector<User> DAL::getAllUsers() {
    std::vector<User> users;
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
        SELECT id, username, password FROM myusers;
    )");

    nanodbc::result result = stmt.execute();

    while (result.next()) {
        User user;
        user.id = result.get<int>(0);
        user.username = result.get<std::string>(1);
        user.password = result.get<std::string>(2);
        users.push_back(user);
    }

    return users;
}

User dezerealizeaza_user(char s[])
{
     char u[455];
     strcpy_s(u, s);
     std::string str(u);
                   std::string json = u;
                   User persoanaDeserializata;
                   persoanaDeserializata.Deserialize(json);
   


    return persoanaDeserializata;
}

void citire_simulare1(char s[]) {

    std::ifstream inputFile("simularea1.txt");
    std::string fileContent;

    if (inputFile.is_open()) {
        // Obține lungimea fișierului
        inputFile.seekg(0, std::ios::end);
        std::streampos fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        // Alocă suficient spațiu în string pentru conținutul fișierului
        fileContent.resize(fileSize);

        // Citește conținutul fișierului în string
        inputFile.read(&fileContent[0], fileSize);


        strcpy(s, fileContent.c_str());
        // Verifică dacă citirea a fost cu succes
        if (inputFile) {
            std::cout << "Continutul fisierului:\n";
            std::cout << fileContent;
        }
        else {
            std::cout << "Eroare la citirea fisierului.";
        }

        // Închide fișierul
        inputFile.close();
    }
    else {
        std::cout << "Nu s-a putut deschide fisierul.";
    }






}




int deserializare_tip_operatie(char s[])
{
    char u[455];
    strcpy_s(u, s);
    std::string str(u);
    std::string json = u;

    Simulare1 sim1;
    sim1=Deserialize_Simulare1(json);

   // cout << sim1.nume_switch << " CU " << sim1.ip_switch << " " << sim1.Port_switch1 << " CONNECT " << sim1.nume_Router << " " << sim1.ip_Router << " " << sim1.Port_switch2 << " CONNECT" << sim1.nume_PC;


    if (sim1.tip_operatie == 2)
    {
        cout << "sunt in if";
        fstream f("simularea1.txt", ios::out);
        f << "Switch-ul: "<<sim1.nume_switch << " CU IP-ul: " << sim1.ip_switch << " si cu Portul:" << sim1.Port_switch1 << " conectat la routerul: " << sim1.nume_Router << " care are ip: " << sim1.ip_Router << " iar portul2: " << sim1.Port_switch2 << " conectat cu PC-ul: " << sim1.nume_PC;

        f.close();
        return 2;

}
    
    return 0;
   // return n.tip_operatie;
}


void run_Simularea2(char s[]) {



    char u[455];
    strcpy_s(u, s);
    std::string str(u);
    std::string json = u;

    Simulare2 sim1;
    sim1 = Deserialize_Simulare2(json);

    fstream f("simularea2.txt", ios::out);
    f << "Pinging " <<sim1.ip_PC1<<" with 32 bytes of data:";

    f.close();


}


void run_Simularea3(char s[]) {



    char u[455];
    strcpy_s(u, s);
    std::string str(u);
    std::string json = u;

    Simulare2 sim1;
    sim1 = Deserialize_Simulare2(json);

    fstream f("simularea3.txt", ios::out);
    f << "Internet Address: " << sim1.ip_PC1 << " Phisycal Address: "<< sim1.nume_PC1<<" Type Dynamic";

    f.close();


}



void citire_simulare2(char s[]) {

    std::ifstream inputFile("simularea2.txt");
    std::string fileContent;

    if (inputFile.is_open()) {
        // Obține lungimea fișierului
        inputFile.seekg(0, std::ios::end);
        std::streampos fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        // Alocă suficient spațiu în string pentru conținutul fișierului
        fileContent.resize(fileSize);

        // Citește conținutul fișierului în string
        inputFile.read(&fileContent[0], fileSize);


        strcpy(s, fileContent.c_str());
        // Verifică dacă citirea a fost cu succes
        if (inputFile) {
            std::cout << "Continutul fisierului:\n";
            std::cout << fileContent;
        }
        else {
            std::cout << "Eroare la citirea fisierului.";
        }

        // Închide fișierul
        inputFile.close();
    }
    else {
        std::cout << "Nu s-a putut deschide fisierul.";
    }


}





void citire_simulare3(char s[]) {

    std::ifstream inputFile("simularea3.txt");
    std::string fileContent;

    if (inputFile.is_open()) {
        // Obține lungimea fișierului
        inputFile.seekg(0, std::ios::end);
        std::streampos fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        // Alocă suficient spațiu în string pentru conținutul fișierului
        fileContent.resize(fileSize);

        // Citește conținutul fișierului în string
        inputFile.read(&fileContent[0], fileSize);


        strcpy(s, fileContent.c_str());
        // Verifică dacă citirea a fost cu succes
        if (inputFile) {
            std::cout << "Continutul fisierului:\n";
            std::cout << fileContent;
        }
        else {
            std::cout << "Eroare la citirea fisierului.";
        }

        // Închide fișierul
        inputFile.close();
    }
    else {
        std::cout << "Nu s-a putut deschide fisierul.";
    }


}

