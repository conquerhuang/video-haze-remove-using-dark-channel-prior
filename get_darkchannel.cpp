#include "get_dark_channel.h"

void get_darkchannel(const cv::Mat &input,  cv::Mat &dark_channel, const int window_size)
{
	cv::Mat RGB_channel[3];//三通道，分别是B,G,R  OpenCV中顺序相反
	cv::split(input, RGB_channel);//将原图分离到三通道

	cv::Mat min_channel;//三个颜色通道中最小值
	min_channel = cv::min(cv::min(RGB_channel[2], RGB_channel[1]), RGB_channel[0]);

	cv::Matx<unsigned char, 15, 15> element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(window_size, window_size));
	//进行腐蚀操作
	cv::erode(min_channel, dark_channel, element);
}


