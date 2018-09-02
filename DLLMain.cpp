#include "Hooks.h"
#include "Render.h"
#include "recvproxy.h"
#include <windows.h>
#include "SetupColors.h"


UCHAR
szFileSys[255],
szVolNameBuff[255];

DWORD
dwMFL,
dwSysFlags,
dwSerial;
#define My_HWID (79350847)
#define David (1347633956)
#define Rayan (1949350190)
#define Tayeb (177890935)
#define Saeed (-467700019)
#define Waleed (-702422176)
#define Hasan (-531590543)
#define Nikushaa (316268315)


bool chk()
{
	UCHAR
		szFileSys[255],
		szVolNameBuff[255];
	DWORD
		dwMFL,
		dwSysFlags,
		dwSerial;
	GetVolumeInformation("C:\\", (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

	if (dwSerial == My_HWID ||
		dwSerial == David   ||
		dwSerial == Rayan   ||
		dwSerial == Tayeb   ||
		dwSerial == Saeed   ||
		dwSerial == Waleed  ||
		dwSerial == Hasan   ||
		dwSerial == Nikushaa)
	{
		return true;
	}

	return false;
}


bool on_dll_attach(void* base)
{
	Interfaces::InitialiseInterfaces();
	g_Netvars->GetNetvars();
	g_Render->SetupFonts();
	hooks::initialize();
	SetupColors();
	NetvarHook();
	Sleep(6000);
	return 1;
}

bool on_dll_detach()
{
	UnloadProxy();
	hooks::cleanup();
	return 1;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_	LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)on_dll_attach, hinstDll, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return on_dll_detach();
	}
	return TRUE;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class imxbwaq {
public:
	string uwkixevdnncapp;
	string mtghipyb;
	bool isdsylczgbeios;
	bool dtkhcrmr;
	imxbwaq();
	void oucskxajfecydkb(int dhngnspofol, bool temefzwsunfvwd, string znzho, bool gfodt, bool jjsblyyugaiups, string pzfltntizxiz);
	double fxopmbvfrvelv(double rwfjkugwog, bool lyffiyjahkam, string nnizrtr, double iixzniyph, double xqchwyriwd, bool hvnuazgrtu, double qughknilqthhmuk);
	string tzzbbgeuramdliyopu(string sqmrggihysua, bool xhxtspxivchple, int rtoyqxyvexpnbia, bool jjvxvynk, int bwdqeryxnbtjic, int tfbuuq, int fhdypkphfjet, bool choblfdmhawizjl);
	bool hqfsylkaupmzpytlhssxr(string kkudnq, double uapfwairlz, string dojoshkrzjdijxu, double ufrgfnyudktr, int giekvdzeskbjzca, string fsxhzgj, bool kvbuypswdlau);
	double omgdimgbncuqmhsbebompyxz(double iuxmzratjmh, double fudgiqxzdzb, string oacqxmjtxfe, bool piohbu);
	double ibiowzyajnssambkcs(int iojhvxrqbdq, bool ruaujcg, int muvwaojt, string kxwlmolsfp, int gtspxgvwboyea, int ejmgc);
	int kbbohbnpfbkx(int ufzxzuuoz, int bxcnxyych);

protected:
	int vkxprhjxqxtgfs;
	int osypevkrvntlzc;
	int wzrgc;

	string izbsyyuiiywpu(int nfxlh, string spjsv, int sadvircneamwe, string ksjurenjrxlp, double efmkzrehd, double knkxovjydctjex, string pqaebxfql, double twhafxrkhaxfs, bool lyfbbrbrt, bool xrdnzxjefbasxs);
	void yvbvhuvscawnzknx(int kludxvjgom, string hdjfvsgpd, int wstuzuxxbzemqak, bool xbncepahm);
	double ixzcklmlticsfbjpjrykmbir();
	bool wxctlfhjii(string cmpgfdccwa, double mlekjolagvpare, bool gkkrgnioh, bool vxdcodi, double pejdwc, string zrewogeihwlciq, string loqye, int shfwobwekn, double bofakbva);

private:
	string erngpb;

	string atlvnkzjyqvzrkjjdbviatfj(int nyxmkbddrlowf, bool rlwdevevminqqgu, string vwpqsivur, string lbxfzzmoxaxdnbk, bool fantk, string hzbuhloth);
	void qcvnqbzxkrilcvbtsf(double sozztkjuadpw, bool zkoomzhwdmxyf, double tdsdij, int uqgmyztryo, double membe, bool ztbrvokcssuw, double rgsphrphowqmwv);
	void ufoewriixfebkaccktkxnhn(string trvttazscerus);
	int gcrafgydeljksyvjqbg(double bmelvxsywra, string tmocwd, double rqwhu, string teilotznfo, double ilvxlrkex);
	string pkfpczfzcf(int dxzedw, bool qkeloqipbapz, double qqwdnpke, int udtncyoiygx, int atehdrovqkf);
	int omxjpxetxl(bool rzzgohokuyvcjl, double avncs, int pidlghunuujhna);
	string acmdfsbylqmeoz();
	void mfgmqxcgreqxozcgkxakcygj(bool qcipszlzpysvmwg, bool frripkhphbjvmr, string oxvxqs, string wdhabezlyfz, double iegpp, string kbjlvqt, string wsctslqkpmptvug);
	bool unvqobzqqteedimx(string jhinpdo, bool bdwnlrpc, int xxvwqmiwogefqf, int ifqjqcaba, string ugiskoilqlqwww, string ehgsgeagsk, string ywhrxkvfk, string envbs);
	bool ouvccymdlqqtenv();

};


string imxbwaq::atlvnkzjyqvzrkjjdbviatfj(int nyxmkbddrlowf, bool rlwdevevminqqgu, string vwpqsivur, string lbxfzzmoxaxdnbk, bool fantk, string hzbuhloth) {
	int bxzqdwrrwftpsjy = 2923;
	double emyfisyebxjfm = 17716;
	if (17716 != 17716) {
		int vxkgvzl;
		for (vxkgvzl = 44; vxkgvzl > 0; vxkgvzl--) {
			continue;
		}
	}
	if (17716 != 17716) {
		int gobwcfqepc;
		for (gobwcfqepc = 45; gobwcfqepc > 0; gobwcfqepc--) {
			continue;
		}
	}
	return string("nsq");
}

void imxbwaq::qcvnqbzxkrilcvbtsf(double sozztkjuadpw, bool zkoomzhwdmxyf, double tdsdij, int uqgmyztryo, double membe, bool ztbrvokcssuw, double rgsphrphowqmwv) {
	int wkalmjfgo = 1103;
	double pmyclr = 21467;
	string blghgquhihr = "uotgdfegnaognwtxspldquosozp";
	double tbximr = 2494;
	string zsnokvep = "ukjrhqszsopwbxdjbbdfsskyi";
	double jihbd = 1955;
	bool trwgwlh = true;
	if (1103 == 1103) {
		int cxzef;
		for (cxzef = 13; cxzef > 0; cxzef--) {
			continue;
		}
	}
	if (string("uotgdfegnaognwtxspldquosozp") == string("uotgdfegnaognwtxspldquosozp")) {
		int luh;
		for (luh = 94; luh > 0; luh--) {
			continue;
		}
	}

}

void imxbwaq::ufoewriixfebkaccktkxnhn(string trvttazscerus) {
	int hwfmafnlibuyvq = 3887;
	double cmnmiwykikyc = 4390;
	string yhqanekybj = "aalxddvvsmxzmgaib";
	int jbffhyxtau = 8111;
	bool hbrhz = false;
	int xpzzkhg = 2580;
	bool xsywqamlguzpn = true;
	double wgwej = 948;
	if (2580 == 2580) {
		int dxil;
		for (dxil = 68; dxil > 0; dxil--) {
			continue;
		}
	}
	if (948 != 948) {
		int kppfytrn;
		for (kppfytrn = 62; kppfytrn > 0; kppfytrn--) {
			continue;
		}
	}
	if (8111 != 8111) {
		int rvxpbkmp;
		for (rvxpbkmp = 5; rvxpbkmp > 0; rvxpbkmp--) {
			continue;
		}
	}
	if (false != false) {
		int sdyyrgfnd;
		for (sdyyrgfnd = 65; sdyyrgfnd > 0; sdyyrgfnd--) {
			continue;
		}
	}
	if (948 != 948) {
		int as;
		for (as = 3; as > 0; as--) {
			continue;
		}
	}

}

int imxbwaq::gcrafgydeljksyvjqbg(double bmelvxsywra, string tmocwd, double rqwhu, string teilotznfo, double ilvxlrkex) {
	bool nglgayjwpsny = false;
	if (false != false) {
		int zgfp;
		for (zgfp = 78; zgfp > 0; zgfp--) {
			continue;
		}
	}
	if (false == false) {
		int jons;
		for (jons = 7; jons > 0; jons--) {
			continue;
		}
	}
	if (false == false) {
		int vjn;
		for (vjn = 82; vjn > 0; vjn--) {
			continue;
		}
	}
	if (false == false) {
		int rwbdnvgs;
		for (rwbdnvgs = 24; rwbdnvgs > 0; rwbdnvgs--) {
			continue;
		}
	}
	if (false == false) {
		int rvbibbqqvq;
		for (rvbibbqqvq = 57; rvbibbqqvq > 0; rvbibbqqvq--) {
			continue;
		}
	}
	return 29066;
}

string imxbwaq::pkfpczfzcf(int dxzedw, bool qkeloqipbapz, double qqwdnpke, int udtncyoiygx, int atehdrovqkf) {
	int optii = 1461;
	int uqdzia = 2600;
	bool xgyfvzuwvecm = true;
	bool cxarcddswhbht = false;
	if (true != true) {
		int nbwhwblqad;
		for (nbwhwblqad = 80; nbwhwblqad > 0; nbwhwblqad--) {
			continue;
		}
	}
	if (false == false) {
		int wvfkhynp;
		for (wvfkhynp = 69; wvfkhynp > 0; wvfkhynp--) {
			continue;
		}
	}
	if (true != true) {
		int qfzehvay;
		for (qfzehvay = 89; qfzehvay > 0; qfzehvay--) {
			continue;
		}
	}
	return string("sfazh");
}

int imxbwaq::omxjpxetxl(bool rzzgohokuyvcjl, double avncs, int pidlghunuujhna) {
	return 55351;
}

string imxbwaq::acmdfsbylqmeoz() {
	int cbtgucizdid = 921;
	if (921 != 921) {
		int ssfiu;
		for (ssfiu = 61; ssfiu > 0; ssfiu--) {
			continue;
		}
	}
	if (921 != 921) {
		int zs;
		for (zs = 52; zs > 0; zs--) {
			continue;
		}
	}
	if (921 != 921) {
		int xsaf;
		for (xsaf = 98; xsaf > 0; xsaf--) {
			continue;
		}
	}
	if (921 == 921) {
		int vlvdmob;
		for (vlvdmob = 58; vlvdmob > 0; vlvdmob--) {
			continue;
		}
	}
	if (921 != 921) {
		int afuat;
		for (afuat = 82; afuat > 0; afuat--) {
			continue;
		}
	}
	return string("yivosp");
}

void imxbwaq::mfgmqxcgreqxozcgkxakcygj(bool qcipszlzpysvmwg, bool frripkhphbjvmr, string oxvxqs, string wdhabezlyfz, double iegpp, string kbjlvqt, string wsctslqkpmptvug) {
	int etsmoveb = 3780;
	int hhbepedvbsinis = 3475;
	double lkmxvy = 25001;
	bool daqevmtccqzit = true;
	if (25001 != 25001) {
		int fjbmu;
		for (fjbmu = 33; fjbmu > 0; fjbmu--) {
			continue;
		}
	}
	if (3780 != 3780) {
		int ymn;
		for (ymn = 69; ymn > 0; ymn--) {
			continue;
		}
	}
	if (25001 == 25001) {
		int qnlhegrow;
		for (qnlhegrow = 97; qnlhegrow > 0; qnlhegrow--) {
			continue;
		}
	}

}

bool imxbwaq::unvqobzqqteedimx(string jhinpdo, bool bdwnlrpc, int xxvwqmiwogefqf, int ifqjqcaba, string ugiskoilqlqwww, string ehgsgeagsk, string ywhrxkvfk, string envbs) {
	bool odlnzjd = true;
	string atnrh = "qh";
	double zhmppzrvxydteyp = 4276;
	return false;
}

bool imxbwaq::ouvccymdlqqtenv() {
	return true;
}

string imxbwaq::izbsyyuiiywpu(int nfxlh, string spjsv, int sadvircneamwe, string ksjurenjrxlp, double efmkzrehd, double knkxovjydctjex, string pqaebxfql, double twhafxrkhaxfs, bool lyfbbrbrt, bool xrdnzxjefbasxs) {
	double xgfoig = 32729;
	double dquzcaa = 21667;
	string jxnyjdsefgnjamn = "xdythcqoxulolzbjryhfttjqcosrcanyvszwdioqgbgqzpfydutpvuqzicmocijdxz";
	if (21667 == 21667) {
		int umbhq;
		for (umbhq = 71; umbhq > 0; umbhq--) {
			continue;
		}
	}
	if (21667 != 21667) {
		int ctaphnvy;
		for (ctaphnvy = 25; ctaphnvy > 0; ctaphnvy--) {
			continue;
		}
	}
	if (32729 == 32729) {
		int std;
		for (std = 42; std > 0; std--) {
			continue;
		}
	}
	if (21667 != 21667) {
		int pcwfnmpog;
		for (pcwfnmpog = 88; pcwfnmpog > 0; pcwfnmpog--) {
			continue;
		}
	}
	if (32729 == 32729) {
		int wscyccizce;
		for (wscyccizce = 34; wscyccizce > 0; wscyccizce--) {
			continue;
		}
	}
	return string("");
}

void imxbwaq::yvbvhuvscawnzknx(int kludxvjgom, string hdjfvsgpd, int wstuzuxxbzemqak, bool xbncepahm) {
	bool pbgnhxf = true;
	string zzjtjvkmkz = "ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf";
	if (true != true) {
		int dgoahvnzhr;
		for (dgoahvnzhr = 8; dgoahvnzhr > 0; dgoahvnzhr--) {
			continue;
		}
	}
	if (string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf") == string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf")) {
		int vdyffqwi;
		for (vdyffqwi = 31; vdyffqwi > 0; vdyffqwi--) {
			continue;
		}
	}
	if (string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf") == string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf")) {
		int hzr;
		for (hzr = 81; hzr > 0; hzr--) {
			continue;
		}
	}
	if (string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf") == string("ankitjxdkwgnhidymzhepsjlrdtkknxqjumkdyzhudnkmualvcoillsreascsjhuhphnuf")) {
		int pzfhmqhn;
		for (pzfhmqhn = 67; pzfhmqhn > 0; pzfhmqhn--) {
			continue;
		}
	}
	if (true == true) {
		int keqelp;
		for (keqelp = 33; keqelp > 0; keqelp--) {
			continue;
		}
	}

}

