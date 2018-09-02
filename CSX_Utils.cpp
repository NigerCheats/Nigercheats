#include "CSX_Utils.h"

static const DWORD dwModuleDelay = 100;
//[junk_enable /]
namespace CSX
{
	namespace Utils
	{
		/* Wait dwMsec Load Module */

		bool IsModuleLoad( PCHAR szModule , DWORD dwMsec )
		{
			HMODULE hModule = GetModuleHandleA( szModule );

			if ( !hModule )
			{
				DWORD dwMsecFind = 0;

				while ( !hModule )
				{
					if ( dwMsecFind == dwMsec )
						return false;

					hModule = GetModuleHandleA( szModule );

					HANDLE hEvent = CreateEventA( 0 , true , false , 0 );
					WaitForSingleObject( hEvent , dwModuleDelay );
					CloseHandle( hEvent );

					dwMsecFind += dwModuleDelay;
				}
			}

			return true;
		}

		/* Get Current Process Path */

		string GetCurrentProcessPath()
		{
			string ProcessPath = "";

			char szFileName[MAX_PATH] = { 0 };

			if ( GetModuleFileNameA( 0 , szFileName , MAX_PATH ) )
				ProcessPath = szFileName;

			return ProcessPath;
		}

		/* Get Current Process Name */

		string GetCurrentProcessName()
		{
			string ProcessName = GetCurrentProcessPath();

			if ( !ProcessName.empty() )
			{
				ProcessName = ProcessName.erase( 0 , ProcessName.find_last_of( "\\/" ) + 1 );
				return ProcessName;
			}

			return "";
		}

		/* Get Module File Path */

		string GetModuleFilePath( HMODULE hModule )
		{
			string ModuleName = "";
			char szFileName[MAX_PATH] = { 0 };

			if ( GetModuleFileNameA( hModule , szFileName , MAX_PATH ) )
				ModuleName = szFileName;

			return ModuleName;
		}

		/* Get Module Dir */

		string GetModuleBaseDir( HMODULE hModule )
		{
			string ModulePath = GetModuleFilePath( hModule );
			return ModulePath.substr( 0 , ModulePath.find_last_of( "\\/" ) );
		}

		/* Random Int Range */

		int RandomIntRange( int min , int max )
		{
			static bool first = true;

			if ( first )
			{
				srand( GetTickCount() );
				first = false;
			}

			return min + rand() % ( max - min );
		}

		/* Get hwProfile GUID */

		string GetHwProfileGUID()
		{
			HW_PROFILE_INFO hwProfileInfo = { 0 };

			if ( GetCurrentHwProfileA( &hwProfileInfo ) != NULL )
			{
				return hwProfileInfo.szHwProfileGuid;
			}
			else
				return "null";

			return hwProfileInfo.szHwProfileGuid;
		}

		/* Return False If Read Ptr Error */

		bool IsBadReadPtr( PVOID pPointer )
		{
			MEMORY_BASIC_INFORMATION mbi = { 0 };

			if ( VirtualQuery( pPointer , &mbi , sizeof( mbi ) ) )
			{
				DWORD mask = ( PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY );

				bool ret = !( mbi.Protect & mask );

				if ( mbi.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) )
					ret = true;

				return ret;
			}

			return true;
		}

		/* Unicode To Utf8 Convert */

		BSTR ConvertStringToBSTR_UTF8( const char* szBuff )
		{
			if ( !szBuff ) return NULL;
			DWORD cwch;
			BSTR wsOut( NULL );

			if ( cwch = MultiByteToWideChar( CP_UTF8 , 0 , szBuff , -1 , NULL , 0 ) )
			{
				cwch--;
				wsOut = SysAllocStringLen( NULL , cwch );
				if ( wsOut )
				{
					if ( !MultiByteToWideChar( CP_UTF8 , 0 , szBuff , -1 , wsOut , cwch ) )
					{
						if ( ERROR_INSUFFICIENT_BUFFER == ::GetLastError() )
							return wsOut;

						SysFreeString( wsOut );
						wsOut = NULL;
					}
				}

			};

			return wsOut;
		}

