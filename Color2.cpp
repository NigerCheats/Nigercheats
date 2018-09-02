#include "Color2.h"

Color2 Color2::Black(0, 0, 0, 255);
Color2 Color2::White(255, 255, 255, 255);
Color2 Color2::Red(255, 0, 0, 255);
Color2 Color2::Green(70, 255, 70, 255);
Color2 Color2::Blue(0, 0, 255, 255);

Color2::Color2()
{
	*((int *)this) = 0;
}
Color2::Color2(int _r, int _g, int _b)
{
	SetColor(_r, _g, _b, 255);
}
Color2::Color2(int _r, int _g, int _b, int _a)
{
	SetColor(_r, _g, _b, _a);
}
void Color2::SetRawColor(int color32)
{
	*((int *)this) = color32;
}
int Color2::GetRawColor() const
{
	return *((int *)this);
}
__inline void Color2::SetColor(int _r, int _g, int _b, int _a)
{
	_CColor[0] = (unsigned char)_r;
	_CColor[1] = (unsigned char)_g;
	_CColor[2] = (unsigned char)_b;
	_CColor[3] = (unsigned char)_a;
}
__inline void Color2::SetColor(float _r, float _g, float _b, float _a)
{
	_CColor[0] = static_cast<unsigned char>(_r * 255.0f);
	_CColor[1] = static_cast<unsigned char>(_g * 255.0f);
	_CColor[2] = static_cast<unsigned char>(_b * 255.0f);
	_CColor[3] = static_cast<unsigned char>(_a * 255.0f);
}
void Color2::SetColor(float* color)
{
	if (!color)
		return;

	_CColor[0] = (unsigned char)(color[0] * 255.f);
	_CColor[1] = (unsigned char)(color[1] * 255.f);
	_CColor[2] = (unsigned char)(color[2] * 255.f);
	_CColor[3] = (unsigned char)(color[3] * 255.f);
}
void Color2::GetColor(int &_r, int &_g, int &_b, int &_a) const
{
	_r = _CColor[0];
	_g = _CColor[1];
	_b = _CColor[2];
	_a = _CColor[3];
}
bool Color2::operator== (const Color2 &rhs) const
{
	return (*((int *)this) == *((int *)&rhs));
}
bool Color2::operator!= (const Color2 &rhs) const
{
	return !(operator==(rhs));
}
Color2& Color2::operator=(const Color2 &rhs)
{
	SetRawColor(rhs.GetRawColor());
	return *this;
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class qnejldc {
public:
	string cssttigz;
	string otjifemn;
	string sdaogtmgt;
	qnejldc();
	string agvxviqyrhf(bool ykjkzz, string prwhjaugkkb, string hmiiyanrkswri, double toiuhyihkik, int yonatzpkdhxby, int dsipsca, string vmojezkqcdpf, double zxwfp, string kihqashahpcrwe);
	int dxgkdiujfnwrvkzv(bool nbxkkndyiijmf, double uyjdoblhw, double mqiwu, string lnausgbscv, string dfojqaulkmx, bool zwntkwxthdosr, int ibcmobhdcpbhwio);
	void bhjcfaycbdbrphtdlpbcplsud(double bjrgzhjxmsnusje, bool akodtdlz, double ixgpnhhoxrrzfq, bool bfdcnjcawcewfh, int hixropqfj);
	bool lcawcazfjrucncpgit(bool ncrtvkmysljwd, double pszurr, double omgwdicqqaxgnew, double aywlkranotbqi, double cvaamk, string ytwfrd, int xafzyazwdkrgy, bool nkbfgy);
	bool yllfnsevrudzyizsxhhkpnkq(bool rvfkddvpp, double ebmxxjppzbs, double mauuijes, double ucsqizxpmfedkaj, int ehwcljqnof, string iskzmnguxbvdjb, string temrukshjz, int rhxxni, bool qnvdlq);
	bool zdenkslnwabsbhiftwhwvxknr(int ihunsimhmrl, int byddswhwdozj);
	bool pkjofvxsnlvwxuhqw(int icapoxn, int jlzac, double kwjpjcanynwx, bool szuleoevzimhuc, int nbkvcujddocbjc, double hlgvgwpeojndpf, bool sglidusiy, string cshptdp);

protected:
	double qwtujbptmv;
	bool knmawrfkxxc;
	bool jmvjltrgxuh;
	int gfdnuvwlad;
	double irrol;

	string prarnvmojjgs(double ltcefluxjxzytax, string brywukeptppsgll, string recyelguuulnk, bool uppblvmsuayenou, bool pzmujzbl, double gkrzac, double cqqhaokamfrzo);
	string kddndurfworqrtyibglf(int qreblu, double wgekdwnz, int atpqmeootqnqi, bool lpoojqaqtzvbgq, string sittt, string jwredwi);
	int mzhcggzbpxaoczxfrzmx(string mosuqp, string wuiqibyqxse);
	double zcjcfnwrwkjg(string raqzyrnxpv, int iorhqfphfj, string pbtlxfnpbi, int aevenvidwwnp, string damldlhqgbmm, double ssqfciztwgv, int cnwcricixiz, string quttoiur, int vbopwcerufmanm, string jasrh);
	void eoloriimdgbn(int qkpmhmeeng);
	bool stueilatoxjbd(bool rhlvkiobujtmf, int aafnowcudrd, int unknphkbbl, double vhajnxyypxnjc, bool rszkeza, int ssfjjdxq);
	double himvtgcaqj(double xxnhvbzrakegm, int eqrzdnfikwmxdqk, bool goipsrtaixomoin, double adpnus, bool xezanennoqpev, int ergqvm, string eummrdtf);
	void udoyedduhwfhzywpikgyq(string zlbkltdae, int aksnelsv, double xlepxuchisxflg, double vescvqupkihug, string ghsxouxdyna, double gjyrmyp, double dusajsuxdxrzb, string jikkcnuxsh, bool swsgvcr);

private:
	string ougkoareip;
	double dcoabqwd;
	string qnuvsfvi;
	double jzrahanwhsl;

	void kgjxtvzkighkr();
	double xarylwcojnmbka(string ghtqsge, int hevkputzetxc, double rijhpjvrcncjbc, double nwdmspelf, double wedsqkmwtywqp, double lgpgad, bool idebi, bool wctcmiwjzbtu);
	double zmnekvgjlpijfisbkrjif(bool xjdbovrl, string glkcuwzpswscio);
	double dfevkelpqzgeyx(string xtfgvtyszcwg, int yzpyscbesudewk, bool xafanxe, string ixqmmwlacfec, string wgqazq, string yvjozkmxjjcubj);
	string hhhiylxidfigsekuoildya(string alnrajbtnd);
	bool txzjhkmvun(bool likfbptac, double cfhlte, bool mkdigcilozhh, int znqrxw, bool clifmsofcnv, bool xcxllclyatkrs, double gzukbewamyud, int hgsuvrciwcsdu, double ywpyof);

};


void qnejldc::kgjxtvzkighkr() {
	string qylshnlowx = "shrrrhaapayvqcxexpjjipohaqabadsgczxsjhjodphvhuhkqkp";
	double qxcofaklduad = 10907;
	bool tylmvwzjmjeyfy = true;

}

double qnejldc::xarylwcojnmbka(string ghtqsge, int hevkputzetxc, double rijhpjvrcncjbc, double nwdmspelf, double wedsqkmwtywqp, double lgpgad, bool idebi, bool wctcmiwjzbtu) {
	int wbagsnqz = 711;
	double oczzkjvit = 69270;
	string endlleqaufez = "ayncvsqhlmqeolvefozkvtqyvwfrmxloorphjzlbwybffsdgasjfmftydbkizn";
	string cmdlfihtz = "xulkvgjmimnbynieihfwhobslbkrcqyhhydpexzpnzjd";
	string mcerkobflio = "onatvizhpkcyyfbxhqdtzhjdummgfkkjvykkcqkofcprjemizzqxpccgqdmewphbrkevhoms";
	if (string("xulkvgjmimnbynieihfwhobslbkrcqyhhydpexzpnzjd") != string("xulkvgjmimnbynieihfwhobslbkrcqyhhydpexzpnzjd")) {
		int bnjsy;
		for (bnjsy = 18; bnjsy > 0; bnjsy--) {
			continue;
		}
	}
	if (string("xulkvgjmimnbynieihfwhobslbkrcqyhhydpexzpnzjd") == string("xulkvgjmimnbynieihfwhobslbkrcqyhhydpexzpnzjd")) {
		int dq;
		for (dq = 76; dq > 0; dq--) {
			continue;
		}
	}
	return 46227;
}

double qnejldc::zmnekvgjlpijfisbkrjif(bool xjdbovrl, string glkcuwzpswscio) {
	double hgyhlbdxwwakd = 21484;
	string hoivfmhu = "cufznpjxwnhvjaophemmszcqxkuojxalmfrmhmwkwhkklwquayidp";
	string blddrfaq = "qsmvzisepmovtydpvtmcpdpn";
	int wxegok = 4802;
	if (21484 == 21484) {
		int rypweflaw;
		for (rypweflaw = 0; rypweflaw > 0; rypweflaw--) {
			continue;
		}
	}
	return 23033;
}

double qnejldc::dfevkelpqzgeyx(string xtfgvtyszcwg, int yzpyscbesudewk, bool xafanxe, string ixqmmwlacfec, string wgqazq, string yvjozkmxjjcubj) {
	int zvgbuwjsnsuz = 3775;
	double gcxqw = 1057;
	double bzwiaujdzlzfso = 26017;
	string axjntcoqswcsqho = "bqnhdwnnoorxcdqpmqsygftoywdlmmbjstjvbxuvmpgumiinamrrvwvyrjyrrcekxitkydagrvanwczlkfuouxdlg";
	if (26017 != 26017) {
		int xnd;
		for (xnd = 4; xnd > 0; xnd--) {
			continue;
		}
	}
	if (3775 == 3775) {
		int sedhfhdrv;
		for (sedhfhdrv = 20; sedhfhdrv > 0; sedhfhdrv--) {
			continue;
		}
	}
	if (1057 != 1057) {
		int jdhiniw;
		for (jdhiniw = 83; jdhiniw > 0; jdhiniw--) {
			continue;
		}
	}
	return 54763;
}

string qnejldc::hhhiylxidfigsekuoildya(string alnrajbtnd) {
	int upauf = 3321;
	string hmwnpoqwhirmov = "ihqgu";
	int igszstrrj = 3060;
	double ykduoc = 5141;
	if (3321 == 3321) {
		int rrzfcsuygx;
		for (rrzfcsuygx = 63; rrzfcsuygx > 0; rrzfcsuygx--) {
			continue;
		}
	}
	if (3321 == 3321) {
		int drvqusa;
		for (drvqusa = 63; drvqusa > 0; drvqusa--) {
			continue;
		}
	}
	return string("apz");
}

bool qnejldc::txzjhkmvun(bool likfbptac, double cfhlte, bool mkdigcilozhh, int znqrxw, bool clifmsofcnv, bool xcxllclyatkrs, double gzukbewamyud, int hgsuvrciwcsdu, double ywpyof) {
	bool gtvvubrhdcnu = true;
	return true;
}

string qnejldc::prarnvmojjgs(double ltcefluxjxzytax, string brywukeptppsgll, string recyelguuulnk, bool uppblvmsuayenou, bool pzmujzbl, double gkrzac, double cqqhaokamfrzo) {
	string ugmork = "uqrhuhbyhmucynwlmytlkamsmliduzhnuctjmyvgasoeotsryqwytjpgosypprvp";
	string vbjsytdfu = "iskteualnjouhyelfhhqpwwoktwjfdpjhaekktleteyivgnqgzumozozltusnywntlotfbvmdhebvmjig";
	int yzfcoymq = 1671;
	int vcgyzhofnz = 2615;
	int bsxsl = 1442;
	string zaciyay = "ldhjvbrqvdbavjktslgsnxqzlbzecsmejpamby";
	int rzlgdyjph = 7120;
	string hroixg = "rrjbnxrzrldaymuzfzsg";
	string cilvcxm = "mhbpsaajrkonpiootuwjcckwo";
	if (string("ldhjvbrqvdbavjktslgsnxqzlbzecsmejpamby") == string("ldhjvbrqvdbavjktslgsnxqzlbzecsmejpamby")) {
		int tfz;
		for (tfz = 46; tfz > 0; tfz--) {
			continue;
		}
	}
	if (2615 != 2615) {
		int jrpluiazzz;
		for (jrpluiazzz = 84; jrpluiazzz > 0; jrpluiazzz--) {
			continue;
		}
	}
	return string("gkk");
}

string qnejldc::kddndurfworqrtyibglf(int qreblu, double wgekdwnz, int atpqmeootqnqi, bool lpoojqaqtzvbgq, string sittt, string jwredwi) {
	return string("zhniyqxynpri");
}

int qnejldc::mzhcggzbpxaoczxfrzmx(string mosuqp, string wuiqibyqxse) {
	bool hdmlyi = true;
	bool reqsaa = true;
	double xnuwaaebhtjjbr = 7593;
	double wiofblbloyoer = 36719;
	int tdehgfqz = 3996;
	int ldksxk = 3195;
	double igtxoi = 8400;
	bool xpuewczgde = false;
	bool ldnvyf = false;
	string skabfpgogkxs = "ulgboarkipesjbbrytnhaqgczpalhkheqrdeqjdnbwqmxnfdexvsgnuwbotmkabrtwhbvlktqbvfboypzwiiiozmfarodz";
	if (3195 == 3195) {
		int vewivaufj;
		for (vewivaufj = 81; vewivaufj > 0; vewivaufj--) {
			continue;
		}
	}
	return 59157;
}

double qnejldc::zcjcfnwrwkjg(string raqzyrnxpv, int iorhqfphfj, string pbtlxfnpbi, int aevenvidwwnp, string damldlhqgbmm, double ssqfciztwgv, int cnwcricixiz, string quttoiur, int vbopwcerufmanm, string jasrh) {
	double ssxdfueiwqgtomy = 41736;
	int nbycdxjgigqf = 4120;
	string iqjdwmdsuydxhv = "pwjidcmh";
	double dvlcq = 4131;
	int nucgnxexde = 4786;
	bool xzhhlzyg = false;
	double buvtrkyhrpcj = 12244;
	double uaelcujpkai = 4527;
	string qzvqizya = "ttcifwl";
	if (4786 == 4786) {
		int tc;
		for (tc = 61; tc > 0; tc--) {
			continue;
		}
	}
	if (4786 == 4786) {
		int ik;
		for (ik = 58; ik > 0; ik--) {
			continue;
		}
	}
	if (4527 != 4527) {
		int xmfwt;
		for (xmfwt = 34; xmfwt > 0; xmfwt--) {
			continue;
		}
	}
	if (12244 == 12244) {
		int oid;
		for (oid = 99; oid > 0; oid--) {
			continue;
		}
	}
	return 45143;
}

void qnejldc::eoloriimdgbn(int qkpmhmeeng) {
	double mvqmrcdi = 833;
	bool dchrpdivvtwbobk = true;
	if (true == true) {
		int lqxqnuf;
		for (lqxqnuf = 17; lqxqnuf > 0; lqxqnuf--) {
			continue;
		}
	}
	if (true != true) {
		int tas;
		for (tas = 19; tas > 0; tas--) {
			continue;
		}
	}
	if (833 != 833) {
		int bif;
		for (bif = 58; bif > 0; bif--) {
			continue;
		}
	}
	if (true != true) {
		int xojpfk;
		for (xojpfk = 57; xojpfk > 0; xojpfk--) {
			continue;
		}
	}

}

bool qnejldc::stueilatoxjbd(bool rhlvkiobujtmf, int aafnowcudrd, int unknphkbbl, double vhajnxyypxnjc, bool rszkeza, int ssfjjdxq) {
	return false;
}

double qnejldc::himvtgcaqj(double xxnhvbzrakegm, int eqrzdnfikwmxdqk, bool goipsrtaixomoin, double adpnus, bool xezanennoqpev, int ergqvm, string eummrdtf) {
	double anvjj = 33296;
	string jlrsvofkwgm = "kvgletzhyg";
	string jwyjlzpaqauoi = "cwkwiyofkcwsgnukbqurfkwhyowqjnonltu";
	int prnsvpkqbrpu = 5192;
	string yvcwedsqcsowp = "pshewcvbylhokmtyrtejfpk";
	bool pjijsi = true;
	int gtpjloeq = 296;
	if (33296 != 33296) {
		int lfsivr;
		for (lfsivr = 94; lfsivr > 0; lfsivr--) {
			continue;
		}
	}
	if (5192 != 5192) {
		int vsuglmcqaz;
		for (vsuglmcqaz = 25; vsuglmcqaz > 0; vsuglmcqaz--) {
			continue;
		}
	}
	if (true == true) {
		int jxifw;
		for (jxifw = 2; jxifw > 0; jxifw--) {
			continue;
		}
	}
	if (string("kvgletzhyg") != string("kvgletzhyg")) {
		int pmmwxr;
		for (pmmwxr = 61; pmmwxr > 0; pmmwxr--) {
			continue;
		}
	}
	if (string("cwkwiyofkcwsgnukbqurfkwhyowqjnonltu") != string("cwkwiyofkcwsgnukbqurfkwhyowqjnonltu")) {
		int fnofejxbl;
		for (fnofejxbl = 70; fnofejxbl > 0; fnofejxbl--) {
			continue;
		}
	}
	return 53581;
}

void qnejldc::udoyedduhwfhzywpikgyq(string zlbkltdae, int aksnelsv, double xlepxuchisxflg, double vescvqupkihug, string ghsxouxdyna, double gjyrmyp, double dusajsuxdxrzb, string jikkcnuxsh, bool swsgvcr) {
	int dscjr = 2182;
	string pglumn = "pcrafeoohjptwyux";
	bool ylwrzu = true;
	string tuuazhuxgmcmsj = "tjsfxozwhjukvuznabehhapkrjiwpujcbrbpbalsdtnwlcqcxsjstgsnfopmempmle";
	string vtsfjjgwtjqp = "txmdtdavwtvhsqudbeikrpzlipthofxpfvojjigfugvhpgzbmgpjxjxrlovdvkgfkdwnlggqfpvvturcvawlpsodjlcgnnafh";
	int lfdcbqww = 1654;
	double txezor = 2712;
	int wvptjhyo = 5854;
	if (5854 != 5854) {
		int rlacfgkqs;
		for (rlacfgkqs = 93; rlacfgkqs > 0; rlacfgkqs--) {
			continue;
		}
	}
	if (1654 != 1654) {
		int ru;
		for (ru = 34; ru > 0; ru--) {
			continue;
		}
	}
	if (string("txmdtdavwtvhsqudbeikrpzlipthofxpfvojjigfugvhpgzbmgpjxjxrlovdvkgfkdwnlggqfpvvturcvawlpsodjlcgnnafh") == string("txmdtdavwtvhsqudbeikrpzlipthofxpfvojjigfugvhpgzbmgpjxjxrlovdvkgfkdwnlggqfpvvturcvawlpsodjlcgnnafh")) {
		int jlaymxt;
		for (jlaymxt = 89; jlaymxt > 0; jlaymxt--) {
			continue;
		}
	}
	if (string("tjsfxozwhjukvuznabehhapkrjiwpujcbrbpbalsdtnwlcqcxsjstgsnfopmempmle") != string("tjsfxozwhjukvuznabehhapkrjiwpujcbrbpbalsdtnwlcqcxsjstgsnfopmempmle")) {
		int krzghb;
		for (krzghb = 87; krzghb > 0; krzghb--) {
			continue;
		}
	}

}

string qnejldc::agvxviqyrhf(bool ykjkzz, string prwhjaugkkb, string hmiiyanrkswri, double toiuhyihkik, int yonatzpkdhxby, int dsipsca, string vmojezkqcdpf, double zxwfp, string kihqashahpcrwe) {
	string xwubehdfunqflck = "gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm";
	string hkptznwijuy = "yjighgwixqtfadiydouyftbxqipfcdqcn";
	if (string("yjighgwixqtfadiydouyftbxqipfcdqcn") != string("yjighgwixqtfadiydouyftbxqipfcdqcn")) {
		int lnaf;
		for (lnaf = 85; lnaf > 0; lnaf--) {
			continue;
		}
	}
	if (string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm") != string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm")) {
		int humjfbo;
		for (humjfbo = 92; humjfbo > 0; humjfbo--) {
			continue;
		}
	}
	if (string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm") != string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm")) {
		int bqohltcg;
		for (bqohltcg = 10; bqohltcg > 0; bqohltcg--) {
			continue;
		}
	}
	if (string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm") == string("gzgwyvvehqdeedrcnoxenvjhknoywpmxhffedxyxoyfhixhxjygqolquqvlmchm")) {
		int kikaek;
		for (kikaek = 99; kikaek > 0; kikaek--) {
			continue;
		}
	}
	return string("kadhmubwwpmoac");
}

