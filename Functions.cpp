#include"main.h"
#include"Functions.h"
#include"Console.h"
#include<stdio.h>
Cautrucbang	CTBang;
Cautruco **CTO;

// Vị trí con trỏ hiện tại 
COORD CViTriConTro;

// Sử dụng phím
bool BSuDungPhim = false;

// Toa Do XY
short SToaDoX;
short SToaDoY;

// Cap nhat trang thai coi game
bool BTrangThaiChoiGame = false;


void TaoMang2ChieuDong()
{
	CTO = new Cautruco *[CTBang.SDong];
	for (int  i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new Cautruco[CTBang.SCot];
	} 
}

void XoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}	
	delete[] CTO;	
}

void LuuToaDoBang()
{
	SToaDoX = ((ConsoleWidth / 2) - CTBang.SDong );
	SToaDoY = ((ConsoleHeight - 6 - CTBang.SCot) / 2) + 7;
}

void Khoitao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSobom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	TaoMang2ChieuDong();
	TaoBomNgauNhien();
	LuuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	VeBang();
	veTrangThaiChoiGame(1, 0, 0);
	
	
	//XuatBom(); 
		
}

short ToaDoX(short SX) // Tọa độ x vẽ bảng
{
	return ((SX * 2) + SToaDoX);
}

short ToaDoY(short SY) // Tọa độ y vẽ bảng
{
	return (SY + SToaDoY);
}

void VeO(short SX, short SY, short Skieu)
{
	switch (Skieu)
	{
	case 0: // 0: Màu Xanh lá
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 10, "  ");
		break;
	case 1: // Số 1 xanh dương (So 1-> 8 là nền trắng)
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 9, 15, "1 ");
		break;
	case 2: // Số 2 xanh lá
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 2, 15, "2 ");
		break;
	case 3: // Số 3 đỏ
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 15, "3 ");
		break;
	case 4: // Số 4 xanh dương đậm
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 1, 15, "4 ");
		break;
	case 5:  // Số 5 đỏ đậm
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 4, 15, "5 ");
		break;
	case 6:  // Số 6 CYAN đậm
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 3, 15, "6 ");
		break;
	case 7: // Số 7 Đen
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 15, "7 ");
		break; 
	case 8: // Số 8 hồng
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 13, 15, "8 ");
		break;
	case 9: // Bom  Nen do chu den
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 12, "B ");
		break;
	case 10: // Ô chẵn
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 8, "  ");
		break;
	case 11: // Ô lẻ
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 7, "  ");
		break;
	case 12: // Số 12 theo dõi con trỏ 
		setColorBGTextXY(ToaDoX(SX) + 1, ToaDoY(SY), 0, 13, " ");
		break;
	case 13: // Cắm cờ  nen vang nhat chu do
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 14, "P ");
		break;
	case 14: //  Cắm cờ sai  nen cam chu trang
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 15, 16, "Px");
		break;
	case 15: // Cắm cờ đúng nen vang nhat chu do
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 14, "B ");
		break;
	}
}

void VeBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
				VeO(j, i, 13);
			else if (CTO[i][j].SBomlancan)
				VeO(j, i, CTO[i][j].SBomlancan);
			else if (CTO[i][j].BDaMo)  // Ô rỗng
				VeO(j, i, 0);
			else if ((i + j) % 2) // ô lẻ
				VeO(j, i, 11);
			else // Ô chẵn
				VeO(j, i, 10); 
			
			if (BSuDungPhim)
			{
				VeO(CViTriConTro.X, CViTriConTro.Y, 12);
			}
		}
	}
}

void TaoBomNgauNhien()
{
	short SSoBom = CTBang.SSobom;
	short SI, SJ;// SI vị trí dòng SJ vị trí cột
	//srand(time(NULL));  // reset time
	while (SSoBom)
	{
		// *CT : muốn random trong khoản x,y thì ta sẽ ran() % ( y - x + 1) + x	
		// VD: Random trong khoản từ 0-> 8 => CT: rand() % (8 - 0 + 1) + 0 =rand() % 9 =rand() % CTBang.SDong 
//		srand(time(NULL));  // reset time
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;

		CTO[SI][SJ].BCoBom = true;
		--SSoBom; // Cập nhật lại số lượng bom

	}
}

