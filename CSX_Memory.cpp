#include "CSX_Memory.h"
#include <vector>

#include <Psapi.h>
#pragma comment(lib,"psapi")

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

//[junk_enable /]
MODULEINFO GetModuleInfo( PCHAR szModule )
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA( szModule );

	if ( hModule == 0 )
		return modinfo;

	GetModuleInformation( GetCurrentProcess() , hModule , &modinfo , sizeof( MODULEINFO ) );
	return modinfo;
}

namespace CSX
{
	namespace Memory
	{
		/* Find Push String ( 0x68, dword ptr [str] ) */
		DWORD FindPatternV2(std::string moduleName, std::string Mask)
		{
			const char* pat = Mask.c_str();
			DWORD firstMatch = 0;
			DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
			MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
			DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
			for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
			{
				if (!*pat)
				{
					return firstMatch;
				}
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
				{
					if (!firstMatch)
					{
						firstMatch = pCur;
					}

					if (!pat[2])
					{
						return firstMatch;
					}


					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					{
						pat += 3;
					}
					else
					{
						pat += 2; //one ?
					}

				}
				else
				{
					pat = Mask.c_str();
					firstMatch = 0;
				}
			}
			return NULL;
		}
#define IsInRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))
		DWORD FindSig(DWORD dwAddress, DWORD dwLength, const char* szPattern)
		{
			if (!dwAddress || !dwLength || !szPattern)
				return 0;

			const char* pat = szPattern;
			DWORD firstMatch = NULL;

			for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
			{
				if (!*pat)
					return firstMatch;

				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GetByte(pat))
				{
					if (!firstMatch)
						firstMatch = pCur;

					if (!pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;

					else pat += 2;
				}
				else
				{
					pat = szPattern;
					firstMatch = 0;
				}
			}

			return 0;
		}
		DWORD FindSignature(const char* szModuleName, const char* PatternName, char* szPattern)
		{
			HMODULE hModule = GetModuleHandleA(szModuleName);
			PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
			PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hModule) + pDOSHeader->e_lfanew);

			DWORD ret = FindSig(((DWORD)hModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hModule) + pNTHeaders->OptionalHeader.SizeOfCode, szPattern);;

