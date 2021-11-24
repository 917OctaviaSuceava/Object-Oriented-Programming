//
// Created by Octavia on 3/22/2021.
//

#include "domain.h"

Movie::Movie(std::string title, std::string genre, int year, int likes, std::string trailer)
{
    this->title = title;
    this->trailer = trailer;
    this->genre = genre;
    this->likes = likes;
    this->year = year;
}


ostream & operator << (ostream &out, Movie &m)
{
    out<<m.trailer<<" "<<m.likes<<" "<<m.year<<" "<<m.genre<<" "<<m.title<<endl;
    return out;
}


std::istream &operator>>(istream &in, Movie &m)
{
    in>>m.trailer>>m.likes>>m.year>>m.genre;
    in.ignore();
    getline(in, m.title);
    return in;
}


std::string Movie::get_title()
{
    return this->title;
}

std::string Movie::get_trailer()
{
    return this->trailer;
}

std::string Movie::get_genre()
{
    return this->genre;
}

int Movie::get_year() const
{
    return this->year;
}

int Movie::get_likes() const
{
    return this->likes;
}

void Movie::inc_likes()
{
    this->likes = this->likes + 1;
}