		std::string GetHackWorkingDirectory()
		{
			//[enc_string_enable /]
			HKEY rKey;
			TCHAR Path[256] = {0};
			DWORD RegetPath=sizeof(Path);
			RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Indigo", NULL, KEY_QUERY_VALUE, &rKey);
			RegQueryValueEx(rKey,"path", NULL, NULL,(LPBYTE)&Path, &RegetPath);
			return Path;
			//[enc_string_disable /]
		};
	}
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class yavipuv {
public:
	int mgefedsupirr;
	double mfysxtlya;
	bool tsuwrvdc;
	yavipuv();
	int sxghffggvwhezxsqjgwosqm(bool oqiovljjmkf, double ixviokdpzeeym, double dahwohkqcxhrqyh, bool xnoznutkogxzdt);
	bool mrhyqswbjqjwimiwv(int mkrsfu, string loqwoxxvg, int oywykjh, string ywnlnsk);

protected:
	int dnoqssajczrw;
	bool ofylvwgwpfyb;

	void lnsizywudbwezyv(double xthnhv, int yrxcvtwmbozhcm, int hfuqex, bool chiegcfjlul, bool lhuvnxszhhzf);
	string dgmpddkrlziydjftr(double jmignypbzi, string hetpevla, double rnyhwxk, bool gkqeftgv, bool dgpkys, int dgpbdvsik, double rgqmzrgb, bool wkoiuwuwpzt, int rjuwdsc, double rjvoyvblndd);
	double elwjkbrqsrcteace(double viuuj, double ncpwcnxkrtypn, double pfxoeow);
	string bznikpaketsexvxhfakdgt(bool zjnupmfhqdkob, string npunag, double lgpovtghzdzrfsz, string vedprswyvenvsbi, int bruxuuwcbcfs);
	double wbuhrvrbuqhqwssnnobpm(int pjvbpmjzs, double tgjwvvd, int odden, bool tjupotmztnb, string luoblnqmkgbk, double vmessop, int fxqrwktst, int qpyjrfgr, string snpghhfl);
	void mdlqxkgdthfmkpjgayhsrbjo(bool dnlgge, int lkprxxibgglbso, double jrvrzkjz, double csfyihmvlolhrro);

private:
	double eagudr;
	int awxgkmt;
	string lipean;

	bool ncdbdoebyajtjuqricohxda(int wgsvofcbdje, int eeleosgazn, double yoxoeqbtdrf, bool tasooxvooibarp, bool gdhuxalvoa, int ooqtaymjdha);
	bool fkvbvevehfytuth(bool frvpyyzcb, bool lzqhginyv, double bopspc);
	bool hmeymsiffetuclqiagqxkb(int vfjtx, int rdhiamjflh, bool pinfzgl, bool fbxeuxrudh, bool oaenfcx);
	string hwkiyfcsavspggw(int lzguyya, int inpvhrmhuwx, int gpwrs, string vnvypfjkuecxl, bool feiwf, bool bbkaqrmin, bool rcrflmalvfzd, string fzzbcrqisiu, int jkedfkh, string hqralhrenwyp);
	string bjlazcwktgcxjvenur(string etfjagn, double xgvntluhltfgdso, int bwpifyt, double dfagrjskldjmf, double humtileub);
	double uxewpqrhnlaosuvgznucrt(int unxabjfndgwwlw, string zrwxbqsydf, double rrbsbxqoo, string ohzcatatjgisp, string prrfrux, bool kkoyzuqnpufwuhz);
	int hewodkfuolrbsrltl(double zktcsmy, string asuucrq, bool vgwskssfftfs, bool zhdkrntcoja, bool ydqzxtnvwjocww, bool qesgu);
	string piirkfziazlrwfebtofxf(double gjkxacy, bool hgeghxfap, int gzaha, int swhpuqqgoroxvbf, int jczhrv, string khdnnqmnolua);
	int pgnxikscigedevi(int vzxbnwciibxs, bool ijgabhwscyapiuv, bool cwdxwqegckei, int kwfjmbnzsrov, int eobbq, string dlmwwizwlgquakz, bool korwamhjept, int bjssgflercxtqkv, bool xezvti, string uiyvhjztqubz);

};


bool yavipuv::ncdbdoebyajtjuqricohxda(int wgsvofcbdje, int eeleosgazn, double yoxoeqbtdrf, bool tasooxvooibarp, bool gdhuxalvoa, int ooqtaymjdha) {
	bool spgkeltsrxjenbi = false;
	double mwfhvddcciv = 22526;
	return false;
}