double imxbwaq::ixzcklmlticsfbjpjrykmbir() {
	double kywgtntmhozihx = 39135;
	if (39135 == 39135) {
		int jsrq;
		for (jsrq = 28; jsrq > 0; jsrq--) {
			continue;
		}
	}
	return 93886;
}

bool imxbwaq::wxctlfhjii(string cmpgfdccwa, double mlekjolagvpare, bool gkkrgnioh, bool vxdcodi, double pejdwc, string zrewogeihwlciq, string loqye, int shfwobwekn, double bofakbva) {
	string eadbedgrytsd = "lyjvbswmhpgwsehweytfdsycroeldkpzffiuehnhmsowqwizq";
	double vyeqxotffducp = 994;
	int vkylo = 6030;
	int xhzzwknmwqnbnc = 409;
	bool ehxetfb = false;
	string zjdwfylfezblfy = "czzhpyloucfqjjkjrcswilvaieqgtgegigegkymvtymbiikzfjoko";
	if (string("czzhpyloucfqjjkjrcswilvaieqgtgegigegkymvtymbiikzfjoko") != string("czzhpyloucfqjjkjrcswilvaieqgtgegigegkymvtymbiikzfjoko")) {
		int xsavxugro;
		for (xsavxugro = 30; xsavxugro > 0; xsavxugro--) {
			continue;
		}
	}
	if (false != false) {
		int gs;
		for (gs = 86; gs > 0; gs--) {
			continue;
		}
	}
	if (409 != 409) {
		int elidrb;
		for (elidrb = 32; elidrb > 0; elidrb--) {
			continue;
		}
	}
	if (409 == 409) {
		int bbzxqeqeti;
		for (bbzxqeqeti = 33; bbzxqeqeti > 0; bbzxqeqeti--) {
			continue;
		}
	}
	return true;
}

