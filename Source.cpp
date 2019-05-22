#include"Source.h"


int main(void)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };//存储用户交互得到的文件信息
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = _T("mp4文件(*.mp4)\0*.mp4\0所有文件(*.*)\0*.*\0");//要选择的文件后缀   
	ofn.lpstrInitialDir = _T("E:\\graduation_project\\via C++\\test_video");//默认的文件路径   
	ofn.lpstrFile = szBuffer;//存放文件的缓冲区   
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT  
	BOOL bSel = GetOpenFileName(&ofn);

	g_cap.open(szBuffer);

	
	frams = static_cast<int>(g_cap.get(cv::CAP_PROP_FRAME_COUNT));     //视频帧数
	int tmpw = static_cast<int>(g_cap.get(cv::CAP_PROP_FRAME_WIDTH));  //视频帧宽度
	int tmph = static_cast<int>(g_cap.get(cv::CAP_PROP_FRAME_HEIGHT)); //视频帧长度
	cout << "video has " << frams << " frams" << " wideth tmpw " << tmpw << " height " << tmph << endl;//显示视频信息
	writer.open("dehazed_video.avi", -1, 30, cv::Size(tmpw, tmph*2));
	int nframs{0};//用于计算视频处理速度的变量。
	nframs = frams;

	int saved_frams;
	saved_frams = frams;

	distribution_frams();//为线程预分配处理帧

	//启用线程
	thread task1(thread1);
	thread task2(thread2);
	thread task3(thread3);
	thread task4(thread4);
	task1.detach();
	task2.detach();
	task3.detach();
	task4.detach();
	
	clock_t start, finish;
	start = clock();//从线程打开开始计时，统计程序运行速度。
	//按照视频顺序存储视频帧
	int index[2] = { 0,0 };
	cv::Mat frame;
	while (saved_frams > 0 )
	{
		if (ready_to_save(saved_frams, index))//检查是否当前需要存储的帧已经转化完成
		{
			frame=proposed_frams[index[0]][index[1]];  
			writer << frame;                  //将转化好的帧存入视频中去
			cv::imshow("output", frame);       //实时刷新已经转化好的帧
			task_index[2 * index[0]][index[1]] = 0;                         //将该帧对应空间标记为数据已取出
			cv::waitKey(1);                                                 //等待1ms，此处如果不等待1ms，转换后的视频图像不会自动刷新
			saved_frams--;                                                  //
		}
		distribution_frams();
	}

	finish = clock();
	//显示程序运行时间
	cout << "totally used time is " << static_cast<double>(finish - start)/CLOCKS_PER_SEC <<" S"<< endl;
	cout << "proposed speed " << nframs / (static_cast<double>(finish - start) / CLOCKS_PER_SEC) << " fps" << endl;
	writer.release();
	//显示输入图像
	//cv::namedWindow("input image", cv::WINDOW_NORMAL);
	////显示去雾图像
	//cv::namedWindow("dehazed image", cv::WINDOW_NORMAL);
	//cv::imshow("input image", input_image);
	//cv::imshow("dehazed image", radiance);
	system("pause");
	cv::destroyAllWindows();
	return 0;
}