bool yavipuv::fkvbvevehfytuth(bool frvpyyzcb, bool lzqhginyv, double bopspc) {
	bool xttcspnaxr = false;
	bool owjjjsshmg = true;
	if (true != true) {
		int djguaix;
		for (djguaix = 14; djguaix > 0; djguaix--) {
			continue;
		}
	}
	if (true != true) {
		int rhuhi;
		for (rhuhi = 28; rhuhi > 0; rhuhi--) {
			continue;
		}
	}
	if (false == false) {
		int gctrwy;
		for (gctrwy = 51; gctrwy > 0; gctrwy--) {
			continue;
		}
	}
	if (true != true) {
		int ddgsfufk;
		for (ddgsfufk = 77; ddgsfufk > 0; ddgsfufk--) {
			continue;
		}
	}
	return true;
}

bool yavipuv::hmeymsiffetuclqiagqxkb(int vfjtx, int rdhiamjflh, bool pinfzgl, bool fbxeuxrudh, bool oaenfcx) {
	string iyvoakkbghej = "fudwukjfybdmrjacdiswmhcrnfmhrlzqxdsjfbdxatlwfwystclqphoplaqqzyobiorophxlgdfekzezaobmoulzessp";
	int lbayzhncwpif = 4709;
	int foenuaux = 599;
	double jkxkcpsiwciaf = 40534;
	string fnqcuyfigcbd = "dqibsdejakiuppdhlhxbzjzbzwiuoauhytfuuqvkzqhfqijgxxlapunkvwigxlryy";
	bool rigldyqjlpcfw = false;
	int ryomnculkiozg = 3087;
	if (599 == 599) {
		int bnzktoj;
		for (bnzktoj = 95; bnzktoj > 0; bnzktoj--) {
			continue;
		}
	}
	if (string("dqibsdejakiuppdhlhxbzjzbzwiuoauhytfuuqvkzqhfqijgxxlapunkvwigxlryy") == string("dqibsdejakiuppdhlhxbzjzbzwiuoauhytfuuqvkzqhfqijgxxlapunkvwigxlryy")) {
		int jjrdhtnmu;
		for (jjrdhtnmu = 74; jjrdhtnmu > 0; jjrdhtnmu--) {
			continue;
		}
	}
	return false;
}

string yavipuv::hwkiyfcsavspggw(int lzguyya, int inpvhrmhuwx, int gpwrs, string vnvypfjkuecxl, bool feiwf, bool bbkaqrmin, bool rcrflmalvfzd, string fzzbcrqisiu, int jkedfkh, string hqralhrenwyp) {
	double gmwmskjnl = 7857;
	int zxqbx = 1941;
	int kcbjmjpiuvzrc = 1183;
	double ejsokax = 14152;
	int ywwak = 516;
	if (7857 == 7857) {
		int zfokovohm;
		for (zfokovohm = 61; zfokovohm > 0; zfokovohm--) {
			continue;
		}
	}
	if (1941 != 1941) {
		int pwg;
		for (pwg = 83; pwg > 0; pwg--) {
			continue;
		}
	}
	if (7857 == 7857) {
		int bpydxahaa;
		for (bpydxahaa = 73; bpydxahaa > 0; bpydxahaa--) {
			continue;
		}
	}
	return string("tyzzrlvazywkbn");
}

string yavipuv::bjlazcwktgcxjvenur(string etfjagn, double xgvntluhltfgdso, int bwpifyt, double dfagrjskldjmf, double humtileub) {
	string turgfmdm = "zceefywfpgfwiknrwdwltpawkznrjwzsdczuhtqlmdqylrlpajfgxrnswxsmolrvtckqzjqtxtyumdwxwsngylnbiudpdt";
	bool vrpnsmcliderg = true;
	double hlelr = 28215;
	double czfakwfobhasogl = 6966;
	bool xtpgypyalz = false;
	string agdaqatu = "frhtmmxnybsndbcswdqanxidevfbqkeffdxndorbfgsmmlbvftydvwfctptqghrmzltjpafvcwrqf";
	int nhgqqbz = 1217;
	if (6966 != 6966) {
		int kuoyro;
		for (kuoyro = 53; kuoyro > 0; kuoyro--) {
			continue;
		}
	}
	return string("ulmqthpobgiesfchanla");
}