void imxbwaq::oucskxajfecydkb(int dhngnspofol, bool temefzwsunfvwd, string znzho, bool gfodt, bool jjsblyyugaiups, string pzfltntizxiz) {
	bool xgfhtvpq = false;
	string mwzez = "qlzddwixfoqanpjuusnwl";
	string lgjoujemzn = "kmcnhdzwkjdcpxiccamwoyiadealquepsmrdtjxfatzmffxgjssilwslmhqaqjiaisr";
	double wvtqkzcjdustww = 2578;
	bool vitcxnbojhrr = true;
	int jvixxb = 4092;
	if (true != true) {
		int jtzrg;
		for (jtzrg = 44; jtzrg > 0; jtzrg--) {
			continue;
		}
	}
	if (string("qlzddwixfoqanpjuusnwl") == string("qlzddwixfoqanpjuusnwl")) {
		int vmmocnvhx;
		for (vmmocnvhx = 45; vmmocnvhx > 0; vmmocnvhx--) {
			continue;
		}
	}
	if (4092 != 4092) {
		int pnkfnyr;
		for (pnkfnyr = 34; pnkfnyr > 0; pnkfnyr--) {
			continue;
		}
	}
	if (string("qlzddwixfoqanpjuusnwl") != string("qlzddwixfoqanpjuusnwl")) {
		int exl;
		for (exl = 5; exl > 0; exl--) {
			continue;
		}
	}
	if (string("qlzddwixfoqanpjuusnwl") == string("qlzddwixfoqanpjuusnwl")) {
		int mlmhzryh;
		for (mlmhzryh = 66; mlmhzryh > 0; mlmhzryh--) {
			continue;
		}
	}

}

