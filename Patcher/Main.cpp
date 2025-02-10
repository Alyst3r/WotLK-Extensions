#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

using namespace std;

static fstream wow_exe;

template <typename T>
void write_pos(streampos pos, T value)
{
	wow_exe.clear();
	wow_exe.seekg(0);
	wow_exe.seekp(pos);
	wow_exe << value;
}

void write_pos(streampos pos, vector<uint8_t> const& values)
{
	wow_exe.clear();
	wow_exe.seekg(0);
	wow_exe.seekp(pos);
	for (uint8_t v : values)
		wow_exe << v;
}

void write_pos_n(streampos pos, uint8_t value, size_t n)
{
	wow_exe.clear();
	wow_exe.seekg(0);
	wow_exe.seekp(pos);
	for (size_t i = 0; i < n; i++)
		wow_exe << value;
}

int main(int argc, char** argv)
{
	string wow;
	bool laa = false;

	if (argc < 2)
	{
		cout << "World of Warcraft exe not found!\n";
		return 1;
	}

	wow = argv[1];

	wow_exe = fstream(wow, ios::in | ios::out | ios::binary);

	if (!wow_exe)
	{
		cout << "World of Warcraft exe not found!\n";
		return 1;
	}

	// applies Large Address Aware flag - so called 4GB patch
	write_pos<uint8_t>(0x126, 0x23);

	// rewrites a couple things in the header that were recalculated
	write_pos(0x168, { 0x05, 0xE4, 0x76 });
	write_pos(0x1A9, { 0x00, 0x00, 0x00, 0x00, 0x00 });
	write_pos(0x210, { 0x00, 0xE0 });
	write_pos(0x238, { 0x00, 0x70 });
	write_pos(0x260, { 0x00, 0xB0 });
	write_pos(0x2B0, { 0x00, 0x10 });

	// StartAddress
	write_pos(0x40B7D0, { 0xE9, 0xDB, 0xA4, 0x0D, 0x00, 0x90, 0x90, 0x90 });

	// ScanDllStart
	write_pos(0x4E5CB0, {
		0xB8, 0x01, 0x00, 0x00, 0x00, 0xA3, 0x74, 0xB4, 0xB6, 0x00, 0x68, 0x70, 0x42, 0x9E, 0x00, 0xE8,
		0x1C, 0x68, 0x38, 0x00, 0x83, 0xC4, 0x04, 0x55, 0x8B, 0xEC, 0xE8, 0xA1, 0x10, 0xF2, 0xFF, 0xE9,
		0x04, 0x5B, 0xF2, 0xFF
	});

	// Lua_ScanDLLStart
	write_pos(0x4DCCF0, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 });

	// WotLKExtensions.dll
	write_pos(0x5E2A70, {
		0x57, 0x6F, 0x74, 0x4C, 0x4B, 0x45, 0x78, 0x74, 0x65, 0x6E, 0x73, 0x69, 0x6F, 0x6E, 0x73, 0x2E,
		0x64, 0x6C, 0x6C 
	});

	cout << "World of Warcraft exe has been patched. Remember to copy WotLKExtensions.dll to your game folder!\n";

	return 0;
}
