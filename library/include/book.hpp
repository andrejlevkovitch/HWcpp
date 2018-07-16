//book.hpp

#pragma once

#include<cstdbool>
#include<string>

class Book {
    private:
        std::string name_;
        std::string autor_;
    public:
        Book ();
        Book (const std::string & name, const std::string & autor);
        bool operator<(const Book &);
};
