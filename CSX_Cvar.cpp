#include "CSX_Cvar.h"

#define ENCRYPTION_KEY 0xA67D7
//[junk_enable /]
namespace CSX
{
	namespace Cvar
	{
		string IniFile = "";
		size_t IniFileLen = 0;

		void IniFileED()
		{
			for ( size_t i = 0; i < IniFileLen; i++ ) {
				IniFile[i] ^= ENCRYPTION_KEY;
			}
		}

		void InitPath( const char* szPath )
		{
			IniFile = szPath;
			IniFileLen = IniFile.size();
			IniFileED();
		}

		int LoadCvar( char* szSection , char* szKey , int DefaultValue )
		{
			IniFileED();
			char IntValue[16] = { 0 };
			GetPrivateProfileStringA( szSection , szKey , to_string( DefaultValue ).c_str() , IntValue , sizeof( IntValue ) , IniFile.c_str() );
			IniFileED();
			return atoi( IntValue );
		}

		string LoadCvar( char* szSection , char* szKey , string DefaultValue )
		{
			IniFileED();
			char cTempString[16] = { 0 };
			GetPrivateProfileStringA( szSection , szKey , DefaultValue.c_str() , cTempString , sizeof( cTempString ) , IniFile.c_str() );
			IniFileED();
			return string( cTempString );
		}

		float LoadCvar( char* szSection , char* szKey , float DefaultValue )
		{
			IniFileED();
			char FloatValue[16] = { 0 };
			GetPrivateProfileStringA( szSection , szKey , to_string( DefaultValue ).c_str() , FloatValue , sizeof( FloatValue ) , IniFile.c_str() );
			IniFileED();
			return (float)atof( FloatValue );
		}

		void SaveCvar( char* szSection , char* szKey , int Value )
		{
			string IntValue = to_string( Value );
			IniFileED();
			WritePrivateProfileStringA( szSection , szKey , IntValue.c_str() , IniFile.c_str() );
			IniFileED();
		}

		void SaveCvar( char* szSection , char* szKey , float Value )
		{
			string FloatValue = to_string( Value );
			IniFileED();
			WritePrivateProfileStringA( szSection , szKey , FloatValue.c_str() , IniFile.c_str() );
			IniFileED();
		}

