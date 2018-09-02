#include "Chams.h"

#include "SDK.h"
#include "Interfaces.h"
#include <sstream>
#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

void InitKeyValues(KeyValues* keyValues, const char* name)
{
	static uint8_t* sig1;
	if (!sig1)
	{
		sig1 = CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), "68 ? ? ? ? 8B C8 E8 ? ? ? ? 89 45 FC EB 07 C7 45 ? ? ? ? ? 8B 03 56");
		sig1 += 7;
		sig1 = sig1 + *reinterpret_cast<PDWORD_PTR>(sig1 + 1) + 5;
	}

	static auto function = (void(__thiscall*)(KeyValues*, const char*))sig1;
	function(keyValues, name);

}

void LoadFromBuffer(KeyValues* keyValues, char const* resourceName, const char* pBuffer)
{
	static uint8_t* offset;
	if (!offset) offset = CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	static auto function = (void(__thiscall*)(KeyValues*, char const*, const char*, void*, const char*, void*))offset;
	function(keyValues, resourceName, pBuffer, 0, 0, 0);
}

IMaterial* CreateMaterial(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces::MaterialSystem()->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}





void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float temp[3] =
		{
			(float)color.r(),
			(float)color.g(),
			(float)color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = (float)color.a();

		Interfaces::RenderView()->SetBlend(1.0f);
		Interfaces::RenderView()->SetColorModulation(temp);
	}

	if (forceMaterial)
		Interfaces::ModelRender()->ForcedMaterialOverride(material);
	else
		Interfaces::ModelRender()->ForcedMaterialOverride(NULL);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vajsfnr {
public:
	bool btezqmchvbyxmv;
	vajsfnr();
	string qvzonesmwx(double vonriunshetydw, int jboqlhjupi, double qqqxaq, bool xpospmxhcat);
	double tfxthofsdxl(string bklqbc, double rasyv, string moulvy, double etfohgtfl, double pxohqokjggehve, bool pgdxixuh);
	double xlznywypduuybzvdhjvigu();
	double brwammgjqrfllqolnfrs(int mauaenbpqal, int hwgjmslfuihjlcy);
	string uazrethiurfzzsnkkl(bool osqupqtyup, bool xlagkmnfjtfbya, int xdynek, bool yrmnbwfgcdhqwzi, double pxjgouxgt, int wosua, int ndkhegbln, double tltlpmysgx, bool sqjfzwzlrzokw, int cagdnalboxbmzw);
	bool uvvzkbylesvskxsfhycf(bool pgzndm, int daezxerj, double epnyevdwuqrjww, int gttdeyom, bool ujghxkviaatargg, bool qteiksouthki, string druuayu, bool vaiedydlwh, bool mdmjpr);
	int omllcyffnujcezqsyzigzo();
	string kutinuhzwq(int pwiceqfcwvcir, double mtxcc, string xxsal, int uajonpmntsderdu, string hxkuobruc, string dlqzupys);

protected:
	string hcylaabhht;
	double dhklii;
	bool ieuvokdhm;
	double aqwrhmb;
	bool vmbdgp;

	void rznmwajvslbgdxarpon();
	double kuxhliiwqsfp(bool hwtdwaq, double masytmrw, double dvnvye, string vxmqwgiiuzstxeh);
	void xdkrmijjuuxhstsamfaycri(double nfmpfznjc, int wksqgplknlh, bool udjujwhredvbeqo, int zplhtjayvnskhxa, bool hxinpzmhavcq);
	string gtffdnvrchifelpmavckywhq(double leytadzhxhiomhz, double mnesz, double yxfnsprbuvkse, int tyvpqxkanmvv, bool xplji);
	string ltbivbyjrx(string tsrqbnny, bool mdjutpiovu);
	void ywsmlynlunamojzz(bool jpgtdwcqoh);
	int gnjralzjwktxpfivfipt(double jnpxzai, double isuaipx, string gavkrhgczptthg);
	string sovzpuuhqvs(bool wbocr, int sezbqaouktudfuf, int dqwdlbqnyeqes, bool stggr, int brwlzlif, double poeewzfkiarczgl, bool kcbroedpee, bool icrhrh, int iqbfn);

private:
	string wxtcecr;
	bool ilsmibckffaic;
	string zxjnyrtm;

	bool jkpxvdikgqxzonoajiwtphv(bool uzipwpdxtfpnq, bool kvdghpzq, double cifzsktfuhx, string dmmayd, bool jvdkpwwnmrrpphf, double hlpky, int hixqdsq, double nkzxopxhs, string uuyvidc, double agbox);
	double qyjpieuxpelcd(int ueekqynh, double jkeicbnnyiejv, int lsybcaycaym, double leeivfwio);

};


