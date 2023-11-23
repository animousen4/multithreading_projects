#pragma once
#include <string>
class PathmakerBuilder {
public:
	PathmakerBuilder& setDir(std::string dir) {
		this->dir = dir;
		return *this;
	}

	PathmakerBuilder& setFilePrefix(std::string filePrefix) {
		this->filePrefix = dir;
		return *this;
	}

	PathmakerBuilder& setFilePostfix(std::string filePostfix) {
		this->filePostfix = filePostfix;
		return *this;
	}

	std::string build() {
		return dir + filePrefix + filePostfix;
	}
private:
	std::string dir;
	std::string filePrefix;
	std::string filePostfix;
};

