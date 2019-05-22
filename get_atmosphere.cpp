#include "get_atmosphere.h"

void get_atmosphere(const cv::Mat &image, const cv::Mat &dark_channel, cv::Vec3f &atmosphere)
{
	unsigned int m{ 0 }, n{ 0 };
	m = image.rows;
	n = image.cols;
	unsigned int n_pixels = n * m;
	unsigned int n_search_pixels = n_pixels * 0.01;
	cv::Mat dark_vec = dark_channel.reshape(0, 1);//����ͨ����Ϊ��������ʽ
	cv::Mat image_vec = image.reshape(3, 1);//��ԭͼת��Ϊ������

	//�԰�ͨ��ͼ��������õ���ͨ��ͼ����
	cv::Mat indices(1, n_pixels, CV_8UC1);//�洢����ͨ�������õ�����������
	cv::sortIdx(dark_vec, indices, CV_SORT_DESCENDING);//�԰�ͨ����������
	atmosphere=cv::Vec3f( 0,0,0 );//���ڴ洢������ֵ
	cv::Vec3f temp;
	unsigned int temp1;
	for (unsigned int i = 0; i < n_search_pixels; i++)//�˴����õ��������ܻή������Ч��
	{
		temp1 = indices.at<int>(i);
		temp = image_vec.at<cv::Vec3f>(temp1);
		atmosphere = atmosphere + temp;
	}
	atmosphere[0] /= n_search_pixels;//Bͨ��������
	atmosphere[1] /= n_search_pixels;//Gͨ��������
	atmosphere[2] /= n_search_pixels;//Rͨ��������
}



