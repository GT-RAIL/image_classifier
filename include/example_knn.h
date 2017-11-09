#ifndef EXAMPLE_KNN_H_
#define EXMAPLE_KNN_H_

// C++
#include <fstream>

// ROS
#include <ros/ros.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

class ExampleKNN
{
public:
    ExampleKNN();

    void trainAndClassify();

    void readCSV(std::string filename, std::vector< std::vector<int> > &file_contents);

    void readImages(std::vector< std::vector<int> > &file_contents, cv::Mat &features, cv::Mat &labels);

private:
    cv::Ptr<cv::ml::KNearest> knn;
};

#endif  // EXAMPLE_KNN_H_