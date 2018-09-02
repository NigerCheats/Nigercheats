

#pragma once

#include "Render.h"





// We don't use these anywhere else, no reason for them to be
// available anywhere else
enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

void Render::SetupFonts()
{

	font.Default = 0x1D; // MainMenu Font from vgui_spew_fonts 
	font.ESP = Interfaces::Surface()->FontCreate();
	font.ESPan = Interfaces::Surface()->FontCreate();
	font.Defuse = Interfaces::Surface()->FontCreate();
	font.DroppedGuns = Interfaces::Surface()->FontCreate();
	font.Icon = Interfaces::Surface()->FontCreate();
	font.LBY = Interfaces::Surface()->FontCreate();
	font.Watermark = Interfaces::Surface()->FontCreate();
	font.NameFont = Interfaces::Surface()->FontCreate();
	font.Guns = Interfaces::Surface()->FontCreate();


	Interfaces::Surface()->SetFontGlyphSet(font.ESP, "Smallest Pixel-7", 11, 400, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_DROPSHADOW);
	Interfaces::Surface()->SetFontGlyphSet(font.Defuse, "Tahoma", 15, 700, 0, 0, FONTFLAG_DROPSHADOW);
	Interfaces::Surface()->SetFontGlyphSet(font.Watermark, "Verdana", 16, 700, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_DROPSHADOW);
	Interfaces::Surface()->SetFontGlyphSet(font.Icon, "astriumwep", 17, 400, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	//	g_Surface->SetFontGlyphSet(font.Icon, "Counter-Strike", 16, 500, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS);
	Interfaces::Surface()->SetFontGlyphSet(font.Guns, "Smallest Pixel-7", 12, 550, 0, 0, FONTFLAG_DROPSHADOW | FONTFLAG_OUTLINE);
	Interfaces::Surface()->SetFontGlyphSet(font.NameFont, "Verdana", 16, 800, 0, 0, FONTFLAG_DROPSHADOW);
	Interfaces::Surface()->SetFontGlyphSet(font.LBY, "Verdana", 36, 900, 0, 0, FONTFLAG_ANTIALIAS);
}

RECT Render::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	Interfaces::Engine()->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

void Render::Clear(int x, int y, int w, int h, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawFilledRect(x, y, x + w, y + h);
}

void Render::DrawOutlinedRect(int x, int y, int w, int h, Color col)
{
	Interfaces::Surface()->DrawSetColor(col);
	Interfaces::Surface()->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::Outline(int x, int y, int w, int h, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::DrawString2(DWORD font, int x, int y, Color color, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	uint8_t r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	int width, height;
	Interfaces::Surface()->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextColor(r, g, b, a);
	Interfaces::Surface()->DrawSetTextPos(x, y - height / 2);
	Interfaces::Surface()->DrawPrintText(wbuf, wcslen(wbuf));
}

void Render::DrawRect(int x1, int y1, int x2, int y2, Color clr)
{
	Interfaces::Surface()->DrawSetColor(clr);
	Interfaces::Surface()->DrawFilledRect(x1, y1, x2, y2);
}
void Render::OutlineRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
{
	Color colColor(0, 0, 0);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		Outline(x + i, y, 1, height, colRainbow);
	}
}


void Render::DrawCircle(float x, float y, float r, float s, Color color)
{
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI*2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;

		Line(x1, y1, x2, y2, color);
	}
}
void Render::Pixel(int x, int y, Color col)
{
	Interfaces::Surface()->DrawSetColor(col);
	Interfaces::Surface()->DrawFilledRect(x, y, x + 1, y + 1);
}

void Render::TexturedPolygon(int n, std::vector<Vertex_t> vertice, Color color) {
	static int texture_id = Interfaces::Surface()->CreateNewTextureID(true);
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	Interfaces::Surface()->DrawSetTextureRGBA(texture_id, buf, 1, 1);
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawSetTexture(texture_id);
	Interfaces::Surface()->DrawTexturedPolygon(n, vertice.data());
}

void Render::Line(int x, int y, int x2, int y2, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawLine(x, y, x2, y2);
}

void Render::DrawBox(int x, int y, int w, int h, Color color)
{
	// top
	DrawRect(x, y, w, 1, color);
	// right
	DrawRect(x, y + 1, 1, h - 1, color);
	// left
	DrawRect(x + w - 1, y + 1, 1, h - 1, color);
	// bottom
	DrawRect(x, y + h - 1, w - 1, 1, color);
}

void Render::DrawTexturedPoly(int n, Vertex_t* vertice, Color col)
{
	static int texture_id = Interfaces::Surface()->CreateNewTextureID(true);
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	Interfaces::Surface()->DrawSetTextureRGBA(texture_id, buf, 1, 1);
	Interfaces::Surface()->DrawSetColor(col);
	Interfaces::Surface()->DrawSetTexture(texture_id);
	Interfaces::Surface()->DrawTexturedPolygon(n, vertice);
}

void Render::DrawFilledCircle(Vector2D center, Color color, float radius, float points) {
	std::vector<Vertex_t> vertices;
	float step = (float)M_PI * 2.0f / points;
	for (float a = 0; a < (M_PI * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + center.x, radius * sinf(a) + center.y)));

	g_Render->DrawTexturedPoly((int)points, vertices.data(), color);
}

void Render::DrawFilledCircle2(int x, int y, int radius, int segments, Color color) {
	std::vector<Vertex_t> vertices;
	float step = M_PI * 2.0f / segments;
	for (float a = 0; a < (M_PI * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + x, radius * sinf(a) + y)));

	TexturedPolygon(vertices.size(), vertices, color);
}

void Render::PolyLine(int *x, int *y, int count, Color color)
{
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawPolyLine(x, y, count);
}