			return ret;
		}

		/* Find Push String ( 0x68, dword ptr [str] ) */

		DWORD FindPushString( DWORD dwStart , DWORD dwEnd , DWORD dwAddress )
		{
			char szPattern[5] = { 0x68 , 0x00 , 0x00 , 0x00 , 0x00 };
			*(PDWORD)&szPattern[1] = dwAddress;
			return FindPattern( szPattern , sizeof( szPattern ) , dwStart , dwEnd , 0 );
		}

		DWORD FindPushString( PCHAR szModule , DWORD dwAddress )
		{
			MODULEINFO mInfo = GetModuleInfo( szModule );

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPushString( dwStart , dwStart + dwSize , dwAddress );
		}

		/* Code Style Use Mask \x8B\xFF\xFF\xFF\xFF x???? */

		DWORD FindPattern( PCHAR pPattern , PCHAR pszMask , DWORD dwStart , DWORD dwEnd , DWORD dwOffset )
		{
			bool bFound = false;
			DWORD dwPtLen = lstrlenA( pszMask );

			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::FindPattern(%s) Init", pszMask);
			#endif

			for ( DWORD dwPtr = dwStart; dwPtr < dwEnd - dwPtLen; dwPtr++ ) {
				bFound = true;

				for ( DWORD idx = 0; idx < dwPtLen; idx++ ) {
					if ( pszMask[idx] == 'x' && pPattern[idx] != *(PCHAR)( dwPtr + idx ) )
					{
						bFound = false;
						break;
					}
				}

				if ( bFound )
				{
					#if ENABLE_DEBUG_FILE == 1
						string pPattern_str = pPattern;
						CSX::Log::Add( "::>>FindPattern(%s) = %X", pszMask, dwPtr + dwOffset - dwStart);
					#endif
					return dwPtr + dwOffset;
				}
			}

			return 0;
		}

		ULONG FindPBYTEPattern(std::string sModuleName, PBYTE pbPattern, std::string sMask, ULONG uCodeBase, ULONG uSizeOfCode)
		{
			BOOL bPatternDidMatch = FALSE;
			HMODULE hModule = GetModuleHandle(sModuleName.c_str());

			if (!hModule)
				return 0x0;

			PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(hModule);
			PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(LONG(hModule) + pDsHeader->e_lfanew);
			PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

			if (uCodeBase == 0x0)
				uCodeBase = (ULONG)hModule + pOptionalHeader->BaseOfCode;

			if (uSizeOfCode == 0x0)
				uSizeOfCode = pOptionalHeader->SizeOfCode;

			ULONG uArraySize = sMask.length();

			if (!uCodeBase || !uSizeOfCode || !uArraySize)
				return 0x0;

			for (size_t i = uCodeBase; i <= uCodeBase + uSizeOfCode; i++)
			{
				for (size_t t = 0; t < uArraySize; t++)
				{
					if (*((PBYTE)i + t) == pbPattern[t] || sMask.c_str()[t] == '?')
						bPatternDidMatch = TRUE;

					else
					{
						bPatternDidMatch = FALSE;
						break;
					}
				}

				if (bPatternDidMatch)
					return i;
			}

			return 0x0;
		}

		DWORD FindPattern( PCHAR szModule , PCHAR pPattern , PCHAR pszMask , DWORD dwOffset )
		{
			MODULEINFO mInfo = GetModuleInfo( szModule );

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern( pPattern , pszMask , dwStart , dwStart + dwSize , dwOffset );
		}

		/* Code Style No Use Mask \x55\x56\xFF\x00 */

		DWORD FindPattern( PCHAR pPattern , DWORD dwPtLen , DWORD dwStart , DWORD dwEnd , DWORD dwOffset )
		{
			bool bFound = false;

			for ( DWORD dwPtr = dwStart; dwPtr < dwEnd - dwPtLen; dwPtr++ ) {
				bFound = true;

				for ( DWORD idx = 0; idx < dwPtLen; idx++ ) {
					if ( pPattern[idx] != *(PCHAR)( dwPtr + idx ) )
					{
						bFound = false;
						break;
					}
				}

				if ( bFound )
					return dwPtr + dwOffset;
			}

			return 0;
		}

		DWORD FindPattern( PCHAR szModule , PCHAR pPattern , DWORD dwPtLen , DWORD dwOffset )
		{
			MODULEINFO mInfo = GetModuleInfo( szModule );

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern( pPattern , dwPtLen , dwStart , dwStart + dwSize , dwOffset );
		}

		/* Find String */

		DWORD FindString( PCHAR szModule , PCHAR pszStr )
		{
			return FindPattern( szModule , pszStr , lstrlenA( pszStr ) , 0 );
		}

		/* IDA Style 00 FF ?? */

		DWORD FindPattern( PCHAR pPattern , DWORD dwStart , DWORD dwEnd , DWORD dwOffset )
		{
			const char* pPat = pPattern;
			DWORD dwFind = 0;

			for ( DWORD dwPtr = dwStart; dwPtr < dwEnd; dwPtr++ ) {
				if ( !*pPat )
					return dwFind;

				if ( *(PBYTE)pPat == '\?' || *(BYTE*)dwPtr == getByte( pPat ) )
				{
					if ( !dwFind )
						dwFind = dwPtr;

					if ( !pPat[2] )
						return dwFind + dwOffset;

					if ( *(PWORD)pPat == '\?\?' || *(PBYTE)pPat != '\?' )
					{
						pPat += 3;
					}
					else
						pPat += 2;
				}
				else
				{
					pPat = pPattern;
					dwFind = 0;
				}
			}

			return 0;
		}

		DWORD FindPattern( PCHAR szModule , PCHAR pPattern , DWORD dwOffset )
		{
			MODULEINFO mInfo = GetModuleInfo( szModule );

			DWORD dwStart = (DWORD)mInfo.lpBaseOfDll;
			DWORD dwSize = (DWORD)mInfo.SizeOfImage;

			return FindPattern( pPattern , dwStart , dwStart + dwSize , dwOffset );
		}

		/* Native memory Func */

		void nt_memset( PVOID pBuffer , DWORD dwLen , DWORD dwSym )
		{
			_asm
			{
				pushad
				mov edi , [pBuffer]
				mov ecx , [dwLen]
				mov eax , [dwSym]
				rep stosb
				popad
			}
		}

		std::uint8_t* NewPatternScan(void* module, const char* signature)
		{
			static auto pattern_to_byte = [](const char* pattern) {
				auto bytes = std::vector<int>{};
				auto start = const_cast<char*>(pattern);
				auto end = const_cast<char*>(pattern) + strlen(pattern);

				for (auto current = start; current < end; ++current) {
					if (*current == '?') {
						++current;
						if (*current == '?')
							++current;
						bytes.push_back(-1);
					}
					else {
						bytes.push_back(strtoul(current, &current, 16));
					}
				}
				return bytes;
			};

			auto dosHeader = (PIMAGE_DOS_HEADER)module;
			auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

			auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			auto patternBytes = pattern_to_byte(signature);
			auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

			auto s = patternBytes.size();
			auto d = patternBytes.data();

			for (auto i = 0ul; i < sizeOfImage - s; ++i) {
				bool found = true;
				for (auto j = 0ul; j < s; ++j) {
					if (scanBytes[i + j] != d[j] && d[j] != -1) {
						found = false;
						break;
					}
				}
				if (found) {
					return &scanBytes[i];
				}


			}
			return nullptr;
		}

		void nt_memcpy( PVOID pDst , PVOID pSrc , size_t Count )
		{
			_asm
			{
				mov	edi , [pDst]
				mov	esi , [pSrc]
				mov	ecx , [Count]
				rep	movsb
			}
		}
	}
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ncjjuyg {
public:
	string onovpwuowegxq;
	bool eeiigqo;
	double mjbczeer;
	string ynmfjpkp;
	int vksxeaxaedvplf;
	ncjjuyg();
	bool tgewzgrwdigjwwgf(bool ngwsk, double imtef, double jjbkofctdzp, string mysudhmwdk, double lpmmixjjfxss, bool wrosezxnn, string nrwcpthrqhscq);
	void fonbcanfvrbwcmnnbktputgf(string iyswrbirvit, string acyymbyazbgmokm, bool gmgqbxjr);
	double xupljzpjeejwigzggkkia(string dvhkoyzbprwmjg, double pkalav, string gdyvlqiher, string vunogzgbofpfin);
	string amcuukhpnxsv(string jyrdjvgis, bool yqfgtzium, string yikoynwgftng, string vugsqabyatpee, string nzwxpq, double hllubbwyeshpnbs, string szuioyj, bool lcptxn);
	int kwxobtqylpqeeqobgtxmgsn(bool ixofsc, int mvxzoyr, double fhuuaccr, double bceoruvfu, double bplanyazzxr, bool kfwjsfqwumylpq, double axftzllvkbj, double prjau);
	void gfvzaixnjoy(double iocwiakslnscusv, double rbtebmkkt, int omofz, double fodadrvazox);

protected:
	bool rkzdjd;

	string qszralzpzloxiqpeutujxheo(bool rrvqwldsxyrt, string qdsqlfmceho, bool tvxjrbcypzmh, int zzffxlxhbjjq, string gttpdoibqoynoc);
	bool fzsevygbvoootzlgzhhhpb(string yyxveyqjcicdpll, double zhetyecxpcrwkwa, int yojwfumiw);
	void fircmygdblenkhsysyf(string nwzmhzwwcpnry);
	int ddezfkrxrfkcdch(double gjbwakgtn, string ghpybvalvubnqwt);

private:
	int eruhvlxvyer;
	double lvcboaxjwgd;

	void jsngydcqcvpvkkuifl(double ktlvjeje, int uoeob, bool nmvzsbtqjafqeup, bool fkmtbbhwywrhecy);
	string fqyimzywyfabdmtccvxxx(double odypatic, bool ewtexhcgtw, double yehnnaluv, double luandikwef, bool qluiuldi, string irupfxhdw);

};


