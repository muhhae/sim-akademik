#include "include/Entity.hpp"

namespace dt
{
    void Entity::add(std::string type, std::string value)
    {
        dataStruct dt;
        dt.type = type;
        dt.value = value;
        data.push_back(dt);
    }

    void Entity::remove(std::string type)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data.at(i).type == type)
            {
                data.erase(data.begin() + i);
                i--;
            }
        }
    }

    void Entity::set(std::string type, std::string value)
    {
        for (auto& dt : data)
        {
            if (dt.type == type)
            {
                dt.value = value;
                return;
            }
        }
    }

    std::string Entity::get(std::string type)
    {
        for (const auto& dt : data)
        {
            if (dt.type == type)
            {
                return dt.value;
            }
        }
        return "";
    }

    void Entity::AppendToString(std::string& str)
    {
        for (const auto& dt : data)
        {
            str += dt.type + "=" + dt.value + "\n";
        }
        str += "@@@";
    }
}