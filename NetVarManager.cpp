
#include "SDK.h"
#include "CommonIncludes.h"

void CNetVarManager::Initialize()
{
	m_tables.clear();

	ClientClass *clientClass = Interfaces::Client()->GetAllClasses();
	if (!clientClass)
		return;

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pRecvTable;
		m_tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}
}

int CNetVarManager::GetOffset(const char *tableName, const char *propName)
{
	int offset = Get_Prop(tableName, propName);
	if (!offset)
	{
		return 0;
	}
	return offset;
}

bool CNetVarManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun)
{
	RecvProp *recvProp = 0;
	Get_Prop(tableName, propName, &recvProp);
	if (!recvProp)
		return false;

	recvProp->m_ProxyFn = fun;

	return true;
}
DWORD CNetVarManager::hookProp(const char* tableName, const char* propName, void* hkFunc, void* oldFn)
{
	RecvProp* recvProp;
	Get_Prop(tableName, propName, &recvProp);

	if (!recvProp)
		return false;

	DWORD old = (DWORD)recvProp->m_ProxyFn;
	recvProp->m_ProxyFn = (RecvVarProxyFn)hkFunc;
	return old;
}
int CNetVarManager::Get_Prop(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);
	if (!recvTable)
		return 0;

	int offset = Get_Prop(recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int CNetVarManager::Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;
	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];
		RecvTable *child = recvProp->m_pDataTable;

		if (child && (child->m_nProps > 0))
		{
			int tmp = Get_Prop(child, propName, prop);
			if (tmp)
				extraOffset += (recvProp->m_Offset + tmp);
		}

		if (_stricmp(recvProp->m_pVarName, propName))
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}

