#include "get_dark_channel.h"

void get_darkchannel(const cv::Mat &input,  cv::Mat &dark_channel, const int window_size)
{
	cv::Mat RGB_channel[3];//��ͨ�����ֱ���B,G,R  OpenCV��˳���෴
	cv::split(input, RGB_channel);//��ԭͼ���뵽��ͨ��

	cv::Mat min_channel;//������ɫͨ������Сֵ
	min_channel = cv::min(cv::min(RGB_channel[2], RGB_channel[1]), RGB_channel[0]);

	cv::Matx<unsigned char, 15, 15> element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(window_size, window_size));
	//���и�ʴ����
	cv::erode(min_channel, dark_channel, element);
}


