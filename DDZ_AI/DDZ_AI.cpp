// DDZ_AI.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "OptimizedCard.h"
#include"Recorder.h"
#include <time.h>
#include <iostream>
#include "OpenCVEntry.h"
using namespace std;

int main()
{
	cout << "fdsafsdaf";
		OpenCVEntry *s=new OpenCVEntry(_TEXT(""));
		s->Show("C:\\Users\\liu\\Pictures\\Saved Pictures\\1.jpg", "C:\\Users\\liu\\Pictures\\Saved Pictures\\2.jpg");
		s->Wait(5000);
		//OptimizedCard *opt = new OptimizedCard();
	//auto multiBoom = new MultiBoomDealStrategy(opt, 5);
	//opt->Optimized(multiBoom, 3);
	//std::string s = opt->ToString2();//必须要创建变量才可以
	//const std::string name = "D:\\UnityProject\\DDZCardImage\\Card.exe " + s;
	//system(name.c_str());
	//system("pause");
	//delete multiBoom;
	//delete opt;
    return 0;
}