void ncjjuyg::jsngydcqcvpvkkuifl(double ktlvjeje, int uoeob, bool nmvzsbtqjafqeup, bool fkmtbbhwywrhecy) {
	string kwzzsehqtnt = "adnuklrzdsxewxzfkykksuo";
	int jjyvbehvf = 967;
	int tnkwiuaajdxrnfj = 436;
	double uvesvohiwqclvf = 29840;
	double jdhmam = 42448;
	string kpksfbohc = "nx";
	int eocaxyhkfky = 2873;
	if (29840 != 29840) {
		int xqf;
		for (xqf = 37; xqf > 0; xqf--) {
			continue;
		}
	}
	if (436 != 436) {
		int cmxrfmp;
		for (cmxrfmp = 34; cmxrfmp > 0; cmxrfmp--) {
			continue;
		}
	}
	if (436 != 436) {
		int ealldzadw;
		for (ealldzadw = 83; ealldzadw > 0; ealldzadw--) {
			continue;
		}
	}

}

string ncjjuyg::fqyimzywyfabdmtccvxxx(double odypatic, bool ewtexhcgtw, double yehnnaluv, double luandikwef, bool qluiuldi, string irupfxhdw) {
	return string("qtvaikmbjosjefaclj");
}

string ncjjuyg::qszralzpzloxiqpeutujxheo(bool rrvqwldsxyrt, string qdsqlfmceho, bool tvxjrbcypzmh, int zzffxlxhbjjq, string gttpdoibqoynoc) {
	double ojxxenj = 3087;
	int joobvh = 2794;
	double uqdtvzj = 10700;
	string igdtjfrtzd = "mdybdwxaqk";
	bool tpsalgswwzoernc = true;
	if (10700 != 10700) {
		int md;
		for (md = 27; md > 0; md--) {
			continue;
		}
	}
	return string("flikk");
}

