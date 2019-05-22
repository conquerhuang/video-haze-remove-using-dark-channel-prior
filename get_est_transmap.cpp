#include "get_est_transmap.h"

void get_esttransmap(const cv::Mat &image, const cv::Vec3f &atmosphere, const double &omega, const unsigned int win_size, cv::Mat &trans_est)
{
	unsigned int m{ 0 }, n{ 0 };
	m = image.rows;
	n = image.cols;
	//获得扩展大气光矩阵
	cv::Mat atmosphere_Matx(m, n, CV_32FC3, cv::Scalar(atmosphere[0], atmosphere[1], atmosphere[2]));
	cv::Mat dark_sub;
	get_darkchannel(image / atmosphere_Matx, dark_sub,win_size);
	trans_est = 1 - (omega*dark_sub);
}