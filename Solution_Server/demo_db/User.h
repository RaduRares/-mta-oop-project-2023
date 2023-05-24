#pragma once
#include <string>
using namespace std;
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;



class User {
public:
    int id;
    int tip_operatie;
    string username;
    string password;
   /* User(int id, const string& username, const string& email)
        : id(id), username(username), email(email) {}*/
    void Deserialize(const std::string& json)
    {
        Document document;
        document.Parse(json.c_str());

        if (document.HasMember("nume") && document["nume"].IsString())
            username = document["nume"].GetString();

        if (document.HasMember("password") && document["password"].IsString())
            password = document["password"].GetString();
        
        if (document.HasMember("id") && document["id"].IsInt())
            id = document["id"].GetInt();

        if (document.HasMember("tip_operatie") && document["tip_operatie"].IsInt())
            tip_operatie = document["tip_operatie"].GetInt();


    }


}; 