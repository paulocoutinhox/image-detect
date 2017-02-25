#include <image-detect.h>

#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
	IMD::ImageDetect *imd = new IMD::ImageDetect();

    // check params
    if (argc < 3)
    {
		string message = imd->getResultAsJSON(false, "invalid-parameters", NULL);
		printf("%s", message.c_str());
		return EXIT_FAILURE;
    }

	// process
	string screenImagePath = argv[1];
    string detectImagePath = argv[2];
    string outputImagePath = (argc > 3 ? argv[3] : ""); // can be empty to dont store diff file on disk
	double thresholdToDetect = 0.9;

	string message = imd->process(screenImagePath, detectImagePath, outputImagePath, thresholdToDetect);
	printf("%s", message.c_str());
	
	return EXIT_SUCCESS;
}
