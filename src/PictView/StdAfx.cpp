// stdafx.cpp : source file that includes just the standard includes
//	PictView.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#undef		WINVER
#define		WINVER 0X500
#include	"stdafx.h"

//在实现动画窗口的程序时，发现如果直接在VC中使用AnimateWindow函数，
//在编译时会报告出错。以上述程序为例，在编译时系统会报告：  
//''AnimateWindow'' : undeclared identifier 
//''AW_HIDE'' : undeclared identifier 
//''AW_CENTER'' : undeclared identifier 
//   通过错误提示可以看出是编译系统认为AnimateWindow函数和AW_HIDE、AW_CENTER两个参数没有定义。
//因该函数是定义在Winuser.h头文件中的，于时，笔者显示地在程序中定义了对该头文件的包含，编译时
//却仍然出现相同的错误。为什么在VC中编译不能通过呢？通过查阅MSDN笔者发现在MSDN中明确提到
//WindowsNT5.0和Windows98以上版本均支持该函数。通过笔者的研究发现，问题出在定义AnimateWindow
//函数的头文件Winuser.h中，在VC安装目录下进入include子目录，用EDIT打开Winuser.h文件，按F3键查
//找AnimateWindow，可以发现有两处定义，一处是定义该函数中使用到的参数；另一处是该函数原型的定义。
//在这两处定义中均出现了对Windows版本的条件判断，#if (WINVER >= 0X500)……，原来问题出在这里，
//我们目前所使用的各种Windows主版本号均为5点零以下，所以在VC中编译上述程序时，编译系统自然将
//AnimateWindow函数排除在外。因此为了在我们的程序中使用该函数，就得对其头文件进行一些小小的修改，
//即将#if (WINVER >= 0X500)改为#if (WINVER >= 0X400)，请注意两处出现该函数定义的部分都要进行修改。 
//假如你不想修改Winuser.h,可以在工程里的StdAfx.h文件靠前位置加上如下定义 
//#undef WINVER
//#define WINVER 0X500
 



