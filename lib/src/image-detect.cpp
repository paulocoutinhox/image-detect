#include "image-detect.h"

#include <opencv2/opencv.hpp>
#include <sstream>

using namespace cv;

IMD::ImageDetect::ImageDetect()
{

}

string IMD::ImageDetect::getResultAsJSON(bool success, string message, vector<IMD::DetectedPoint> *detectedPoints)
{
    string detectedPointsListStr = "";

    if (detectedPoints != NULL)
    {
		int totalOfDetectedPoints = detectedPoints->size();

		if (totalOfDetectedPoints > 0)
		{
			detectedPointsListStr += ", \"data\": {\"list\": [";

			for (int x = 0; x < totalOfDetectedPoints; x++)
			{
				DetectedPoint detectedPoint = detectedPoints->at(x);
				ostringstream newDetectedPointListStr;
				newDetectedPointListStr << "{\"x1\": " << detectedPoint.x1 << ", \"y1\": " << detectedPoint.y1 << ", \"x2\": " << detectedPoint.x2 << ", \"y2\": " << detectedPoint.y2 << "}";

				if (x < (totalOfDetectedPoints - 1))
				{
					newDetectedPointListStr << ", ";
				}

				detectedPointsListStr += newDetectedPointListStr.str();
			}

			detectedPointsListStr += "]}";
		}
    }

	ostringstream result;
	result << "{\"success\": " << (success ? "true" : "false") << ", \"message\": \"" << message.c_str() << "\"" << detectedPointsListStr.c_str() << "}\n";
	return result.str();
}

string IMD::ImageDetect::process(string screenImagePath, string detectImagePath, string outputImagePath, double thresholdToDetect)
{
    int matchMethod = CV_TM_CCOEFF_NORMED;
	
    // screen image and detect image
    Mat screenImage = imread(screenImagePath, 1);
    Mat detectImage = imread(detectImagePath, 1);

    // create the result matrix
    int resultCols = screenImage.cols - detectImage.cols + 1;
    int resultRows = screenImage.rows - detectImage.rows + 1;

    Mat outputImage(resultCols, resultRows, CV_32FC1);

    // do the "matching"
    matchTemplate(screenImage, detectImage, outputImage, matchMethod);
    threshold(outputImage, outputImage, thresholdToDetect, 1.0, CV_THRESH_TOZERO);
    
    Point maxLoc;
    Point minLoc;
    Point matchLoc;

    double maxVal;
    double minVal;
    double matchVal;

    bool resultSuccess = false;
    string resultMessage = "";

    vector<DetectedPoint> detectedPoints;

    bool detectedNewPoint = true;
    
    while (detectedNewPoint)
    {
        // find new point
        minMaxLoc(outputImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        
        int pointX1 = maxLoc.x;
        int pointY1 = maxLoc.y;
        
        int pointX2 = maxLoc.x + detectImage.cols;
        int pointY2 = maxLoc.y + detectImage.rows;

        // get correct value by match method for threshold compare
        if (matchMethod == CV_TM_SQDIFF || matchMethod == CV_TM_SQDIFF_NORMED)
        {
            matchLoc = minLoc;
            matchVal = minVal;
        }
        else
        {
            matchLoc = maxLoc;
            matchVal = maxVal;
        }

        if (matchVal >= thresholdToDetect)
        {
            // paint the image
            rectangle(screenImage, Point(pointX1, pointY1), Point(pointX2, pointY2), Scalar(0, 255, 0), 2);
            
            // store data to dont search the same points
            floodFill(outputImage, maxLoc, cv::Scalar(0), 0, cv::Scalar(0.1), cv::Scalar(1.0));

            // create detected point list
            DetectedPoint newDetectedPoint = DetectedPoint();
            newDetectedPoint.x1 = pointX1;
            newDetectedPoint.y1 = pointY1;
            newDetectedPoint.x2 = pointX2;
            newDetectedPoint.y2 = pointY2;
            detectedPoints.push_back(newDetectedPoint);
        }
        else
        {
            detectedNewPoint = false;
        }
    }
    
    // prepare result message
    if (detectedPoints.size() > 0)
    {
        resultSuccess = true;
        resultMessage = "found";
    }
    else
    {
        resultSuccess = false;
        resultMessage = "not-found";
    }

    // write image to disk if need
    if (!outputImagePath.empty())
    {
		imwrite(outputImagePath, screenImage);
    }

    return getResultAsJSON(resultSuccess, resultMessage, &detectedPoints);
}