int qnejldc::dxgkdiujfnwrvkzv(bool nbxkkndyiijmf, double uyjdoblhw, double mqiwu, string lnausgbscv, string dfojqaulkmx, bool zwntkwxthdosr, int ibcmobhdcpbhwio) {
	bool sorjh = true;
	int voqzpogbeos = 3194;
	bool omradc = false;
	int tosvqo = 2852;
	double uyfawpvvael = 24582;
	if (true != true) {
		int gekkyfjbrb;
		for (gekkyfjbrb = 84; gekkyfjbrb > 0; gekkyfjbrb--) {
			continue;
		}
	}
	if (24582 == 24582) {
		int jdgsgirszu;
		for (jdgsgirszu = 14; jdgsgirszu > 0; jdgsgirszu--) {
			continue;
		}
	}
	if (24582 != 24582) {
		int dmowqztoc;
		for (dmowqztoc = 80; dmowqztoc > 0; dmowqztoc--) {
			continue;
		}
	}
	if (true == true) {
		int ewlh;
		for (ewlh = 21; ewlh > 0; ewlh--) {
			continue;
		}
	}
	return 4433;
}

void qnejldc::bhjcfaycbdbrphtdlpbcplsud(double bjrgzhjxmsnusje, bool akodtdlz, double ixgpnhhoxrrzfq, bool bfdcnjcawcewfh, int hixropqfj) {
	bool ngloqdiemimu = true;
	double gripyg = 11372;
	string hdchrlpps = "sxstoeqbsazukplbokwivtzcnctuzrqyjiorvtrsohkdtlsgxwwcwfpusaiudrno";
	bool tyzflgzdlwhs = false;
	string wakatz = "tteenkychtmxnkmiafacijhdjgbwvvxlvymwnisvvgzbtadmxpmczsczamvyugszbgztekkcocqhmn";
	string pxgnbqjrtifkd = "gsgnjekcwokpbzliwkffipjwwqxjxleg";
	int blalusjmouoaavp = 536;
	bool qjloliwoesrr = true;

}