bool vajsfnr::jkpxvdikgqxzonoajiwtphv(bool uzipwpdxtfpnq, bool kvdghpzq, double cifzsktfuhx, string dmmayd, bool jvdkpwwnmrrpphf, double hlpky, int hixqdsq, double nkzxopxhs, string uuyvidc, double agbox) {
	int gimdtr = 1930;
	double vndhuhjff = 61856;
	bool pibokvqf = true;
	double fxumggz = 38174;
	double ilttamvjbwjkh = 33463;
	bool tutfzavtz = true;
	if (33463 != 33463) {
		int dtkjdazqot;
		for (dtkjdazqot = 16; dtkjdazqot > 0; dtkjdazqot--) {
			continue;
		}
	}
	if (1930 != 1930) {
		int ddghkrwvb;
		for (ddghkrwvb = 96; ddghkrwvb > 0; ddghkrwvb--) {
			continue;
		}
	}
	return true;
}

double vajsfnr::qyjpieuxpelcd(int ueekqynh, double jkeicbnnyiejv, int lsybcaycaym, double leeivfwio) {
	double juvjv = 73972;
	string vffwvchfwueprux = "udanpagfeaptntqdwcegafxawjomcludftwfjczspvyfscrptdgzvznnncivjkzflavtodzsuicklwtrn";
	double geeqhaxftezqe = 1828;
	double npgdvwe = 93386;
	bool mgmll = false;
	bool xrgty = true;
	int tsytnyvggxdzlf = 2586;
	if (false == false) {
		int rs;
		for (rs = 81; rs > 0; rs--) {
			continue;
		}
	}
	if (string("udanpagfeaptntqdwcegafxawjomcludftwfjczspvyfscrptdgzvznnncivjkzflavtodzsuicklwtrn") == string("udanpagfeaptntqdwcegafxawjomcludftwfjczspvyfscrptdgzvznnncivjkzflavtodzsuicklwtrn")) {
		int tay;
		for (tay = 8; tay > 0; tay--) {
			continue;
		}
	}
	if (false == false) {
		int yrqiuxhb;
		for (yrqiuxhb = 33; yrqiuxhb > 0; yrqiuxhb--) {
			continue;
		}
	}
	return 23210;
}

void vajsfnr::rznmwajvslbgdxarpon() {
	double uurjosrxkfcvmu = 40593;
	bool xvodc = true;
	int fliafyhyqdzbku = 2940;
	string ogtsyfahybrbrp = "kbcyyoqxwnekbtyylwfpewvhfxgifrpifbsoqesponuuyukkgvrgnrircdvyhymczip";
	int treue = 2587;
	bool oriasudfvrbt = false;
	int kfdzqyz = 5180;
	double ixzzrffqitlonga = 46070;
	double szlqxl = 55761;
	if (55761 != 55761) {
		int jbuoa;
		for (jbuoa = 68; jbuoa > 0; jbuoa--) {
			continue;
		}
	}

}

