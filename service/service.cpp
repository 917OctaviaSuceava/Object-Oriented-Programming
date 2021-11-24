
#include <iostream>
#include "../validators/validators.h"
#include "service.h"

Service::Service(Repository &s, FileRepo &f): service{s}
{
    file_repo = &f;
}

void Service::service_add(Movie movie, std::string filename)
{
    //MovieValidate::validate_add(this->service, movie.get_trailer());
    service.repo_add(movie, filename);
}

void Service::load(std::string filename)
{
    service.load_from_file(filename);
}

void Service::service_delete(std::string trailer, std::string filename)
{
    Movie movie = this->get_elem(trailer);
    service.repo_delete(service.get_position(movie), filename);
}

void Service::service_update(std::string trailer, Movie movie_update, std::string filename)
{
    this->service.repo_update(trailer, movie_update, filename);
}

int Service::get_pos(Movie movie)
{
    return service.get_position(movie);
}

int Service::get_len()
{
    return this->service.get_len();
}

vector<Movie> Service::get_elems()
{
    return this->service.get_elems();
}

Movie Service::get_elem(std::string trailer)
{
    return this->service.get_element(trailer);
}

void Service::service_inc_likes(std::string trailer, std::string filename)
{
    Movie movie = this->get_elem(trailer);
    service.increase_likes(service.get_position(movie), filename);
}

void Service::write_to_html()
{
    file_repo->write_repo_in_file(user_service.get_elems());
    //html_repo.write_repo_in_file(user_service.get_elems());
}

void Service::write_to_csv()
{
    //csv_repo.write_repo_in_file(user_service.get_elems());
}

void Service::write_to_file_format()
{
    file_repo->write_repo_in_file(user_service.get_elems());
}

void Service::add_watch_list(Movie movie, std::string filename)
{
    if(user_service.get_position(movie) != -1)
        return;
    user_service.repo_add(movie, filename);
    write_to_file_format();
//    if(format == 1)
//        write_to_html();
//    else if(format == 2)
//        write_to_csv();
}


vector<Movie> Service::get_watch_list()
{
    return this->user_service.get_elems();
}

int Service::get_watch_list_len()
{
    return this->user_service.get_len();
}

int Service::get_user_pos(std::string trailer)
{
    Movie movie = user_service.get_element(trailer);
    return user_service.get_position(movie);
}

void Service::delete_from_watch_list(std::string trailer)
{
    Movie movie = user_service.get_element(trailer);
    user_service.repo_delete(user_service.get_position(movie), R"(C:\Users\Octavia\Documents\GitHub\a67-917OctaviaSuceava\watch_list.txt)");
    write_to_file_format();
}