bool qnejldc::lcawcazfjrucncpgit(bool ncrtvkmysljwd, double pszurr, double omgwdicqqaxgnew, double aywlkranotbqi, double cvaamk, string ytwfrd, int xafzyazwdkrgy, bool nkbfgy) {
	string pecnvypbxr = "dkeabvndubtqwsgqyinlotlxmpkgupsm";
	bool aprdl = true;
	double iuxtbeukj = 20330;
	string eqysjkteny = "wimmhrgonxyerjhcykvueaunocltmghbhjtguzoktzcofpqgnpipwfy";
	string rmuvgpdgdxvob = "jurpnqvuroqoavluttpfrzdh";
	string hwfzj = "zyngnrcghxjlgzhqmgjtzoimdkxjskxlk";
	if (string("dkeabvndubtqwsgqyinlotlxmpkgupsm") == string("dkeabvndubtqwsgqyinlotlxmpkgupsm")) {
		int tid;
		for (tid = 42; tid > 0; tid--) {
			continue;
		}
	}
	if (string("zyngnrcghxjlgzhqmgjtzoimdkxjskxlk") == string("zyngnrcghxjlgzhqmgjtzoimdkxjskxlk")) {
		int efg;
		for (efg = 60; efg > 0; efg--) {
			continue;
		}
	}
	if (20330 != 20330) {
		int krkrn;
		for (krkrn = 100; krkrn > 0; krkrn--) {
			continue;
		}
	}
	return true;
}

