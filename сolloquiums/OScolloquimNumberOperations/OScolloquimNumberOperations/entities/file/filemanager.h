#include <string>
#include "../file_data/file_data.h"
#include <fstream>
#include "../path_maker/path_maker.h"
class FileManager {
public:
	std::vector<std::string> filesPaths;

	std::vector<FileData> getFileDataSequence() {
		std::vector<FileData> files;

		for (auto path : filesPaths)
			files.push_back(readFile(path));

		return files;
	}

private:
	std::string path;
	

	FileData readFile(std::string path) {
		FileData fileData;

		std::ifstream file(
			path
		);

		file >> fileData.operation;

		double num;
		while (file >> num)
			fileData.sequence.push_back(num);
		
		file.close();

		return fileData;
		
	}

	
};