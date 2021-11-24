//
// Created by Octavia on 3/22/2021.
//

#ifndef A45_917OCTAVIASUCEAVA_DOMAIN_H
#define A45_917OCTAVIASUCEAVA_DOMAIN_H

#endif //A45_917OCTAVIASUCEAVA_DOMAIN_H
#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
//#include "../validators/validators.h"

using namespace std;

class Movie
{
private:
    std::string title;
    std::string genre;
    std::string trailer;
    int year;
    int likes;

public:
    //default constructor
    Movie()=default;

    //constructor initializing all the fields
    Movie(std::string title, std::string genre, int year, int likes, std::string trailer);

    friend ostream & operator << (ostream &out, Movie &m);

    friend istream & operator >> (istream &in,  Movie &m);

    // returns the title of a movie
    std::string get_title();

    //returns the trailer of a movie
    std::string get_trailer();

    //returns the genre of a movie
    std::string get_genre();

    //returns the year of a movie
    int get_year() const;

    //returns the number of likes
    int get_likes() const;

    //increases the number of likes with 1
    void inc_likes();
};

