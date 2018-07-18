//book.hpp

#pragma once

#include<iostream>
#include<cstdbool>
#include<string>

class Book {
    private:
        std::string name_;
        std::string autor_;
    public:
        Book ();
        Book (const std::string & name, const std::string & autor);
        bool operator<(const Book &) const;
        bool operator==(const Book &) const;
        bool operator!=(const Book &) const;
        friend std::ostream & operator<<(std::ostream &, const Book &);
};
