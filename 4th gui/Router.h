#pragma once
#include<iostream>
using namespace std;
class Router {
public:
    static Router& GetInstance() {
        static Router instance;
        return instance;
    }



    void PrintInfo() {
        
    }
    void SetName(string name)
    {
        name = name;
    }

private:
    Router() {}

    string name;
};
