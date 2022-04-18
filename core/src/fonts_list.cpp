#include "fonts_list.h"

namespace imago
{
    FontEntryDefinition::FontEntryDefinition(const std::string& _name, const std::string& _data)
    {
        name = _name;
        data = _data;
    }

    FontEntries::FontEntries()
    {
    }

    FontEntries getFontsList()
    {
        static FontEntries result;
        return result;
    }
}