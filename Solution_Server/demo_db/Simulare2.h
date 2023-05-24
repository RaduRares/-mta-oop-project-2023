#pragma once
#pragma warning(disable : 4996)
#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace rapidjson;

class Simulare2
{
public:
	string nume_PC;
	string ip_PC;
	string nume_PC1;
	string ip_PC1;
	string nume_switch;
	string ip_switch;
	string Port_switch1;
	string Port_switch2;
	string nume_Router;
	string ip_Router;
	int tip_operatie;
	/*Simulare1(const std::string& nume_PC, const string ip_PC, const string nume_switch, const string ip_switch, const string Port_switch1, string Port_switch2, string nume_Router, string ip_Router, const int tip_operatie)
		: nume_PC(nume_PC), ip_PC(ip_PC), nume_switch(nume_switch), ip_switch(ip_switch), Port_switch1(Port_switch1), Port_switch2(Port_switch2), nume_Router(nume_Router), ip_Router(ip_Router), tip_operatie(tip_operatie) {}*/







};

Simulare2 Deserialize_Simulare2(const std::string& json);