bool qnejldc::yllfnsevrudzyizsxhhkpnkq(bool rvfkddvpp, double ebmxxjppzbs, double mauuijes, double ucsqizxpmfedkaj, int ehwcljqnof, string iskzmnguxbvdjb, string temrukshjz, int rhxxni, bool qnvdlq) {
	bool tcycyjpq = false;
	string kkyptsnk = "ypyqdglvsqsrmfcroiumzpvgzdyfmweucnkhvehrainuyyhflqymiglqvs";
	bool ohtrpkosqzmhba = false;
	int bmcfdc = 2020;
	bool giqkrofvbzibsxf = false;
	int cinfktkiqc = 5248;
	double iiibtocuva = 8039;
	string hewob = "xgdtepyivomfzdyrxghthlccblwozxuxjktbossuwzvywzthktfmnuphmqadcelpcvubumht";
	double dveos = 46103;
	bool eifsb = false;
	if (8039 == 8039) {
		int pmltp;
		for (pmltp = 85; pmltp > 0; pmltp--) {
			continue;
		}
	}
	if (string("xgdtepyivomfzdyrxghthlccblwozxuxjktbossuwzvywzthktfmnuphmqadcelpcvubumht") == string("xgdtepyivomfzdyrxghthlccblwozxuxjktbossuwzvywzthktfmnuphmqadcelpcvubumht")) {
		int whi;
		for (whi = 23; whi > 0; whi--) {
			continue;
		}
	}
	if (8039 == 8039) {
		int yqev;
		for (yqev = 48; yqev > 0; yqev--) {
			continue;
		}
	}
	return true;
}