double imxbwaq::fxopmbvfrvelv(double rwfjkugwog, bool lyffiyjahkam, string nnizrtr, double iixzniyph, double xqchwyriwd, bool hvnuazgrtu, double qughknilqthhmuk) {
	bool wybgaidzgw = true;
	double yxbyftvvutxga = 3242;
	string nxhxhgawmvh = "xnymitagdwfegzebunmvsnbvbcavleaieagbmijkvfjlyamtjviutlhlpctz";
	string moybbe = "zqbevnilhhlhtyeegmzmcxrlnihambijqkbfqvenyfblbauttmicfsdtanmrmllctqajjwcsnywohieghgrwuwpo";
	bool vwjagdgporuukdb = true;
	double ovwwdkt = 38443;
	double ccdyxelqfyvfald = 74746;
	string lguauvtnflmylov = "akmjilq";
	if (38443 != 38443) {
		int ap;
		for (ap = 62; ap > 0; ap--) {
			continue;
		}
	}
	return 79320;
}

string imxbwaq::tzzbbgeuramdliyopu(string sqmrggihysua, bool xhxtspxivchple, int rtoyqxyvexpnbia, bool jjvxvynk, int bwdqeryxnbtjic, int tfbuuq, int fhdypkphfjet, bool choblfdmhawizjl) {
	bool ggosnqbmdbawc = true;
	bool xehhbymrydjl = false;
	if (true != true) {
		int iljnm;
		for (iljnm = 42; iljnm > 0; iljnm--) {
			continue;
		}
	}
	if (false == false) {
		int vq;
		for (vq = 32; vq > 0; vq--) {
			continue;
		}
	}
	if (false == false) {
		int tbufdnaa;
		for (tbufdnaa = 31; tbufdnaa > 0; tbufdnaa--) {
			continue;
		}
	}
	if (false == false) {
		int elveg;
		for (elveg = 50; elveg > 0; elveg--) {
			continue;
		}
	}
	if (false == false) {
		int lkuqa;
		for (lkuqa = 26; lkuqa > 0; lkuqa--) {
			continue;
		}
	}
	return string("cxphnqqeshf");
}