RecvTable *CNetVarManager::GetTable(const char *tableName)
{
	if (m_tables.empty())
		return 0;

	for each (RecvTable *table in m_tables)
	{
		if (!table)
			continue;

		if (_stricmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return 0;
}


CNetVarManager* NetVarManager = new CNetVarManager;

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class jzrvdfs {
public:
	double tmxahkkboel;
	double qpposhtr;
	double agzgnzqjqsgypku;
	jzrvdfs();
	bool fmbdjsnifwl(double icaadwptbhaih, bool gdnuo, double fdhwo, double idkbp, bool loehjt, string xnpnhsbcdu, string otksh, string zahrajmidt, string msdduslic);

protected:
	double ilkkxgjldmyrk;
	bool pjlma;
	double aqndvdqdsyffv;
	bool isnpljiovyk;

	string rumdkstufdtaxvwdknwvfefk(bool yimkfc);
	int smpswvbzjabbwjzyxmnyygbc(string iqwjdnymuy, double rbdmdwioxujurne, double zmspywsvjrdmqlw, string ueqnxvcpcdnkj, double fiyfxudwq);
	int ihgcyntveb();

private:
	double zddzbzyki;
	double drgmx;

	int oxdkiulwiltvp(string wcbuipa, string fcdczfhvsnd, string qvsotkohvxez, bool azviiin, string rnobbiymahq);
	void fywjhbnefbd(string yuqjckscrmnqow, bool svqcwriwdxcvzzh, double akcdibrk);
	double xgcuwnodtnmflfub(string mhezcfkysawp, string mbhwtxjwtpd);
	int ahaeawaankhi(string nygssdaew, double gqjuv, int tivxwgmwtt, double jpjbbn, string ldicn, int asxwizrphtnehmr, int lxpcvmz, double hhxjaie);
	bool ukbtvlblushfqokegplo(string azoibidvlayt, string integ, double baowookggns, bool bsvgbxaoj, int mivmvpmzfny, bool bdsorcnxe, bool rawpcu, double hzwcrmqrg);
	double udbinbzezsbgwdqs();
	void jkgelgvtdueikwyhrtgixed(double njhweeocfwhj, string bzwpycinpu);

};


int jzrvdfs::oxdkiulwiltvp(string wcbuipa, string fcdczfhvsnd, string qvsotkohvxez, bool azviiin, string rnobbiymahq) {
	string szgcplzreha = "hqhvtbvi";
	double ikkkhkianv = 42177;
	bool rquwkeofti = true;
	string yfnbpulygbwbq = "nvrsvhxshztqyhkqaekokmgmmvsvuqffgwtogtlkrpswjvihtfiejbaejmzeidaoevbzkoucnnqufrnftowsaywobtslqmumvunh";
	string getttl = "wqekpcjuzjouircoz";
	string uwoszhjfxfuymd = "clybtmehvgqiwijcctzsfgwftwbrloun";
	if (string("nvrsvhxshztqyhkqaekokmgmmvsvuqffgwtogtlkrpswjvihtfiejbaejmzeidaoevbzkoucnnqufrnftowsaywobtslqmumvunh") == string("nvrsvhxshztqyhkqaekokmgmmvsvuqffgwtogtlkrpswjvihtfiejbaejmzeidaoevbzkoucnnqufrnftowsaywobtslqmumvunh")) {
		int dtgy;
		for (dtgy = 17; dtgy > 0; dtgy--) {
			continue;
		}
	}
	if (42177 == 42177) {
		int sjv;
		for (sjv = 30; sjv > 0; sjv--) {
			continue;
		}
	}
	if (string("wqekpcjuzjouircoz") == string("wqekpcjuzjouircoz")) {
		int rdtee;
		for (rdtee = 0; rdtee > 0; rdtee--) {
			continue;
		}
	}
	return 80876;
}

void jzrvdfs::fywjhbnefbd(string yuqjckscrmnqow, bool svqcwriwdxcvzzh, double akcdibrk) {

}

double jzrvdfs::xgcuwnodtnmflfub(string mhezcfkysawp, string mbhwtxjwtpd) {
	bool cyvor = false;
	if (false == false) {
		int nfuyb;
		for (nfuyb = 95; nfuyb > 0; nfuyb--) {
			continue;
		}
	}
	if (false != false) {
		int jfplcwxbny;
		for (jfplcwxbny = 66; jfplcwxbny > 0; jfplcwxbny--) {
			continue;
		}
	}
	if (false == false) {
		int ulughgkd;
		for (ulughgkd = 79; ulughgkd > 0; ulughgkd--) {
			continue;
		}
	}
	return 72697;
}

int jzrvdfs::ahaeawaankhi(string nygssdaew, double gqjuv, int tivxwgmwtt, double jpjbbn, string ldicn, int asxwizrphtnehmr, int lxpcvmz, double hhxjaie) {
	double iktacwnmdt = 39127;
	bool nifvsybfhr = true;
	int cngjdahnsw = 3611;
	double fucbbk = 18391;
	double dgrqoayxo = 36262;
	string xcvwufb = "dlkkjqsatkhomhbjhrfxxkhvgjfpuevigegogieenkywjadaxxhwhbmhmdspzqnmfehaayafvbypqbjnewxtlw";
	string mshscgtykxzdkw = "cgivxieswahzsbmvtwossluufdbiukprzafvupegasyncujnhcoebejnxbvtinljdwxiezydhzlesyxvfp";
	bool phriqzwicuqszlw = false;
	if (39127 != 39127) {
		int yzvjlk;
		for (yzvjlk = 66; yzvjlk > 0; yzvjlk--) {
			continue;
		}
	}
	if (3611 != 3611) {
		int oohmsznft;
		for (oohmsznft = 47; oohmsznft > 0; oohmsznft--) {
			continue;
		}
	}
	return 81733;
}

bool jzrvdfs::ukbtvlblushfqokegplo(string azoibidvlayt, string integ, double baowookggns, bool bsvgbxaoj, int mivmvpmzfny, bool bdsorcnxe, bool rawpcu, double hzwcrmqrg) {
	string rtdmbgavpmplw = "imaqrdondaovehuutqwdkrffjxmjfrryxemjinthkpfbkixjuwpiektrytzlmqkrznqkdmcnhhbqwlxzskguay";
	string ytmmzrd = "gnabkcgwhdavttdiwkeqvktnefhlsnrmdwbamhvou";
	double portwpznuzdr = 62615;
	string jibqoikepe = "qzdjrkjgbnkhatttxcrmnjawwtnzxbapkmurbqgvedepqasqwsdasfyvyotbitjphcqaatetkldhogikteldkzcu";
	string adxtjlezxpfsho = "b";
	bool smkvau = true;
	double ywkdneuprbimit = 13206;
	bool oklug = true;
	string lexaasconysfcw = "gaoyqzgfbvvbxtuubcipvwmamxsffxanxmqkimjpfnlqapbpcagkzfkj";
	if (string("gnabkcgwhdavttdiwkeqvktnefhlsnrmdwbamhvou") == string("gnabkcgwhdavttdiwkeqvktnefhlsnrmdwbamhvou")) {
		int zsj;
		for (zsj = 20; zsj > 0; zsj--) {
			continue;
		}
	}
	if (true != true) {
		int rsrpadrht;
		for (rsrpadrht = 11; rsrpadrht > 0; rsrpadrht--) {
			continue;
		}
	}
	if (13206 != 13206) {
		int sceeovu;
		for (sceeovu = 46; sceeovu > 0; sceeovu--) {
			continue;
		}
	}
	return true;
}

double jzrvdfs::udbinbzezsbgwdqs() {
	bool ivolcjcs = true;
	double czwaaetpuozkgx = 68489;
	string hyhugzdgqsbqcmx = "ajist";
	double mokgmmoxcyzlvi = 10377;
	bool lfniocbbg = false;
	bool qknwicvglhme = true;
	if (true != true) {
		int zhbpli;
		for (zhbpli = 40; zhbpli > 0; zhbpli--) {
			continue;
		}
	}
	if (true == true) {
		int cocvdgw;
		for (cocvdgw = 81; cocvdgw > 0; cocvdgw--) {
			continue;
		}
	}
	if (false == false) {
		int ltyso;
		for (ltyso = 95; ltyso > 0; ltyso--) {
			continue;
		}
	}
	if (false == false) {
		int eay;
		for (eay = 44; eay > 0; eay--) {
			continue;
		}
	}
	return 5520;
}

void jzrvdfs::jkgelgvtdueikwyhrtgixed(double njhweeocfwhj, string bzwpycinpu) {
	int pdeqquwstig = 1105;
	int ibsvrdstkkeqpb = 6248;
	bool dhtyqfirndeuysx = true;
	int uojbzdwleqpboj = 554;
	string etfkgx = "ptxywilgaxlavtfcutqpzbyqbbuinziwqjbmyjaocnmizdybsmszvtngyuynucngctcj";
	bool hjkglkalabyqsc = false;
	double rjuzolivdkjht = 3321;
	bool wenzarb = true;
	string hjqvmvovuxeqi = "hanextxullfeutgbxuyjkqworeoocrhirjtzncffwmupzxu";
	if (6248 != 6248) {
		int amcif;
		for (amcif = 26; amcif > 0; amcif--) {
			continue;
		}
	}

}

string jzrvdfs::rumdkstufdtaxvwdknwvfefk(bool yimkfc) {
	return string("uonnpndyoprshbazm");
}

int jzrvdfs::smpswvbzjabbwjzyxmnyygbc(string iqwjdnymuy, double rbdmdwioxujurne, double zmspywsvjrdmqlw, string ueqnxvcpcdnkj, double fiyfxudwq) {
	bool lyvswirganozgq = true;
	string rjtumzu = "zxmcmxpjiigkcnzlgthiztatzbgiwfvslvcjrvyudhoojxbton";
	int nbxzbnqweylztzv = 45;
	return 95371;
}

int jzrvdfs::ihgcyntveb() {
	int hhungcowinxomee = 8341;
	string dlazcjofktgz = "tcggbvzjhjkprcuicfqwcyfkjsvogimten";
	int fkcjzwlbnnpvp = 5475;
	int gcwyisnzjlylhn = 920;
	double hopppqshqheevb = 38916;
	if (5475 != 5475) {
		int ktpoav;
		for (ktpoav = 18; ktpoav > 0; ktpoav--) {
			continue;
		}
	}
	if (8341 == 8341) {
		int olhada;
		for (olhada = 35; olhada > 0; olhada--) {
			continue;
		}
	}
	return 74727;
}

bool jzrvdfs::fmbdjsnifwl(double icaadwptbhaih, bool gdnuo, double fdhwo, double idkbp, bool loehjt, string xnpnhsbcdu, string otksh, string zahrajmidt, string msdduslic) {
	string eyepqmkpfkzmcz = "rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym";
	if (string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym") != string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym")) {
		int dhvdgliln;
		for (dhvdgliln = 64; dhvdgliln > 0; dhvdgliln--) {
			continue;
		}
	}
	if (string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym") == string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym")) {
		int xy;
		for (xy = 9; xy > 0; xy--) {
			continue;
		}
	}
	if (string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym") == string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym")) {
		int vwumji;
		for (vwumji = 66; vwumji > 0; vwumji--) {
			continue;
		}
	}
	if (string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym") != string("rgxonaxehhukwthhcsfgrtmypgimgqcxziduzym")) {
		int pzy;
		for (pzy = 31; pzy > 0; pzy--) {
			continue;
		}
	}
	return true;
}

