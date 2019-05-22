#pragma once
#include<opencv2/opencv.hpp>
#include "get_dark_channel.h"
using namespace std;

void get_esttransmap(const cv::Mat &, const cv::Vec3f &, const double &, const unsigned int, cv::Mat &);