bool Render::ScanColorFromCvar(const char* str, float* colors)
{
	int len = strlen(str);
	if (len>11)return false;
	int clrnum = 0;
	int clrsum = 0;
	for (int i = 0; i<len; i++)
	{
		if (clrnum >= 3)return false;
		if (str[i] >= '0'&&str[i] <= '9')
		{
			clrsum = clrsum * 10 + str[i] - (int)'0';
		}
		else
		{
			colors[clrnum++] = (float)clrsum / 255.f;
			clrsum = 0;
		}
	}
	colors[clrnum] = (float)clrsum / 255.f;
	return true;
}

bool Render::WorldToScreen(const Vector& vOrigin, Vector& vScreen)
{
	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	static float* ViewMatrixOld = nullptr;
	float* ViewMatrix = nullptr;
	Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);
	if (!ViewMatrixOld)
	{
		ViewMatrixOld = FindW2Matrix();
	}
	else
	{
		ViewMatrix = (float*)(*(PDWORD)(ViewMatrixOld)+0x3DC);
	}

	if (ViewMatrix && *ViewMatrix)
	{
		vScreen.x = ViewMatrix[0] * vOrigin.x + ViewMatrix[1] * vOrigin.y + ViewMatrix[2] * vOrigin.z + ViewMatrix[3];
		vScreen.y = ViewMatrix[4] * vOrigin.x + ViewMatrix[5] * vOrigin.y + ViewMatrix[6] * vOrigin.z + ViewMatrix[7];
		float w = ViewMatrix[12] * vOrigin.x + ViewMatrix[13] * vOrigin.y + ViewMatrix[14] * vOrigin.z + ViewMatrix[15];

		if (w < 0.01f)
			return false;

		float invw = 1.0f / w;
		vScreen.x *= invw;
		vScreen.y *= invw;

		float x = (float)iScreenWidth / 2.f;
		float y = (float)iScreenHeight / 2.f;

		x += 0.5f * vScreen.x * iScreenWidth + 0.5f;
		y -= 0.5f * vScreen.y * iScreenHeight + 0.5f;

		vScreen.x = x;
		vScreen.y = y;

		return true;
	}

	return false;
}


void Render::Text(int x, int y, Color color, DWORD font, const char* text, ...)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	Interfaces::Surface()->DrawSetTextFont(font);

	Interfaces::Surface()->DrawSetTextColor(color);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(wcstring, wcslen(wcstring));
}

void Render::Text(int x, int y, Color color, DWORD font, const wchar_t* text)
{
	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextColor(color);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(text, wcslen(text));
}

void Render::Text(int x, int y, DWORD font, const wchar_t* text)
{
	Interfaces::Surface()->DrawSetTextFont(font);
	Interfaces::Surface()->DrawSetTextPos(x, y);
	Interfaces::Surface()->DrawPrintText(text, wcslen(text));
}

void Render::Textf(int x, int y, Color color, DWORD font, const char* fmt, ...)
{
	if (!fmt) return; //if the passed string is null return
	if (strlen(fmt) < 2) return;

	//Set up va_list and buffer to hold the params 
	va_list va_alist;
	char logBuf[256] = { 0 };

	//Do sprintf with the parameters
	va_start(va_alist, fmt);
	_vsnprintf_s(logBuf + strlen(logBuf), 256 - strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	Text(x, y, color, font, logBuf);
}

RECT Render::GetTextSize(DWORD font, const char* text)
{
	char Buffer[1024] = { '\0' };

	/* set up varargs*/
	va_list Args;

	va_start(Args, text);
	vsprintf_s(Buffer, text, Args);
	va_end(Args);

	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];

	mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);

	RECT rect;
	int x, y;
	Interfaces::Surface()->GetTextSize(font, WideBuffer, x, y);
	rect.left = x;
	rect.bottom = y;
	rect.right = x;
	return rect;
}

void Render::GradientV(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = float(i), fh = float(h);
		float a = float(fi / fh);
		DWORD ia = DWORD(a * 255);
		Clear(x, y + i, w, 1, Color(first, second, third, ia));
	}
}

void Render::GradientH(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = float(i), fw = float(w);
		float a = float(fi / fw);
		DWORD ia = DWORD(a * 255);
		Clear(x + i, y, 1, h, Color(first, second, third, ia));
	}
}

void Render::Polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = Interfaces::Surface()->CreateNewTextureID(true); //need to make a texture with procedural true
	unsigned char buffer[4] = { 255, 255, 255, 255 };//{ color.r(), color.g(), color.b(), color.a() };

	Interfaces::Surface()->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
	Interfaces::Surface()->DrawSetColor(color); // keep this full color and opacity use the RGBA @top to set values.
	Interfaces::Surface()->DrawSetTexture(Texture); // bind texture

	Interfaces::Surface()->DrawTexturedPolygon(count, Vertexs);
}

void Render::PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Polygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = int(Vertexs[i].m_Position.x);
		y[i] = int(Vertexs[i].m_Position.y);
	}

	PolyLine(x, y, count, colorLine);
}

void Render::PolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = int(Vertexs[i].m_Position.x);
		y[i] = int(Vertexs[i].m_Position.y);
	}

	PolyLine(x, y, count, colorLine);
}

void Render::OutlineCircle(int x, int y, int r, int seg, Color color)
{
	Interfaces::Surface()->DrawSetColor(0, 0, 0, 255);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r - 1, seg);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r + 1, seg);
	Interfaces::Surface()->DrawSetColor(color);
	Interfaces::Surface()->DrawOutlinedCircle(x, y, r, seg);
}

