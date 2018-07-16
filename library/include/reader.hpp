//reader.hpp

#pragma once

#include<cstdbool>
#include<string>

class Reader {
    private:
        std::string name_;
        std::string surname_;
    public:
        Reader ();
        Reader (const std::string & name, const std::string & surname);
        bool operator<(const Reader &) const;
};