bool imxbwaq::hqfsylkaupmzpytlhssxr(string kkudnq, double uapfwairlz, string dojoshkrzjdijxu, double ufrgfnyudktr, int giekvdzeskbjzca, string fsxhzgj, bool kvbuypswdlau) {
	double tgyvcuguu = 29492;
	double qyjjihmsdg = 75473;
	double atkqgtus = 34484;
	int ichpjrzh = 895;
	int qhybcyid = 528;
	bool otmubrzim = false;
	if (75473 == 75473) {
		int hu;
		for (hu = 80; hu > 0; hu--) {
			continue;
		}
	}
	if (75473 != 75473) {
		int kpvak;
		for (kpvak = 91; kpvak > 0; kpvak--) {
			continue;
		}
	}
	if (false != false) {
		int lo;
		for (lo = 2; lo > 0; lo--) {
			continue;
		}
	}
	if (895 != 895) {
		int xsb;
		for (xsb = 96; xsb > 0; xsb--) {
			continue;
		}
	}
	if (75473 == 75473) {
		int xk;
		for (xk = 7; xk > 0; xk--) {
			continue;
		}
	}
	return true;
}

double imxbwaq::omgdimgbncuqmhsbebompyxz(double iuxmzratjmh, double fudgiqxzdzb, string oacqxmjtxfe, bool piohbu) {
	string jacctguca = "uklysomqzxgnorfgqffxnnfaqfwbzjrykwprupjkcgsiundtqkhcuoswvwqbwmvoaijcmbqwfgmyowjs";
	int ssvbnfgqv = 5508;
	int thbqml = 6766;
	int cbhtzr = 654;
	string kqdpuy = "vistvxiqgfrgvmaezjfroxtagvxdgevmnmxmsijebcwsooudjc";
	if (string("uklysomqzxgnorfgqffxnnfaqfwbzjrykwprupjkcgsiundtqkhcuoswvwqbwmvoaijcmbqwfgmyowjs") == string("uklysomqzxgnorfgqffxnnfaqfwbzjrykwprupjkcgsiundtqkhcuoswvwqbwmvoaijcmbqwfgmyowjs")) {
		int wgwyhpcsqi;
		for (wgwyhpcsqi = 46; wgwyhpcsqi > 0; wgwyhpcsqi--) {
			continue;
		}
	}
	return 85929;
}

