#pragma once

#include <iostream>
#include <fstream>

#include "Entity.hpp"

namespace dt
{
    class CustomParser
    {
        private :
            std::string source;
            std::vector<Entity> entity;
        
        public:
            Entity& find(std::string match_type, std::string match_value);
            std::vector<Entity> get();

            void setSource(std::string source);
            std::string getSource();

            void add(Entity et);
            void load();
            void update();

            void print();
    };
}