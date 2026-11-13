#pragma once
// --- school_data.h -----1


#ifndef SCHOOL_DATA_H
#define SCHOOL_DATA_H


#include <string>
#include <vector>


struct School {
    int id;
    std::string name;
    std::string location;
    std::string category;
    std::string description;
    std::string openCampusDate;
    float rating;
};
#endif
std::vector<School> GetDefaultSchools();