double imxbwaq::ibiowzyajnssambkcs(int iojhvxrqbdq, bool ruaujcg, int muvwaojt, string kxwlmolsfp, int gtspxgvwboyea, int ejmgc) {
	string pikez = "kuvlcagwbqwvegapuxvmtpzsyxjeppivweitchzjrqvabqiuvddmrvrrzlbmqfffhacgtfaggzpxgmvvevhdrbxouzmkzjxgpkn";
	double atxgycx = 31198;
	bool qbiknoygo = false;
	bool ybaxvcxxikclga = true;
	if (true != true) {
		int lqkundatw;
		for (lqkundatw = 0; lqkundatw > 0; lqkundatw--) {
			continue;
		}
	}
	return 1412;
}

int imxbwaq::kbbohbnpfbkx(int ufzxzuuoz, int bxcnxyych) {
	double hvajls = 8542;
	int xxbaxskhfcd = 2500;
	double tjsjmzrysawkn = 1637;
	double nkzbzxwlpipu = 21088;
	bool omxicbz = false;
	if (8542 == 8542) {
		int wxzveh;
		for (wxzveh = 80; wxzveh > 0; wxzveh--) {
			continue;
		}
	}
	if (1637 == 1637) {
		int zbmm;
		for (zbmm = 21; zbmm > 0; zbmm--) {
			continue;
		}
	}
	if (1637 != 1637) {
		int nyvzgoz;
		for (nyvzgoz = 55; nyvzgoz > 0; nyvzgoz--) {
			continue;
		}
	}
	if (2500 == 2500) {
		int btpmri;
		for (btpmri = 39; btpmri > 0; btpmri--) {
			continue;
		}
	}
	if (false == false) {
		int ouwgs;
		for (ouwgs = 36; ouwgs > 0; ouwgs--) {
			continue;
		}
	}
	return 31468;
}

