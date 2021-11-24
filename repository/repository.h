//
// Created by Octavia on 3/23/2021.
//

#ifndef A45_917OCTAVIASUCEAVA_REPOSITORY_H
#define A45_917OCTAVIASUCEAVA_REPOSITORY_H

#endif //A45_917OCTAVIASUCEAVA_REPOSITORY_H
#pragma once
#include <iostream>
#include <fstream>
#include "../domain/domain.h"

class Repository
{
private:
    //sets the class for the templates class <DynamicVector> to <Movie>
    //DynamicVector<Movie> repository;
    vector<Movie> repository;

public:
    //constructor
    Repository();

    //copy constructor
    Repository(const Repository &repo_copy);

    //adds the movie <elem> into the repository
    void repo_add(Movie elem, std::string filename);

    void add_in_file(Movie elem, std::string filename);

    void write_repo_in_file(std::string filename);

    //returns the list of movies from the repository
    vector<Movie> get_elems();

    //deletes the movie from the position <position>
    void repo_delete(int position, std::string filename);

    //returns the position of a given movie
    int get_position(Movie element);

    //gets a movie based on its unique identifier, which is the <trailer> field
    Movie get_element(std::string trailer);

    //replaces the movie that has the given <trailer> with a new movie, called <movie_update>
    void repo_update(std::string trailer, Movie movie_update, std::string filename);

    //increases the number of likes of a movie from a given position
    void increase_likes(int position, std::string filename);

    //returns the length of the movies list
    int get_len();

    void load_from_file(std::string filename);
};
