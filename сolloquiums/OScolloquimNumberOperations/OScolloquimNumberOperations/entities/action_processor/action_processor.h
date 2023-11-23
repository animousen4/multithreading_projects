#include <Windows.h>
#include "../file/filemanager.h"
#include <functional>
#include "../opercode.cpp"
struct ActionProcessorArgs {
	FileData* fileData;
	double result = 0;
};
class ActionProcessor {
	static DWORD WINAPI process(LPVOID sId) {
		ActionProcessorArgs args = *static_cast<ActionProcessorArgs*>(sId);
		FileData fileData = *args.fileData;

		double res;
		auto func = getFunction(fileData.operation, res);

		
		for (auto v : fileData.sequence)
			func(res, v);
		
		args.result = res;

		return 0;
	}

	static std::function<void(double& total, double& cur)> getFunction(int code, double& initTotal) {
		switch (code)
		{
		case ADD:
			initTotal = 0;
			return [](double& total, double& cur) {
					total += cur;
				};
		case MULT:
			initTotal = 1;
			return [](double& total, double& cur) {
					total *= cur;
				};
		case SQUARE:
			initTotal = 0;
			return [](double& total, double& cur) {
					total += cur * cur;
				};
		default:
			throw std::exception("Bad code format");
		}
	}
};