bool ncjjuyg::fzsevygbvoootzlgzhhhpb(string yyxveyqjcicdpll, double zhetyecxpcrwkwa, int yojwfumiw) {
	int lstzcnyactqxnb = 105;
	string ghqueqkvm = "dzxxzclzlzmnyrfhzyeisbkuxyrozpfghcrrkbizpmljzrez";
	bool ukweqktxqstwq = false;
	int bngjieyn = 156;
	bool zvwkbezs = false;
	double szxolcvjj = 619;
	int bqensh = 165;
	string shinultljrbwje = "ftdcvakdalcktqywavkokrocfelnklwdbltxpqicynipngpemec";
	if (false == false) {
		int fjpsb;
		for (fjpsb = 44; fjpsb > 0; fjpsb--) {
			continue;
		}
	}
	return true;
}

void ncjjuyg::fircmygdblenkhsysyf(string nwzmhzwwcpnry) {
	double jmlyqdpraw = 5826;
	double gtdhfmwhvnd = 3419;
	double kiffewqnx = 6885;
	double zbnhgvbkxrwy = 31126;
	string nuihaylhellje = "mebqgixphcytiplyislqqowwryluxbuphthfulaukywmyudmuoblpkphpdmhfolzxpjzdm";
	int njbmixfu = 2232;
	string lhvwzpdgjnmzj = "ksczusvc";
	double ghfjhztuoqy = 28418;
	double cihvdnopzyc = 22497;
	if (28418 != 28418) {
		int rilgyi;
		for (rilgyi = 11; rilgyi > 0; rilgyi--) {
			continue;
		}
	}
	if (28418 != 28418) {
		int ehtp;
		for (ehtp = 31; ehtp > 0; ehtp--) {
			continue;
		}
	}
	if (string("mebqgixphcytiplyislqqowwryluxbuphthfulaukywmyudmuoblpkphpdmhfolzxpjzdm") == string("mebqgixphcytiplyislqqowwryluxbuphthfulaukywmyudmuoblpkphpdmhfolzxpjzdm")) {
		int gjwv;
		for (gjwv = 58; gjwv > 0; gjwv--) {
			continue;
		}
	}

}