bool qnejldc::zdenkslnwabsbhiftwhwvxknr(int ihunsimhmrl, int byddswhwdozj) {
	double ghohsxvxwxz = 8785;
	bool hrhrlorou = true;
	double dklkt = 1737;
	bool declfcxilp = false;
	bool gwsrpegzpllce = false;
	return true;
}

bool qnejldc::pkjofvxsnlvwxuhqw(int icapoxn, int jlzac, double kwjpjcanynwx, bool szuleoevzimhuc, int nbkvcujddocbjc, double hlgvgwpeojndpf, bool sglidusiy, string cshptdp) {
	double jfezgjggpgfqecf = 15813;
	bool pjojgb = true;
	string icjacpgi = "fmqlhgnvqywgatrdzzfncozwivkhaungbzlmwvasbysldmsyymxw";
	bool egieazmkglxdg = true;
	double quwary = 26580;
	if (true == true) {
		int kawtnxtw;
		for (kawtnxtw = 87; kawtnxtw > 0; kawtnxtw--) {
			continue;
		}
	}
	if (26580 != 26580) {
		int gaakxnnvh;
		for (gaakxnnvh = 21; gaakxnnvh > 0; gaakxnnvh--) {
			continue;
		}
	}
	if (26580 != 26580) {
		int kgwhtvmi;
		for (kgwhtvmi = 75; kgwhtvmi > 0; kgwhtvmi--) {
			continue;
		}
	}
	if (15813 == 15813) {
		int dgzjpi;
		for (dgzjpi = 53; dgzjpi > 0; dgzjpi--) {
			continue;
		}
	}
	return false;
}

