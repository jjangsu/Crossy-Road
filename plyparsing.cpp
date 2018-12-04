#include <iostream>
#include <vector>
using namespace std;

struct COLOR
{
	int r;
	int g;
	int b;
};


struct VECTOR2
{
	int x;
	int y;
};

struct VECTOR3
{
	int x;
	int y;
	int z;
};

struct PLYINFO
{
	COLOR color;
	VECTOR3 vec;
};

void loadPLY(string path, vector<PLYINFO>& info)
{
	
	char* exist = strstr((char*)path.c_str(), "ply");

	if (exist == NULL)
	{
		return;
	}

	else
	{
		FILE* file = fopen(path.c_str(), "r");

		if (file)//읽는데 성공을 했다면
		{
			char buffer[300];
			int numofvertex;
			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file);			// format
			}
			strcpy(buffer, buffer + strlen("element vertex"));
			sscanf(buffer, "%i", &numofvertex);

			cout << numofvertex << endl;
			system("pause");
			
			while (strncmp("end_header", buffer, strlen("end_header")) != 0)
			{
				//system("pause");
				fgets(buffer, 300, file);//계속 입력을 받겠죠?
			}


			PLYINFO temp;
			for (int i = 0; i < numofvertex; ++i)
			{
				fgets(buffer, 300, file);
				sscanf(buffer, "%d %d %d %d %d %d", &temp.color.r, &temp.color.g, &temp.color.b, &temp.vec.x, &temp.vec.y, &temp.vec.z);
				info.push_back(temp);
			}
			

		}
	}
}

int main()
{
	vector<PLYINFO> info;

	loadPLY("chicken.ply", info);
	
	for (auto iter : info)
	{
		cout << iter.color.r <<" " << iter.color.g << " " << iter.color.b << " " << iter.vec.x << " " << iter.vec.y << " " << iter.vec.z << endl;
	}
}