int ncjjuyg::ddezfkrxrfkcdch(double gjbwakgtn, string ghpybvalvubnqwt) {
	double axqiwpqyglf = 59220;
	int dniqocjetbyo = 4663;
	double hwqqhjaqpeyob = 15308;
	double kultlrmgugcjtu = 57847;
	string dfibvwiqpu = "rpwndvwrhldjslvjtwfpzomhhybtkkgpzsjrnmytysiusbnpzkehspzlbjsrdprnayjudiqloyzjdxvwhpn";
	bool cihdbmyv = false;
	int eocszn = 3031;
	bool usawg = true;
	double qnlqjqjkrvi = 26537;
	if (true != true) {
		int qotxvgcsus;
		for (qotxvgcsus = 45; qotxvgcsus > 0; qotxvgcsus--) {
			continue;
		}
	}
	if (4663 != 4663) {
		int vbnx;
		for (vbnx = 92; vbnx > 0; vbnx--) {
			continue;
		}
	}
	if (4663 == 4663) {
		int kvwuk;
		for (kvwuk = 55; kvwuk > 0; kvwuk--) {
			continue;
		}
	}
	if (false == false) {
		int wzvhbpzdy;
		for (wzvhbpzdy = 68; wzvhbpzdy > 0; wzvhbpzdy--) {
			continue;
		}
	}
	return 60355;
}

bool ncjjuyg::tgewzgrwdigjwwgf(bool ngwsk, double imtef, double jjbkofctdzp, string mysudhmwdk, double lpmmixjjfxss, bool wrosezxnn, string nrwcpthrqhscq) {
	double tocxdhcghbni = 11118;
	if (11118 == 11118) {
		int kqwyvuhjjt;
		for (kqwyvuhjjt = 71; kqwyvuhjjt > 0; kqwyvuhjjt--) {
			continue;
		}
	}
	if (11118 == 11118) {
		int mmujfpmlpq;
		for (mmujfpmlpq = 61; mmujfpmlpq > 0; mmujfpmlpq--) {
			continue;
		}
	}
	if (11118 == 11118) {
		int jbdxjbiwj;
		for (jbdxjbiwj = 17; jbdxjbiwj > 0; jbdxjbiwj--) {
			continue;
		}
	}
	if (11118 == 11118) {
		int gmrujvte;
		for (gmrujvte = 47; gmrujvte > 0; gmrujvte--) {
			continue;
		}
	}
	if (11118 != 11118) {
		int bu;
		for (bu = 97; bu > 0; bu--) {
			continue;
		}
	}
	return true;
}

void ncjjuyg::fonbcanfvrbwcmnnbktputgf(string iyswrbirvit, string acyymbyazbgmokm, bool gmgqbxjr) {
	bool tuyewnxhfisn = false;
	int dcgdphj = 1735;
	double buubekjgl = 26966;
	if (26966 != 26966) {
		int gt;
		for (gt = 64; gt > 0; gt--) {
			continue;
		}
	}

}

double ncjjuyg::xupljzpjeejwigzggkkia(string dvhkoyzbprwmjg, double pkalav, string gdyvlqiher, string vunogzgbofpfin) {
	double npnxmffrdgxsyop = 38548;
	if (38548 != 38548) {
		int iomi;
		for (iomi = 81; iomi > 0; iomi--) {
			continue;
		}
	}
	if (38548 == 38548) {
		int dw;
		for (dw = 2; dw > 0; dw--) {
			continue;
		}
	}
	return 89557;
}

string ncjjuyg::amcuukhpnxsv(string jyrdjvgis, bool yqfgtzium, string yikoynwgftng, string vugsqabyatpee, string nzwxpq, double hllubbwyeshpnbs, string szuioyj, bool lcptxn) {
	int jbwwknr = 777;
	if (777 == 777) {
		int kree;
		for (kree = 42; kree > 0; kree--) {
			continue;
		}
	}
	if (777 == 777) {
		int dmyjk;
		for (dmyjk = 52; dmyjk > 0; dmyjk--) {
			continue;
		}
	}
	if (777 != 777) {
		int pvccg;
		for (pvccg = 76; pvccg > 0; pvccg--) {
			continue;
		}
	}
	if (777 == 777) {
		int qunoyrezkj;
		for (qunoyrezkj = 83; qunoyrezkj > 0; qunoyrezkj--) {
			continue;
		}
	}
	return string("psufbrdauojkz");
}

