// Copyright 2020 Your Name <your_email>
#pragma once
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include<iostream>
#include<any>
#include<string>
#include <fstream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include <json.hpp>
#include <any>
#include <fstream>
#include <iomanip>
using nlohmann::json;
struct Student {
    std::string Name;
    std::any Group;
    double Avg;
    std::any Debt;
};
class jsonholder {
public:
    jsonholder(); 
    jsonholder(const std::string& path_);
protected:
    json _data;
private:
    json& getJson();
};
class parser: public jsonholder {
public:
    parser();
    parser(const std::string& path);    
    void Print() const;
private:
    std::string _path;
    size_t _size = 0;
    std::vector<Student> _students;
private:
    void isarray();
    size_t FindSizeOfTheBiggestGroup() const;
    size_t FindSizeOfTheBiggestName() const;
    std::string getGroup(int index) const;
    std::string getDebt(int index) const;
};
#endif // INCLUDE_HEADER_HPP_
