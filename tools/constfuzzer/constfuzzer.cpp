#define _CRT_NON_CONFORMING_SWPRINTFS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>


int round(double v)
{
	if (v >= 0.0) return (int)(v + 0.5);
	else return (int)(v - 0.5);
}

double rand_range(double base, double factor)
{
	double r1 = (double)rand()/(double)RAND_MAX;
	//printf("%f\n", r1);
	return (r1 - 0.5) * base * factor;
}

int wmain(int argc, wchar_t* argv[])
{
	srand((unsigned int)time(NULL));

	if (argc < 3)
	{
		wprintf(L"Usage: ConstFuzzer src_file out_file [range_factor] [-strict]\n");
		wprintf(L" -strict mode replaces only constant marked with FUZZ prefix\n");
	}
	else
	{
		int changed = 0;
		std::wstring source = argv[1];
		std::wstring output = argv[2];
		std::wstring range = L"0.5";
		bool strict_mode = false;		
		if (argc > 3)
			range = argv[3];
		if (argc > 4)
		{
			if (argv[4] == std::wstring(L"-strict"))
				strict_mode = true;
			wprintf(L"Strict mode selected\n");
		}
		double range_d = _wtof(range.c_str());
		wprintf(L"Fuzzing %s to %s with range=%f\n", source.c_str(), output.c_str(), range_d);
		bool copy_only_mode = range_d < 0.0001;
		FILE* s = _wfopen(source.c_str(), L"r");
		if (s == NULL)
		{
			wprintf(L"Failed to open input file\n");
			return 2;
		}
		FILE* o = _wfopen(output.c_str(), L"w");
		if (o == NULL)
		{
			wprintf(L"Failed to open output file\n");
			return 2;
		}
		while (!feof(s))
		{
			wchar_t buf[1024] = {0};
			fgetws(buf, 1024, s);
			
			// parse string
			std::vector<std::wstring> items;
			std::wstring prefix;
			{
				std::wstring temp;
				for (size_t i = 0; i < wcslen(buf); i++)
				{
					if (buf[i] != L' ' && buf[i] != L';' && buf[i] != L'\t')
					{
						temp += buf[i];
					}
					else
					{
						if (items.size() == 0 && temp.empty())
							prefix += buf[i];

						if (!temp.empty())
							items.push_back(temp);
						temp = L"";
					}
				}
			}
			// items should be like
			// const,int,data,=,value,something
			
			if (copy_only_mode)
			{
				// just pass
			}
			else if (strict_mode)
			{
				if (items.size() > 3 && items[0] == L"FUZZ")
				{
					std::wstring varname = items[1];
					std::wstring equality = items[2];
					std::wstring value = items[3];					
					std::wstring old = value;
					if (equality == L"=")
					{
						bool ok = false;
						if (value == L"true" || value == L"false")
						{
							value = (rand()%2 == 1) ? L"true" : L"false";
							ok = true;
						}
						else 
						{
							double val_double = _wtof(value.c_str());
							int val_int = _wtoi(value.c_str());
							wchar_t buff_double[32];
							wchar_t buff_int[32];
							swprintf(buff_double, L"%f", val_double);
							swprintf(buff_int, L"%i", val_int);							
							if (value == buff_int)
							{
								int new_val = round(val_int + rand_range(val_int, range_d));
								swprintf(buff_int, L"%i", new_val);
								value = buff_int;
								ok = true;
							}
							else if (val_double != 0.0 && fabs(val_double - _wtof(buff_double)) < 0.000001 )
							{
								double new_val = val_double + rand_range(val_double, range_d);
								swprintf(buff_double, L"%f", new_val);
								value = buff_double;
								ok = true;
							}
						}
						if (ok)
						{
							swprintf(buf, L"%sFUZZ %s = %s; // fuzzed, old value = %s\n", prefix.c_str(), varname.c_str(), value.c_str(), old.c_str());
							changed++;
						}
					}
				}
			}
			else if ((items.size() > 4) && items[0] == L"const")
			{
				bool _bool = false, _int = false, _double = false;
				// any other types are unsupported
				_bool = items[1] == L"bool";
				_int = items[1] == L"int";
				_double = items[1] == L"double" || items[1] == L"float";

				if (_bool || _int || _double)
				{
					if (items[3] == L"=") // assignment
					{
						std::wstring name = items[2];
						std::wstring value = items[4];
						std::wstring old = value;
						std::wstring type = L"";
						bool all_good = false;

						if (_bool)
						{
							type = L"bool";
							// source value not required
							value = (rand()%2 == 1) ? L"true" : L"false";
							all_good = true;
						}
						
						if (_int)
						{
							type = L"int";
							int old_val = _wtoi(value.c_str());
							if (old_val != 0)
							{
								int new_val = round(old_val + rand_range(old_val, range_d));
								wchar_t hz[64] = {0};
								swprintf(hz, L"%i", new_val);
								value = hz;
								all_good = true;
							}
						}

						if (_double)
						{
							type = L"double";
							double old_val = _wtof(value.c_str());
							if (old_val != 0.0)
							{
								double new_val = old_val + rand_range(old_val, range_d);
								wchar_t hz[64] = {0};
								swprintf(hz, L"%f", new_val);
								value = hz;
								all_good = true;
							}
						}

						if (all_good)
						{
							swprintf(buf, L"%sconst %s %s = %s; //fuzzed from %s\n", prefix.c_str(), type.c_str(), name.c_str(), value.c_str(), old.c_str());
							changed++;
						}
					}
				}
			}
			
			fputws(buf, o);
		}
		fclose(s);
		fclose(o);
		printf("Done, changed %i lines of code.\n", changed);
	}
			

	return 0;
}

