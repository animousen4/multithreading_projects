#include <string>
#include <filesystem>
#include <regex>
#include "../consts/regexpr.cpp"
#include "../file/filemanager.h"

class DataProcessor {

	FileManager fileManager;

	void process() {
		
	}

	std::vector<std::string> getInputFileIndexes() {
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