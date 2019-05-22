#include"fast_dehaze.h"

void fast_dehaze(const cv::Mat &image, cv::Mat & radiance, const int &win_size, const double &omega)
{


	/*************************************获取暗通道***********************************/
	cv::Mat dark_channel;
	get_darkchannel(image, dark_channel, win_size);
	/*********************************************************************************/
	cv::Mat image_double;//获得double类型的图像，防止后续计算溢出
	image.convertTo(image_double, CV_32F, 1.0 / 255, 0);//转换为浮点图，方便后续计算而不溢出
	dark_channel.convertTo(dark_channel, CV_32F, 1.0 / 255, 0);
	/**************************由暗通道和原图计算大气光*********************************/
	cv::Vec3f atmosphere{ 0,0,0 };//用于存储大气光值的向量
	get_atmosphere(image_double, dark_channel, atmosphere);//通过函数获取大气光
	/*********************************************************************************/

	/*********************************计算光照传递评估图*******************************/
	cv::Mat trans_est;
	get_esttransmap(image_double, atmosphere, omega, win_size, trans_est);
	/*********************************************************************************/

	/***************************采用导向滤波改良传递评估图******************************/
	cv::Mat trans_map;//光照传输图矩阵
	cv::Mat image_gray;//原图对应的灰度图
	cv::cvtColor(image_double, image_gray, CV_BGR2GRAY);
	//采用导向滤波计算传递矩阵
	trans_map = fastGuidedFilter(image_gray, trans_est, 15, 0.001, 1);;
	/*********************************************************************************/
	
	/****************************对trans图进行改进*************************************/
	cv::Mat trans_2, trans_3;
	cv::pow(trans_map, 3, trans_3);
	cv::pow(trans_map, 2, trans_2);
	trans_map = ((-0.52)*trans_3) + (1.28*trans_2) + 0.24;
	/*********************************************************************************/

	/********************************获得无雾图像**************************************/
	get_radiance(image_double, trans_map, atmosphere, radiance);

	/********************************进行伽马校正**************************************/
	cv::pow(radiance, 0.75, radiance);
}