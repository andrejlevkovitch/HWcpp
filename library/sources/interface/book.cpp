//book.cpp

#include"book.hpp"

Book::Book () : name_ {}, autor_ {}
{
}

Book::Book (const std::string & name, const std::string & autor) :
    name_ {name}, autor_ {autor}
{
}

bool Book::operator<(const Book & rhs) const
{
    if (autor_ < rhs.autor_) {
        return true;
    }
    else if (autor_ == rhs.autor_ && name_ < rhs.name_) {
        return true;
    }
    else {
        return false;
    }
}

bool Book::operator==(const Book & rhs) const
{
    return (name_ == rhs.name_ && autor_ == rhs.autor_);
}

bool Book::operator!=(const Book & rhs) const
{
    return (name_ != rhs.name_ && autor_ != rhs.autor_);
}

std::ostream & operator<<(std::ostream & out, const Book & book)
{
    out << book.name_ << ' ' << book.autor_;
    return out;
}
