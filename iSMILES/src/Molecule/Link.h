#pragma once

namespace gga
{
namespace mol
{
    class Element;

    struct Link
	{
        enum    Type
        {
            LT_SINGLE,
            LT_DOUBLE,
            LT_TRIPLE,
            LT_AROMATIC,
        };
        enum    Direction
        {
            LD_NONE,
            LD_UP,
            LD_DOWN,
        };

        Link::Type      Type;
        Link::Direction Direction;
        const Element*  FirstElement;
        const Element*  LastElement;
    public:
		inline  Link(const Element* left, const Element* rigth) : FirstElement(left), LastElement(rigth) {}
		inline ~Link() {}
	};
}
}

