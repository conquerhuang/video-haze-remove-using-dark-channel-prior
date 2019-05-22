#pragma once
#include<opencv2/opencv.hpp>
cv::Mat fastGuidedFilter(const cv::Mat &I_org, const cv::Mat &p_org, int r, double eps, int s);

