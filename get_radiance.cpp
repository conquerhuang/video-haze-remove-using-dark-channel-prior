#include"get_radiance.h"

void get_radiance(const cv::Mat&image, const cv::Mat&trans_map, const cv::Vec3f &atmosphere, cv::Mat &radiance)
{
	unsigned int m{ 0 }, n{ 0 };
	m = image.rows;
	n = image.cols;
	//�õ���������󣨽�����ͨ���Ĵ�������п�����
	cv::Mat rep_atmosphere(m, n, CV_32FC3, cv::Scalar(atmosphere[0], atmosphere[1], atmosphere[2]));
	
	cv::Mat max_transmap = cv::max(trans_map, 0.1);//���ô����⴫�ݾ�����СֵΪ0.1����ֹ����������
	
	//�������⴫�ݾ����Ƶ�����ͨ��(Ĭ������ͨ������ͬһ������)
	vector<cv::Mat>trans_map_final;
	cv::Mat trans_3channel;
	trans_map_final.push_back(trans_map); 
	trans_map_final.push_back(trans_map);
	trans_map_final.push_back(trans_map);
	cv::merge(trans_map_final, trans_3channel);

	//���ô�������ģ�ͼ�����Ҫ�ָ���ͼ��
	radiance = ((image - rep_atmosphere) / trans_3channel) + rep_atmosphere;
}