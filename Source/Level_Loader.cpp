#include "Level_Loader.h"
#include <fstream>
#include <sstream>

Level_Loader::Level_Loader()
{
	
}

void Level_Loader::Save(const std::string name, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale)
{
	bool found = false;
	if (!save_data.empty())
	{
		for (auto& save : save_data)
		{
			if (save.name == name)
			{
				if (save.position.x != position.x || save.position.y != position.y || save.position.z != position.z)
				{
					save.position = position;
				}
				if (save.rotation.x != rotation.x || save.rotation.y != rotation.y || save.rotation.z != rotation.z)
				{
					save.rotation = rotation;
				}
				if (save.scale.x != scale.x || save.scale.y != scale.y || save.scale.z != scale.z)
				{
					save.scale = scale;
				}
				found = true;
				break;
			}
		}
	}
	if(!found)
	{
		save_data.emplace_back(name , position, rotation, scale);
	}
}

void Level_Loader::Load()
{
	save_data.clear();

	std::wifstream file(filename);
	std::wstring line;
	std::string name;
	DirectX::XMFLOAT3 position = {}, rotation = {}, scale = {};
	bool readingEntry = false;

	while (std::getline(file, line))
	{
		// Trim line if needed or just skip empty lines
		if (line.empty())
			continue;

		// Convert wstring to lowercase for case-insensitive compare if needed
		// Here assuming exact match is fine

		if (line.find(L"name") == 0)
		{
			// extract name from the rest of the line after "name"
			std::wstring wname = line.substr(4); // after "name"
			// trim whitespace
			wname.erase(0, wname.find_first_not_of(L" \t"));
			name = std::string(wname.begin(), wname.end());
			readingEntry = true;
		}
		else if (line.find(L"position") == 0)
		{
			float x, y, z;
			// read from the line after "position"
			std::wstringstream ss(line.substr(8));
			ss >> x >> y >> z;
			position = { x, y, z };
		}
		else if (line.find(L"rotation") == 0)
		{
			float x, y, z;
			std::wstringstream ss(line.substr(8));
			ss >> x >> y >> z;
			rotation = { x, y, z };
		}
		else if (line.find(L"scale") == 0)
		{
			float x, y, z;
			std::wstringstream ss(line.substr(5));
			ss >> x >> y >> z;
			scale = { x, y, z };

			if (readingEntry)
			{
				save_data.emplace_back(name, position, rotation, scale);
				readingEntry = false;
			}
		}
	}
	file.close();

	// Clear the file contents after loading
	std::wofstream clear_file(filename, std::ios::trunc);
	clear_file.close();
}

void Level_Loader::SaveInTxt(const char* filename)
{
	if (filename = "")
	{
		std::ofstream file(this->filename);
		for (auto& save : save_data)
		{
			file << "name " << save.name << '\n';
			file << "position " << save.position.x << ' ' << save.position.y << ' ' << save.position.z << '\n';
			file << "rotation " << save.rotation.x << ' ' << save.rotation.y << ' ' << save.rotation.z << '\n';
			file << "scale " << save.scale.x << ' ' << save.scale.y << ' ' << save.scale.z << "\n\n";
		}
		file.close();
	}
	else
	{
		std::ofstream file(filename);
		for (auto& save : save_data)
		{
			file << "name " << save.name << '\n';
			file << "position " << save.position.x << ' ' << save.position.y << ' ' << save.position.z << '\n';
			file << "rotation " << save.rotation.x << ' ' << save.rotation.y << ' ' << save.rotation.z << '\n';
			file << "scale " << save.scale.x << ' ' << save.scale.y << ' ' << save.scale.z << "\n\n";
		}
		file.close();
	}	
}