#include "OScolloquimNumberOperations.h"
#include "entities/payload_manipulator/payload_manipulator.h"
#include "entities/consts/regexpr.cpp"

int main()
{	
	const char* outDir = "out.dat";
	FileManager manager("input", validFileRegex);
	PayloadManipulator manipulator(&manager);

	double result = manipulator.getResult();

	std::cout << "Found files:\n";
	manager.outFoundFiles();
	std::cout << std::endl;

	std::cout << "Result of calculations: " << result << std::endl << std::endl;
	std::cout << "File saved in " << outDir;

	manager.writeOutput(outDir, result);

	std::cout << std::endl;
	system("pause");

	return 0;

}