void Render::Draw3DCube(float scalar, QAngle angles, Vector middle_origin, Color outline)
{
	Vector forward, right, up;
	AngleVectors(angles, &forward, &right, &up);

	Vector points[8];
	points[0] = middle_origin - (right * scalar) + (up * scalar) - (forward * scalar); // BLT
	points[1] = middle_origin + (right * scalar) + (up * scalar) - (forward * scalar); // BRT
	points[2] = middle_origin - (right * scalar) - (up * scalar) - (forward * scalar); // BLB
	points[3] = middle_origin + (right * scalar) - (up * scalar) - (forward * scalar); // BRB

	points[4] = middle_origin - (right * scalar) + (up * scalar) + (forward * scalar); // FLT
	points[5] = middle_origin + (right * scalar) + (up * scalar) + (forward * scalar); // FRT
	points[6] = middle_origin - (right * scalar) - (up * scalar) + (forward * scalar); // FLB
	points[7] = middle_origin + (right * scalar) - (up * scalar) + (forward * scalar); // FRB

	Vector points_screen[8];
	for (int i = 0; i < 8; i++)
		if (!g_Render->WorldToScreen(points[i], points_screen[i]))
			return;

	Interfaces::Surface()->DrawSetColor(outline);

	// Back frame
	Interfaces::Surface()->DrawLine(points_screen[0].x, points_screen[0].y, points_screen[1].x, points_screen[1].y);
	Interfaces::Surface()->DrawLine(points_screen[0].x, points_screen[0].y, points_screen[2].x, points_screen[2].y);
	Interfaces::Surface()->DrawLine(points_screen[3].x, points_screen[3].y, points_screen[1].x, points_screen[1].y);
	Interfaces::Surface()->DrawLine(points_screen[3].x, points_screen[3].y, points_screen[2].x, points_screen[2].y);

	// Frame connector
	Interfaces::Surface()->DrawLine(points_screen[0].x, points_screen[0].y, points_screen[4].x, points_screen[4].y);
	Interfaces::Surface()->DrawLine(points_screen[1].x, points_screen[1].y, points_screen[5].x, points_screen[5].y);
	Interfaces::Surface()->DrawLine(points_screen[2].x, points_screen[2].y, points_screen[6].x, points_screen[6].y);
	Interfaces::Surface()->DrawLine(points_screen[3].x, points_screen[3].y, points_screen[7].x, points_screen[7].y);

	// Front frame
	Interfaces::Surface()->DrawLine(points_screen[4].x, points_screen[4].y, points_screen[5].x, points_screen[5].y);
	Interfaces::Surface()->DrawLine(points_screen[4].x, points_screen[4].y, points_screen[6].x, points_screen[6].y);
	Interfaces::Surface()->DrawLine(points_screen[7].x, points_screen[7].y, points_screen[5].x, points_screen[5].y);
	Interfaces::Surface()->DrawLine(points_screen[7].x, points_screen[7].y, points_screen[6].x, points_screen[6].y);
}
Render* g_Render = new(Render);


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class rbhexsh {
public:
	int nbgutmwpuddlj;
	bool nobegmrqc;
	string iluifldf;
	int ovnsl;
	rbhexsh();
	double blyoxvcefjelk(int ywzmfc, double bqmvxmdhjply);
	bool vddmmytstzisavhuudfyrbio(string jfrwdc, int zitqkfy, int rgyjjqcppfrs, bool uqweqxrvhyvq, double crlbtwh);
	double jfnwmqbmhgbimqiudbykc(int jsexkoysnfqa, string hwjnlppy, string qnxebnvrfucvmqc);
	void rmjwwcrjmvivgc(string oridokfkx, int hzpuxtuggcyyihz, bool rdrlaeayon, int ysrxpulimqld, int scdkooqybfxx);
	string nviseqtflxcrzngstbdqfiw(bool ildeasvqctrefhs, int ihobwbxsbyv, string xdtqvplbuh, double zqpmtqufjvd, bool lhbodtyaokeyzo, double koozvkvdpwaklni);
	bool spiyioswvvvntoidmbul(bool httvzh, int qlrcsxpub, bool lmguuuaotrhxjtp, string ttadfg, bool dxxddtmayyglmkt, double bkclgl, string evprwf, double hzhbryvpu, int hnzwpvzxs, int vuxbo);
	int srmsasmrhsbrlzvhdrhfuamo(bool hjuvyqboqmtfv, double mvdmszqsclbocx, int ybnrj, bool sohsfi, double jwvdsgousmz, double lvtxaaahs, double cuuhqe, int bneapwwwqwaayke);
	bool rolkhofzqjdsklurqbpij(string hidkvliigtjciv, double gtpbhqm);
	int dxccfxxmnnboissmkhtjuz(string hjaotpy, string gtkdbud, int oiodpkjceg, int juflbgbmcxax);
	void kcqywlnxlp(string aryrstp, double muktgkwetk, bool nhulatfpivtmq, double pwuujpjzjvaff, string nqfjwcomcm, string pjvstqyzkboqqh);

protected:
	int mqwiymckzaa;
	double lwjzdbheqh;
	bool yyddpa;
	int pbnnunm;
	double sretyvfdhkd;

	bool nsljxjeumu(bool tlghimczuqk, double tmpxwfjggvfqo, double pqwxhvcworctsr, int djwtsern, int zrazflbuhectl);
	void zfybdusxbpdnjodovs(bool xlegegtpzmeroq);
	double rlmsvirwzhlbwyoxxiefcoqh(double bobpoiyvynot, int wsmlnwnv, int pystjmchcizt, double qnmimpsgwprrzdr, int fszkzzx, bool unbhbpynuscet, string qpsivgnwqlgk, string hadigpszanzkliw);
	int qjkcnijibg(bool lqwoyjwbeyud, bool dvxmdhrhb, string ighohzrfzbc, bool juakcke, double mcfcr);
	string adevkmtpcwmfgjsqeofte(string zylwjjrnorl, bool ojvlywhe, string ewvgmu, string gncgb);
	double gplwsyypwjmmzllbadyrrsc(string syrmzuisu, string tmxshk, int ztjgj, bool gjzvrijtxgcyuf, int ybcggvwflqdtev, double systt, int jgwjfaouciqhwh);
	double rfstjcezlpolyc(double njgvhgr, string gxfelnmux, bool hnvvugbe, int ulwplk, bool rdimo, string bhcrhjgygsxf, bool pueqgfuzdmz, int ngjffwxbkjfh, int yrlzafoujp, double xfpwtuhmb);

private:
	int dbbkcwkhus;

	int cintxuueovzokuq(int ccjgmxsycpo);
	double kyqqlnqorgiytmkdetewb(string fiyersjpjnik, int ignhuuteuk, string vmckstdagprw, bool dbpqqofuckvrgt, string cdccsp, int khgartwfhkkj);
	double qzzomcghiw(string mfdflyeoimpjtw);
	int muszvsfxppcxiskfofqyviq(double ehysdo, string uheev, string facibfhkuhnfnx, bool ypjialdzzbx, string krxswqpegcg, bool dscwqdlevt);
	string lgwrerhutmaoodepav(int ztkgbnnhwjq, string nnnqnqrlfx, string riyae, int kbtgnro, int alnmdud, bool iwnpguuuqks);
	void wcyrxmmktqlenlupmdignfcch(bool hqqmtnlf, string ygfdgowyfamfivt, bool xyytfpcpooirt);

};


