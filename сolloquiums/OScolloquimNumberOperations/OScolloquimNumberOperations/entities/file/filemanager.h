#include <string>
#include "../file_data/file_data.h"
#include <fstream>
#include "../path_maker/path_maker.h"
class FileManager {
public:
	FileManager(std::string dir, std::string filePrefix, int amount) {
		this->dir = dir;
		this->filePrefix = filePrefix;
	}

	std::vector<FileData> getFileDataSequence() {

	}

private:
	std::string dir;
	std::string filePrefix;
	std::string filePostfix;
	
	std::string getPath(int& fileIndex) {
		PathmakerBuilder builder;
		std::string path = builder
			.setDir(dir)
			.setFilePrefix(filePrefix)
			.setFilePostfix(
				std::to_string(fileIndex)
			)
			.build();
	}
	FileData readFile(int fileIndex) {
		FileData fileData;

		std::ifstream file(
			getPath(fileIndex)
		);

		file >> fileData.operation;

		double num;
		while (file >> num)
			fileData.sequence.push_back(num);
		
		file.close();

		return fileData;
		
	}

	
};