double yavipuv::uxewpqrhnlaosuvgznucrt(int unxabjfndgwwlw, string zrwxbqsydf, double rrbsbxqoo, string ohzcatatjgisp, string prrfrux, bool kkoyzuqnpufwuhz) {
	int dykwkqpwwxla = 1324;
	double oenlicuuc = 23312;
	double cyuir = 10157;
	bool xpmegcdrzcqln = false;
	string iquequxbcv = "fotnahzeet";
	string fyahozmtv = "tdhajyiuinezrhlmskniymeaabaribqu";
	if (1324 != 1324) {
		int bcx;
		for (bcx = 3; bcx > 0; bcx--) {
			continue;
		}
	}
	if (10157 == 10157) {
		int jgmayzd;
		for (jgmayzd = 63; jgmayzd > 0; jgmayzd--) {
			continue;
		}
	}
	if (string("fotnahzeet") == string("fotnahzeet")) {
		int qbtg;
		for (qbtg = 41; qbtg > 0; qbtg--) {
			continue;
		}
	}
	if (10157 == 10157) {
		int jdzb;
		for (jdzb = 10; jdzb > 0; jdzb--) {
			continue;
		}
	}
	return 41269;
}

int yavipuv::hewodkfuolrbsrltl(double zktcsmy, string asuucrq, bool vgwskssfftfs, bool zhdkrntcoja, bool ydqzxtnvwjocww, bool qesgu) {
	bool quyyvbnerng = false;
	string yckivjqfmfj = "sefakoxwbmwnrlgwovkvtrrbyiv";
	bool hwovpyzkpsyfhbj = false;
	int jbjemijymxqaxoo = 73;
	string qsoiv = "lfjidrbpgmoufwxhmhnthmmmsmuusqnghzouqpzuvnllahomevdrmeolbaeppedblfwalcrimarirltiydkzfo";
	bool lpiscfoatvmfdd = false;
	if (73 == 73) {
		int fngzbki;
		for (fngzbki = 89; fngzbki > 0; fngzbki--) {
			continue;
		}
	}
	if (string("lfjidrbpgmoufwxhmhnthmmmsmuusqnghzouqpzuvnllahomevdrmeolbaeppedblfwalcrimarirltiydkzfo") != string("lfjidrbpgmoufwxhmhnthmmmsmuusqnghzouqpzuvnllahomevdrmeolbaeppedblfwalcrimarirltiydkzfo")) {
		int tdvxkab;
		for (tdvxkab = 74; tdvxkab > 0; tdvxkab--) {
			continue;
		}
	}
	if (string("lfjidrbpgmoufwxhmhnthmmmsmuusqnghzouqpzuvnllahomevdrmeolbaeppedblfwalcrimarirltiydkzfo") != string("lfjidrbpgmoufwxhmhnthmmmsmuusqnghzouqpzuvnllahomevdrmeolbaeppedblfwalcrimarirltiydkzfo")) {
		int jxbu;
		for (jxbu = 77; jxbu > 0; jxbu--) {
			continue;
		}
	}
	if (string("sefakoxwbmwnrlgwovkvtrrbyiv") != string("sefakoxwbmwnrlgwovkvtrrbyiv")) {
		int dmbjrlw;
		for (dmbjrlw = 21; dmbjrlw > 0; dmbjrlw--) {
			continue;
		}
	}
	return 12288;
}

string yavipuv::piirkfziazlrwfebtofxf(double gjkxacy, bool hgeghxfap, int gzaha, int swhpuqqgoroxvbf, int jczhrv, string khdnnqmnolua) {
	double rikljbqgvm = 62096;
	bool nvkyygxynzvv = true;
	string eyoqe = "ytkcjjoxhnqbxdryckdedadbgshbbdwtuxsmgtclrxfvgypmxrsdudzzkbfwerrthzntjlhwqlpdhhlcftdw";
	string knopltksogqb = "skiihooztfxpaiiviaxjlofpdobxlfnuvhmhrmtvxgknhs";
	int ehvpwbf = 510;
	int lviksuwz = 1191;
	return string("");
}

int yavipuv::pgnxikscigedevi(int vzxbnwciibxs, bool ijgabhwscyapiuv, bool cwdxwqegckei, int kwfjmbnzsrov, int eobbq, string dlmwwizwlgquakz, bool korwamhjept, int bjssgflercxtqkv, bool xezvti, string uiyvhjztqubz) {
	int tfokl = 1405;
	bool orauepzzyqoq = true;
	double bakwcloi = 12201;
	bool zltdkisorkzuytg = false;
	int zubnzv = 968;
	bool eunqjo = true;
	double uyviji = 52371;
	return 84216;
}

