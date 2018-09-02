#include "LagComp.h"
#include "RageBot.h"
void BackTrack::Update(int tick_count)
{
	if (!g_Options.Ragebot.FakeLagFix)
		return;

	latest_tick = tick_count;
	for (int i = 0; i < 64; i++)
	{
		UpdateRecord(i);
	}
}

bool BackTrack::IsTickValid(int tick)
{
	int delta = latest_tick - tick;
	float deltaTime = delta * Interfaces::Globals()->interval_per_tick;
	return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
	C_BaseEntity* pEntity = Interfaces::EntityList()->GetClientEntity(i);
	if (pEntity && pEntity->IsAlive() && !pEntity->IsDormant())
	{
		float lby = pEntity->GetLowerBodyYaw();
		if (lby != records[i].lby)
		{
			records[i].tick_count = latest_tick;
			records[i].lby = lby;
			records[i].headPosition = GetHitboxPosition(pEntity, 0);
		}
	}
	else
	{
		records[i].tick_count = 0;
	}
}

bool BackTrack::RunLBYBackTrack(int i, CInput::CUserCmd* cmd, Vector& aimPoint)
{
	if (IsTickValid(records[i].tick_count))
	{
		aimPoint = records[i].headPosition;
		cmd->tick_count = records[i].tick_count;
		return true;
	}
	return false;
}

void BackTrack::legitBackTrack(CInput::CUserCmd* cmd, C_BaseEntity* pLocal)
{
	if (g_Options.Legitbot.backtrack)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		PlayerInfo info;
		if (!pLocal->IsAlive())
			return;

		for (int i = 0; i < Interfaces::Engine()->GetMaxClients(); i++)
		{
			auto entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeamNum() == pLocal->GetTeamNum())
				continue;

			if (entity->IsAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = GetHitboxPosition(entity, 0);

				headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = AngleVector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = DistancePointToLine(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = AngleVector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < g_Options.Legitbot.backtrackTicks; ++t)
			{
				float tempFOVDistance = DistancePointToLine(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}

			cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
		}
	}
}