imxbwaq::imxbwaq() {
	this->oucskxajfecydkb(996, true, string("yjpwgjgaugyqtcuyjxlqnrpvgsbtciiqhwrhzibritxeijnnvvbqvrq"), false, false, string("nifxfkaodxgqyohmocxrfxagl"));
	this->fxopmbvfrvelv(20932, false, string("odnpaidymbmkhwwfpjwuzvfrcqzcabbnpxjgqnjzctrkprmsjpjgdifaxb"), 36092, 68146, false, 13752);
	this->tzzbbgeuramdliyopu(string("ypbryagwsaeulgmkwqwhcsemfydlxamveciueilitadwqjzdacpbkbuefocthfvttudlcwfdkxms"), true, 8539, false, 1770, 1474, 2114, false);
	this->hqfsylkaupmzpytlhssxr(string("ahxshthdrrepgxuozqfqqwfkrnxqpmgnxbqiddbmcinzbhogrcyvxzuxrnlfzqgyqgzefcbooiolgfhznrv"), 67408, string("uybutopupvwjornzeiabxpkskmoaycdtmhesojekehzifonvljpjcdozvpowwzfwauvtkphwwqtcvrzzzgqvxzp"), 9665, 5729, string("zjucqfxm"), true);
	this->omgdimgbncuqmhsbebompyxz(3910, 9585, string("weoiydgrftrommgylrqvimkukfupcdmjuiuqpvqvamtswfgjmnxoioygqjfreji"), false);
	this->ibiowzyajnssambkcs(1136, false, 7068, string("folcgyqkhuzexxdpixbdjqbhlshezveoihivdbglthoaqtvynnmqeiuiwxeeuzlmctjvsudcsmzteemgfhhghajhctkubsh"), 3191, 8193);
	this->kbbohbnpfbkx(8156, 2273);
	this->izbsyyuiiywpu(1276, string("eoccbgdfxjxhsegujvwhkszbjmkhaaeggzijfzjcjrpbasqdccdquyzefwmznajqwmkagbwlfrmljrg"), 361, string("llschvwmvjsrrqpjslxphwwznlkggovsjqvgrwhwhmgqhvkogfarpnphtmeayfqffrbmimtjifohnmwofrjlwu"), 33746, 6545, string("ovpoaezfpqntnkdzwgckubzwhzrtirgpbqqguidrmazvnhufytveqjnvsudsmgmzpp"), 1787, true, true);
	this->yvbvhuvscawnzknx(4702, string("nqvyhumdfbbpshsoawwachiqdicdnilaqfqkcjlqqjwou"), 1561, false);
	this->ixzcklmlticsfbjpjrykmbir();
	this->wxctlfhjii(string("dzrysxnfncpynnoquuvyksdbxkypudhtexhkaxvqicblnnnllftwweoh"), 40413, true, true, 9707, string("zsrxbwbr"), string("uyzbbtmffgrfsxdoewcekpbonrgbputwtwnlpvocauuomcvsjgnawluwvpjykekqnqxnoyljrsyqwnzvemnuzfrfupblbogmp"), 6058, 34267);
	this->atlvnkzjyqvzrkjjdbviatfj(2214, true, string("fgidgwqbklmmcsuslhiqnphinbddxnsrbwmpgqzwgzwbsirzuk"), string("ovtlvssvlylfbehyzfuanmkitpybhuhzdylolozdgexzsnisygjulsimesdjdwhjvtvjxroawyz"), true, string("sdbp"));
	this->qcvnqbzxkrilcvbtsf(13043, false, 74700, 6921, 31359, true, 3255);
	this->ufoewriixfebkaccktkxnhn(string("hbpkobfblebzpcrosjecweyskfewyhfppvhzpsqoriersioactgjjismkiftwazcltmimtpzknqhxwreavqjniepsjul"));
	this->gcrafgydeljksyvjqbg(9170, string("mevoygucvud"), 13138, string("curgwipbzysuwhipfxeqczvjjyswmnukmanggjbvhmyvfgaqexsslmhcllmezzmzoclulyqgqyswnbv"), 54190);
	this->pkfpczfzcf(7142, true, 52409, 437, 245);
	this->omxjpxetxl(true, 3126, 7352);
	this->acmdfsbylqmeoz();
	this->mfgmqxcgreqxozcgkxakcygj(false, false, string("xgsxoxxzbtyoezytuwzekghvvsbfumdtdvkykufxwlnpazfxmwxuoyrxqpcbirejrooozzorbwzwoakcpbhllmwssni"), string("ooflfjocemqukgpasugmzditfgxcqndaftrhzabhlhgqhnarlzvaqfoduvxvzsddginboafbelalglpe"), 41245, string("mdzxeubfuwsjwcjwqjevuoqdyfocsatiaatnfijsffygljxtiuhldgwqbakyixmoguvqnufeevidglpkppnqfmjjhwwsnlhsrcm"), string("piwvciiodtikmvzqjfybdojobienqochswcbpkxiwgrmzdmfiiycvyydricu"));
	this->unvqobzqqteedimx(string("bowozwuskuiuohrjvgwtnsqleyrionzlttrbpluvyddmnsmnbbgztgv"), false, 1907, 3112, string("onogsapyyrgusu"), string("bcagdefmeernhoscyvdm"), string("xdkywiofnguxbbutcuyvxhdfkqnlhdop"), string("ouryfburxxuaejuazdfbuylnngcjrpqjymhxpwbthtxtcvuicmqjx"));
	this->ouvccymdlqqtenv();
}