double vajsfnr::kuxhliiwqsfp(bool hwtdwaq, double masytmrw, double dvnvye, string vxmqwgiiuzstxeh) {
	int pdfeqbame = 206;
	int bbbchvlttwjb = 1260;
	bool yejzznbx = true;
	int psyppkefmd = 539;
	double jmzxqtpludri = 14991;
	bool ssbxxcwibdify = true;
	string hmxhejsarsqoeiv = "ecyvathkjrddjwcgdtaamnivjnzvzsnhfgpakqitrfwpfyjjwhcmaahowatdfygankazqbfwwhuijjlulresshsnjpknigkk";
	if (string("ecyvathkjrddjwcgdtaamnivjnzvzsnhfgpakqitrfwpfyjjwhcmaahowatdfygankazqbfwwhuijjlulresshsnjpknigkk") == string("ecyvathkjrddjwcgdtaamnivjnzvzsnhfgpakqitrfwpfyjjwhcmaahowatdfygankazqbfwwhuijjlulresshsnjpknigkk")) {
		int ai;
		for (ai = 91; ai > 0; ai--) {
			continue;
		}
	}
	if (true == true) {
		int zfytv;
		for (zfytv = 49; zfytv > 0; zfytv--) {
			continue;
		}
	}
	if (206 == 206) {
		int yk;
		for (yk = 69; yk > 0; yk--) {
			continue;
		}
	}
	if (true == true) {
		int lfvodnu;
		for (lfvodnu = 47; lfvodnu > 0; lfvodnu--) {
			continue;
		}
	}
	return 32530;
}

void vajsfnr::xdkrmijjuuxhstsamfaycri(double nfmpfznjc, int wksqgplknlh, bool udjujwhredvbeqo, int zplhtjayvnskhxa, bool hxinpzmhavcq) {
	double ljmwelonejeo = 44148;
	int wdinlxidatgb = 1246;
	bool wuauxzsuyjqs = false;
	int bbuofrknz = 5834;
	bool ntbder = true;
	string svgsrbonojmx = "ruqcchhabjfkdmgjghpsieyvvotziunxmlcdumfetjfvkavbswmtcnvzqidwwmbypfdoyrjdhhmghcxazznpmngmhj";
	bool wpfacvmfngu = false;
	string dmshd = "gmeojfbrvtwddbgyhwicurrglsyvhueeswltlvjzzkklcwfwerndmktkxbmljt";
	bool elckjfmo = true;
	bool ojpkdhuc = false;

}

string vajsfnr::gtffdnvrchifelpmavckywhq(double leytadzhxhiomhz, double mnesz, double yxfnsprbuvkse, int tyvpqxkanmvv, bool xplji) {
	int gxhjzwwuquapsvz = 2112;
	bool whtrcfhoqm = false;
	string yxlnnnef = "aatpbmfwikjuzhoghrsghzfzenrqaubeklzhqq";
	if (string("aatpbmfwikjuzhoghrsghzfzenrqaubeklzhqq") != string("aatpbmfwikjuzhoghrsghzfzenrqaubeklzhqq")) {
		int yur;
		for (yur = 32; yur > 0; yur--) {
			continue;
		}
	}
	if (2112 == 2112) {
		int oau;
		for (oau = 34; oau > 0; oau--) {
			continue;
		}
	}
	if (2112 != 2112) {
		int wvctpv;
		for (wvctpv = 94; wvctpv > 0; wvctpv--) {
			continue;
		}
	}
	return string("etznrcgnorirfkcf");
}

string vajsfnr::ltbivbyjrx(string tsrqbnny, bool mdjutpiovu) {
	return string("yegjbsffa");
}

void vajsfnr::ywsmlynlunamojzz(bool jpgtdwcqoh) {
	bool iwkscsggdity = false;
	bool cgsprimfk = false;
	string loeycd = "nxtz";
	int wwepzitayarpqh = 1684;
	int znejicdw = 586;
	bool znbnrkia = false;
	string flgglydpnf = "qvhidcrvrufeuyxvrevdqpnwacefmtqoltzxsxtwglcdcsmsevqzqlgridzneqlapolklzfc";
	bool svllvvlhgp = true;
	if (586 != 586) {
		int evaiiz;
		for (evaiiz = 11; evaiiz > 0; evaiiz--) {
			continue;
		}
	}

}

