#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>

class Level_Loader
{
public:
	
	static Level_Loader& Instance()
	{
		static Level_Loader instance;
		return instance;
	}
	Level_Loader();
	~Level_Loader() {};

	void Save(const std::string name, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale);
	auto Load();
	void SaveInTxt();

private :

	struct Save_Data
	{
		std::string name;	
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;

		Save_Data(const std::string n, DirectX::XMFLOAT3 p,
			DirectX::XMFLOAT3 r,
			DirectX::XMFLOAT3 s) : name(n), position(p), rotation(r), scale(s) {
		};
	};
	std::vector<Save_Data> save_data;

	std::string filename = "data/obj_save.txt";
};