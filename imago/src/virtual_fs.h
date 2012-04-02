#pragma once
#include <string>
#include <vector>

namespace imago
{
	struct VirtualFSRecord
	{
		std::string filename;
		std::vector<unsigned char> data;
	};

	class VirtualFS : public std::vector<VirtualFSRecord>
	{
	public:
		bool createNewFile(const std::string& filename, const std::string& data);
		bool appendData(const std::string& filename, const std::string& data);		
		
		// gets internal data to external storage
		void getData(std::vector<char>& output) const;

		// sets internal state by specified input
		void setData(std::vector<char>& input);
		
		// if non-empty, the trailing slash is required
		void storeOnDisk(const std::string& folder = "") const;
	};
};