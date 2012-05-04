#include "constants.h"

namespace imago
{
	static bool g_isHandwritten = false;
	static bool g_debugSession = false;
		
	// only failsafe defaults
	static int g_imageWidth = 800;
	static int g_imageHeight = 600;
	static double g_capitalHeight = 16.0;
	static double g_lineThickness = 6.0;
	static double g_avgBondLength = 30.0;

	static double g_addVertexEps = consts::ChemicalStructureRecognizer::sc::AddVertexEps;
	static double g_maxSymRatio = consts::ChemicalStructureRecognizer::sc::MaxSymRatio;
	static double g_minSymRatio = consts::ChemicalStructureRecognizer::sc::MinSymRatio;
	static double g_parLinesEps = consts::ChemicalStructureRecognizer::sc::ParLinesEps;
	static double g_symHeightErr = consts::ChemicalStructureRecognizer::sc::SymHeightErr;
	static double g_capitalHeightError = consts::ChemicalStructureRecognizer::sc::CapHeightError;
	static int g_doubleBondDist = consts::Separator::sc::DoubleBondDist;
	static int g_segmentVerEps = consts::Separator::sc::SegmentVerEps;

	double imago::vars::getSymHeightErr()
	{
		return g_symHeightErr;
	}

	double imago::vars::getAddVertexEps()
	{
		return g_addVertexEps;
	}

	void imago::vars::setAddVertexEps(double value)
	{
		g_addVertexEps = value;
	}

	void imago::vars::setHandwritten(bool value)
	{
		g_isHandwritten = value;
		if (g_isHandwritten)
		{
			g_addVertexEps = consts::ChemicalStructureRecognizer::hw::AddVertexEps;
			g_maxSymRatio = consts::ChemicalStructureRecognizer::hw::MaxSymRatio;
			g_minSymRatio = consts::ChemicalStructureRecognizer::hw::MinSymRatio;
			g_parLinesEps = consts::ChemicalStructureRecognizer::hw::ParLinesEps;
			g_symHeightErr = consts::ChemicalStructureRecognizer::hw::SymHeightErr;
			g_capitalHeightError = consts::ChemicalStructureRecognizer::hw::CapHeightError;
			g_doubleBondDist = consts::Separator::hw::DoubleBondDist;
			g_segmentVerEps = consts::Separator::hw::SegmentVerEps;
		}
	}

	bool imago::vars::getHandwritten()
	{
		return g_isHandwritten;
	}

	void imago::vars::setDebugSession(bool value)
	{
		g_debugSession = value;
	}

	bool imago::vars::getDebugSession()
	{
		return g_debugSession;
	}

	double imago::vars::getLineThickness()
	{
		return g_lineThickness;
	}

	void imago::vars::setLineThickness(double value)
	{
		g_lineThickness = value;
	}

	double imago::vars::getCapitalHeight()
	{
		return g_capitalHeight;
	}

	void imago::vars::setCapitalHeight(double value)
	{
		g_capitalHeight = value;
	}
		
	double imago::vars::getAvgBondLength()
	{
		return g_avgBondLength;
	}

	void imago::vars::setAvgBondLength(double value)
	{
		g_avgBondLength = value;
	}

	int imago::vars::getImageWidth()
	{
		return g_imageWidth;
	}

	void imago::vars::setImageWidth(int value)
	{
		g_imageWidth = value;
	}

	int imago::vars::getImageHeight()
	{
		return g_imageHeight;
	}

	void imago::vars::setImageHeight(int value)
	{
		g_imageHeight = value;
	}

	double imago::vars::getCharactersSpace()
	{
		double c = consts::ChemicalStructureRecognizer::sc::CharactersSpaceCoef;
		if (g_isHandwritten)
			c = consts::ChemicalStructureRecognizer::hw::CharactersSpaceCoef;

		return g_capitalHeight * c;
	}

	double imago::vars::getCapitalHeightError()
	{
		return g_capitalHeightError;
	}

	double imago::vars::getParLinesEps()
	{
		return g_parLinesEps;
	}

	double imago::vars::getMaxSymRatio()
	{
		return g_maxSymRatio;
	}

	double imago::vars::getMinSymRatio()
	{
		return g_minSymRatio;
	}

	int imago::vars::getDoubleBondDist()
	{
		return g_doubleBondDist;
	}

	int imago::vars::getSegmentVerEps()
	{		
		return g_segmentVerEps;
	}
}