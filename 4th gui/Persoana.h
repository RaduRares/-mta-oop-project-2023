#pragma once
#pragma warning(disable : 4996)
#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <json/json.h>
using namespace std;
//string getstring();
class MyClass {
public:
    int id;
    std::string name;
    std::vector<int> values;

    // Serializare în JSON
    Json::Value serialize() {
        Json::Value root;
        root["id"] = id;
        root["name"] = name;

        Json::Value jsonValues(Json::arrayValue);
        for (const int& value : values) {
            jsonValues.append(value);
        }
        root["values"] = jsonValues;

        return root;
    }

    // Deserializare din JSON
    void deserialize(const Json::Value& root) {
        id = root["id"].asInt();
        name = root["name"].asString();

        const Json::Value& jsonValues = root["values"];
        for (const Json::Value& value : jsonValues) {
            values.push_back(value.asInt());
        }
    }
};

