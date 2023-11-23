#include <string>
#include "../file/filemanager.h"
#include "../thread_manager/thread_manager.h"
class PayloadManipulator {
public:
	PayloadManipulator(FileManager* manager) {
		this->manager = manager;
	}
	double getResult() {
		std::vector<FileData> files = manager->getFileDataSequence();
		ThreadManager threadManager(files.size());
		
		std::vector<ActionProcessorArgs> args = mapToArgs(files);
		threadManager.createAllThreads(args);
		threadManager.awaitAll();

		return calculate(args);

	}

	std::vector<ActionProcessorArgs> mapToArgs(std::vector<FileData>& files) {
		std::vector<ActionProcessorArgs> args;
		for (auto fileData : files)
			args.push_back(ActionProcessorArgs{ &fileData });
		return args;
	}

	double calculate(std::vector<ActionProcessorArgs> argsCalculated) {
		double res;
		for (auto arg : argsCalculated)
			res += arg.result;
	}
private:
	FileManager* manager;

};