#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <array>

using namespace std;

#define forloop for(size_t i = 0; i < 3; ++i)
typedef array<float, 3> Vec3;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Please specify the file to modify" << endl;
		return -1;
	}

	ifstream obj(argv[1]);

	if (!obj.is_open())
	{
		cout << "Can't open the file \"" << argv[1] << "\"\n";
		return -1;
	}
	
	string line;
	bool foundFirstVertex = false;

	Vec3 max = { numeric_limits<double>::min(), numeric_limits<double>::min(), numeric_limits<double>::min() };
	Vec3 min = { numeric_limits<double>::max(), numeric_limits<double>::max(), numeric_limits<double>::max() };

	while (std::getline(obj, line))
	{
		if (line[0] != 'v' || (line[1] != ' ' && foundFirstVertex))
		{
			continue;
		}
		else
		{
			if (!foundFirstVertex)
				foundFirstVertex = true;

			Vec3 vertices;
			int check = sscanf(line.c_str(), "%*c %g %g %g", &vertices[0], &vertices[1], &vertices[2]);
		

			forloop
			{
				if (max[i] < vertices[i])
					max[i] = vertices[i];

				if (min[i] > vertices[i])
					min[i] = vertices[i];
			}
		}
	}

	obj.clear();
	obj.seekg(0);

	string fileContent;
	Vec3 center;

	forloop
	{
		center[i] = min[i] + (max[i] - min[i]) / 2.0f;
	}

	while (std::getline(obj, line))
	{
		if (!(line[0] != 'v' || (line[1] != ' ' && foundFirstVertex)))
		{
			ostringstream newLine;

			if (!foundFirstVertex)
				foundFirstVertex = true;

			Vec3 vertices;
			int check = sscanf(line.c_str(), "v %g %g %g", &(vertices[0]), &(vertices[1]), &(vertices[2]));

			newLine << "v ";
			forloop
			{
				float vertex = vertices[i] - center[i];
				newLine << " " << vertex;
			}

			line = newLine.str();
		}
		fileContent += line + "\n";
	}
	obj.close();

	ofstream newObj(argv[1]);
	newObj.flush();

	newObj.write(fileContent.c_str(), fileContent.size());

	newObj.close();

	return 0;
}