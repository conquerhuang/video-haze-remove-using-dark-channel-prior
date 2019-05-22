#pragma once
#include<opencv2/opencv.hpp>
#include "get_dark_channel.h"
#include "get_atmosphere.h"
#include "get_est_transmap.h"
#include "guided_filter.h"
#include "get_radiance.h"

void fast_dehaze(const cv::Mat & , cv::Mat & , const int & , const double & );