int rbhexsh::cintxuueovzokuq(int ccjgmxsycpo) {
	return 8264;
}

double rbhexsh::kyqqlnqorgiytmkdetewb(string fiyersjpjnik, int ignhuuteuk, string vmckstdagprw, bool dbpqqofuckvrgt, string cdccsp, int khgartwfhkkj) {
	bool metwewcpvzqfmpo = true;
	bool tlfmyumbd = false;
	int cddbymubcjm = 8716;
	if (true == true) {
		int evpyxpmviu;
		for (evpyxpmviu = 82; evpyxpmviu > 0; evpyxpmviu--) {
			continue;
		}
	}
	if (false != false) {
		int mhy;
		for (mhy = 24; mhy > 0; mhy--) {
			continue;
		}
	}
	return 15386;
}

double rbhexsh::qzzomcghiw(string mfdflyeoimpjtw) {
	bool heaxl = false;
	int vdvehzxvdmp = 1713;
	string rqcluwmfxb = "yllbekdstkxfbihgvcwsmnjgdfkjxjjqksrdxzchjaslcwnrqsflnqdzgnihwafoicd";
	double iltyirnmoy = 4458;
	bool fmpqslzyyyuk = false;
	string asaxlnjurfr = "faxbznvwtpayptclpthozzotlzmmhnstgaifpubyelgymxvpewvt";
	int zkdjlprpq = 5424;
	int bmlohnafreduwhr = 2157;
	if (2157 == 2157) {
		int vdnellxd;
		for (vdnellxd = 71; vdnellxd > 0; vdnellxd--) {
			continue;
		}
	}
	if (false != false) {
		int va;
		for (va = 18; va > 0; va--) {
			continue;
		}
	}
	if (false == false) {
		int pjrqw;
		for (pjrqw = 50; pjrqw > 0; pjrqw--) {
			continue;
		}
	}
	return 28846;
}

int rbhexsh::muszvsfxppcxiskfofqyviq(double ehysdo, string uheev, string facibfhkuhnfnx, bool ypjialdzzbx, string krxswqpegcg, bool dscwqdlevt) {
	int emsoaxmzhtkkgz = 347;
	bool chaxfqto = true;
	bool jwsbeo = false;
	string oletsokldtx = "jphibmxeqokrrtjicixkbmxnoambtcswmrecngvmgbgbdispemur";
	double gigzxvleuysv = 30296;
	bool gxeuonjrnjqj = false;
	string qocpecr = "zfwceivdmwnihoghuiiekxhykuvydmgdnvwnrbmknhynmejdnzivqbaovhrpsbyp";
	if (false == false) {
		int qvoekjics;
		for (qvoekjics = 65; qvoekjics > 0; qvoekjics--) {
			continue;
		}
	}
	if (347 != 347) {
		int huqboqgpsi;
		for (huqboqgpsi = 47; huqboqgpsi > 0; huqboqgpsi--) {
			continue;
		}
	}
	return 74514;
}

string rbhexsh::lgwrerhutmaoodepav(int ztkgbnnhwjq, string nnnqnqrlfx, string riyae, int kbtgnro, int alnmdud, bool iwnpguuuqks) {
	double mhtjarafvleku = 28006;
	double hgmfdn = 16897;
	string urzmsxvvxp = "llfcnscscsxxylrvrvpazldeejgqcauspgplazjnwcpjatiaumvfiylohptaqgoswebqtuygcfbuokaurdafaopfrkedtuk";
	string owjqldi = "azshmrwveqewbhvrfxpjhjojbvqpicspoyirzzahgjxndlecsaibxwcultwrplifvuewvrwascstadjxieth";
	string ryafymkir = "ghsnjbicuhwknvscddvjeoberfxzgyjlmyoemorec";
	bool qqcdeqpvjjtvp = false;
	int tqvdmpn = 3861;
	int hevmuqtrelgem = 4006;
	double vurpoqjowjsaqru = 12242;
	bool rnjodf = true;
	if (string("ghsnjbicuhwknvscddvjeoberfxzgyjlmyoemorec") != string("ghsnjbicuhwknvscddvjeoberfxzgyjlmyoemorec")) {
		int hu;
		for (hu = 11; hu > 0; hu--) {
			continue;
		}
	}
	if (string("azshmrwveqewbhvrfxpjhjojbvqpicspoyirzzahgjxndlecsaibxwcultwrplifvuewvrwascstadjxieth") != string("azshmrwveqewbhvrfxpjhjojbvqpicspoyirzzahgjxndlecsaibxwcultwrplifvuewvrwascstadjxieth")) {
		int lqwlguxup;
		for (lqwlguxup = 51; lqwlguxup > 0; lqwlguxup--) {
			continue;
		}
	}
	if (4006 == 4006) {
		int hebpk;
		for (hebpk = 71; hebpk > 0; hebpk--) {
			continue;
		}
	}
	if (string("ghsnjbicuhwknvscddvjeoberfxzgyjlmyoemorec") != string("ghsnjbicuhwknvscddvjeoberfxzgyjlmyoemorec")) {
		int btqhnzkxh;
		for (btqhnzkxh = 9; btqhnzkxh > 0; btqhnzkxh--) {
			continue;
		}
	}
	if (16897 != 16897) {
		int hmdwzpljwt;
		for (hmdwzpljwt = 69; hmdwzpljwt > 0; hmdwzpljwt--) {
			continue;
		}
	}
	return string("sayqnctplbn");
}

