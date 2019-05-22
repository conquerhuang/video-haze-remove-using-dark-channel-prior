#include"fast_dehaze.h"

void fast_dehaze(const cv::Mat &image, cv::Mat & radiance, const int &win_size, const double &omega)
{


	/*************************************��ȡ��ͨ��***********************************/
	cv::Mat dark_channel;
	get_darkchannel(image, dark_channel, win_size);
	/*********************************************************************************/
	cv::Mat image_double;//���double���͵�ͼ�񣬷�ֹ�����������
	image.convertTo(image_double, CV_32F, 1.0 / 255, 0);//ת��Ϊ����ͼ�������������������
	dark_channel.convertTo(dark_channel, CV_32F, 1.0 / 255, 0);
	/**************************�ɰ�ͨ����ԭͼ���������*********************************/
	cv::Vec3f atmosphere{ 0,0,0 };//���ڴ洢������ֵ������
	get_atmosphere(image_double, dark_channel, atmosphere);//ͨ��������ȡ������
	/*********************************************************************************/

	/*********************************������մ�������ͼ*******************************/
	cv::Mat trans_est;
	get_esttransmap(image_double, atmosphere, omega, win_size, trans_est);
	/*********************************************************************************/

	/***************************���õ����˲�������������ͼ******************************/
	cv::Mat trans_map;//���մ���ͼ����
	cv::Mat image_gray;//ԭͼ��Ӧ�ĻҶ�ͼ
	cv::cvtColor(image_double, image_gray, CV_BGR2GRAY);
	//���õ����˲����㴫�ݾ���
	trans_map = fastGuidedFilter(image_gray, trans_est, 15, 0.001, 1);;
	/*********************************************************************************/
	
	/****************************��transͼ���иĽ�*************************************/
	cv::Mat trans_2, trans_3;
	cv::pow(trans_map, 3, trans_3);
	cv::pow(trans_map, 2, trans_2);
	trans_map = ((-0.52)*trans_3) + (1.28*trans_2) + 0.24;
	/*********************************************************************************/

	/********************************�������ͼ��**************************************/
	get_radiance(image_double, trans_map, atmosphere, radiance);

	/********************************����٤��У��**************************************/
	cv::pow(radiance, 0.75, radiance);
}