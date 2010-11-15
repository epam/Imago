#pragma once
#include <string>
#include <vector>
#include "../Image/Point.h"

namespace gga
{
namespace mol
{
    struct Link;

	struct FormulaItem  // one chemical element like 14N2-3
    {
        unsigned    Isotope;
        std::string Name;
        unsigned    Number;
        signed int  Charge;
        inline FormulaItem(const std::string& name="") : Isotope(0), Name(name), Number(1), Charge(0) {}
    };

	class Element
	{
        typedef std::vector<Link*> LinkList;
        std::vector<FormulaItem>   Formula;
        Point       Location;
        LinkList    Links;
    public:
		inline  Element(const Point& point) : Location(point) {}
		inline ~Element() {}
        std::string printToString ()const;   // Example: C or N or "C2 N O3+2 H- 14N2-3
        bool        makeFromString(const std::string &str);
	};
}
}

