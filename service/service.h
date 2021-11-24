//
// Created by Octavia on 3/23/2021.
//

#ifndef A45_917OCTAVIASUCEAVA_SERVICE_H
#define A45_917OCTAVIASUCEAVA_SERVICE_H

#endif //A45_917OCTAVIASUCEAVA_SERVICE_H

#pragma once
#include "../repository/repository.h"
#include "../repository/file_repo.h"

class Service
{

private:
    //repo for the administrator mode
    Repository service;
    //repo for the user mode
    Repository user_service;
    //HTML html_repo;
    //CSV csv_repo;
    FileRepo *file_repo;

public:
    //constructor
    Service(Repository &s, FileRepo &f);

    //function for the user mode
    //adds a movie to the user's repository
    void add_watch_list(Movie movie, std::string filename);

    //function for the user mode
    //returns the list of movies from the user's repository
    vector<Movie> get_watch_list();

    //function for the user mode
    //returns the length of the user's watch list
    int get_watch_list_len();

    //returns the position of a given movie
    int get_pos(Movie movie);

    //deletes the movie having the given <trailer> from the user's repo
    void delete_from_watch_list(std::string trailer);

    //increases the number of likes of a movie having the given <trailer>
    void service_inc_likes(std::string trailer, std::string filename);

    //deletes the movie having the given <trailer> from the administrator's repo
    void service_delete(std::string trailer, std::string filename);

    //adds a movie having the given fields in the administrator's repo
    void service_add(Movie movie, std::string filename);

    //replaces the movie having the given <trailer> with a new movie containing the given fields
    void service_update(std::string trailer, Movie movie_update, std::string filename);

    //returns the list of movies from the administrator's repo
    vector<Movie> get_elems();

    //gets a movie from the repo having a given trailer
    Movie get_elem(std::string trailer);
    int get_user_pos(std::string trailer);

    //returns the length of the administrator's list of movies
    int get_len();

    void load(std::string filename);

    void write_to_html();

    void write_to_csv();

    void write_to_file_format();
};