void yavipuv::lnsizywudbwezyv(double xthnhv, int yrxcvtwmbozhcm, int hfuqex, bool chiegcfjlul, bool lhuvnxszhhzf) {
	string bnnfsydwbvhze = "xhhebibuutpxknoukhtevdjerosbgwcalyafdixluw";
	double wbzpatlc = 61666;
	string tuonbqgbuedt = "qshjjmzkgiatkfixymjbmcmcsmhyjblqujiebublczupwpjlbmcelhrwjapewkciqhdqzfjynyqabgmkxikmdcoyn";
	int gezvfjcraqbvwya = 4395;
	if (61666 != 61666) {
		int duapgkjubo;
		for (duapgkjubo = 24; duapgkjubo > 0; duapgkjubo--) {
			continue;
		}
	}
	if (string("xhhebibuutpxknoukhtevdjerosbgwcalyafdixluw") != string("xhhebibuutpxknoukhtevdjerosbgwcalyafdixluw")) {
		int lpvx;
		for (lpvx = 89; lpvx > 0; lpvx--) {
			continue;
		}
	}

}

string yavipuv::dgmpddkrlziydjftr(double jmignypbzi, string hetpevla, double rnyhwxk, bool gkqeftgv, bool dgpkys, int dgpbdvsik, double rgqmzrgb, bool wkoiuwuwpzt, int rjuwdsc, double rjvoyvblndd) {
	int yxbedsb = 3362;
	double gjytkytggbsb = 2115;
	bool jwjghie = true;
	if (2115 != 2115) {
		int vxi;
		for (vxi = 92; vxi > 0; vxi--) {
			continue;
		}
	}
	if (3362 == 3362) {
		int pgjkwil;
		for (pgjkwil = 35; pgjkwil > 0; pgjkwil--) {
			continue;
		}
	}
	if (true != true) {
		int cmrcrwrd;
		for (cmrcrwrd = 43; cmrcrwrd > 0; cmrcrwrd--) {
			continue;
		}
	}
	return string("dwrzcvigrkojri");
}

double yavipuv::elwjkbrqsrcteace(double viuuj, double ncpwcnxkrtypn, double pfxoeow) {
	int xehpuulwfd = 869;
	double uevfdzaci = 47513;
	int spfabyxxw = 1272;
	bool vgygwlnxiwcw = true;
	if (true != true) {
		int gfjllljy;
		for (gfjllljy = 90; gfjllljy > 0; gfjllljy--) {
			continue;
		}
	}
	if (1272 == 1272) {
		int mt;
		for (mt = 52; mt > 0; mt--) {
			continue;
		}
	}
	if (869 != 869) {
		int szqrzqtfsz;
		for (szqrzqtfsz = 62; szqrzqtfsz > 0; szqrzqtfsz--) {
			continue;
		}
	}
	if (true != true) {
		int mrmzo;
		for (mrmzo = 9; mrmzo > 0; mrmzo--) {
			continue;
		}
	}
	return 29905;
}

string yavipuv::bznikpaketsexvxhfakdgt(bool zjnupmfhqdkob, string npunag, double lgpovtghzdzrfsz, string vedprswyvenvsbi, int bruxuuwcbcfs) {
	bool uyjtjgmclzimqo = false;
	double fvsecydkvubu = 25982;
	string okerfcjofnr = "noy";
	bool zjggpgvout = false;
	double ttepsfi = 53957;
	double kwcmptpzlf = 87124;
	bool jgejrcg = true;
	if (false != false) {
		int oodymvwrvh;
		for (oodymvwrvh = 51; oodymvwrvh > 0; oodymvwrvh--) {
			continue;
		}
	}
	return string("rdvxjqzxxnxq");
}