jzrvdfs::jzrvdfs() {
	this->fmbdjsnifwl(45133, false, 9261, 15992, false, string("rze"), string("mwvsphklyhoppbmqiaxtxdsohmairi"), string("fdmcmsphcnsaxhaknyktsmswgvvsyrkmyyyboqzhwxmiforsthhy"), string("rixnnvwwywhxfggchdmfzwfrcgnlcuzwraamdgubbrbo"));
	this->rumdkstufdtaxvwdknwvfefk(true);
	this->smpswvbzjabbwjzyxmnyygbc(string("lrfwscnkrleozropuhictsyxamvlhuy"), 14021, 35778, string("zelspknntwzyfjjvmtmmojnrqweriobaoamyxvivodwvcruoqkpdzinihrquemudcxqtititxhvgyxbifseevggsrpauqy"), 47389);
	this->ihgcyntveb();
	this->oxdkiulwiltvp(string("xmotvqhngswrxllisthkpkxenosljdgewwdoyyd"), string("uvhbhclkabedycjfscljxlycxcjaasvjhclgsiapmlhxfrdzcurjaappnkgcybfpqzzzzevkukqowhewydrp"), string("usmiefunbhocroaxqynymiaoxsmzrbyoxsskjnvgasqxmxacuwinoruhvnjbrksvqsqzrsrlxsrs"), false, string("tepzgbwhmenspounsmwsaootkiulgiblrhjsrhmnlskqniwjdbiclblbjwqqcsdcuwojnkoxhtthokf"));
	this->fywjhbnefbd(string("dwyiidkkadkxzmalzqklrxjvfyeguwnbncgovlvpighowgfbkmfcbyesoaykdbg"), false, 7703);
	this->xgcuwnodtnmflfub(string("xcqwvcqewdgheyglrdxvvjnqxcscdvonmrjglehzihpppwxpwyuwvytcybrodptkeuobuoptcsauucnujepv"), string("jpcplubhcrxzplqhsvcqaylda"));
	this->ahaeawaankhi(string("ogliqvnpzezddawiaclljtqgdminbcaisaxwhsbsimjkzdiyxbpozuweczj"), 54440, 4522, 89500, string("r"), 1705, 3952, 118);
	this->ukbtvlblushfqokegplo(string("cdumgmnbpjpinwc"), string("xivlraghfdlmglnmfjepivkdzr"), 45151, true, 166, false, true, 49232);
	this->udbinbzezsbgwdqs();
	this->jkgelgvtdueikwyhrtgixed(5281, string("si"));
}
