
class trapeze
{
private:
	struct color
	{
		int r, g, b;
	};
	struct point
	{
		float x; float y;
	};
	color rgb;
	point center, a[8], AB, BC, CD, AD, sa[8];
	HDC hdc;
	HWND hwnd;
	HBRUSH hBrush1, fonBrush, pointBrush;
	int right, bottom, asd;
	
	point Center()
	{
		center.x = (a[1].x + a[2].x + a[3].x + a[0].x) / 4;
		center.y = (a[1].y + a[2].y + a[3].y + a[0].y) / 4;
		return center;
	}
	bool si(point D)
	{
		return (D.x > 0 && D.x < right && D.y > 0 && D.y < bottom);
	}
	point coordinate_transformation(point v, point t, int z) // изменение координат вершины при вращениии 
	{
		float x, y;
		x = t.x + (v.x - t.x) * cos(5 * M_PI / 180) -z * (v.y - t.y) * sin(5 * M_PI / 180);
		y = t.y + z *(v.x - t.x) * sin(5 * M_PI / 180) + (v.y - t.y) * cos(5 * M_PI / 180);
		v.x = x;
		v.y = y;
		return v;
	}
	void setColor()
	{
		printf_s("Input color, please(r g b):");
		scanf_s("%d %d %d", &rgb.r, &rgb.g, &rgb.b);
		if (rgb.r > 0 && rgb.r < 255 && rgb.g > 0 && rgb.g < 255 && rgb.b > 0 && rgb.b < 255)
		{
			system("cls");
			pointBrush = CreateSolidBrush(RGB(rgb.r, rgb.g, rgb.b));
		}
		else
		{
			printf_s("\nERROR color, repeat please!");
			Sleep(3000);
			system("cls");
		}
	}
	void rotation(int z) // изменение координат при вращениии 
	{
		a[0] = coordinate_transformation(a[0], center, z);
		a[1] = coordinate_transformation(a[1], center, z);
		a[2] = coordinate_transformation(a[2], center, z);
		a[3] = coordinate_transformation(a[3], center, z);
		a[4] = coordinate_transformation(a[4], center, z);
		a[5] = coordinate_transformation(a[5], center, z);
		a[6] = coordinate_transformation(a[6], center, z);
		a[7] = coordinate_transformation(a[7], center, z);
	}
	void asdfg()
	{
		for (int r = 0; r < 8; r++)
			a[r] = sa[r];
	}
	void qwerty(int k)
	{

		a[0].x = a[0].x - k; a[0].y = a[0].y + k;
		a[1].x = a[1].x - k; a[1].y = a[1].y - k;
		a[2].x = a[2].x + k; a[2].y = a[2].y - k;
		a[3].x = a[3].x + k; a[3].y = a[3].y + k;
		a[4].x = a[4].x - k; a[4].y = a[4].y + k;
		a[5].x = a[5].x - k; a[5].y = a[5].y - k;
		a[6].x = a[6].x + k; a[6].y = a[6].y - k;
		a[7].x = a[7].x + k; a[7].y = a[7].y + k;
	}
public:
	void LoadFromFile(FILE *f)
	{
		fscanf_s(f, "(%f,%f) (%f,%f) (%f,%f) (%f,%f) (%f,%f) (%f,%f) (%f,%f) (%f,%f)\n", &a[0].x, &a[0].y, &a[1].x, &a[1].y, &a[2].x, &a[2].y, &a[3].x, &a[3].y, &a[4].x, &a[4].y, &a[5].x, &a[5].y, &a[6].x, &a[6].y, &a[7].x, &a[7].y);
	}