void rbhexsh::wcyrxmmktqlenlupmdignfcch(bool hqqmtnlf, string ygfdgowyfamfivt, bool xyytfpcpooirt) {
	int vhxlsobosewkca = 8210;
	string lesmibl = "fryduevxiklwlwlnojfzvlygmkoqv";
	string apqcpo = "deomjivwac";
	bool rlvcksjtgamnl = false;
	bool pdiofrrafvpylbw = true;
	double frepysthw = 35497;
	double pguduxwmxylfg = 21163;
	string hlzsrgq = "xetbnezxcn";
	if (35497 != 35497) {
		int rugrzgi;
		for (rugrzgi = 100; rugrzgi > 0; rugrzgi--) {
			continue;
		}
	}
	if (string("deomjivwac") != string("deomjivwac")) {
		int dtb;
		for (dtb = 55; dtb > 0; dtb--) {
			continue;
		}
	}

}

bool rbhexsh::nsljxjeumu(bool tlghimczuqk, double tmpxwfjggvfqo, double pqwxhvcworctsr, int djwtsern, int zrazflbuhectl) {
	bool rtfritg = false;
	bool twvkoyn = false;
	double ppoqwzwocjtln = 53181;
	if (false != false) {
		int knzatpi;
		for (knzatpi = 83; knzatpi > 0; knzatpi--) {
			continue;
		}
	}
	if (false == false) {
		int lt;
		for (lt = 59; lt > 0; lt--) {
			continue;
		}
	}
	if (53181 != 53181) {
		int sporcjiffg;
		for (sporcjiffg = 45; sporcjiffg > 0; sporcjiffg--) {
			continue;
		}
	}
	if (53181 != 53181) {
		int pfgvco;
		for (pfgvco = 44; pfgvco > 0; pfgvco--) {
			continue;
		}
	}
	if (false == false) {
		int ityavkh;
		for (ityavkh = 5; ityavkh > 0; ityavkh--) {
			continue;
		}
	}
	return true;
}

void rbhexsh::zfybdusxbpdnjodovs(bool xlegegtpzmeroq) {
	bool gfppocvihb = true;
	bool wjsykboulzdfkm = true;
	bool wojpfv = true;
	int iaswgazomaxcpz = 522;
	int fkzzmoaagagykj = 3356;
	bool ecisngzgrvvq = true;
	bool ksctw = false;
	double ypdgrqfcanlpri = 15145;
	string yyhyvbapyj = "zasiehlrdwxigsaakmikvlhffvmtzztkwcwtabqkleeqzyrgqoobotrsygbgibfk";
	if (true != true) {
		int chzlbuj;
		for (chzlbuj = 83; chzlbuj > 0; chzlbuj--) {
			continue;
		}
	}
	if (15145 != 15145) {
		int cdwwluea;
		for (cdwwluea = 99; cdwwluea > 0; cdwwluea--) {
			continue;
		}
	}
	if (true != true) {
		int pvxdhxygs;
		for (pvxdhxygs = 41; pvxdhxygs > 0; pvxdhxygs--) {
			continue;
		}
	}
	if (string("zasiehlrdwxigsaakmikvlhffvmtzztkwcwtabqkleeqzyrgqoobotrsygbgibfk") == string("zasiehlrdwxigsaakmikvlhffvmtzztkwcwtabqkleeqzyrgqoobotrsygbgibfk")) {
		int ovtywtmfh;
		for (ovtywtmfh = 37; ovtywtmfh > 0; ovtywtmfh--) {
			continue;
		}
	}

}

double rbhexsh::rlmsvirwzhlbwyoxxiefcoqh(double bobpoiyvynot, int wsmlnwnv, int pystjmchcizt, double qnmimpsgwprrzdr, int fszkzzx, bool unbhbpynuscet, string qpsivgnwqlgk, string hadigpszanzkliw) {
	string twhcj = "latzgdpwrjbofmnumgvasflylzhop";
	string mygahg = "sqpnnxwviypzjcpqmrfnqsdgnngbixvvxuyxnvgrxomxuewgaqabndtz";
	double vwjhx = 4797;
	if (string("latzgdpwrjbofmnumgvasflylzhop") != string("latzgdpwrjbofmnumgvasflylzhop")) {
		int rvdr;
		for (rvdr = 26; rvdr > 0; rvdr--) {
			continue;
		}
	}
	if (string("sqpnnxwviypzjcpqmrfnqsdgnngbixvvxuyxnvgrxomxuewgaqabndtz") != string("sqpnnxwviypzjcpqmrfnqsdgnngbixvvxuyxnvgrxomxuewgaqabndtz")) {
		int gejkbpyrc;
		for (gejkbpyrc = 32; gejkbpyrc > 0; gejkbpyrc--) {
			continue;
		}
	}
	if (string("latzgdpwrjbofmnumgvasflylzhop") != string("latzgdpwrjbofmnumgvasflylzhop")) {
		int wnmbqnwr;
		for (wnmbqnwr = 4; wnmbqnwr > 0; wnmbqnwr--) {
			continue;
		}
	}
	if (4797 == 4797) {
		int yqg;
		for (yqg = 90; yqg > 0; yqg--) {
			continue;
		}
	}
	if (4797 != 4797) {
		int esxuigxbd;
		for (esxuigxbd = 34; esxuigxbd > 0; esxuigxbd--) {
			continue;
		}
	}
	return 13822;
}

