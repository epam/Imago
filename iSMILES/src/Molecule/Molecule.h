#pragma once
#include <list>
#include <vector>
#include <string>
#include "Element.h"
#include "Link.h"

namespace gga
{
namespace mol
{
	class Molecule
	{
        std::list  <Element>    Elements;
        std::vector<Link   >    Links;
    public:
        class IElementProcessor
        {
        public:
            virtual bool processElement(const Element& element)=0;
        };

		inline  Molecule() {}
		inline ~Molecule() {}
        inline size_t getElementNumber()const        {return Elements.size ();}
        inline const Element& getFirstElement()const {return Elements.front();}
        inline       Element& getFirstElement()      {return Elements.front();}
        inline Element& addElement(Element& el)      {Elements.push_back(el); return Elements.back();}
        inline Link&    addLink   (Link& lnk)        {Links.push_back(lnk); return Links.back();}
        void sort();
//        inline eraseElement(Element& el)         {Elements.erase() find(el);}

        bool processElements(IElementProcessor& p)
        {
            return true;
        }
	};
}
}

