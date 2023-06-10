#include "include/CustomParser.hpp"

namespace dt
{
    Entity& CustomParser::find(std::string match_type, std::string match_value)
    {
        for (auto& et : entity)
        {
            if (et.get(match_type) == match_value) return et;
        }

        return *new Entity();
    }

    std::vector<Entity> CustomParser::get()
    {
        return entity;
    }

    void CustomParser::setSource(std::string source)
    {
        this->source = source;
    }
    std::string CustomParser::getSource()
    {
        return source;
    }

    void CustomParser::load()
    {
        std::ifstream dt_file(source);
        std::string str_tmp;

        Entity et;

        while (std::getline(dt_file, str_tmp))
        {
            // std::cout<<"line : "<<str_tmp<<std::endl;
            if (str_tmp == "@@@")
            {
                // std::cout<<"end"<<std::endl;
                entity.push_back(et);
                et = Entity();
                continue;
            }

            std::string type;
            std::string value;

            bool dtvl = false;

            for (auto c : str_tmp)
            {
                if (c == '=') 
                {
                    dtvl = true;
                    continue;
                }
                if (!dtvl) type += c;
                else value += c;
            }

            et.add(type, value);   
        }
        dt_file.close();
    }
    void CustomParser::update()
    {
        std::string temp_data = ""; 
        for(auto et : entity)
        {
            et.AppendToString(temp_data);
            temp_data += "\n";
        }
        temp_data.erase(temp_data.size()-1);
        
        std::ofstream dt_file;

        dt_file.open(source);
        dt_file << temp_data;
        dt_file.close();
    }

    void CustomParser::print()
    {
        std::string temp_data = ""; 
        for(auto et : entity)
        {
            et.AppendToString(temp_data);
            temp_data += "\n";
        }
        temp_data.erase(temp_data.size()-1);
        std::cout<<temp_data;
    }

    void CustomParser::add(Entity et)
    {
        entity.push_back(et);
    }
}