int rbhexsh::qjkcnijibg(bool lqwoyjwbeyud, bool dvxmdhrhb, string ighohzrfzbc, bool juakcke, double mcfcr) {
	double dsqjm = 515;
	double vihiey = 74940;
	string wjyrknfic = "cpbvvhcravtapw";
	bool obycrsrws = true;
	double mibuhjxsjx = 5916;
	if (string("cpbvvhcravtapw") != string("cpbvvhcravtapw")) {
		int ta;
		for (ta = 96; ta > 0; ta--) {
			continue;
		}
	}
	return 32861;
}

string rbhexsh::adevkmtpcwmfgjsqeofte(string zylwjjrnorl, bool ojvlywhe, string ewvgmu, string gncgb) {
	double ykdvoqtc = 35157;
	if (35157 != 35157) {
		int tyzbwptild;
		for (tyzbwptild = 81; tyzbwptild > 0; tyzbwptild--) {
			continue;
		}
	}
	if (35157 == 35157) {
		int wwgr;
		for (wwgr = 95; wwgr > 0; wwgr--) {
			continue;
		}
	}
	if (35157 != 35157) {
		int gspigh;
		for (gspigh = 27; gspigh > 0; gspigh--) {
			continue;
		}
	}
	if (35157 == 35157) {
		int uxumrgzvc;
		for (uxumrgzvc = 11; uxumrgzvc > 0; uxumrgzvc--) {
			continue;
		}
	}
	return string("nbeasj");
}

double rbhexsh::gplwsyypwjmmzllbadyrrsc(string syrmzuisu, string tmxshk, int ztjgj, bool gjzvrijtxgcyuf, int ybcggvwflqdtev, double systt, int jgwjfaouciqhwh) {
	double yugydkrikdk = 41426;
	int rbseft = 1560;
	int poeauut = 908;
	double omlbb = 8815;
	return 78713;
}

double rbhexsh::rfstjcezlpolyc(double njgvhgr, string gxfelnmux, bool hnvvugbe, int ulwplk, bool rdimo, string bhcrhjgygsxf, bool pueqgfuzdmz, int ngjffwxbkjfh, int yrlzafoujp, double xfpwtuhmb) {
	return 39543;
}

double rbhexsh::blyoxvcefjelk(int ywzmfc, double bqmvxmdhjply) {
	string cqkykhrf = "amomqmxftlleufqcggycugricizhrplbfjoqzxnpvaxkonjxescrnnjwrwxozhcokqijzqmzay";
	string yhreizvpignjvsf = "zjsrsnvsswbgotjephgbpibvvch";
	int asxpk = 1667;
	double hprcwdewy = 49528;
	bool uxghmeulrh = true;
	string entjqqtrv = "lbcnjh";
	double baioirujalwg = 64060;
	string vonysrjhkytkhp = "uslhxhgoeeqhjzijmoiwmzythiwxqvkwilbsutxrpdzxbsuqjpywoxcuqpbowxgpntgek";
	if (string("uslhxhgoeeqhjzijmoiwmzythiwxqvkwilbsutxrpdzxbsuqjpywoxcuqpbowxgpntgek") == string("uslhxhgoeeqhjzijmoiwmzythiwxqvkwilbsutxrpdzxbsuqjpywoxcuqpbowxgpntgek")) {
		int dsagi;
		for (dsagi = 25; dsagi > 0; dsagi--) {
			continue;
		}
	}
	if (string("uslhxhgoeeqhjzijmoiwmzythiwxqvkwilbsutxrpdzxbsuqjpywoxcuqpbowxgpntgek") != string("uslhxhgoeeqhjzijmoiwmzythiwxqvkwilbsutxrpdzxbsuqjpywoxcuqpbowxgpntgek")) {
		int xebpwfvs;
		for (xebpwfvs = 5; xebpwfvs > 0; xebpwfvs--) {
			continue;
		}
	}
	return 66457;
}

bool rbhexsh::vddmmytstzisavhuudfyrbio(string jfrwdc, int zitqkfy, int rgyjjqcppfrs, bool uqweqxrvhyvq, double crlbtwh) {
	bool ovohtdh = true;
	string oolrigc = "wcsodnyanmgfibgrgljiedilufmfnrvrtcvpowjxapwjrkmcbdbsecieuqthiycwigjuvtwtpwgipxeeerelbcjuoipfrmv";
	string mpveaulcx = "fbchzcznvzlcfwsbyalolldraxmvifatxdweejbreealezp";
	int vyydeskxs = 23;
	double myibzuo = 23829;
	if (string("fbchzcznvzlcfwsbyalolldraxmvifatxdweejbreealezp") != string("fbchzcznvzlcfwsbyalolldraxmvifatxdweejbreealezp")) {
		int bu;
		for (bu = 12; bu > 0; bu--) {
			continue;
		}
	}
	return true;
}

double rbhexsh::jfnwmqbmhgbimqiudbykc(int jsexkoysnfqa, string hwjnlppy, string qnxebnvrfucvmqc) {
	int wypiulex = 419;
	bool kacgm = true;
	double ngfze = 11318;
	if (419 != 419) {
		int lisles;
		for (lisles = 12; lisles > 0; lisles--) {
			continue;
		}
	}
	if (true == true) {
		int tlmx;
		for (tlmx = 19; tlmx > 0; tlmx--) {
			continue;
		}
	}
	if (true == true) {
		int roy;
		for (roy = 58; roy > 0; roy--) {
			continue;
		}
	}
	if (true == true) {
		int xm;
		for (xm = 23; xm > 0; xm--) {
			continue;
		}
	}
	if (true == true) {
		int tnd;
		for (tnd = 3; tnd > 0; tnd--) {
			continue;
		}
	}
	return 46305;
}

