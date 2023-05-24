#include "Persoana.h"
//
std::string getstring() {

    MyClass myObj;
    myObj.id = 1;
    myObj.name = "John Doe";
    myObj.values = { 10, 20, 30 };

    // Serializare în JSON
    Json::Value jsonData = myObj.serialize();
    Json::StreamWriterBuilder writerBuilder;
    std::string jsonString = Json::writeString(writerBuilder, jsonData);
    // std::string jsonString = Json::writeString(writerBuilder, jsonData);
    std::cout << "JSON serializat: " << jsonString << std::endl;

    return myObj.name;

}

//int main() {
//    return 0;
//}

