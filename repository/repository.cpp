//
// Created by Octavia on 3/23/2021.
//

#include "repository.h"
#include "../validators/validators.h"

Repository::Repository()
{

}

Repository::Repository(const Repository &repo_copy)
{

}

void Repository::repo_add(Movie elem, std::string filename)
{
    int ok = 0;
    try
    {
        MovieValidate::validate_movie(elem);
    }
    catch (ValidationException &ex)
    {
        ok = 1;
        cout<<ex.get_message()<<endl;
    }
    if(ok == 0)
    {
        this->repository.push_back(elem);
        add_in_file(elem, filename);
    }
}

void Repository::load_from_file(std::string filename)
{
    ifstream in(filename);
    Movie movie;
    while(in>>movie)
    {
        int ok = 0;
        try
        {
            MovieValidate::validate_movie(movie);
        }
        catch (ValidationException &ex)
        {
            ok = 1;
            cout<<ex.get_message()<<endl;
        }
        if(ok == 0)
            this->repository.push_back(movie);
    }
    in.close();
}

void Repository::add_in_file(Movie elem, std::string filename)
{
    ofstream out;
    out.open(filename, ios::app);
    out<<elem;
    out.close();
}

vector<Movie> Repository::get_elems()
{
    return this->repository;
}

int Repository::get_len()
{
    return this->repository.size();
}

int Repository::get_position(Movie element)
{
    int pos = 0;
    for(auto i: this->repository)
    {
        if (i.get_title() == element.get_title() &&
            i.get_year() == element.get_year() &&
            i.get_trailer() == element.get_trailer() &&
            i.get_genre() == element.get_genre() &&
            i.get_title() == element.get_title())
            return pos;
        pos++;
    }
    return -1;
}

void Repository::repo_delete(int position, std::string filename)
{
    this->repository.erase(this->repository.begin() + position);
    write_repo_in_file(filename);
}

void Repository::repo_update(std::string trailer, Movie movie_update, std::string filename)
{
    int ok = 0;
    try
    {
        MovieValidate::validate_movie(movie_update);
    }
    catch (ValidationException &ex)
    {
        ok = 1;
        cout<<ex.get_message()<<endl;
    }
    if(ok == 0) {
        int pos = 0;
        for (auto i: this->repository) {
            if (i.get_trailer() == trailer)
                this->repository[pos] = movie_update;
            pos++;
        }
        write_repo_in_file(filename);
    }
}

void Repository::write_repo_in_file(std::string filename)
{
    int pos = 0;
    ofstream out(filename);
    for(auto i: this->repository)
    {
        //out << endl << pos << ':' << endl;
        out << i;
        pos++;
    }
    out.close();
}

Movie Repository::get_element(std::string trailer)
{
    for(auto i: this->repository)
        if(i.get_trailer() == trailer)
            return i;
    return Movie();
}

void Repository::increase_likes(int position, std::string filename)
{
    this->repository[position].inc_likes();
    write_repo_in_file(filename);
}