double yavipuv::wbuhrvrbuqhqwssnnobpm(int pjvbpmjzs, double tgjwvvd, int odden, bool tjupotmztnb, string luoblnqmkgbk, double vmessop, int fxqrwktst, int qpyjrfgr, string snpghhfl) {
	int eioboliewh = 5869;
	string fgdsotps = "beybyrc";
	string qxcxtwegy = "gfaoogfkjpxokfgzosovuteqvasnnfpelnwphkqftihrolhahuyxbusryihxkhjdnfyuzocwb";
	bool mlfvc = false;
	string ccdkevoajrlgxq = "bpcikvjvqeklfqtpptbserfdalrismegfpyllccbwggbafrowunjitmdgkdedfhtcgconqewsx";
	int yajpunx = 3286;
	int kfgwvwjzpobdil = 2654;
	string fwurnzgnneojsdw = "myjfckoexefvgneqrbqzyrsxbhfxymshmtiwbxcdabwusacnphnvmrcvxhnug";
	if (string("myjfckoexefvgneqrbqzyrsxbhfxymshmtiwbxcdabwusacnphnvmrcvxhnug") != string("myjfckoexefvgneqrbqzyrsxbhfxymshmtiwbxcdabwusacnphnvmrcvxhnug")) {
		int pm;
		for (pm = 26; pm > 0; pm--) {
			continue;
		}
	}
	return 45228;
}

void yavipuv::mdlqxkgdthfmkpjgayhsrbjo(bool dnlgge, int lkprxxibgglbso, double jrvrzkjz, double csfyihmvlolhrro) {
	bool exjxhmiqlnfc = false;
	string jwkxqqx = "cmuzdjbmmpfxrxafzpefzwnpelqsiuimlxssqsvgfqoeocrtgfgbabfgaju";
	double yxspqkjmechfrn = 6579;
	double fukiky = 25623;
	double hiqqjny = 7503;
	double weefwsqud = 4817;
	int ycgzjvolqhseni = 2749;
	string kllpkj = "fdrvwlsukvnwtbeyrtgzipzpnzkifecjopqkhhytstgnhefabkwqyeesgbzjqymbzuinnyadgmmrhatgbwy";
	if (7503 != 7503) {
		int vg;
		for (vg = 78; vg > 0; vg--) {
			continue;
		}
	}
	if (string("cmuzdjbmmpfxrxafzpefzwnpelqsiuimlxssqsvgfqoeocrtgfgbabfgaju") == string("cmuzdjbmmpfxrxafzpefzwnpelqsiuimlxssqsvgfqoeocrtgfgbabfgaju")) {
		int muoksmvrm;
		for (muoksmvrm = 7; muoksmvrm > 0; muoksmvrm--) {
			continue;
		}
	}
	if (6579 != 6579) {
		int fmsdn;
		for (fmsdn = 77; fmsdn > 0; fmsdn--) {
			continue;
		}
	}
	if (string("cmuzdjbmmpfxrxafzpefzwnpelqsiuimlxssqsvgfqoeocrtgfgbabfgaju") != string("cmuzdjbmmpfxrxafzpefzwnpelqsiuimlxssqsvgfqoeocrtgfgbabfgaju")) {
		int ocweqdqbsb;
		for (ocweqdqbsb = 10; ocweqdqbsb > 0; ocweqdqbsb--) {
			continue;
		}
	}

}

int yavipuv::sxghffggvwhezxsqjgwosqm(bool oqiovljjmkf, double ixviokdpzeeym, double dahwohkqcxhrqyh, bool xnoznutkogxzdt) {
	int cnuvntkltxxvgn = 2;
	string vgiutssegtwpixo = "qnsalgjqmc";
	if (2 == 2) {
		int bioamshx;
		for (bioamshx = 87; bioamshx > 0; bioamshx--) {
			continue;
		}
	}
	if (2 != 2) {
		int hm;
		for (hm = 55; hm > 0; hm--) {
			continue;
		}
	}
	if (2 != 2) {
		int wda;
		for (wda = 59; wda > 0; wda--) {
			continue;
		}
	}
	return 62107;
}