void rbhexsh::rmjwwcrjmvivgc(string oridokfkx, int hzpuxtuggcyyihz, bool rdrlaeayon, int ysrxpulimqld, int scdkooqybfxx) {
	double cuqqytqfofcjyz = 27872;
	int rfnhancjpl = 697;
	int kiggvjcg = 837;
	string kickwfalfhewhqc = "jpzrynwddeixxstthfgsjivnrdjkcpvsguqmkhmpry";
	if (697 != 697) {
		int joksbx;
		for (joksbx = 30; joksbx > 0; joksbx--) {
			continue;
		}
	}
	if (697 == 697) {
		int yw;
		for (yw = 7; yw > 0; yw--) {
			continue;
		}
	}
	if (string("jpzrynwddeixxstthfgsjivnrdjkcpvsguqmkhmpry") != string("jpzrynwddeixxstthfgsjivnrdjkcpvsguqmkhmpry")) {
		int brhkmmkrnm;
		for (brhkmmkrnm = 84; brhkmmkrnm > 0; brhkmmkrnm--) {
			continue;
		}
	}
	if (837 != 837) {
		int ctglopw;
		for (ctglopw = 23; ctglopw > 0; ctglopw--) {
			continue;
		}
	}
	if (837 == 837) {
		int gfhkcvzbg;
		for (gfhkcvzbg = 95; gfhkcvzbg > 0; gfhkcvzbg--) {
			continue;
		}
	}

}

string rbhexsh::nviseqtflxcrzngstbdqfiw(bool ildeasvqctrefhs, int ihobwbxsbyv, string xdtqvplbuh, double zqpmtqufjvd, bool lhbodtyaokeyzo, double koozvkvdpwaklni) {
	int optvkugvzfhwer = 3795;
	double mrunv = 35680;
	bool fmscbbrn = true;
	if (true != true) {
		int ksfyrpjh;
		for (ksfyrpjh = 4; ksfyrpjh > 0; ksfyrpjh--) {
			continue;
		}
	}
	if (35680 != 35680) {
		int ccbgcauc;
		for (ccbgcauc = 89; ccbgcauc > 0; ccbgcauc--) {
			continue;
		}
	}
	if (35680 == 35680) {
		int nosholhcey;
		for (nosholhcey = 86; nosholhcey > 0; nosholhcey--) {
			continue;
		}
	}
	return string("ckyldbnhesp");
}

bool rbhexsh::spiyioswvvvntoidmbul(bool httvzh, int qlrcsxpub, bool lmguuuaotrhxjtp, string ttadfg, bool dxxddtmayyglmkt, double bkclgl, string evprwf, double hzhbryvpu, int hnzwpvzxs, int vuxbo) {
	double flxwriulggwez = 29711;
	if (29711 == 29711) {
		int gboryhcks;
		for (gboryhcks = 29; gboryhcks > 0; gboryhcks--) {
			continue;
		}
	}
	if (29711 != 29711) {
		int xkqppsmkfs;
		for (xkqppsmkfs = 91; xkqppsmkfs > 0; xkqppsmkfs--) {
			continue;
		}
	}
	if (29711 == 29711) {
		int ztoaflr;
		for (ztoaflr = 40; ztoaflr > 0; ztoaflr--) {
			continue;
		}
	}
	if (29711 != 29711) {
		int xza;
		for (xza = 29; xza > 0; xza--) {
			continue;
		}
	}
	return true;
}

int rbhexsh::srmsasmrhsbrlzvhdrhfuamo(bool hjuvyqboqmtfv, double mvdmszqsclbocx, int ybnrj, bool sohsfi, double jwvdsgousmz, double lvtxaaahs, double cuuhqe, int bneapwwwqwaayke) {
	string ujnhdwckjkwi = "phvhduvumqbgnfyfsvsdkmwakcotnhykbboodjbuomevejpgymnsboneeqylfxrggnfoqsadwxcafejewrducaxkerrlriaglra";
	if (string("phvhduvumqbgnfyfsvsdkmwakcotnhykbboodjbuomevejpgymnsboneeqylfxrggnfoqsadwxcafejewrducaxkerrlriaglra") != string("phvhduvumqbgnfyfsvsdkmwakcotnhykbboodjbuomevejpgymnsboneeqylfxrggnfoqsadwxcafejewrducaxkerrlriaglra")) {
		int sbqyirh;
		for (sbqyirh = 29; sbqyirh > 0; sbqyirh--) {
			continue;
		}
	}
	return 34605;
}

bool rbhexsh::rolkhofzqjdsklurqbpij(string hidkvliigtjciv, double gtpbhqm) {
	string nqrzhtdab = "pbkuajtivfgyfywitikpdqcagqyvpfjly";
	int iszligd = 1698;
	bool agzspljfsak = true;
	string khhri = "oiaebfgrnnkhnsurxfjrjvhi";
	bool icbiahyuflwb = true;
	if (1698 != 1698) {
		int dipd;
		for (dipd = 95; dipd > 0; dipd--) {
			continue;
		}
	}
	if (1698 == 1698) {
		int dzudwyodp;
		for (dzudwyodp = 69; dzudwyodp > 0; dzudwyodp--) {
			continue;
		}
	}
	return false;
}

int rbhexsh::dxccfxxmnnboissmkhtjuz(string hjaotpy, string gtkdbud, int oiodpkjceg, int juflbgbmcxax) {
	int yyxgtzxoykb = 274;
	bool dhoka = false;
	string cxdpjvkfgsithol = "wpbkjgolvjrxamrowavpgylwtfwcatrvdzfwdasfpexkj";
	bool zntgxkqppu = false;
	int iskteqmsnmj = 1919;
	bool avkvxbeg = true;
	string ondjxzu = "rwfre";
	int tzsqzrb = 633;
	if (1919 != 1919) {
		int yxmigktejp;
		for (yxmigktejp = 78; yxmigktejp > 0; yxmigktejp--) {
			continue;
		}
	}
	return 38476;
}

