#pragma once

#include <iostream>
#include <vector>
#include <fstream>

namespace dt
{
    class Entity
    {
        private:
            struct dataStruct
            {
                std::string type;
                std::string value;
            };
            std::vector<dataStruct> data;

        public:
            void add(std::string type, std::string value);
            void remove(std::string type);
            
            void set(std::string type, std::string value);
            std::string get(std::string type);

            void AppendToString(std::string& str);
    };
}