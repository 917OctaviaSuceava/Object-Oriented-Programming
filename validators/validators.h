//
// Created by Octavia on 4/12/2021.
//

#ifndef A67_917OCTAVIASUCEAVA_VALIDATORS_H
#define A67_917OCTAVIASUCEAVA_VALIDATORS_H

#endif //A67_917OCTAVIASUCEAVA_VALIDATORS_H

#pragma once

#include <exception>
#include "../service/service.h"

class MovieValidate
{
public:
    static void validate_add(Service &s, std::string trailer);

    static void validate_delete_update(Service &s, string trailer);

    static void validate_movie(Movie &m);

    static void validate_user_delete(Service &s, string trailer);
};

class ValidationException {
private:
    std::string message;

public:
    ValidationException(std::string m);

    std::string get_message() const;
};