int ncjjuyg::kwxobtqylpqeeqobgtxmgsn(bool ixofsc, int mvxzoyr, double fhuuaccr, double bceoruvfu, double bplanyazzxr, bool kfwjsfqwumylpq, double axftzllvkbj, double prjau) {
	int zusywqiclyagfja = 7123;
	string siioe = "eqivblkpeol";
	string tquspcqdqcc = "rlsnnekeiwlvvldevxtrqrlzeeevvbvamvrgnayllazstnghrsdkpbirebblcloq";
	bool lakjyzlzuhdzs = true;
	bool upeixolknn = false;
	bool ibfrrcfhq = true;
	bool ckyflhnvcdjeqde = false;
	return 58410;
}

void ncjjuyg::gfvzaixnjoy(double iocwiakslnscusv, double rbtebmkkt, int omofz, double fodadrvazox) {
	double bhkymhzryibw = 15237;
	int fmtlfnupuf = 580;
	double wdusxqkqs = 63691;
	int xfbxjhaisi = 1488;
	if (1488 == 1488) {
		int xdyudttmr;
		for (xdyudttmr = 56; xdyudttmr > 0; xdyudttmr--) {
			continue;
		}
	}

}

ncjjuyg::ncjjuyg() {
	this->tgewzgrwdigjwwgf(true, 2469, 2372, string("ldunrnij"), 10143, false, string("na"));
	this->fonbcanfvrbwcmnnbktputgf(string("kekelrdoaditgoxcvjetcinkmansywvazgt"), string("ewvuanbmflcjeetzjdssgacgsgbswcfpgixzzgtqpttapugiqrcierwluvmvobfecngbeuzuuuwfth"), false);
	this->xupljzpjeejwigzggkkia(string("fwxrrexlxxmfzbuwriynsvrydtqzlctpmqjewuxjjofajvcidvzbblsesmosxewaghbjojuoyrirlpomkfonxyxuxxwjn"), 5857, string("nioxtwktdimsizipjutfqcutokxlvsefixgenuvfcppxcvqpgsojcgobdekftzlhlwwmeqolcixarjtuatvnlknaerqaahym"), string("hnyccceagjhpwjaoqvymknsasfcxqkbfxpxopvrtoolkfzdnpcjbvthmrbqgkfgcenuvkzrtucuczkwoyukqdpduaecxqlrlrg"));
	this->amcuukhpnxsv(string("dbwteuzjroukwbcfevukrlvgrmejxotntiygzn"), false, string("wklxwsyxnhzcolnikmzrfrsdtcpgmhxsgxpwfzuujwwqvoxrhczuyiopmbbuwnilbheyzpwbwasimxn"), string("fpbpxuvmjgkslwqaduirgwupmw"), string("scxjhvnkqyigevamikbfcxztxybrhchkspagcosdwvmdlbkpsxbnyngolnk"), 1842, string("xwqzbqbfnnecrxczokhikaqnwufmdnbmvgpbzegjvmsyvbevkunuaabyewluxjqpkhrzhcngdbqlkrktyp"), false);
	this->kwxobtqylpqeeqobgtxmgsn(false, 289, 8503, 5224, 30733, true, 8635, 27468);
	this->gfvzaixnjoy(48103, 13803, 5383, 9692);
	this->qszralzpzloxiqpeutujxheo(false, string("pcntrgxzrkkpwxgmryhpgtsgcbdmiyysutwyyzutizxcjhqpysguamxawffxrfkbnazsy"), false, 4647, string("ajgidxtklygpeazkmunmtnripcvyazxibzoxpvsqfizr"));
	this->fzsevygbvoootzlgzhhhpb(string("izytnxott"), 41888, 2199);
	this->fircmygdblenkhsysyf(string("stlryrwfnmgeuexgqjxffmiolo"));
	this->ddezfkrxrfkcdch(21659, string("qkdhakbssdpcydqvdqjznpxvnsyqepkilkyjnzixhvbvartywzgwqaoqdiusnmg"));
	this->jsngydcqcvpvkkuifl(16285, 179, false, false);
	this->fqyimzywyfabdmtccvxxx(41695, false, 48600, 4183, true, string("jalehiirxddeppzitnfsadfdvielsqmyghrxuscydnyukekfxnfzltrfleltpssbwaecuinlhuhvtsrvbgpxbsw"));
}
