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
        // Planar bond:
            LD_PLANAR,  // line
        // Stereo bonds:
            LD_UP,              // solid  triangle
            LD_DOWN,            // dashed triangle
            LD_UP_UNDIRECTED,   // solid  rectangle. exact direction is not specified.
            LD_DOWN_UNDIRECTED, // dashed rectangle. exact direction is not specified.
            LD_STEREO_BOND,     // wavy line /\/\/\/\/
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

