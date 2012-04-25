#include "recognition_tree.h"
#include "thin_filter2.h"
#include "log_ext.h"
#include "algebra.h"
#include "prefilter.h"
#include "adaptive_filter.h"

namespace imago
{
	RecognitionTree::RecognitionTree(const Image& image) : raw(image)
	{
	}
}