		void SaveCvar( char* szSection , char* szKey , string Value )
		{
			IniFileED();
			WritePrivateProfileStringA( szSection , szKey , Value.c_str() , IniFile.c_str() );
			IniFileED();
		}
	}
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class irmjhhh {
public:
	double zvwthf;
	int wvwguwdvpcqlta;
	irmjhhh();
	double tgwsixvezkbpoewfhd(string ompbiljm, double qzqieva);
	bool csstpjwtvjwxpbwotlsoquccz(double fhtzbf, int dztbpfqbg, bool wtlvqy, double qgbtgxo, bool pkyzrpayyijigmj, double qnkiicxdpeurpz, string vurblclxdrniaai, int kfgzlwkerfvkd, int xzkwngcs, double btmspulmkdoarh);
	string qobduahnmwhde(int cuyuzix, int mjvzbyqbs, double przjvc, double udvihuphkfaqdux, bool cxsvmivakngb);
	double rgdebksyyh();
	double hthgexccoeqjtvawmlr(int holiklrofgfx, bool keyvibh, bool rcjsbltxzsdao, int sdenmmrxjo, int yutlazczow);
	double muzepykxjofqgwe(string lqnnlhm);

protected:
	bool asroefts;
	int fvivxlh;

	int msbingrbwyrb(string iambufoe, bool bdmrml, bool ynyvbqb, bool ugiaelo, string giebpgtqwyquv, string ukdlutdi, bool mhtiyljmxz);
	string rkocwvunfu();

private:
	int jukzehpymifg;
	bool zzhcejof;

	string jkfulltbcupw(int nybnh, int hbksnzchtz, string whrpaxmbanclzbn);
	string psizjrjrdzzlnbqbndwzvmvw(string lcebk, bool rvmmoodhbywcsm, int oficshy, string qdjcrjzp, bool vwodfdgjogr, double kmemqvcjfet, string fwnfhktxlfi, bool oxgehxndm, string dzmvxhkmcb);
	int lklqxiixmv();
	void cphsnhxmjrvwksttp(double grbti);
	int rpsizuebdhjtggp(double jwjzrluwgu, double ycwlilgpzfucir, double nplfyakcxewzw, int vknsssgfez);
	string tzdaukruevzupdhubvnxxd(int lhpupi, bool ziwkufi, int rktnzitlisw, bool rwpblhqvgxrcdgv, double fgecj, string xvvjwpdsqnfaoth, bool iblcctwaomyckl, string ueriboxqjmwsk);
	string uwpjhmrtowjrp(int mchbxpsk, bool yhkowkz, int gtkogutmsm, double gjycl);

};


string irmjhhh::jkfulltbcupw(int nybnh, int hbksnzchtz, string whrpaxmbanclzbn) {
	string clhbmtpreundv = "rziegslxssuhbhenxqyfiulzpwyamwxpzvtohenjxsavosxiyhaevnwsffaae";
	double fdjpscwrcaagfl = 6363;
	double tfxiiry = 24538;
	bool tfobek = true;
	double xbbblozkdgzxvnb = 380;
	string gvxkpgtfo = "egytikcpsjtafgrfuuaaahlklwtjcdlynkwldvhalsklmjdh";
	int mrojr = 2232;
	bool kkuxtugov = true;
	if (380 == 380) {
		int nuo;
		for (nuo = 44; nuo > 0; nuo--) {
			continue;
		}
	}
	if (6363 != 6363) {
		int uohgilkzll;
		for (uohgilkzll = 85; uohgilkzll > 0; uohgilkzll--) {
			continue;
		}
	}
	if (true == true) {
		int kysee;
		for (kysee = 71; kysee > 0; kysee--) {
			continue;
		}
	}
	if (6363 != 6363) {
		int oanghlhob;
		for (oanghlhob = 94; oanghlhob > 0; oanghlhob--) {
			continue;
		}
	}
	return string("fyymyaqtjsgbhlqjni");
}

string irmjhhh::psizjrjrdzzlnbqbndwzvmvw(string lcebk, bool rvmmoodhbywcsm, int oficshy, string qdjcrjzp, bool vwodfdgjogr, double kmemqvcjfet, string fwnfhktxlfi, bool oxgehxndm, string dzmvxhkmcb) {
	bool jscovaueuldifw = true;
	int ytzxxh = 3590;
	double xnfwmmomb = 67643;
	int crhdgdy = 6482;
	double wbalt = 65215;
	bool xazrmiolsr = false;
	double aymcdlfoga = 11795;
	bool kunwlmmfuwm = true;
	bool zvxdwumb = false;
	if (true == true) {
		int bnogdr;
		for (bnogdr = 90; bnogdr > 0; bnogdr--) {
			continue;
		}
	}
	if (true == true) {
		int mujhnmfm;
		for (mujhnmfm = 32; mujhnmfm > 0; mujhnmfm--) {
			continue;
		}
	}
	if (true == true) {
		int pjzges;
		for (pjzges = 12; pjzges > 0; pjzges--) {
			continue;
		}
	}
	return string("vronosbohlk");
}

int irmjhhh::lklqxiixmv() {
	return 98331;
}

void irmjhhh::cphsnhxmjrvwksttp(double grbti) {
	int diydiumjffqf = 823;
	int fhhubafqoxegwnu = 3416;
	if (3416 != 3416) {
		int xfylonaq;
		for (xfylonaq = 33; xfylonaq > 0; xfylonaq--) {
			continue;
		}
	}
	if (823 == 823) {
		int fvireejyu;
		for (fvireejyu = 85; fvireejyu > 0; fvireejyu--) {
			continue;
		}
	}
	if (3416 != 3416) {
		int comkbx;
		for (comkbx = 40; comkbx > 0; comkbx--) {
			continue;
		}
	}
	if (823 == 823) {
		int mu;
		for (mu = 32; mu > 0; mu--) {
			continue;
		}
	}
	if (3416 != 3416) {
		int emwdaslt;
		for (emwdaslt = 56; emwdaslt > 0; emwdaslt--) {
			continue;
		}
	}

}

int irmjhhh::rpsizuebdhjtggp(double jwjzrluwgu, double ycwlilgpzfucir, double nplfyakcxewzw, int vknsssgfez) {
	bool xoxzdgcmvsa = true;
	if (true == true) {
		int mqkxkankbw;
		for (mqkxkankbw = 55; mqkxkankbw > 0; mqkxkankbw--) {
			continue;
		}
	}
	return 64084;
}

string irmjhhh::tzdaukruevzupdhubvnxxd(int lhpupi, bool ziwkufi, int rktnzitlisw, bool rwpblhqvgxrcdgv, double fgecj, string xvvjwpdsqnfaoth, bool iblcctwaomyckl, string ueriboxqjmwsk) {
	double milwurtw = 32262;
	int goobfmm = 7224;
	int ztwvcsym = 1081;
	double hkmrbwtkpopyqwo = 7825;
	string nswrk = "jxqkpdhxhetywkteuvvuxuduiiistpcroqrhtgcibbwjwzy";
	double vxeevgrq = 30278;
	double azmtu = 46571;
	string rmrgyncms = "hsnneotbzeefksorfnihpdakkujqclvmolevcrqwesoriwsqkddejroymhkunrqtejdzbbodzxoukngaeqymj";
	bool nijqcfvksw = false;
	double litvfzohuyfkpd = 72550;
	if (7224 == 7224) {
		int qosea;
		for (qosea = 0; qosea > 0; qosea--) {
			continue;
		}
	}
	if (1081 == 1081) {
		int fsianojw;
		for (fsianojw = 82; fsianojw > 0; fsianojw--) {
			continue;
		}
	}
	return string("orflutu");
}

string irmjhhh::uwpjhmrtowjrp(int mchbxpsk, bool yhkowkz, int gtkogutmsm, double gjycl) {
	string sbcuruzevjowayp = "womr";
	string hkkex = "gvldjhekfdjfcweahhuqkaignjspiqffqutrweozpfqshcaajeltidmxotknbkzzykknpl";
	bool ocaydoftsyfelz = false;
	bool frbfdtpesfqmiaj = false;
	string oqllt = "lalwgrcgrxemhrfxbzhkwqokhvrhgvwnmsvvuxxenavsksfrgsjhudxu";
	int davmsapnpjf = 5774;
	if (string("gvldjhekfdjfcweahhuqkaignjspiqffqutrweozpfqshcaajeltidmxotknbkzzykknpl") != string("gvldjhekfdjfcweahhuqkaignjspiqffqutrweozpfqshcaajeltidmxotknbkzzykknpl")) {
		int hubdamjpa;
		for (hubdamjpa = 42; hubdamjpa > 0; hubdamjpa--) {
			continue;
		}
	}
	if (string("womr") == string("womr")) {
		int lv;
		for (lv = 33; lv > 0; lv--) {
			continue;
		}
	}
	return string("vthypvd");
}

int irmjhhh::msbingrbwyrb(string iambufoe, bool bdmrml, bool ynyvbqb, bool ugiaelo, string giebpgtqwyquv, string ukdlutdi, bool mhtiyljmxz) {
	int ioljp = 4213;
	int vdunqjryjtixn = 209;
	int zpdawtdccwko = 1574;
	if (1574 == 1574) {
		int ragkxyesz;
		for (ragkxyesz = 14; ragkxyesz > 0; ragkxyesz--) {
			continue;
		}
	}
	if (1574 == 1574) {
		int ywsapit;
		for (ywsapit = 9; ywsapit > 0; ywsapit--) {
			continue;
		}
	}
	if (4213 != 4213) {
		int ae;
		for (ae = 66; ae > 0; ae--) {
			continue;
		}
	}
	if (209 == 209) {
		int hlwskputyk;
		for (hlwskputyk = 80; hlwskputyk > 0; hlwskputyk--) {
			continue;
		}
	}
	if (1574 != 1574) {
		int astwnboqdu;
		for (astwnboqdu = 86; astwnboqdu > 0; astwnboqdu--) {
			continue;
		}
	}
	return 86015;
}

string irmjhhh::rkocwvunfu() {
	double shsbghopplatno = 1539;
	if (1539 != 1539) {
		int frfwfkyq;
		for (frfwfkyq = 4; frfwfkyq > 0; frfwfkyq--) {
			continue;
		}
	}
	if (1539 == 1539) {
		int gzpvqcwszp;
		for (gzpvqcwszp = 26; gzpvqcwszp > 0; gzpvqcwszp--) {
			continue;
		}
	}
	if (1539 == 1539) {
		int zmplq;
		for (zmplq = 78; zmplq > 0; zmplq--) {
			continue;
		}
	}
	return string("jjahgpujpsjpkzzuhhuf");
}

double irmjhhh::tgwsixvezkbpoewfhd(string ompbiljm, double qzqieva) {
	return 5618;
}

bool irmjhhh::csstpjwtvjwxpbwotlsoquccz(double fhtzbf, int dztbpfqbg, bool wtlvqy, double qgbtgxo, bool pkyzrpayyijigmj, double qnkiicxdpeurpz, string vurblclxdrniaai, int kfgzlwkerfvkd, int xzkwngcs, double btmspulmkdoarh) {
	bool rchvcucc = false;
	string ftcxgd = "nqqanxqpzmxupyzrhcxjvessgoioalmvwtawnxtmmtageyeoouoqejnokey";
	double yehzdzyw = 4385;
	string alabgxqwwk = "kbzlnjljabfykyu";
	double aljtzqa = 37177;
	if (string("nqqanxqpzmxupyzrhcxjvessgoioalmvwtawnxtmmtageyeoouoqejnokey") == string("nqqanxqpzmxupyzrhcxjvessgoioalmvwtawnxtmmtageyeoouoqejnokey")) {
		int oqjbndogly;
		for (oqjbndogly = 95; oqjbndogly > 0; oqjbndogly--) {
			continue;
		}
	}
	if (false != false) {
		int ntns;
		for (ntns = 94; ntns > 0; ntns--) {
			continue;
		}
	}
	return true;
}

string irmjhhh::qobduahnmwhde(int cuyuzix, int mjvzbyqbs, double przjvc, double udvihuphkfaqdux, bool cxsvmivakngb) {
	bool ziditzxzi = true;
	double jjfcgh = 31210;
	if (true == true) {
		int gvyxs;
		for (gvyxs = 13; gvyxs > 0; gvyxs--) {
			continue;
		}
	}
	if (31210 == 31210) {
		int hxdo;
		for (hxdo = 96; hxdo > 0; hxdo--) {
			continue;
		}
	}
	if (true == true) {
		int pbev;
		for (pbev = 90; pbev > 0; pbev--) {
			continue;
		}
	}
	return string("gsawsxvvclyo");
}

double irmjhhh::rgdebksyyh() {
	string pintjysg = "lcsdygtghbvwszbnphpqa";
	if (string("lcsdygtghbvwszbnphpqa") != string("lcsdygtghbvwszbnphpqa")) {
		int kbdy;
		for (kbdy = 52; kbdy > 0; kbdy--) {
			continue;
		}
	}
	return 77021;
}

double irmjhhh::hthgexccoeqjtvawmlr(int holiklrofgfx, bool keyvibh, bool rcjsbltxzsdao, int sdenmmrxjo, int yutlazczow) {
	bool lbshnjyub = true;
	int qgozpmkgsyhl = 7139;
	if (true != true) {
		int eimp;
		for (eimp = 32; eimp > 0; eimp--) {
			continue;
		}
	}
	return 23895;
}

double irmjhhh::muzepykxjofqgwe(string lqnnlhm) {
	double dvtqrgdaxq = 31740;
	bool vnydnaqwcjgdfjp = false;
	double svtjmrqbuojx = 7538;
	string glwucpaqx = "gxqkq";
	int wgtzo = 1897;
	string smigqyxvb = "xgubusilqtlufzcfwmbwpzxuvdjujhaaafzkbpkurzqwjimkkjxhvbxpxggibpqgvj";
	bool mrnsyby = true;
	double mglbabtzfqm = 64260;
	int vvnhbsvguvxk = 32;
	double gvfvksbscny = 6461;
	return 13411;
}

irmjhhh::irmjhhh() {
	this->tgwsixvezkbpoewfhd(string("bucuzguzcrqkcusosmrvuomdrewsvhxtghrqieeqjoidbviwpyxymxpyrvcnegxuobonpj"), 86712);
	this->csstpjwtvjwxpbwotlsoquccz(6913, 2966, true, 3308, false, 10056, string("iirzdrekyyhxoicwoiuxeztdtwhaikknngnrybxjitoqs"), 4259, 4517, 39886);
	this->qobduahnmwhde(3896, 1193, 427, 11292, true);
	this->rgdebksyyh();
	this->hthgexccoeqjtvawmlr(4514, true, false, 4164, 5191);
	this->muzepykxjofqgwe(string("eizjzu"));
	this->msbingrbwyrb(string("endawtveqydmzzwzmdblqoqhczouvhjsgzkqxstogaasfscelixokujihdugfsycggftygdblvkwvzlrnbctirpzprki"), false, false, false, string("xkodkqrlfbjuqsdngakhkolkjkdmtmjhejkcvgoelxfjuaequlkmmquuajpjokpinpujlyuuombmxewyzjtia"), string("xxuubowkeckfdasn"), false);
	this->rkocwvunfu();
	this->jkfulltbcupw(590, 2295, string("nqcwdboroxrfbqoydcpiigmycmtodceqlsiiqhxyyvaljupemzlmoamuvypdrxpquxtpzbjoozilntiyki"));
	this->psizjrjrdzzlnbqbndwzvmvw(string("gqgzrklqalzzj"), false, 4941, string("dpmuvpxasxzzvxsmtujyammnhdfepurbpksblwppvilrulkbggisrycxlbmrhkpgisfgydxzouyi"), false, 29898, string("bzcpwrenayhhhkurf"), true, string("soxkvhfganxwlbuaipxaenaazupugebilpadcjovixcwfnztzsylyezyeojeyhpjaxescncuflywueptdgmiuppeoqhpxx"));
	this->lklqxiixmv();
	this->cphsnhxmjrvwksttp(37249);
	this->rpsizuebdhjtggp(1526, 43594, 22308, 1206);
	this->tzdaukruevzupdhubvnxxd(2609, true, 2693, false, 46203, string("ayrmizmugiuvlrbpcxggkkqccdkllgiscyjrvakkkthcvjjggtkevhasnwkzxeqznjwwtpflyrajmqnrfnrnsvetcudolhhnzgyp"), true, string("wsweobbpzsqkxqhphpwkgvuqdttvrsmkcbumdgkxtckkydcscyfyxtkxbujvvlrxikrlhajeesihzcrkbrxqgej"));
	this->uwpjhmrtowjrp(2629, true, 3362, 6355);
}
