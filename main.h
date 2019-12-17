#pragma once
#include<iostream>
#include <Shlwapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include<ctime>
#include"resource.h"
#include<Windows.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "winmm.lib")

#define Sound(filename) (PlaySound(MAKEINTRESOURCE(filename),GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC))
#define IsExist(x) (PathFileExists(TEXT(x)))


#define ClickTrai 0x5A
#define ClickPhai 0x58

#define ConsoleWidth 80
#define ConsoleHeight 40
struct Cautrucbang // cấu trúc bảng
{
	short SDong = 0;
	short SCot = 0;	
	short SSobom = 0;
	short SSoODaMo = 0;
	short SSoCo = 0;
};

struct Cautruco // cấu trúc ô
{
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	short SBomlancan = 0;
};

struct CauTrucBangDiem
{
	CHAR Ten[30];
	UINT Thoi_Gian;
};

// Trang , vi tri dang chon , tong muc
extern short STrang, SViTriDangChon, STongMuc;