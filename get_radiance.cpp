#include"get_radiance.h"

void get_radiance(const cv::Mat&image, const cv::Mat&trans_map, const cv::Vec3f &atmosphere, cv::Mat &radiance)
{
	unsigned int m{ 0 }, n{ 0 };
	m = image.rows;
	n = image.cols;
	//得到大气光矩阵（将三个通道的大气光进行拷贝）
	cv::Mat rep_atmosphere(m, n, CV_32FC3, cv::Scalar(atmosphere[0], atmosphere[1], atmosphere[2]));
	
	cv::Mat max_transmap = cv::max(trans_map, 0.1);//设置大气光传递矩阵最小值为0.1（防止除零主导）
	
	//将大气光传递矩阵复制到三个通道(默认三个通道采用同一大气光)
	vector<cv::Mat>trans_map_final;
	cv::Mat trans_3channel;
	trans_map_final.push_back(trans_map); 
	trans_map_final.push_back(trans_map);
	trans_map_final.push_back(trans_map);
	cv::merge(trans_map_final, trans_3channel);

	//采用大气光照模型计算需要恢复的图像
	radiance = ((image - rep_atmosphere) / trans_3channel) + rep_atmosphere;
}