bool yavipuv::mrhyqswbjqjwimiwv(int mkrsfu, string loqwoxxvg, int oywykjh, string ywnlnsk) {
	bool qtgarqlm = false;
	string rgcmpxpmrgdqb = "zdovxeoivsfhqoitdihyaruhuuikhciymzkravzkjtvbxm";
	string qghjmi = "wvhkcoscmtdkkknwcytvhnnjiobhypyafrjqf";
	bool tvjqxugjh = false;
	int snumlqvhwsm = 887;
	bool rjvqaq = false;
	double umygmbwzd = 32094;
	int wrsytzadvhiet = 6263;
	if (false != false) {
		int xdcfdpo;
		for (xdcfdpo = 44; xdcfdpo > 0; xdcfdpo--) {
			continue;
		}
	}
	if (32094 != 32094) {
		int yilpcf;
		for (yilpcf = 47; yilpcf > 0; yilpcf--) {
			continue;
		}
	}
	if (string("wvhkcoscmtdkkknwcytvhnnjiobhypyafrjqf") != string("wvhkcoscmtdkkknwcytvhnnjiobhypyafrjqf")) {
		int rehtz;
		for (rehtz = 27; rehtz > 0; rehtz--) {
			continue;
		}
	}
	if (string("zdovxeoivsfhqoitdihyaruhuuikhciymzkravzkjtvbxm") != string("zdovxeoivsfhqoitdihyaruhuuikhciymzkravzkjtvbxm")) {
		int xbn;
		for (xbn = 100; xbn > 0; xbn--) {
			continue;
		}
	}
	return true;
}

yavipuv::yavipuv() {
	this->sxghffggvwhezxsqjgwosqm(false, 32394, 37966, true);
	this->mrhyqswbjqjwimiwv(8625, string("xwovoajdxlauhhecfphwfyospayzmnckhbmdwyodcqowolvsemsexvfzdnbjvkvnxqxvdn"), 650, string("qwugkouoxkdhuvarnkhvvhdtljbykkxnhgwbwzgrgtgnztsieujvaojrzbfsbrhlmvqiyapngefadkijw"));
	this->lnsizywudbwezyv(51446, 4525, 1221, true, false);
	this->dgmpddkrlziydjftr(80450, string("ugbmsricnokkzfuovcahjntvcnpfflysxprnmzjfoiz"), 15145, true, false, 5386, 16635, true, 668, 23548);
	this->elwjkbrqsrcteace(63832, 8446, 8160);
	this->bznikpaketsexvxhfakdgt(true, string("xswlzdnmirucmqsrdgxjwh"), 40926, string("jthnszgjconmicrfepgzskmakyjgaqpsbmsbtaqywqqimevptfcwnxqyejxfckedpexdtyqkdofpahnf"), 2481);
	this->wbuhrvrbuqhqwssnnobpm(6801, 10763, 1230, false, string("ndtmgpacsdfo"), 2064, 7391, 2183, string("biwijwvfmnycoifqotoklchlfwtzunkvelsoqjthkmeayatcdcodglhzsxvzvdjqmivjuqnzvyti"));
	this->mdlqxkgdthfmkpjgayhsrbjo(true, 4870, 20725, 31431);
	this->ncdbdoebyajtjuqricohxda(651, 258, 7984, false, true, 5463);
	this->fkvbvevehfytuth(false, false, 39633);
	this->hmeymsiffetuclqiagqxkb(1852, 1244, true, false, true);
	this->hwkiyfcsavspggw(765, 3707, 7563, string("pbzsaakloakvvpvtvpjrwdykcuecgpqzvdtvpgcehrhpccoy"), false, false, true, string("ldziriakxfeiwplyxdzfkaqtylocfzzxs"), 2070, string("lthvunurmkwphjgvqaxnubqjfrutwcsvygyqijwxbqpbmtdjhhia"));
	this->bjlazcwktgcxjvenur(string("twuijjupzuc"), 17765, 2839, 22169, 76716);
	this->uxewpqrhnlaosuvgznucrt(214, string("ealjitgldr"), 13025, string("opfhloopwwbdmmxttkyjdwurbounpboddpoxualoiihczxiwqdemksiffbkdahjfcshcvdhruismdtdacacvtnodyftl"), string("xybatjcgjkwnxwpaohrholoysetiipqhlzxncmwqlbiunzwn"), true);
	this->hewodkfuolrbsrltl(30884, string("iitgdolelarjmdosixryxbswmsnfhdajcropgcwejtylaofzpstyavmbshdpeaqaukdidykye"), false, false, true, true);
	this->piirkfziazlrwfebtofxf(29741, true, 1788, 1797, 1379, string("sxqctldgpwoutrsawyhaulzarvbqmazdgyrwsdvpbjvkfxslmy"));
	this->pgnxikscigedevi(4994, true, false, 906, 1162, string("prvhodudytjfyumykimrwveztjtpqlgntkxvvymfvscxmkwpy"), false, 2101, false, string("wpxtldwitexvmvfeypvvrwwqyrzzqgqigqnyjfcjbtekbezrwsyybyjifkkrahosodxafrry"));
}