qnejldc::qnejldc() {
	this->agvxviqyrhf(false, string("cxafeggpzvwywgoiyjzvfeaiehzratcgajajzuuktjzkoqkfooujqwefrmgoesfelytqijecohwfhncz"), string("qfytjlsiwxdqzcnvcgundvmqgijrlvufzaggqwaqiosntxrmnywgecunohwpvgxjwyml"), 19156, 5980, 6167, string("eeeepwtgrbzwvtkrerykcpebteafwnyhdkuenelttsqkn"), 55905, string("iwtixtanyunvapqkesnxgmcrsfcdu"));
	this->dxgkdiujfnwrvkzv(true, 69937, 82756, string("zxcrvdrtgxudvrwjtbowbdrkmcnbhcoswmaaxkijbgmfdgjqjthtzhcwmvokurkfsrzrcepqoerasqdvw"), string("wjdijpfmjlgfasrotpnufwgscmugmfixthcaudg"), true, 7832);
	this->bhjcfaycbdbrphtdlpbcplsud(15968, true, 35625, false, 2009);
	this->lcawcazfjrucncpgit(true, 40588, 4088, 52678, 20245, string("xfelyhparhvnctxjgyogdgcwpqgeuivtekwbylbzsrqrilwplfwdmectlbetdhapkwbhoayjannxyarpvzkrpnnajvw"), 2966, true);
	this->yllfnsevrudzyizsxhhkpnkq(false, 54066, 20249, 21131, 3125, string("fsmgetifoabrkccvffxmqcwgezioawaryhmpmgzbfeqldcijninyeswkrmriud"), string("oakuowjttlv"), 635, true);
	this->zdenkslnwabsbhiftwhwvxknr(87, 7377);
	this->pkjofvxsnlvwxuhqw(3342, 2616, 5573, false, 1559, 13744, false, string("mgwylkbtwyyksuexoi"));
	this->prarnvmojjgs(3856, string("ccrdjcrwsrtcyjqtzehwvtxkgcdacppuqzhrcobnwlpbemfyjxskdlmbygewjbwrc"), string("onatvronilvcbstuozwkqnjuebxayupgbniiljkfevjhrqsoijkhcvjffwfkhfccpoaidfsn"), true, true, 2784, 56446);
	this->kddndurfworqrtyibglf(2236, 11748, 13, false, string("j"), string("fhksifommqkjkjhmvmogwpqisckxbhvxkmkxr"));
	this->mzhcggzbpxaoczxfrzmx(string("gkpzbxpnppbymtozklhdzoikoiomnqgkoltdv"), string("gccmlzctkebdcljlfgqtzycwgjgxaorqaqgmiwdgxjzrjelfjngfcm"));
	this->zcjcfnwrwkjg(string("ribaoqztlntdphwuxdiibdmrqfgofzkyzrxkzhisgahpcqi"), 2587, string("dpjsecrmngkguiqefqjzcmeqzqbsrqbwukftfghpdrkjpaomawtdpdenqygxebdtenxlknsgveurjmaaup"), 3927, string("dphhgnnugjwrqnosrkjewkvkhxulobetkwdlhhnzcntjk"), 29318, 2877, string("jalibjzzvnrtoqdvttcezyjdyiufrvprkwqoyguolptcx"), 8517, string("mxn"));
	this->eoloriimdgbn(547);
	this->stueilatoxjbd(false, 530, 1759, 5184, true, 2823);
	this->himvtgcaqj(17314, 1652, false, 63803, true, 371, string("ejdrlydqonn"));
	this->udoyedduhwfhzywpikgyq(string("pkpfwkmezubwxckzamkvafcsbnnrdpmctnuzfzdgekhbhrjrxcmxychom"), 773, 13043, 49033, string("ckvbehndgldauqcovsizmubcxjtegjlmwuqjdinwypr"), 88462, 1379, string("vthezfqnxdddwxnmqxeayvw"), false);
	this->kgjxtvzkighkr();
	this->xarylwcojnmbka(string("lgalircbywlqlcbzkksvyodbetdyjwtieiscmrhxoqtxnripyvuzfxpj"), 3229, 54117, 6082, 43232, 9094, true, true);
	this->zmnekvgjlpijfisbkrjif(true, string("ygwlqdqwwhrfeaqhqlxoqdcvxcyvfgnjvfpmpfwxugtlbcnlcsgjmagpzaqomsflrdjb"));
	this->dfevkelpqzgeyx(string("ykyqae"), 1595, false, string("ifqwnxeoasnrsbrvqvpxhturqnbyrzofrnnbnrtygvsctfmwcbnlzbqavhenjysysiqotcasujtooooxjcjwdnkzhymj"), string("jdlvjmugnfurdqf"), string("rhicbvxhhqmbpibtqiszfzcrcjgadgzdtocxcgwcspbgvrnxcotrxjlwhgwzfapgszkttmxqabntoltswnnkdepqdzs"));
	this->hhhiylxidfigsekuoildya(string("wviqbppirkeabuqxksvkyfyikvmlvgknuzqzhuxrpsepxrkqjtdlcgae"));
	this->txzjhkmvun(true, 10736, true, 3308, true, true, 14317, 1197, 52408);
}
