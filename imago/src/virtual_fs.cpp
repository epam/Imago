#include "virtual_fs.h"

namespace imago
{
	bool VirtualFS::createNewFile(const std::string& filename, const std::string& data)
	{
		VirtualFSRecord rec;
		rec.filename = filename;
		rec.data.insert(rec.data.end(), data.begin(), data.end());
		push_back(rec);
		return true;
	}

	bool VirtualFS::appendData(const std::string& filename, const std::string& data)
	{
		for (size_t u = 0; u < size(); u++)
		{
			if (filename == at(u).filename)
			{
				at(u).data.insert(at(u).data.end(), data.begin(), data.end());
				return true;
			}
		}

		return createNewFile(filename, data);
	}
}