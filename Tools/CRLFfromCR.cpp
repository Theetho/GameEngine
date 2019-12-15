#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Specify the path of the file to modify\n" << std::endl;
		return -1;
	}

	std::ifstream file(argv[1]);
	
	if (!file.is_open())
	{
		std::cout << "Can't open the file \"" << argv[1] << "\"\n";
		return -1;
	}

	std::string file_content;
	std::string line;

	while (std::getline(file, line, (char)13))
	{
		file_content += line + "\n";
	}

	file.close();

	std::ofstream newFile(argv[1]);

	newFile.flush();

	newFile.write(file_content.c_str(), file_content.size());

	newFile.close();

	return 0;
}