void XuatBom()
{
	for (int i = 0; i < CTBang.SDong; i++)
	{
		for (int j = 0; j < CTBang.SCot; j++)
		{
			std::cout << CTO[i][j].BCoBom << " ";

		}
		std::cout << std::endl;
	}
}

void clickPhai(short SX,short SY) // Cam co 
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
		Sound(IDR_WAVE2);
	}
	VeBang();
	deleteRow(4, 1);
	veTrangThaiChoiGame(1, 0, 0);

}




short DemBomLanCan(short SX, short SY)
{
	short sDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY -1 ; j <= SY + 1; ++j)
		{
			// Xét những vị trí không hợp => tiếp tục lặp
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;

			// Xét xem ô có bom hay khong ; Có tăng lên 1
			if (CTO[i][j].BCoBom)
				sDem++;
		}
	}
	return sDem;
}
void MoO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)  // Ô có bom
			Thua(); // Thua
 		else
		{
			CTBang.SSoODaMo++;
			short SSoBomLanCan = DemBomLanCan(SX, SY);
			if (SSoBomLanCan) // Co	bom lan can
				CTO[SX][SY].SBomlancan = SSoBomLanCan;
			else  // Ô rỗng
			{
				// Duyệt các ô lân cận và gọi đệ qui
				for (int i = SX - 1;  i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1 ; ++j)
					{
						// Xét những vị trí không hợp => tiếp tục lặp
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;
						
						// Gọi đệ quy
						MoO(i, j);
					}
				}
			}
		}
	}
}

bool ThongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSobom) == (CTBang.SDong * CTBang.SCot))
		return true;
	return false;
}

void clickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		MoO(SX, SY);
		
		if (BTrangThaiChoiGame == true)
		{
			VeBang();
			if (ThongKeCo())
				Thang();
			else
			{
				Sound(IDR_WAVE1);
			}
		}
	}
}

void Thang()
{
	BTrangThaiChoiGame = false;
	//XoaMang2ChieuDong(); //giai phong con tro
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2,2,0); // Cap nhat lai trang thai thang
	Sound(IDR_WAVE4);
}

void Thua()
{
	//Hien bom an va kiem tra cam co dung hay sai
	for (int i = 0; i < CTBang.SDong; i++)
	{
		for (int j = 0; j < CTBang.SCot; j++)
		{
			if (CTO[i][j].BCamCo)  // Co Cam co
			{
				if (CTO[i][j].BCoBom)
					VeO(j, i, 15); // Cam co dung
				else
					VeO(j, i, 14); // Cam co sai		
			}
			else  // Khong co cam co
			{
				if (CTO[i][j].BCoBom)  // KT co bom 
				{
					VeO(j, i, 9); // Hien bom An
				}
			}
		}
	}
	BTrangThaiChoiGame = false;
	//XoaMang2ChieuDong(); // Giai phong con tro
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0); // Cap nhat lai trang thai thua

	Sound(IDR_WAVE3);
}

/*
Y tuong xu li menu
1/ Trang menu chinh
2/ Trang menu cap do
3/ Trang choi game
4/ Trang thua
5/ Trang thang
6 Trang luu game
7/ Trang Thong tin
8/ Trang banfg diem
*/

void XuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown) // Có nhấn phím
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: // Mũi tên lên 
			//std::cout << "Mui ten len" << std::endl;
			switch (STrang)
			{
			case 1: //Menu chinh
				if (STongMuc == 4)
				{ 
					if (SViTriDangChon == 0)
						SViTriDangChon = STongMuc - 1;
					else
						SViTriDangChon -= 1;
					veMenuChinh(SViTriDangChon);
				}
				break;
			case 2: // Menu chon cap do
				if (STongMuc == 4)
				{
					if (SViTriDangChon == 0)
						SViTriDangChon = STongMuc - 1;
					else
						SViTriDangChon -= 1;
					veMenuCapDo(SViTriDangChon);
				}
				break;
			case 3:	// Trang choi game
				if (BTrangThaiChoiGame == true)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					VeBang();
				}
				break;
			case 4:	// Trang thua
				veTrangThaiChoiGame(3, 3, (SViTriDangChon == 0) ? 1 : 0);
				break;
			case 5:	// Trang thang
				veTrangThaiChoiGame(2, 2, (SViTriDangChon == 0) ? 1 : 0);
				break;
			}
		
			break;
		case VK_DOWN: // Mũi tên xuống
			//std::cout << "Mui ten xuong" << std::endl;
			switch (STrang)
			{
			case 1: //Menu chinh
				if (STongMuc == 4)
				{
					if (SViTriDangChon == STongMuc - 1)
						SViTriDangChon = 0;
					else
						SViTriDangChon += 1;
					veMenuChinh(SViTriDangChon);

				}
				break;
			case 2: // Menu chon cap do
				if (STongMuc == 4)
				{
					if (SViTriDangChon == STongMuc - 1)
						SViTriDangChon = 0;
					else
						SViTriDangChon += 1;
					veMenuCapDo(SViTriDangChon);
				}
				break;
			case 3:	// Trang choi game
				if (BTrangThaiChoiGame == true)	
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					VeBang();
				}
				break;
			case 4:	// Trang thua
				veTrangThaiChoiGame(3, 3, (SViTriDangChon == 0) ? 1 : 0);
				break;
			case 5:	// Trang thang
				veTrangThaiChoiGame(2, 2, (SViTriDangChon == 0) ? 1 : 0);
				break;
			}
			
			
			break;
		case VK_LEFT:// Mũi tên trái
			//std::cout << "Mui ten trai" << std::endl;
			if (BTrangThaiChoiGame == true)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				VeBang();
			}
			break;
		case VK_RIGHT: // Mũi tên phải
			//std::cout << "Mui ten phai" << std::endl;
			if (BTrangThaiChoiGame == true)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				VeBang();
			}
			
			break;
		case VK_RETURN: // Phím Enter 
			//std::cout << "Phim Enter" << std::endl;
			switch (STrang)
			{
			case 1: //Menu chinh
				if (SViTriDangChon == 0)
				{
					STrang = 2;
					deleteRow(4, 10);
					veMenuCapDo(0);
				}
				else if (SViTriDangChon == 1)  // Trang bang diem
				{
					STrang = 8;
					deleteRow(4, 10);
					VeBangDiem();
				}
				else if (SViTriDangChon == 2)	//Trang thong tin
				{
					STrang = 7;
					deleteRow(4, 10);
					VeTrangThongTin();
				}
				else
				{
					exit(0);
				}
				break;
			case 2: // Menu chon cap do
				if (SViTriDangChon == 0) // Muc do de 9 * 9 va 10 bom
				{
					STrang = 3;		// Cap nhat lai trang dang choi
					deleteRow(4, 10);
					Khoitao(9, 9, 10);	
				}
				else if (SViTriDangChon == 1)  // Muc do trung binh 16 * 16 va 40 bom
				{
					STrang = 3;		// Cap nhat lai trang dang choi 
					deleteRow(4, 10);
					Khoitao(16, 16, 40);
				}
				else if (SViTriDangChon == 2)	//  Muc do kho 24 * 24 va 99 bom
				{
					STrang = 3;		// Cap nhat lai trang dang choi
					deleteRow(4, 10);
					Khoitao(24, 24, 99);
				}
				else
				{
					STrang = 1; // Cap nhat lai menu chinh
					deleteRow(4, 10	);
					veMenuChinh(0);
				}	
			
				break;
			
			case 4:	// Trang thua
				if (SViTriDangChon)
				{
					STrang = 1; // Tro ve menu chinh
					deleteRow(3, ConsoleHeight - 3);
					veMenuChinh(0);
				}
				else
				{
					STrang = 3; // Trang choi game
					deleteRow(3, ConsoleHeight - 3);
					Khoitao(CTBang.SDong, CTBang.SCot, CTBang.SSobom);

				}
				break;
			case 5:	// Trang thang
				if (SViTriDangChon)
				{
					STrang = 1; // Tro ve menu chinh
					deleteRow(3, ConsoleHeight - 3);
					veMenuChinh(0);
				}
				break;
			case 6:	// Trang luu game
				if (SViTriDangChon )
				{
					STrang = 1; // Tro ve menu chinh
					deleteRow(3, ConsoleHeight - 3);
					veMenuChinh(0);
				}
				else 
				{
					// Luu game ->Xu li file
				}
				break;
			case 7: // Trang Thong tin
					STrang = 1; // Cap nhat lai menu chinh
					deleteRow(3, ConsoleHeight -3);
					veMenuChinh(0);
				break;
			}
		
			break;
		case VK_ESCAPE: // Phím ESC(thoát)
			//std::cout << "Phim ESC" << std::endl;
			switch (STrang)
			{
			case 1: //Menu chinh
				exit(0);
				break;
			case 2: // Menu chon cap do
				STrang = 1;
				deleteRow(4, 10);
				veMenuChinh(0);
				break;
			case 3:
				STrang = 6;
				STrang = 1;
				deleteRow(3, ConsoleHeight - 3);
				veMenuChinh(0);
				//veTrangThaiChoiGame(1, 1, 0);
				break;
			case 4:	// Trang thua

				break;
			case 5:	// Trang thang
				STrang = 2;
				deleteRow(3, ConsoleHeight - 3);
				veMenuCapDo(0);
				break;
			case 7:
				STrang = 1;
				deleteRow(3, ConsoleHeight - 3);
				veMenuChinh(0);
			case 8:
				STrang = 1;
				deleteRow(3, ConsoleHeight - 3);
				veMenuChinh(0);

			}
			break;
		case ClickTrai: //Phím Z - Mở ô
			// std::cout << "Phim Z" << std::endl;
			if (STrang==3 && BTrangThaiChoiGame)
				clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai: // Phím X - Cắm Cờ
			//std::cout << "Phim X" << std::endl;
			if (STrang == 3 && BTrangThaiChoiGame)
				clickPhai(CViTriConTro.Y, CViTriConTro.X); 
			break;	

		
		}
	}
}	