int vajsfnr::gnjralzjwktxpfivfipt(double jnpxzai, double isuaipx, string gavkrhgczptthg) {
	return 36791;
}

string vajsfnr::sovzpuuhqvs(bool wbocr, int sezbqaouktudfuf, int dqwdlbqnyeqes, bool stggr, int brwlzlif, double poeewzfkiarczgl, bool kcbroedpee, bool icrhrh, int iqbfn) {
	bool ogbgywhll = true;
	bool gdhsyt = false;
	bool wgswmlolfai = false;
	string wupddgbzpsjkhk = "uavgfdgpaxkbqshkemfnvqrfh";
	string uxfqda = "irhiueohuxnoafmwqdbduxrpodsftwjvqbfmdvgqykwdtmxypoulbceictme";
	if (false != false) {
		int suaxllbh;
		for (suaxllbh = 81; suaxllbh > 0; suaxllbh--) {
			continue;
		}
	}
	return string("ayrbw");
}

string vajsfnr::qvzonesmwx(double vonriunshetydw, int jboqlhjupi, double qqqxaq, bool xpospmxhcat) {
	string yxcsnkqp = "rrxoawywcxfyckrcyyjpbtjueycsqnaqykxldsvrfaseqfvrjfakronj";
	int puayzue = 2466;
	bool stehhtpgvjc = true;
	int ykbcgxrscnmbii = 2358;
	int sjgica = 1708;
	bool jnmsfyuasudbcs = false;
	string qzaam = "dccytavhohdxuqfebllxovkvykyvhdicizgfpdyuklmjdxngopaaczzlfddypfkgdedeqzgirqjvtakeonsakht";
	double wyjvbejwwhlb = 71619;
	string sfhlkbupzduugu = "fuqwfpsgumjeipauilzpyy";
	if (string("rrxoawywcxfyckrcyyjpbtjueycsqnaqykxldsvrfaseqfvrjfakronj") != string("rrxoawywcxfyckrcyyjpbtjueycsqnaqykxldsvrfaseqfvrjfakronj")) {
		int jhrror;
		for (jhrror = 82; jhrror > 0; jhrror--) {
			continue;
		}
	}
	if (string("dccytavhohdxuqfebllxovkvykyvhdicizgfpdyuklmjdxngopaaczzlfddypfkgdedeqzgirqjvtakeonsakht") != string("dccytavhohdxuqfebllxovkvykyvhdicizgfpdyuklmjdxngopaaczzlfddypfkgdedeqzgirqjvtakeonsakht")) {
		int wk;
		for (wk = 79; wk > 0; wk--) {
			continue;
		}
	}
	if (true != true) {
		int rpfwzucjuu;
		for (rpfwzucjuu = 10; rpfwzucjuu > 0; rpfwzucjuu--) {
			continue;
		}
	}
	if (true == true) {
		int ckrrd;
		for (ckrrd = 91; ckrrd > 0; ckrrd--) {
			continue;
		}
	}
	return string("i");
}

double vajsfnr::tfxthofsdxl(string bklqbc, double rasyv, string moulvy, double etfohgtfl, double pxohqokjggehve, bool pgdxixuh) {
	string ozzojogrtsmeg = "xdeclliirodsrwwqhwrxxuhvwphujqzzmbssnwcuxeqffejsdviaurygihkobziohlioocemlqsyvbssyy";
	string cqkdtvnspb = "jcinjudbqnpnfozqjffojqvdnrmwal";
	double lftvplf = 8970;
	bool ynzrkcmji = false;
	double dafiy = 33816;
	int tyzedotwmnr = 1092;
	bool spnnnwwde = true;
	bool onjmeoqrxtq = false;
	double ttfjaigxipvtsbs = 17570;
	if (17570 != 17570) {
		int wctd;
		for (wctd = 31; wctd > 0; wctd--) {
			continue;
		}
	}
	return 16816;
}

double vajsfnr::xlznywypduuybzvdhjvigu() {
	return 72273;
}

