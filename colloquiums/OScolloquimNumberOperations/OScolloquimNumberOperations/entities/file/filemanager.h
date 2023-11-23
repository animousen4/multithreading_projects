#pragma once
#include <string>
#include "../file_data/file_data.h"
#include <fstream>
#include "../path_maker/path_maker.h"
#include <filesystem>
#include <regex>
#include <iostream>
class FileManager {
public:
	
	FileManager(std::string dir, std::regex validFileRegex) {
		this->dir = dir;
		this->validFileRegex = validFileRegex;
	}

	std::vector<FileData*> getFileDataSequence() {
		auto dirs = getInputFileDirs();
		return getFileDataSequence(dirs);
	}

	void writeOutput(std::string fileName, double result) {
		std::ofstream file(fileName);
		file << result;
		file.close();
	}

	void outFoundFiles() {
		auto files = getInputFileDirs();
		if (files.empty())
			std::cout << "Not found";
		else
			for (auto el : files)
				std::cout << "\t" << el << "\n";
	}
	

private:
	std::string dir;
	std::regex validFileRegex;
	FileData* readFile(std::string path) {
		FileData* fileData = new FileData;

		std::ifstream file(
			path
		);

		file >> fileData->operation;

		double num;
		while (file >> num)
			fileData->sequence.push_back(num);
		
		file.close();

		return fileData;
		
	}
	std::vector<FileData*> getFileDataSequence(std::vector<std::string> filesPaths) {

		std::vector<FileData*> files;

		for (auto path : filesPaths)
			files.push_back(readFile(path));

		return files;
	}

	std::vector<std::string> getInputFileDirs() {
		std::vector<std::string> files;

		std::string path;
		for (const auto& entry : std::filesystem::directory_iterator(dir)) {
			path = entry.path().string();
			if (std::regex_match(path, validFileRegex))
				files.push_back(path);

		}

		return files;

	}



	
};