void XuLySuKien()
{
	while (true)
	{
		DWORD DWNumberOfEvents = 0; // Lưu lại sự kiện hiện tại
		DWORD DWNumberOfEventsRead = 0; // Lưu lại số lượng sự kiện đã được lọc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // thiết bị đầu vào
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // Đặt sự kiện đầu vào của giao diện cho biến DWNumberOfEvents

		if (DWNumberOfEvents)
		{
			INPUT_RECORD *IREventBuffer = new INPUT_RECORD[DWNumberOfEvents]; // Con trỏ EventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); // Đặt các sự kiện lưu vào con trỏ EventsBuffer

			// Chạy vòng lặp để đọc sự kiện
			for (DWORD i = 0; i < DWNumberOfEvents; i++)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) // Nếu là sự kiện phím
				{
					XuLyPhim(IREventBuffer[i].Event.KeyEvent);

				}
				/*else if (IREventBuffer[i].EventType == MOUSE_EVENT)
				{

				}*/
			}
		}

	}
}

// design
void veTieuDeGame()
{
	for (short i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}
	
	setColorBGTextXY((ConsoleWidth / 2) - 5, 1, 5, 0, "MINISWEEPER\n");
	for (short i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}
}

void veTrangThaiChoiGame(short STrangThai,short SCheDo,short SIndex)
{
	SViTriDangChon = SIndex;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 15, 0, "Ban Do : %d * %d", CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 15, 0, "So Bom : %d", CTBang.SSobom -CTBang.SSoCo );

	// Ve menu thang thua

	LPSTR STRTextMenuCheDo ;
	if (SCheDo == 1)   
	{
		STRTextMenuCheDo = "  Luu Lai  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	//if (SCheDo == 2) // Thang
	//{
	//	STRTextMenuCheDo = "  Luu Ten  ";
	//	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);
	//}
	if (SCheDo == 3)	// Thua
	{
		STRTextMenuCheDo = "  Choi Lai  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2) + 1, 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	if (SCheDo >= 1)	// Thoat
	{
		STRTextMenuCheDo = "  Thoat  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 4, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuCheDo);
	}
	


	// Ve trang thai
	if (STrangThai == 1)	// 1 Dang Choi Game
	{
		setColorBGTextXY((ConsoleWidth - 22), 4, 15, 0, "Trang Thai : Dang Choi");
	}
	if (STrangThai == 2)	// 2 Thang	
	{
		setColorBGTextXY((ConsoleWidth - 22), 4, 15, 0, "Trang Thai : Thang\n");
	}
	if (STrangThai == 3)	// 3 Thua
	{
		setColorBGTextXY((ConsoleWidth - 22), 4, 15, 0, "Trang Thai : Thua\n");
	}
	//std::cout << std::endl;
	setColor(7);
	
	for (short i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}


}

void veMenuChinh(short SIndex)
{
	// Cap nhat lai vi tri dang chon cua menu
	SViTriDangChon = SIndex;
	STongMuc = 4;


	// Ve menu

	LPSTR STRTextMenuChinh = "  GAME MOI  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2) , 7, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuChinh);
	
	//STRTextMenuChinh = "  BANG DIEM  ";
	//setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);
	
	STRTextMenuChinh = "  THONG TIN  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);
	
	STRTextMenuChinh = "  THOAT  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((SIndex == 2) ? 2 : 0), STRTextMenuChinh);
	
}

void veMenuCapDo(short SIndex)
{
	// Cap nhat lai vi tri dang chon cua menu
	SViTriDangChon = SIndex;
	STongMuc = 4;


	// Ve menu

	LPSTR STRTextMenuChinh = "CHON CAP DO";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 4, 1 , 0 , STRTextMenuChinh);

	STRTextMenuChinh = "  DE (9 * 9 VA 10 BOM)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  TRUNG BINH (16 * 16 VA 40 BOM)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  KHO (24 * 24 VA 99 BOM)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((SIndex == 2) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  QUAY LAI  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, ((SIndex == 3) ? 2 : 0), STRTextMenuChinh);
}

