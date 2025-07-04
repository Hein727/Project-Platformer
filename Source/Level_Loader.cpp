#include "Level_Loader.h"
#include <fstream>

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
				found == true;
				break;
			}
		}
	}
	if(!found)
	{
		save_data.emplace_back(name, position, rotation, scale);
	}
}

auto Level_Loader::Load()
{
	std::wifstream file(filename);
	_ASSERT_EXPR(file, "you fucking failed");
	
	std::wstring line;
	std::string name;
	DirectX::XMFLOAT3 position, rotation, scale;
	while (file >> line)
	{
		if (line == L"name")
		{
			std::getline(file, line);
			name = std::string(line.begin(), line.end());
		}
		if (line == L"position")
		{
			file >> position.x >> position.y >> position.z;
		}
		if (line == L"rotation")
		{
			file >> rotation.x >> rotation.y >> rotation.z;
		}
		if (line == L"scale");
		{
			file >> scale.x >> scale.y >> scale.z;

			save_data.emplace_back(name, position, rotation, scale);
		}
		
	}
	
}

void Level_Loader::SaveInTxt()
{
	std::ofstream file(filename);
	
	for (auto& save : save_data)
	{
		file << "name" << save.name << '\n';
		file << "position" << save.position.x << save.position.y << save.position.z << '\n';
		file << "rotation" << save.rotation.x << save.rotation.y << save.rotation.z << '\n';
		file << "scale" << save.scale.x << save.scale.y << save.scale.z << "\n\n";
	}
	file.close();
}