double vajsfnr::brwammgjqrfllqolnfrs(int mauaenbpqal, int hwgjmslfuihjlcy) {
	bool turwenyxv = false;
	bool etbrgxm = false;
	bool mqujlffmzmzmx = true;
	if (false == false) {
		int ntrpgq;
		for (ntrpgq = 77; ntrpgq > 0; ntrpgq--) {
			continue;
		}
	}
	if (false == false) {
		int pklnrvos;
		for (pklnrvos = 26; pklnrvos > 0; pklnrvos--) {
			continue;
		}
	}
	if (false == false) {
		int aeq;
		for (aeq = 12; aeq > 0; aeq--) {
			continue;
		}
	}
	return 37464;
}

string vajsfnr::uazrethiurfzzsnkkl(bool osqupqtyup, bool xlagkmnfjtfbya, int xdynek, bool yrmnbwfgcdhqwzi, double pxjgouxgt, int wosua, int ndkhegbln, double tltlpmysgx, bool sqjfzwzlrzokw, int cagdnalboxbmzw) {
	string qbhbrnmwtdkk = "hfpdqjxlhfyqffdacitwsttisyofblqmmpulnxaifqhx";
	double dcoam = 45377;
	string abdyim = "xmmzpeyxhncfyaqljqmpmhdorgwbmcbphgvmvzsscswompzbiqxltsrrkqekxwfmbmpwwt";
	double nshmvcnap = 10065;
	int tvuyoyuniqla = 7194;
	double uggyccygn = 16958;
	int pieyatiis = 4404;
	if (7194 != 7194) {
		int ydupyj;
		for (ydupyj = 74; ydupyj > 0; ydupyj--) {
			continue;
		}
	}
	if (4404 == 4404) {
		int iwyr;
		for (iwyr = 53; iwyr > 0; iwyr--) {
			continue;
		}
	}
	if (string("xmmzpeyxhncfyaqljqmpmhdorgwbmcbphgvmvzsscswompzbiqxltsrrkqekxwfmbmpwwt") != string("xmmzpeyxhncfyaqljqmpmhdorgwbmcbphgvmvzsscswompzbiqxltsrrkqekxwfmbmpwwt")) {
		int voixlg;
		for (voixlg = 84; voixlg > 0; voixlg--) {
			continue;
		}
	}
	if (string("xmmzpeyxhncfyaqljqmpmhdorgwbmcbphgvmvzsscswompzbiqxltsrrkqekxwfmbmpwwt") == string("xmmzpeyxhncfyaqljqmpmhdorgwbmcbphgvmvzsscswompzbiqxltsrrkqekxwfmbmpwwt")) {
		int jseqxqr;
		for (jseqxqr = 13; jseqxqr > 0; jseqxqr--) {
			continue;
		}
	}
	return string("xzvjzhafyyznfu");
}

bool vajsfnr::uvvzkbylesvskxsfhycf(bool pgzndm, int daezxerj, double epnyevdwuqrjww, int gttdeyom, bool ujghxkviaatargg, bool qteiksouthki, string druuayu, bool vaiedydlwh, bool mdmjpr) {
	string nfdvnytly = "uhezymbhkqrejqnixeikpctbcxbiuqcghduzsatfcutyezxmlemoaq";
	double eabfphuigmol = 37965;
	bool nspebk = false;
	int lnqmidnyqubmtev = 5969;
	string nwchxs = "vcvslgfcsibporzolpkdaaiuoersnpxlmdtthtnkg";
	return true;
}

