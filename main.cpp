#include"main.h"
#include"Console.h"
#include"Functions.h"

// Trang , vi tri dang chon , tong muc
short STrang, SViTriDangChon, STongMuc;

/*
Y tuong xu li menu
1/ Trang menu chinh
2/ Trang menu cap do
3/ Trang choi game
4/ Trang thua
5/ Trang thang
6 Trang luu game
7/ Trang Thong tin
8/ Trang bang diem
*/

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHeight);  //Thay doi kich thuoc man hinh Console
 	
	SetConsoleTitle(TEXT("MINISWEEPER"));  // Dat lai tieu de game
	//LoadIcon(NULL, MAKEINTRESOURCEA(IDI_MyIcon));  // Thay doi icon file .exe
	Cursor(false); // Ẩn con trỏ
	veTieuDeGame();
	
	
	veMenuChinh(0);
	STrang = 1;
	//veMenuCapDo(0);

	//Khoitao(9, 9, 10);
	//veTrangThaiChoiGame(1);
	XuLySuKien();


	system("pause");
	return 0;
}