#include "Simulare1.h"


Simulare1 Deserialize_Simulare1(const std::string& json)
{

    Document document;
    document.Parse(json.c_str());
    Simulare1 simulare1;

    // Verific? dac? parsarea a reu?it
    if (!document.HasParseError() && document.IsObject()) {
        // Extrage valorile din obiectul JSON ?i le atribuie membrilor clasei Simulare1


        simulare1.nume_PC = document["nume_PC"].GetString();
        simulare1.ip_PC = document["ip_PC"].GetString();
        simulare1.nume_switch = document["nume_switch"].GetString();
        simulare1.ip_switch = document["ip_switch"].GetString();
        simulare1.Port_switch1 = document["Port_switch1"].GetString();
        simulare1.Port_switch2 = document["Port_switch2"].GetString();
        simulare1.nume_Router = document["nume_Router"].GetString();
        simulare1.ip_Router = document["ip_Router"].GetString();
        simulare1.tip_operatie = document["tip_operatie"].GetInt();


    }

    return simulare1;
}