void VeTrangThongTin()
{
	STongMuc = 1;
	setColorBGTextXY(1, 4, 11, 0, "TEN CHUONG TRINH: MINESWEEPER"); // DONG THU 4
	setColorBGTextXY(1, 5, 11, 0, "TAC GIA: 17110062-NGUYEN DINH THIEN PHUOC"); // DONG THU 5
	setColorBGTextXY(1, 6, 11, 0, "         17110082-MAI NGUYEN ANH THU"); // DONG THU 6	
	setColorBGTextXY(1, 7, 11, 0, "         17110078-LE CHI THONG"); // DONG THU 7

	setColorBGTextXY(1, 9, 13, 0, "HUONG DAN"); // DONG THU 8
	setColorBGTextXY(1, 11, 15, 0, "DOI VOI BAN PHIM."); // DONG THU 10
	setColorBGTextXY(1, 13, 15, 0, "- SU DUNG CAC PHIM MUI TEN DE DI CHUYEN GIUA CAC O."); // DONG THU 12
	setColorBGTextXY(1, 14, 15, 0, "- DUNG PHIM Z DE MO O."); // DONG THU 13
	setColorBGTextXY(1, 15, 15, 0, "- DUNG PHIM X DE CAM CO."); // DONG THU 14
	setColorBGTextXY(1, 16, 15, 0, "- NGOAI RA TRONG LUC DANG CHOI, BAN CO THE NHAN ESC DE MO VA DONG BANG MENU."); // DONG THU 15
	setColorBGTextXY((ConsoleWidth / 2) - 5, 19, 15, 1, "  TRO VE  "); // DONG THU 17
}

void VeBangDiem()
{
	STongMuc = 1;
	setColorBGTextXY((ConsoleWidth / 2) - 13, 4, 14, 0, "TOP 10 NGUOI CAO DIEM NHAT"); // DONG THU 4
	//if (IsExist("BangDiem.txt"))
	//{
	//	FILE *fpIn = fopen("BangDiem.txt", "rb"); // MO TAP TIN RA DOC O DANG NHI PHAN
	//	if (fpIn != NULL)
	//	{
	//		CauTrucBangDiem Bang_Diem;
	//		UCHAR i = 1;
	//		while ((fread(&Bang_Diem, sizeof(CauTrucBangDiem), 1, fpIn) == 1) && (i <= 10)) // LAP TUNG DONG VA LAY DU LIEU VAO CAU TRUC
	//		{
	//			setColorBGTextXY(12, 5 + i, 11, 0, "%d. %s", i, Bang_Diem.Ten);
	//			setColorBGTextXY(50, 5 + i, 13, 0, "THOI GIAN: %d GIAY", Bang_Diem.Thoi_Gian);
	//			i++;
	//		}
	//		fclose(fpIn); // DONG TAP TIN LAI
	//	}
	//	else
	//		setColorBGTextXY((ConsoleWidth / 2) - 15, 6, 12, 0, "KHONG THE DOC DU LIEU TU TAP TIN"); // DONG THU 6
	//}
	//else
	//	setColorBGTextXY((ConsoleWidth / 2) - 7, 6, 12, 0, "CHUA CO DU LIEU"); // DONG THU 6

	//setColorBGTextXY((ConsoleWidth / 2) - 5, 18, 15, 1, "  TRO VE  "); // DONG THU 18
}