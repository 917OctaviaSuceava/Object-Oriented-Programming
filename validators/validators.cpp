//
// Created by Octavia on 4/12/2021.
//

#include "validators.h"

void MovieValidate::validate_add(Service &s, std::string trailer)
{
    std::string errors;
    if(s.get_pos(s.get_elem(trailer)) != -1)
        errors += "That movie already exists in the list!";

    if (!errors.empty())
        throw ValidationException(errors); }

void MovieValidate::validate_delete_update(Service &s, std::string trailer)
{
    std::string errors;
    if(s.get_pos(s.get_elem(trailer)) == -1)
        errors += "That movie does not exist in the list!";

    if (!errors.empty())
        throw ValidationException(errors); }

void MovieValidate::validate_movie(Movie &m)
{
    std::string errors;
    if(m.get_trailer().size() < 7)
        errors += "The trailer should have at least 7 characters!\n";
    if(isdigit(m.get_year()) != 0 || m.get_year() > 2021 || m.get_year() < 1800)
        errors += "That year is not valid!\n";
    if(isdigit(m.get_likes()) != 0 || m.get_likes() < 0)
        errors += "The number of likes is not valid!\n";
    if(m.get_genre().size() <= 1)
        errors += "That genre is not valid!\n";
    if(!errors.empty())
        throw ValidationException(errors);
}

void MovieValidate::validate_user_delete(Service &s, std::string trailer)
{
    std::string errors;
    if(s.get_user_pos(trailer) == -1)
        errors +=  "That movie does not exist in the watch list!";

    if (!errors.empty())
        throw ValidationException(errors); }

ValidationException::ValidationException(std::string m) : message{m} {
}

std::string ValidationException::get_message() const {
    return this->message;
}
