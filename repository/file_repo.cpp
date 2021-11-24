//
// Created by Octavia on 4/22/2021.
//

#include "file_repo.h"

void HTML::write_repo_in_file(vector<Movie> movies)
{
    ofstream out;
    out.open(R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\watch_list.html)");
    out<<"<!DOCTYPE html>\n"
         "<html>\n"
         "<head> \n"
         "    <title>Movies</title> \n"
         "</head> \n"
         "<body> \n"
         "<table border=\"1\">";
    for(auto &movie: movies)
        out<<"<tr>\n"
             "        <td>" + movie.get_title() + "</td>\n"
             "        <td>" + to_string(movie.get_year()) + "</td>\n"
             "        <td>" + to_string(movie.get_likes()) + "</td>\n"
             "        <td>" + movie.get_genre() + "</td>\n"
             "        <td><a href=\"" + movie.get_trailer() + R"(" target="_blank">)" +"Link</a></td>\n"
             "    </tr>";

    out<<"</table>\n"
         "</body>\n"
         "</html>";
    out.close();
}

void CSV::write_repo_in_file(vector<Movie> movies)
{
    ofstream out;
    out.open(R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\watch_list.csv)");
    for(auto &movie: movies)
        out<<movie.get_title()+","+to_string(movie.get_year())+","+to_string(movie.get_likes())+","+movie.get_genre()+","+movie.get_trailer()+"\n";
    out.close();
}