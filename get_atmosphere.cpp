#include "get_atmosphere.h"

void get_atmosphere(const cv::Mat &image, const cv::Mat &dark_channel, cv::Vec3f &atmosphere)
{
	unsigned int m{ 0 }, n{ 0 };
	m = image.rows;
	n = image.cols;
	unsigned int n_pixels = n * m;
	unsigned int n_search_pixels = n_pixels * 0.01;
	cv::Mat dark_vec = dark_channel.reshape(0, 1);//将暗通道变为行向量形式
	cv::Mat image_vec = image.reshape(3, 1);//将原图转换为行向量

	//对暗通道图进行排序得到暗通道图索引
	cv::Mat indices(1, n_pixels, CV_8UC1);//存储将暗通道排序后得到的索引矩阵
	cv::sortIdx(dark_vec, indices, CV_SORT_DESCENDING);//对暗通道进行排序
	atmosphere=cv::Vec3f( 0,0,0 );//用于存储大气光值
	cv::Vec3f temp;
	unsigned int temp1;
	for (unsigned int i = 0; i < n_search_pixels; i++)//此处采用迭代，可能会降低运行效率
	{
		temp1 = indices.at<int>(i);
		temp = image_vec.at<cv::Vec3f>(temp1);
		atmosphere = atmosphere + temp;
	}
	atmosphere[0] /= n_search_pixels;//B通道大气光
	atmosphere[1] /= n_search_pixels;//G通道大气光
	atmosphere[2] /= n_search_pixels;//R通道大气光
}



