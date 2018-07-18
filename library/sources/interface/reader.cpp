//reader.cpp

#include"reader.hpp"

Reader::Reader () : name_ {}, surname_ {}
{
}

Reader::Reader (const std::string & name, const std::string & surname) :
    name_ {name}, surname_ {surname}
{
}

bool Reader::operator<(const Reader & rhs) const
{
    if (surname_ < rhs.surname_) {
        return true;
    }
    else if (surname_ == rhs.surname_ && name_ < rhs.name_) {
        return true;
    }
    else {
        return false;
    }
}

bool Reader::operator==(const Reader & rhs) const
{
    return (surname_ == rhs.surname_ && name_ == rhs.name_);
}

bool Reader::operator!=(const Reader & rhs) const
{
    return (surname_ != rhs.surname_ || name_ != rhs.name_);
}

std::ostream & operator<<(std::ostream & out, const Reader & reader)
{
    out << reader.name_ << ' ' << reader.surname_;
    return out;
}