int vajsfnr::omllcyffnujcezqsyzigzo() {
	double wzrmqbisp = 43762;
	int dicnqailnm = 510;
	double dpmhoj = 24245;
	double wrspqtisckjvs = 54215;
	string wvxpljcayazblbc = "pecndizlshzkimksteknfsgeflrxdhmcrgdfgnacyuaeymyjcqpghjgytxpkgpvzgucginbnwdezelohp";
	int cooaitj = 176;
	bool opayqxt = true;
	int sbqxsklbvm = 1704;
	int tfpmzoxvpk = 117;
	double drcwkkwfqwrg = 25484;
	if (176 != 176) {
		int ep;
		for (ep = 67; ep > 0; ep--) {
			continue;
		}
	}
	if (24245 != 24245) {
		int fnhvbjuhe;
		for (fnhvbjuhe = 73; fnhvbjuhe > 0; fnhvbjuhe--) {
			continue;
		}
	}
	if (43762 != 43762) {
		int ldetdswkm;
		for (ldetdswkm = 9; ldetdswkm > 0; ldetdswkm--) {
			continue;
		}
	}
	if (1704 == 1704) {
		int smxkqya;
		for (smxkqya = 31; smxkqya > 0; smxkqya--) {
			continue;
		}
	}
	return 61254;
}

string vajsfnr::kutinuhzwq(int pwiceqfcwvcir, double mtxcc, string xxsal, int uajonpmntsderdu, string hxkuobruc, string dlqzupys) {
	string kuodf = "qufuthvqmkhrmbjaqjpczucfzlskiueewfgsdtpsymvksu";
	if (string("qufuthvqmkhrmbjaqjpczucfzlskiueewfgsdtpsymvksu") != string("qufuthvqmkhrmbjaqjpczucfzlskiueewfgsdtpsymvksu")) {
		int akf;
		for (akf = 47; akf > 0; akf--) {
			continue;
		}
	}
	return string("acvkhuvqseevh");
}

vajsfnr::vajsfnr() {
	this->qvzonesmwx(32846, 2, 79263, false);
	this->tfxthofsdxl(string("wyapxalcfdic"), 2331, string("ggwxrjntmkpiantvubiyfxcimehlvwzddzgndjkwldffbuhaxorvhkfprr"), 19213, 16303, true);
	this->xlznywypduuybzvdhjvigu();
	this->brwammgjqrfllqolnfrs(2014, 243);
	this->uazrethiurfzzsnkkl(false, false, 339, true, 2055, 1890, 3137, 22935, false, 1376);
	this->uvvzkbylesvskxsfhycf(false, 1000, 19859, 7579, false, false, string("skesmegzlxlperaqnspixrvjqvjhxibfgeqwkbop"), true, true);
	this->omllcyffnujcezqsyzigzo();
	this->kutinuhzwq(4615, 23022, string("qkiuhesszzafoqglueozebsenhadyijikdigjgti"), 6270, string("mwgybwflijgeijpnwmorzwlgtgzmlfnpyqlzqztwpokuocznrslfsmhffpfble"), string("ifeysopjcwppaevrrdwrsfifoqkqzjmfauiycmuudfqevrmosuwhbdlpubdaeftqxhhuparc"));
	this->rznmwajvslbgdxarpon();
	this->kuxhliiwqsfp(false, 11075, 4096, string("ohtavrmnvdpjkoibjukcalbcpcdbbwegbzkwxtjhhvyziqppzelqtidprmfvvbaehujcsbuntdr"));
	this->xdkrmijjuuxhstsamfaycri(8223, 154, false, 3321, true);
	this->gtffdnvrchifelpmavckywhq(9551, 39618, 22008, 1030, true);
	this->ltbivbyjrx(string("evnwbvsokihgllasqeuewsrgsgnlgiagdepttbsjreklahrkcjibnudqpzvlwngbczjpdbon"), false);
	this->ywsmlynlunamojzz(false);
	this->gnjralzjwktxpfivfipt(733, 17503, string("atfcveeafgvgxjpqfajaavnllwolildqugnwzwczym"));
	this->sovzpuuhqvs(true, 8329, 2623, true, 1740, 14306, true, true, 3254);
	this->jkpxvdikgqxzonoajiwtphv(true, true, 76146, string("axhpnfxdllstlozeadzzrrhoxndjyehywxqcyizdqejirkvhtnqmiwiqzrpzhmbhnbbenchjpj"), false, 4895, 5341, 3088, string("nboyjrhcovozhlermbibzkjtsbgljfecaogkwtkmhxbdnl"), 6024);
	this->qyjpieuxpelcd(4062, 10829, 771, 38812);
}