	void saveInFile(char str[])
	{
		FILE *f = fopen(str, "w");
		fprintf_s(f, "(%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) (%.0f,%.0f) | %d, %d, %d", a[0].x, a[0].y, a[1].x, a[1].y, a[2].x, a[2].y, a[3].x, a[3].y, a[4].x, a[4].y, a[5].x, a[5].y, a[6].x, a[6].y, a[7].x, a[7].y, rgb.r, rgb.g, rgb.b);
	}
	void Draw()
	{
		POINT ppt[4] = { { a[0].x, a[0].y }, { a[1].x, a[1].y }, { a[2].x, a[2].y }, { a[3].x, a[3].y } },
			ppt1[4] = { { a[4].x, a[4].y }, { a[5].x, a[5].y }, { a[6].x, a[6].y }, { a[7].x, a[7].y } };
		BOOL bxt, bxt1;

		hBrush1 = SelectBrush(hdc, pointBrush);
		bxt = Polygon(hdc, ppt, 4);
		hBrush1 = SelectBrush(hdc, fonBrush);
		bxt1 = Polygon(hdc, ppt1, 4);
	}
	void move(char k)
	{
		if (si(a[0]) && si(a[1]) && si(a[2]) && si(a[3]))
			switch (k)
		{
			case '4': for (int i = 0; i < 8; i++) a[i].x -= 3; asd = 1; Center(); break;
			case '6': for (int i = 0; i < 8; i++) a[i].x += 3; asd = 2; Center(); break;
			case '8': for (int i = 0; i < 8; i++) a[i].y -= 3; asd = 3; Center(); break;
			case '5': for (int i = 0; i < 8; i++) a[i].y += 3; asd = 4; Center(); break;
			case '1': setColor(); break;
			case '2': saveInFile("save.txt"); break;
			case '3': asdfg(); break;
			case '7':if (si(a[0]) && si(a[1]) && si(a[2]) && si(a[3])) rotation(1); asd = 5; break;
			case '9': if (si(a[0]) && si(a[1]) && si(a[2]) && si(a[3])) rotation(-1); asd = 6; break;
		}
		else
			switch (asd)
		{
			case 1: for (int i = 0; i < 8; i++) a[i].x += 3; break;
			case 2: for (int i = 0; i < 8; i++) a[i].x -= 3; break;
			case 3: for (int i = 0; i < 8; i++) a[i].y += 3; break;
			case 4: for (int i = 0; i < 8; i++) a[i].y -= 3; break;
			case 5:  rotation(-1); break;
			case 6:  rotation(1); break;
			case 7: qwerty(1); break;
			case 8: qwerty(-1); break;
		}
	}
	void clear()
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
	}
	bool Check()
	{
		bool CreateTrapeze = false;
		AD.x = a[0].x - a[3].x;
		AD.y = a[0].y - a[3].y;//верхняя
		BC.x = a[1].x - a[2].x;
		BC.y = a[1].y - a[2].y;//нижняя
		AB.x = a[0].x - a[1].x;
		AB.y = a[0].y - a[1].y;//боковая сторона
		CD.x = a[2].x - a[3].x;
		CD.y = a[2].y - a[3].y;//боковая сторона

		float scalBCAB = BC.x*AB.x + BC.y*AB.y; //две перпендикулярны
		float scalBCCD = BC.x*CD.x + BC.y*CD.y; //две перпендикулярны

		float h = sqrt((a[1].y - a[0].y)*(a[1].y - a[0].y)); //длина высоты
		float ab = sqrt((a[0].x - a[1].x)*(a[0].x - a[1].x) + (a[0].y - a[1].y)*(a[0].y - a[1].y)); //длина боковых сторон
		float cd = sqrt((a[2].x - a[3].x)*(a[2].x - a[3].x) + (a[2].y - a[3].y)*(a[2].y - a[3].y));

		if (scalBCAB != 0 || scalBCCD != 0)
		{
			if (ab >= h && cd >= h)
				CreateTrapeze = true;
			else
				CreateTrapeze = false;
		}
		else
			CreateTrapeze = false;
		return CreateTrapeze;
	}
	trapeze(FILE *f, RECT rt, HDC hdc, HWND hwnd)
	{
		rgb.r = 50; rgb.g = 80; rgb.b = 160;
		fonBrush = CreateSolidBrush(RGB(255, 255, 255));
		pointBrush = CreateSolidBrush(RGB(rgb.r, rgb.g, rgb.b));
		LoadFromFile(f);
		for (int i = 0; i < 8; i++)
			sa[i] = a[i];
		right = rt.right; bottom = rt.bottom;
		this->hdc = hdc;
		this->hwnd = hwnd;
		Center();

	}
};
