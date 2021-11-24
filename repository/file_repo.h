//
// Created by Octavia on 4/22/2021.
//

#ifndef A67_917OCTAVIASUCEAVA_FILE_REPO_H
#define A67_917OCTAVIASUCEAVA_FILE_REPO_H

#endif //A67_917OCTAVIASUCEAVA_FILE_REPO_H
#pragma once
#include "../repository/repository.h"
#include <fstream>
class FileRepo: public Repository
{
public:
    FileRepo()=default;
    virtual void write_repo_in_file(vector<Movie> movies)=0;
};

class HTML: public FileRepo
{
public:
    void write_repo_in_file(vector<Movie> movies) override;
};

class CSV: public FileRepo
{
public:
    void write_repo_in_file(vector<Movie> movies) override;
};