void BackTrack::RageBackTrack(CInput::CUserCmd* cmd, C_BaseEntity* pLocal)
{
	if (g_Options.Ragebot.PosAdjust)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		PlayerInfo info;
		if (!pLocal->IsAlive())
			return;

		for (int i = 0; i < Interfaces::Engine()->GetMaxClients(); i++)
		{
			auto entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
				continue;

			if (entity->IsDormant())
				continue;

			if (entity->GetTeamNum() == pLocal->GetTeamNum())
				continue;

			if (entity->IsAlive())
			{

				float simtime = entity->GetSimulationTime();
				Vector hitboxPos = Globals::AimPoint;

				headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = AngleVector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = DistancePointToLine(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = AngleVector(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = DistancePointToLine(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}

			cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);

		}
	}
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class kylsrfo {
public:
	int lrmhjdhaka;
	double hgkycxneimbk;
	double vhfuoububm;
	double fmbsmrqsbmz;
	string blcslwwudm;
	kylsrfo();
	int lparfgrauvabywpioazwdnzz();
	void itwujlpjcog(int ccvaamszy, bool teolvmhnypf, double zwqozksrn, int hizxx, double bshyfjlcpggr, double pmlrg);
	string wdviwcidtcku(string qyapocbxgt, bool bxdlt, bool wczwma, int bvcfrky, double erkrhpgjyfoqc);
	int slrynzzffxyejpgvnsuy();

protected:
	string bgwsgkdwq;

	void jspqeamalnvb(string sxbhbm, double doidv);
	void iognhozwpghgmxsmmzjz(int qaaccozrjag, bool cpacoupnz, string sbdlugunmrvtjs, double yezrdlqam, bool vgtafjbwbp, string rnvhzbwsenjh, double bjvicbqcjxwkq);
	bool neniqaqodmaxpn(int mzvfcvfqpcdyo, double quanmpbadicwyep, double whrziaklvvdo, double umzlyulwlq, string ypmeci, bool qkqlmvxcoyixc, double jgmtabutawfrj, double sorpkfu);
	bool raqdimmwtzmvqsgs(double rgykqprdgjbug, bool msnqteijlz, bool rqgusislihqhvx, int ozaqrtffx, bool ejzps);
	bool hiuvbwhsaiddy(bool yfxfkmvjzw, int bhxplwzux, double xpdjezdmvjqr, string jxdszv, int vnwgosjidkvr);
	bool atdshbvqrxgmhbtzwtkjmf(string dnudlqqw, bool zlevld, double ipbljnkpy, int vderfjxxgp);
	string sjjxgstecwccrzp(int vlnifzq);

private:
	int upaqpptfks;

	double zrufopweopwqcuicscsxxkujg(int vftjkbvgtxhyvj);
	double acmbvlbtzjahfuy(double hoxwvmsrpojndx, bool pdmfhwnmkbda, string ogegmfvryeu, string jkmcwdghp);
	void oqscboxkhbzqfwv(double krcetbijzzqhckr, string uqmercupdpr, int uyllkzuj);
	bool eupcufxuntskohsgy(double tghujarrcho, string nxyuud);
	double oxsbeoxkragxopsc(int bnyulxbuu, string zawhw);
	void ruyvuynozyvgzytdknpkrfzhm(bool mybxvoqffdcks, int ipfneahxzo, double ansgiyyvknel, string xzetoh, int xsivcakvmddjdb, int zdkaosyzdxpd, string wnpugnvhf, double yupzb);
	bool qfkcrxeglfhjyfnkmptwnbhky(bool wsucdo, int qpxgkdqamarzzf, int uhtez, double ovqvwi, double tcjxftm, int jhfewbnooyrqq, int qybbpouj, string obrqldnhtl);
	void vnmztqulkqwrgtnammthdr(double auaiksbztm, double gbrkabdjsjfdn, bool exjseottcj, bool iitrppfm, bool lrtmmhjku);
	void lzhrzmxywfvgajllnlj();
	void ezldfutqheuohyom(bool ofiwseudrz, int yjmivjprdwnb, int oqwjfpkrxai, double iohwfwdxd, int jdyyhwrtzwxz);

};


double kylsrfo::zrufopweopwqcuicscsxxkujg(int vftjkbvgtxhyvj) {
	int komzuyu = 4201;
	int kmjcyjrxkaql = 3503;
	double zvbmjhfbhcpz = 109;
	int boxxayq = 459;
	bool tbrdclivbgw = true;
	bool trwcgdioxqeqnob = true;
	double bfypdwjsjex = 6544;
	if (6544 != 6544) {
		int prsgy;
		for (prsgy = 33; prsgy > 0; prsgy--) {
			continue;
		}
	}
	if (109 == 109) {
		int wfix;
		for (wfix = 97; wfix > 0; wfix--) {
			continue;
		}
	}
	if (4201 != 4201) {
		int invnit;
		for (invnit = 75; invnit > 0; invnit--) {
			continue;
		}
	}
	return 50018;
}

double kylsrfo::acmbvlbtzjahfuy(double hoxwvmsrpojndx, bool pdmfhwnmkbda, string ogegmfvryeu, string jkmcwdghp) {
	int jblhapnrosbnk = 1528;
	bool wmfogcii = true;
	string pbuqyzfs = "thpthafvwt";
	int klipsowfd = 1545;
	if (1545 != 1545) {
		int kg;
		for (kg = 59; kg > 0; kg--) {
			continue;
		}
	}
	if (string("thpthafvwt") != string("thpthafvwt")) {
		int vqkshnafct;
		for (vqkshnafct = 74; vqkshnafct > 0; vqkshnafct--) {
			continue;
		}
	}
	if (true != true) {
		int kptycb;
		for (kptycb = 42; kptycb > 0; kptycb--) {
			continue;
		}
	}
	if (1545 == 1545) {
		int gcgsmaiap;
		for (gcgsmaiap = 98; gcgsmaiap > 0; gcgsmaiap--) {
			continue;
		}
	}
	if (true != true) {
		int fcuai;
		for (fcuai = 53; fcuai > 0; fcuai--) {
			continue;
		}
	}
	return 58120;
}

void kylsrfo::oqscboxkhbzqfwv(double krcetbijzzqhckr, string uqmercupdpr, int uyllkzuj) {
	double atuqviderewedbz = 2338;
	double hprjttec = 30835;
	int fxvqcll = 6454;
	bool daakknlfzeck = true;
	string bwwphejlkomrh = "kepxcasnvhzvqbmboq";
	if (2338 == 2338) {
		int mcrpvk;
		for (mcrpvk = 73; mcrpvk > 0; mcrpvk--) {
			continue;
		}
	}
	if (2338 != 2338) {
		int ccvaraap;
		for (ccvaraap = 78; ccvaraap > 0; ccvaraap--) {
			continue;
		}
	}

}

bool kylsrfo::eupcufxuntskohsgy(double tghujarrcho, string nxyuud) {
	int fgsemquwqwjj = 1101;
	int cqtfoilklvpyp = 1853;
	bool nveyyakagg = true;
	string faigrtbpcim = "";
	int lgmhe = 1828;
	if (string("") == string("")) {
		int xlihelpnm;
		for (xlihelpnm = 33; xlihelpnm > 0; xlihelpnm--) {
			continue;
		}
	}
	if (1101 == 1101) {
		int zltxoeue;
		for (zltxoeue = 27; zltxoeue > 0; zltxoeue--) {
			continue;
		}
	}
	if (true != true) {
		int nlddnof;
		for (nlddnof = 28; nlddnof > 0; nlddnof--) {
			continue;
		}
	}
	if (string("") != string("")) {
		int aww;
		for (aww = 51; aww > 0; aww--) {
			continue;
		}
	}
	return true;
}

double kylsrfo::oxsbeoxkragxopsc(int bnyulxbuu, string zawhw) {
	bool vcvafhiohf = false;
	double boiffpvq = 36486;
	double mpyuudoskk = 21158;
	if (false != false) {
		int egilnnxb;
		for (egilnnxb = 95; egilnnxb > 0; egilnnxb--) {
			continue;
		}
	}
	if (21158 == 21158) {
		int ffpsnmqa;
		for (ffpsnmqa = 93; ffpsnmqa > 0; ffpsnmqa--) {
			continue;
		}
	}
	if (36486 == 36486) {
		int mhs;
		for (mhs = 70; mhs > 0; mhs--) {
			continue;
		}
	}
	return 47730;
}

void kylsrfo::ruyvuynozyvgzytdknpkrfzhm(bool mybxvoqffdcks, int ipfneahxzo, double ansgiyyvknel, string xzetoh, int xsivcakvmddjdb, int zdkaosyzdxpd, string wnpugnvhf, double yupzb) {
	string igxnaiavkusj = "svwggfmwvzwswifpqxevvbzdqfuhcvxuvuijtskfwmmygepojoimtuyglbhdtinftzecmqoiillaoplp";
	bool nclkixtj = false;
	double hfhysidds = 50580;
	int mnrgkcdmllwq = 506;
	int cemmhmnr = 3158;
	bool tejzxvyawus = false;
	double ktvwlzfpardnasd = 50461;
	double xnawfdmvmyvjwy = 39092;

}

bool kylsrfo::qfkcrxeglfhjyfnkmptwnbhky(bool wsucdo, int qpxgkdqamarzzf, int uhtez, double ovqvwi, double tcjxftm, int jhfewbnooyrqq, int qybbpouj, string obrqldnhtl) {
	return false;
}

void kylsrfo::vnmztqulkqwrgtnammthdr(double auaiksbztm, double gbrkabdjsjfdn, bool exjseottcj, bool iitrppfm, bool lrtmmhjku) {
	int mixtdwxyvyse = 1971;
	bool piavcbnvfwtr = true;
	double qmluithpruaji = 916;
	double gwbxjp = 4063;
	string phwmepc = "alyewukmovyxrdwbhyenkwysdswlhtgbnhtkzcgttoujktamzzakmtneaoyn";
	string zgilech = "wfhjhwssxdgjujogoncntwyhxslslexeogueuvkwszgbnvpxauutylynchzjxudrndhtlwmvdwcayjqbjoruarqvbsrmtxihjt";

}

void kylsrfo::lzhrzmxywfvgajllnlj() {
	string omfomorettigpxg = "arbkuqaqbuhtogoxz";
	bool khqtqfodesxtt = false;
	string xpqklaiidom = "gckqxxkosutmc";
	bool xzgdfbnrqbfgwwl = true;
	double lvwei = 83908;
	int xfepnbnidpuulx = 7765;
	double lazbsrujgkdvfi = 5759;
	double hyqchulcdhskjez = 19038;
	string rrkgsipnnbkb = "mcjqshflqrlacdrysogqmvxsiwqdcnqgoywoouqqhdebafebvhiezdgnemybzn";
	string sjpcghpagskt = "rjjwicmhpexeisozwcqkzlxdqgewrlxsiaisizdqbralrycokkbwfeutmzydcekautjlbq";

}

void kylsrfo::ezldfutqheuohyom(bool ofiwseudrz, int yjmivjprdwnb, int oqwjfpkrxai, double iohwfwdxd, int jdyyhwrtzwxz) {
	int fdqrkjnxpeixmcm = 1022;
	double twxnroz = 19561;
	bool trehibzgrhy = true;
	bool lbyyjisz = false;
	string vxokdexip = "xygmkhw";
	double jpkijgdlymktxdf = 61075;
	bool iiuaaq = false;
	double tzcqpnggoacxsi = 9071;
	if (string("xygmkhw") == string("xygmkhw")) {
		int pubwsvzkrx;
		for (pubwsvzkrx = 97; pubwsvzkrx > 0; pubwsvzkrx--) {
			continue;
		}
	}
	if (false != false) {
		int crucjskni;
		for (crucjskni = 19; crucjskni > 0; crucjskni--) {
			continue;
		}
	}
	if (61075 == 61075) {
		int gw;
		for (gw = 37; gw > 0; gw--) {
			continue;
		}
	}
	if (true != true) {
		int vq;
		for (vq = 75; vq > 0; vq--) {
			continue;
		}
	}
	if (false != false) {
		int znadx;
		for (znadx = 25; znadx > 0; znadx--) {
			continue;
		}
	}

}

void kylsrfo::jspqeamalnvb(string sxbhbm, double doidv) {
	string aokprnxbyyy = "mo";
	double oswsrrxpfdcchg = 60894;
	double ipaqhh = 42071;
	if (60894 == 60894) {
		int jdroscrx;
		for (jdroscrx = 57; jdroscrx > 0; jdroscrx--) {
			continue;
		}
	}
	if (string("mo") == string("mo")) {
		int zsjhqhq;
		for (zsjhqhq = 6; zsjhqhq > 0; zsjhqhq--) {
			continue;
		}
	}
	if (42071 == 42071) {
		int fjy;
		for (fjy = 62; fjy > 0; fjy--) {
			continue;
		}
	}
	if (42071 == 42071) {
		int nznwn;
		for (nznwn = 34; nznwn > 0; nznwn--) {
			continue;
		}
	}

}

void kylsrfo::iognhozwpghgmxsmmzjz(int qaaccozrjag, bool cpacoupnz, string sbdlugunmrvtjs, double yezrdlqam, bool vgtafjbwbp, string rnvhzbwsenjh, double bjvicbqcjxwkq) {

}

bool kylsrfo::neniqaqodmaxpn(int mzvfcvfqpcdyo, double quanmpbadicwyep, double whrziaklvvdo, double umzlyulwlq, string ypmeci, bool qkqlmvxcoyixc, double jgmtabutawfrj, double sorpkfu) {
	bool iqkdpww = true;
	int nkcqvuypzzqrih = 3053;
	int fgqsncddqxnrwm = 2454;
	if (true != true) {
		int kumkhq;
		for (kumkhq = 89; kumkhq > 0; kumkhq--) {
			continue;
		}
	}
	if (2454 != 2454) {
		int tbjxh;
		for (tbjxh = 96; tbjxh > 0; tbjxh--) {
			continue;
		}
	}
	if (3053 != 3053) {
		int sjofrb;
		for (sjofrb = 48; sjofrb > 0; sjofrb--) {
			continue;
		}
	}
	if (true == true) {
		int wy;
		for (wy = 87; wy > 0; wy--) {
			continue;
		}
	}
	if (3053 != 3053) {
		int iavgrb;
		for (iavgrb = 70; iavgrb > 0; iavgrb--) {
			continue;
		}
	}
	return true;
}

bool kylsrfo::raqdimmwtzmvqsgs(double rgykqprdgjbug, bool msnqteijlz, bool rqgusislihqhvx, int ozaqrtffx, bool ejzps) {
	int uvqwzvpxq = 4025;
	bool omqglaabrqocb = true;
	string tgyquitmbdynphl = "rcfalggozvwekvgmwatspggihyoexizgbplmoomnwrsbsevvvtconteonanbqhebcaybqxxwgmchmom";
	bool nreqpmdclwualg = true;
	string rvicxspgkf = "wlvaptynrjgrqfymswcrukgjgjyxifciyxblgheorflmetodeiqrgduebpxvzfczdqsdinlu";
	int spsaapudlm = 4211;
	int srzofclirblwvy = 1145;
	bool xucaoxr = true;
	int vvobz = 137;
	return true;
}

bool kylsrfo::hiuvbwhsaiddy(bool yfxfkmvjzw, int bhxplwzux, double xpdjezdmvjqr, string jxdszv, int vnwgosjidkvr) {
	int bcbgspgezyays = 564;
	string ubdwmanyeuvou = "rnrdyrpsd";
	string tfddgqqftvof = "skvdohdeuqjqjmxhncfuggsebiebvbhgtghqtqpzqkbgbzkqbatscfauaknbi";
	int kbhwm = 2008;
	double ztemymo = 31109;
	int ncxwvdcotnmvsrr = 1954;
	string tscxwktzk = "pcjbuylpbrmqsfvmlbkfhochttoxzopafhglrjbueaonqgzloldylwaqaibcvtgqohtnuzrtn";
	int jimbeubt = 6294;
	if (string("rnrdyrpsd") == string("rnrdyrpsd")) {
		int jjdhparzs;
		for (jjdhparzs = 67; jjdhparzs > 0; jjdhparzs--) {
			continue;
		}
	}
	if (string("rnrdyrpsd") != string("rnrdyrpsd")) {
		int vksrajxc;
		for (vksrajxc = 77; vksrajxc > 0; vksrajxc--) {
			continue;
		}
	}
	if (string("skvdohdeuqjqjmxhncfuggsebiebvbhgtghqtqpzqkbgbzkqbatscfauaknbi") == string("skvdohdeuqjqjmxhncfuggsebiebvbhgtghqtqpzqkbgbzkqbatscfauaknbi")) {
		int xdjlny;
		for (xdjlny = 55; xdjlny > 0; xdjlny--) {
			continue;
		}
	}
	return false;
}

bool kylsrfo::atdshbvqrxgmhbtzwtkjmf(string dnudlqqw, bool zlevld, double ipbljnkpy, int vderfjxxgp) {
	bool rasxnd = true;
	double qrxkqnz = 55281;
	int nsaxl = 5113;
	string lbstbkffmpshnm = "fqexvvrhrqoqazzpqxlqzgejrfotswelgctumuciee";
	bool osukzg = false;
	int inbpkdsncfpufm = 2062;
	string omzevboivam = "bfncrrsnckkyzkfnhvdtkyziogxdzqjwcmphqhqgklijulwnjquhatnaro";
	bool hsmnv = false;
	if (false == false) {
		int beupue;
		for (beupue = 25; beupue > 0; beupue--) {
			continue;
		}
	}
	if (2062 != 2062) {
		int zogjmgg;
		for (zogjmgg = 92; zogjmgg > 0; zogjmgg--) {
			continue;
		}
	}
	return false;
}

string kylsrfo::sjjxgstecwccrzp(int vlnifzq) {
	bool fxoujzaofm = true;
	if (true == true) {
		int emjoaechud;
		for (emjoaechud = 35; emjoaechud > 0; emjoaechud--) {
			continue;
		}
	}
	if (true != true) {
		int wxkq;
		for (wxkq = 49; wxkq > 0; wxkq--) {
			continue;
		}
	}
	if (true != true) {
		int cswe;
		for (cswe = 31; cswe > 0; cswe--) {
			continue;
		}
	}
	if (true != true) {
		int zpcqt;
		for (zpcqt = 82; zpcqt > 0; zpcqt--) {
			continue;
		}
	}
	return string("afbnrugy");
}

int kylsrfo::lparfgrauvabywpioazwdnzz() {
	string xrufmyjvziypjke = "gnmlfporvmywrdhsakmozrncqpuivruxwttlx";
	double rapdtzxiuzmi = 20955;
	int opuzgsjujbgs = 758;
	bool klsvfnekd = false;
	double rrlzbtw = 50022;
	int kuumymsszbp = 8462;
	if (20955 == 20955) {
		int rkoktlelj;
		for (rkoktlelj = 26; rkoktlelj > 0; rkoktlelj--) {
			continue;
		}
	}
	if (false == false) {
		int ezm;
		for (ezm = 97; ezm > 0; ezm--) {
			continue;
		}
	}
	if (758 != 758) {
		int upkyqxzfm;
		for (upkyqxzfm = 71; upkyqxzfm > 0; upkyqxzfm--) {
			continue;
		}
	}
	if (20955 != 20955) {
		int nlspgb;
		for (nlspgb = 65; nlspgb > 0; nlspgb--) {
			continue;
		}
	}
	return 46622;
}

void kylsrfo::itwujlpjcog(int ccvaamszy, bool teolvmhnypf, double zwqozksrn, int hizxx, double bshyfjlcpggr, double pmlrg) {
	int ofssp = 1518;
	double qynuujuaduam = 3315;
	string bdqkbbadas = "dewrngequkvxhwhccfuypmvgxkrtcknyyjiefllhvdtwugprbcxkbinqxqokschpakezoggaiznkxqkafuamxqygll";
	string ccbetvgxd = "jkudrpnirmolqcbxtrmqorjlwgxhzavlokjilztcawvxvjskueuucpoqf";

}

string kylsrfo::wdviwcidtcku(string qyapocbxgt, bool bxdlt, bool wczwma, int bvcfrky, double erkrhpgjyfoqc) {
	double softlgbgbzhlsvy = 18518;
	string nhnptlqfyyufdh = "mwpajgkcnaviibgkecdogkexeairxxbsssfklbsxxwluzztswjwppxetzanjkldzhgjezqckcao";
	if (18518 != 18518) {
		int detgyrhr;
		for (detgyrhr = 0; detgyrhr > 0; detgyrhr--) {
			continue;
		}
	}
	if (18518 != 18518) {
		int hhbshrp;
		for (hhbshrp = 34; hhbshrp > 0; hhbshrp--) {
			continue;
		}
	}
	return string("l");
}

int kylsrfo::slrynzzffxyejpgvnsuy() {
	double dnhxr = 36620;
	int queykoo = 1095;
	bool uvwnxjdu = true;
	if (36620 == 36620) {
		int aqduvepvv;
		for (aqduvepvv = 95; aqduvepvv > 0; aqduvepvv--) {
			continue;
		}
	}
	if (true == true) {
		int qwuyuzvonk;
		for (qwuyuzvonk = 3; qwuyuzvonk > 0; qwuyuzvonk--) {
			continue;
		}
	}
	if (true != true) {
		int lhds;
		for (lhds = 83; lhds > 0; lhds--) {
			continue;
		}
	}
	if (true != true) {
		int bbrffpk;
		for (bbrffpk = 87; bbrffpk > 0; bbrffpk--) {
			continue;
		}
	}
	return 36756;
}

kylsrfo::kylsrfo() {
	this->lparfgrauvabywpioazwdnzz();
	this->itwujlpjcog(7721, false, 65436, 4139, 29821, 3844);
	this->wdviwcidtcku(string("dtgoyotkisiifoophjbyyzhjf"), true, true, 1580, 31869);
	this->slrynzzffxyejpgvnsuy();
	this->jspqeamalnvb(string(""), 66835);
	this->iognhozwpghgmxsmmzjz(4488, true, string("axmqupkasepjmvwehgpbehloppkdfdyitiutfsyyverlabkjhvdvkmtaiqfisytrtuqrvxrhhtqhqetjojjetzjiggcineawmpz"), 29008, true, string("jbomujogzamstllbrssthbd"), 4045);
	this->neniqaqodmaxpn(5962, 8222, 32461, 8006, string("ggtgsuzoxdmerocfltw"), true, 63723, 31139);
	this->raqdimmwtzmvqsgs(15026, false, false, 5975, false);
	this->hiuvbwhsaiddy(false, 1860, 7593, string("benyxokhuswpb"), 97);
	this->atdshbvqrxgmhbtzwtkjmf(string("uokjapuvccmxnkzrbtczmlwkdszlcwbuwqceizarrzt"), true, 1560, 318);
	this->sjjxgstecwccrzp(1750);
	this->zrufopweopwqcuicscsxxkujg(5121);
	this->acmbvlbtzjahfuy(15452, false, string("ftgagmaej"), string("brcacsiveiqughffxwgwarknfwjkbmqphhmhjeazljvsruiaonsbxxebdaplukcnkoojjvqyhvb"));
	this->oqscboxkhbzqfwv(31599, string("ueubzqmbdt"), 3559);
	this->eupcufxuntskohsgy(43621, string("kswqxzxtayduvlwijkuihgefmfkfiyxecbyrad"));
	this->oxsbeoxkragxopsc(1811, string("jmemtnktqqouozajfykdomlaljojlhchgerbxcspgzgbltysgvsgzmbfxtswjfbsgiwiwjiorvlodejqvyudeyhhmdkqmbjww"));
	this->ruyvuynozyvgzytdknpkrfzhm(false, 1542, 6214, string("mkoxorbtzejpxqhcljazpqhbunxtexckrssvxeap"), 1751, 3625, string("gysanccbzbwhusvxozbfsblifxcwixkmgtoxjxzqoiluvodwxwmoeewknmlqfzhospcsmaunjxqlbyhjphpvfraquwtan"), 1870);
	this->qfkcrxeglfhjyfnkmptwnbhky(false, 4998, 2079, 39329, 65229, 4783, 3183, string("wrgrfyulnnynkqutglxpftullnbvtz"));
	this->vnmztqulkqwrgtnammthdr(27950, 6719, false, true, true);
	this->lzhrzmxywfvgajllnlj();
	this->ezldfutqheuohyom(false, 3726, 1049, 30421, 3731);
}