void rbhexsh::kcqywlnxlp(string aryrstp, double muktgkwetk, bool nhulatfpivtmq, double pwuujpjzjvaff, string nqfjwcomcm, string pjvstqyzkboqqh) {
	int buwumrnxzkd = 1715;
	int uoqwuornjzc = 6207;
	string gzmbqpmuvl = "vcuhaaoiik";
	int oflkvrhouur = 784;
	string xrbwcmcbcr = "rifdjrxdudgzbqwtneyejsirenhabzshm";
	string zrqjjlyklajndg = "jkigsahrwmnkkkhtexgfx";
	int fblkh = 3646;

}

rbhexsh::rbhexsh() {
	this->blyoxvcefjelk(879, 24843);
	this->vddmmytstzisavhuudfyrbio(string("vmefptlfioohbgjrowwlumygoqqcmp"), 3506, 2, true, 28442);
	this->jfnwmqbmhgbimqiudbykc(2838, string("xkynniezzphctmkpbxjpurihvxxbxuykryymiqmcuskykfssrwkahhtjjugbcyiddprfsnrgyzmyngkwehvneekxehpsbp"), string("xjjrhqulnfdhiewecsbeaxwekyrdmczgzaoukbavlcgddllgolomexwugttoapuhbjyjnaijorffyuerzencfzozal"));
	this->rmjwwcrjmvivgc(string("vznwozmzgoxdnknojgazglcijumftujjgoytlgnckdtygqxgkaoetsaudkcsvokacczxnoantnpkuqerceefnkvsfniouxaktx"), 4983, false, 2449, 3422);
	this->nviseqtflxcrzngstbdqfiw(false, 619, string("dvpgrjiibwgxhbiatwklqzqcnyyieaxxzqftavjadyhmokmnrshxatpdta"), 29269, true, 11056);
	this->spiyioswvvvntoidmbul(true, 4454, true, string("gdsiskeqjhfbjbgmjfpldfepaj"), false, 19960, string("vmf"), 1235, 4059, 1687);
	this->srmsasmrhsbrlzvhdrhfuamo(false, 45147, 263, false, 12873, 26783, 15511, 1400);
	this->rolkhofzqjdsklurqbpij(string("m"), 47895);
	this->dxccfxxmnnboissmkhtjuz(string("kawgkclfcreqsqyomrnmnhxgywhntakdmrmjalxsemylrgklrqffgfsev"), string("drqsaksorwisozuqkhduvnbiooolbstdlkuseepncrttou"), 8364, 4493);
	this->kcqywlnxlp(string("pqpaisnqkkuzmjdyuaiegygvqmkydrttovnxylrzuhhgnehc"), 29566, true, 7724, string("qftekgkseiyoymkuzirnyeusbcedlbpbxtqprcas"), string("gfudinzaownbrdjsmsgwpuzfrikgxrndvyyvjezivaqnlxpdcwdxfnmlttcpczhbf"));
	this->nsljxjeumu(true, 13502, 53181, 3458, 7028);
	this->zfybdusxbpdnjodovs(true);
	this->rlmsvirwzhlbwyoxxiefcoqh(6019, 620, 7635, 21216, 2968, false, string("jbzw"), string("jdbetrnrtheuwcxgjjurevzwdtwtikamtdcwviwavvzszwtntmyepxxcdatbqtnb"));
	this->qjkcnijibg(true, false, string("kumsxhvwsrmnqnorffxgoqqtdnqremoyqysppjcxqcmhasyxahxfbuiviciglmfkyudqavwldycptkbalp"), false, 4133);
	this->adevkmtpcwmfgjsqeofte(string("fymndatvhdpngckxrhzlltxgpyrarki"), false, string("bwbujjbzglrofwlyngnowfdwcsskmeebmzsnznpolhkxhtbtjrxqlrjkuoqnkfimtyvxtx"), string("yrwqdsegtmgrbcprrhahtfjjkkzeddxv"));
	this->gplwsyypwjmmzllbadyrrsc(string("qh"), string("kmlezvjivlsjyckjxasxdt"), 752, true, 386, 14993, 4316);
	this->rfstjcezlpolyc(11109, string("zqyokobgoekyzitdniq"), false, 1374, true, string("mymqarmilxcah"), false, 547, 1122, 54253);
	this->cintxuueovzokuq(1622);
	this->kyqqlnqorgiytmkdetewb(string("nxssfvetuftztdwjakhbbmnqxdmncklvzgtrjlhowirdfqevgkshecntgjsitlwlfvvssrurmctdri"), 2478, string("qidgmxcqwjqtokkmvremctotwbeywzhlcdytbgqsty"), false, string("whzrsctthpgmuwmkpqcbxocxmgislqrzlyupntvgjdayiirhauyzopjvidchtfvywsvigpudnaamxwllepgct"), 6699);
	this->qzzomcghiw(string("sytycacwsroulflgkmamjctuzkhhgelxbvevephtbuxqvjziragavxxlbwgwyggwjetddsygtqocmxqyq"));
	this->muszvsfxppcxiskfofqyviq(45979, string("gcozvqgijcvefazya"), string("glkdbhgvvhuepkrzprkkernsovadflihilveyabythmhnfzawuhorsdvkjoebzxuezyuvvocshijknkysgupehdm"), false, string("vtnlldmzxivtdamyulfmpseorpgyzhwjfepzbqxfrntsrvclmuwmiuo"), false);
	this->lgwrerhutmaoodepav(1003, string("bxprbnrwxnjnirinkiysflplydrjvfskitgaenrjdfihjpuyslgjxctnzvriuywitkiyiravkvywqvpdibuafqpyrcuxoidrvj"), string("zouubazilrtnlczshpmuiatypoffegzejxbdyvckwvzhsxjcsxeljwbyweislajmmcwfhuxndsggerchszaymlnogno"), 9303, 4040, false);
	this->wcyrxmmktqlenlupmdignfcch(true, string("blacvghfttfznehdzoqzpoypkzrnjjmcfsvzx"), true);
}
