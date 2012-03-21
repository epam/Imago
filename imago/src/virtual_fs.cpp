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

	void VirtualFS::getData(std::vector<char>& output) const
	{
		output.clear();
		for (size_t u = 0; u < size(); u++)
		{
			output.insert(output.end(), at(u).filename.begin(), at(u).filename.end());
			output.push_back('\n');
			for (size_t v = 0; v < at(u).data.size(); v++)
			{
				char c1 = 'a' + ((at(u).data.at(v) & 0xF0) / 16);
				char c2 = 'a' + (at(u).data.at(v) & 0x0F);
				output.push_back(c1);
				output.push_back(c2);
			}
			output.push_back('\n');
		}
	}
}