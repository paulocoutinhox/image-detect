#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

namespace IMD
{
	struct DetectedPoint
	{
		int x1;
		int y1;
		int x2;
		int y2;
	};

	class ImageDetect 
	{
		public:
			ImageDetect();
			string getResultAsJSON(bool success, string message, vector<IMD::DetectedPoint> *detectedPoints);
			string process(string screenImagePath, string detectImagePath, string outputImagePath, double thresholdToDetect);
	};
}