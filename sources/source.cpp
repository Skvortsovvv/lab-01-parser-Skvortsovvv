
#include "include\header.hpp"

void from_json(const json& j, Student& p) {
    j.at("name").get_to(p.Name);

    if (j.at("group").type() == json::value_t::string) {
        p.Group = j.at("group").get<std::string>();
    }
    else {
        p.Group = j.at("group").get<int>();
    }

    if (j.at("avg").type() == json::value_t::string) {
        p.Avg = atof(j.at("avg").get<std::string>().c_str());
    }
    else {
        p.Avg = j.at("avg").get<double>();
    }

    if (j.at("debt").type() == json::value_t::string) {
        p.Debt = j.at("debt").get<std::string>();
    }
    else if (j.at("debt").type() == json::value_t::array) {
        p.Debt = j.at("debt").get<std::vector<std::string>>();
    }
    else {
        p.Debt = NULL;
    }
}

jsonholder::jsonholder() {}
jsonholder::jsonholder(const std::string& path_) {
    std::ifstream fs(path_);
    if (!fs) {
        throw std::runtime_error{ "unable to open json: " + path_ };
    }
    fs >> _data;
}
json& jsonholder::getJson() {
    return _data;
}

parser::parser() {
    throw std::runtime_error{ "The path is empty" };
}


parser::parser(const std::string& path) : jsonholder(path), _path(path) {
    if (_data.at("items").type() == json::value_t::array) {
        _size = _data.at("items").size();
    }
    if (_size != 0) {
        if (_size == _data.at("_meta").at("count")) {
            for (auto const& student : _data.at("items")) {
                Student temp{};
                from_json(student, temp);
                _students.push_back(temp);
            }
        }
        else {

            throw std::runtime_error{ "actual array size not equal _meta count:
                " + std::to_string(_size) + " != "
                + std::to_string(_data.at("_meta").at("count").get<int>()) };
        }
    }
    else {
        throw std::runtime_error{ "The array is empty" };
    }

}


void parser::isarray() {
    if (_data.at("items").type() == json::value_t::array) {
        _size = _data.at("items").size();
    }
}

size_t parser::FindSizeOfTheBiggestGroup() const {
    size_t size = 0;
    for (size_t i = 0; i < _size; ++i) {
        size_t temp = getGroup(i).size();
        if (temp > size) {
            size = temp;
        }
    }
    return size;
}

size_t parser::FindSizeOfTheBiggestName() const {
    size_t size = 0;
    for (size_t i = 0; i < _size; ++i) {
        size_t temp = _students[i].Name.size();
        if (temp > size) {
            size = temp;
        }
    }
    return size;
}

std::string parser::getGroup(int index) const {
    if (_students[index].Group.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(_students[index].Group));
    }
    else {
        return std::any_cast<std::string>(_students[index].Group);
    }
}

std::string parser::getDebt(int index) const {
    if (_students[index].Debt.type() == typeid(std::vector<std::string>)) {
        return (std::to_string(std::any_cast<std::vector<std::string>>(_students[index].Debt).size()) + " items");
    }
    else if (_students[index].Debt.type() == typeid(NULL)) {
        return "null";
    }
    else {
        return std::any_cast<std::string>(_students[index].Debt);
    }
}


void parser::Print() const {
    size_t _bn = FindSizeOfTheBiggestName();
    size_t _bg = FindSizeOfTheBiggestGroup();
    std::cout << "| " << std::setw(_bn) << std::left << "name" << " | ";
    std::cout << std::setw(_bg) << std::left << "group" << " | ";
    std::cout << std::setw(4) << std::left << "avg" << " | ";
    std::cout << std::setw(13) << std::left << "debt" << " |" << std::endl;
    int temp = 0;
    if (_bn <= 4) {
        temp += 4;
    }
    else {
        temp += _bn;
    }
    if (_bg <= 5) {
        temp += 5;
    }
    else {
        temp += _bg;
    }
    temp += 28;

    for (size_t i = 0; i < _size; ++i) {
        std::cout << '|' << std::string(temp, '-') << '|' << std::endl;
        std::cout << "| " << std::setw(_bn) << std::left << _students[i].Name << " | ";
        std::cout << std::setw(_bg) << std::left << getGroup(i) << " | ";
        std::cout << std::left << std::to_string(_students[i].Avg).erase(4, 4) << " | ";
        std::cout << std::setw(13) << std::left << getDebt(i) << " |" << std::endl;
    }
    std::cout << '|' << std::string(temp, '-') << '|' << std::endl;
}
