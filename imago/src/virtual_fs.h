#pragma once
#include <string>
#include <vector>

namespace imago
{
	struct VirtualFSRecord
	{
		std::string filename;
		std::vector<char> data;
	};

	class VirtualFS : public std::vector<VirtualFSRecord>
	{
	public:
		bool createNewFile(const std::string& filename, const std::string& data);
		bool appendData(const std::string& filename, const std::string& data);		
	};
};