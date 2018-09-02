

#include "MiscFunctions.h"
#include "Autowall.h"
#include "Render.h"


char shit[16];
trace_t Trace;
char shit2[16];
C_BaseEntity* entCopy;


bool MiscFunctions::IsVisible(C_BaseEntity* pLocal, C_BaseEntity* pEntity)
{
	entCopy = pEntity;
	if (!pLocal->IsValid())
		return false;

	Vector vSrcOrigin = pLocal->GetEyePosition();

	if (vSrcOrigin.IsZero() || !vSrcOrigin.IsValid())
		return false;

	BYTE bHitBoxCheckVisible[19] = {
		Head,
		LeftHand,
		RightHand,
		LeftFoot,
		RightFoot,
		Chest,
	};

	CTraceFilter filter;

	filter.pSkip = pLocal;

	for (int nHit = 0; nHit < 19; nHit++)
	{
		Vector vHitBox = GetHitboxPosition(pEntity,bHitBoxCheckVisible[nHit]);

		if (vHitBox.IsZero() || !vHitBox.IsValid())
			continue;

		trace_t tr;
		Ray_t ray;

		ray.Init(vSrcOrigin, vHitBox);

		Interfaces::EngineTrace()->TraceRay(ray, PlayerVisibleMask, &filter, &tr);

		if (tr.m_pEnt == (C_BaseEntity*)entCopy && !tr.allsolid)
			return true;
	}

	return false;

}


bool MiscFunctions::IsKnife(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CKnife || pWeaponClass->m_ClassID == (int)ClassID::CC4 || pWeaponClass->m_ClassID == (int)ClassID::CKnifeGG)
		return true;
	else
		return false;
}

bool MiscFunctions::IsBomb(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CC4)
		return true;
	else
		return false;
}

bool MiscFunctions::IsPistol(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponElite || pWeaponClass->m_ClassID == (int)ClassID::CWeaponFiveSeven || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGlock || pWeaponClass->m_ClassID == (int)ClassID::CWeaponHKP2000 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP250 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP228 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponTec9 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponUSP)
		return true;
	else
		return false;
}

bool MiscFunctions::IsRevolver(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CDEagle)
		return true;
	else
		return false;
}

bool MiscFunctions::IsSniper(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponAWP || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSSG08 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSCAR20 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponG3SG1)
		return true;
	else
		return false;
}

bool MiscFunctions::IsRifle(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponFamas || pWeaponClass->m_ClassID == (int)ClassID::CAK47 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponM4A1 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGalil || pWeaponClass->m_ClassID == (int)ClassID::CWeaponGalilAR || pWeaponClass->m_ClassID == (int)ClassID::CWeaponAug || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSG556)
		return true;
	else
		return false;
}

bool MiscFunctions::IsSmg(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponMP7 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMP9 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponUMP45 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponP90 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponBizon || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMAC10)
		return true;
	else
		return false;
}

bool MiscFunctions::IsHeavy(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CWeaponNegev || pWeaponClass->m_ClassID == (int)ClassID::CWeaponM249 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponXM1014 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponNOVA || pWeaponClass->m_ClassID == (int)ClassID::CWeaponMag7 || pWeaponClass->m_ClassID == (int)ClassID::CWeaponSawedoff)
		return true;
	else
		return false;
}

bool MiscFunctions::IsGrenade(void* weapon)
{
	if (weapon == nullptr) return false;
	C_BaseEntity* weaponEnt = (C_BaseEntity*)weapon;
	ClientClass* pWeaponClass = weaponEnt->GetClientClass();

	if (pWeaponClass->m_ClassID == (int)ClassID::CDecoyGrenade || pWeaponClass->m_ClassID == (int)ClassID::CHEGrenade || pWeaponClass->m_ClassID == (int)ClassID::CIncendiaryGrenade || pWeaponClass->m_ClassID == (int)ClassID::CMolotovGrenade || pWeaponClass->m_ClassID == (int)ClassID::CSensorGrenade || pWeaponClass->m_ClassID == (int)ClassID::CSmokeGrenade || pWeaponClass->m_ClassID == (int)ClassID::CFlashbang)
		return true;
	else
		return false;
}


void SayInChat(const char *text)
{
	char buffer[250];
	sprintf_s(buffer, "say \"%s\"", text);
	Interfaces::Engine()->ClientCmd_Unrestricted2(buffer);
}

float GenerateRandomFloat(float Min, float Max)
{
	float randomized = (float)rand() / (float)RAND_MAX;
	return Min + randomized * (Max - Min);
}





Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox)
{
	matrix3x4_t matrix[MAXSTUDIOBONES];
	Vector vRet, vMin, vMax;
	vRet = Vector(0, 0, 0);
	studiohdr_t* hdr = Interfaces::ModelInfo()->GetStudiomodel(pEntity->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);
	if (!hitbox || !pEntity->IsValid())
		return vRet;
	if (!pEntity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, pEntity->GetSimulationTime()))
		return vRet;
	if (!hitbox->bone || !hitbox->bbmin.IsValid() || !hitbox->bbmax.IsValid())
		return vRet;

	VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
	VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
	vRet = (vMin + vMax) * 0.5f;
	return vRet;
}

Vector GetHitboxPositionFromMatrix(C_BaseEntity* pEntity, matrix3x4_t matrix[128], int Hitbox)
{

    studiohdr_t* hdr = Interfaces::ModelInfo()->GetStudiomodel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

    mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

    if (!hitbox)
        return Vector(0, 0, 0);

    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    return vCenter;
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hjjycsy {
public:
	string qvoxmnidvkaqpdu;
	int nbokpnbrd;
	int rpfaa;
	double lcupjklmzcz;
	hjjycsy();
	bool bzlfbapmpaxsxdghavesbpui(int oruanw, int oaorqcnkyyx, double fbsgyrjl);

protected:
	double edadzpnhyfevwl;
	int vebird;
	double yxvzkzr;
	double sksojtjxkdgs;
	string sxzvvztycg;

	double xvymqtrkdmosdrp(double bvxfsukgg, int rairvdhdyz, string nvvdwtzc, bool iwxmg, double sbmcpyry, bool averkxj, string miyactl);
	void yznkpdizlqfoivpwr(int kjrltxahgffgcdi, string lcjglxr, string ceiho, bool etmbr, string easwghdwrnmth);

private:
	int azehruzp;
	string pwguzmi;
	double qgdqgbtclgcmjp;
	bool nbbvyieukdkonjn;

	double xfcynpokhktsdvg(double phfbtm, bool gqkqueqdurrqdlg, string qktvhgfhbgudc, int hdjdqchkgjf, bool ouayt, bool fudtnhserfkcbw, double nqgoxzsopbvbgl, double gffbmm);
	void ornjozvwqewbufecbivepw(double oolgqvhldthorl);
	int rceltehbcbohwsxsbocxr(int jygqkuqv, int dtcjvdoawkazw, string gqcqjfg, string yooun, string lmbajhmbuhxv, double rpwryhog);
	string luyiuacipjmk(bool vvjnrpldctwu, int geuexmmexqm, bool igoxvsculcendkv, int rhybubmprnn, bool vfxyslkfem, string qnvzqsw, string yzitgtlctwvl, int nuaotvveiw);

};


double hjjycsy::xfcynpokhktsdvg(double phfbtm, bool gqkqueqdurrqdlg, string qktvhgfhbgudc, int hdjdqchkgjf, bool ouayt, bool fudtnhserfkcbw, double nqgoxzsopbvbgl, double gffbmm) {
	double yhevhvpmkrsb = 62073;
	bool dvmdqqoyhrkg = true;
	bool plqjr = true;
	bool fmmkzdfwj = true;
	bool jprkdly = false;
	double artapd = 34973;
	string ssgywjuuaeybj = "aisikeaqjbxsfusetmhcw";
	string mggpqejrkjadf = "lzaoubtovnnvgadimbgsxzkkhcgthbsrkihjulhuyhocduaudhwdwsbqbhhdwfb";
	string lrmjw = "cmodxbhxotgedkjitmezpzxbbjleghymhertqzkwrn";
	if (string("lzaoubtovnnvgadimbgsxzkkhcgthbsrkihjulhuyhocduaudhwdwsbqbhhdwfb") == string("lzaoubtovnnvgadimbgsxzkkhcgthbsrkihjulhuyhocduaudhwdwsbqbhhdwfb")) {
		int wahhnofnph;
		for (wahhnofnph = 42; wahhnofnph > 0; wahhnofnph--) {
			continue;
		}
	}
	if (string("aisikeaqjbxsfusetmhcw") != string("aisikeaqjbxsfusetmhcw")) {
		int dsjojb;
		for (dsjojb = 78; dsjojb > 0; dsjojb--) {
			continue;
		}
	}
	if (true != true) {
		int ticue;
		for (ticue = 38; ticue > 0; ticue--) {
			continue;
		}
	}
	if (34973 == 34973) {
		int ical;
		for (ical = 26; ical > 0; ical--) {
			continue;
		}
	}
	if (true == true) {
		int lveldk;
		for (lveldk = 72; lveldk > 0; lveldk--) {
			continue;
		}
	}
	return 70492;
}

void hjjycsy::ornjozvwqewbufecbivepw(double oolgqvhldthorl) {
	double xmmnvdeixzmpq = 13045;
	bool pcgasas = true;
	double gebuplpkc = 29200;
	double dtmacnd = 1537;
	double lglaufx = 67318;
	if (1537 != 1537) {
		int whwati;
		for (whwati = 82; whwati > 0; whwati--) {
			continue;
		}
	}
	if (true != true) {
		int elsi;
		for (elsi = 55; elsi > 0; elsi--) {
			continue;
		}
	}

}

int hjjycsy::rceltehbcbohwsxsbocxr(int jygqkuqv, int dtcjvdoawkazw, string gqcqjfg, string yooun, string lmbajhmbuhxv, double rpwryhog) {
	double qgxkkbaxtdwmtjh = 1558;
	double ixlhqvfxfaj = 6045;
	int eumnvprkxya = 183;
	double ufwxchudsx = 12952;
	string cynuewnizwwa = "exothmgpjyznguqknlxaitnrakuvorvqolzzqytunjlqmnfsemfvflzfjxdspyugnbcffbpmrwpvdeyhbpuusfklupdmvjoyxfd";
	int ampfqu = 4078;
	string wnhgmxb = "zestjcxweihpwvnlfvlfblefxtupymnfsqnzheqhrzpdadwugrnmxnofdorgpvldzlgnaapetbzmlhbwikbef";
	if (12952 != 12952) {
		int acpbf;
		for (acpbf = 94; acpbf > 0; acpbf--) {
			continue;
		}
	}
	if (string("exothmgpjyznguqknlxaitnrakuvorvqolzzqytunjlqmnfsemfvflzfjxdspyugnbcffbpmrwpvdeyhbpuusfklupdmvjoyxfd") == string("exothmgpjyznguqknlxaitnrakuvorvqolzzqytunjlqmnfsemfvflzfjxdspyugnbcffbpmrwpvdeyhbpuusfklupdmvjoyxfd")) {
		int wfkmzys;
		for (wfkmzys = 71; wfkmzys > 0; wfkmzys--) {
			continue;
		}
	}
	if (4078 != 4078) {
		int iqcyplfxtt;
		for (iqcyplfxtt = 11; iqcyplfxtt > 0; iqcyplfxtt--) {
			continue;
		}
	}
	if (4078 != 4078) {
		int zgjullawd;
		for (zgjullawd = 27; zgjullawd > 0; zgjullawd--) {
			continue;
		}
	}
	return 59991;
}

string hjjycsy::luyiuacipjmk(bool vvjnrpldctwu, int geuexmmexqm, bool igoxvsculcendkv, int rhybubmprnn, bool vfxyslkfem, string qnvzqsw, string yzitgtlctwvl, int nuaotvveiw) {
	string ffbieg = "wannpjzxlfhbpkbjiyckqxwpbheiieuwrulmmmkgjygtwxydiizsouhkvt";
	int lhdjxclhclcg = 7197;
	if (string("wannpjzxlfhbpkbjiyckqxwpbheiieuwrulmmmkgjygtwxydiizsouhkvt") != string("wannpjzxlfhbpkbjiyckqxwpbheiieuwrulmmmkgjygtwxydiizsouhkvt")) {
		int lgemfb;
		for (lgemfb = 32; lgemfb > 0; lgemfb--) {
			continue;
		}
	}
	if (string("wannpjzxlfhbpkbjiyckqxwpbheiieuwrulmmmkgjygtwxydiizsouhkvt") == string("wannpjzxlfhbpkbjiyckqxwpbheiieuwrulmmmkgjygtwxydiizsouhkvt")) {
		int nub;
		for (nub = 98; nub > 0; nub--) {
			continue;
		}
	}
	return string("mibdysjysctohrqxf");
}

double hjjycsy::xvymqtrkdmosdrp(double bvxfsukgg, int rairvdhdyz, string nvvdwtzc, bool iwxmg, double sbmcpyry, bool averkxj, string miyactl) {
	bool vxqpssneycdz = false;
	double khspjuqtstrat = 28270;
	int hoegbbnjxjrcxi = 3145;
	bool ekxtshylzuvqw = true;
	bool nhaxdtz = false;
	if (28270 == 28270) {
		int kzifogohik;
		for (kzifogohik = 86; kzifogohik > 0; kzifogohik--) {
			continue;
		}
	}
	if (true != true) {
		int ikcayj;
		for (ikcayj = 81; ikcayj > 0; ikcayj--) {
			continue;
		}
	}
	if (false != false) {
		int uyj;
		for (uyj = 33; uyj > 0; uyj--) {
			continue;
		}
	}
	if (true != true) {
		int cswaa;
		for (cswaa = 80; cswaa > 0; cswaa--) {
			continue;
		}
	}
	if (true == true) {
		int uyu;
		for (uyu = 80; uyu > 0; uyu--) {
			continue;
		}
	}
	return 18068;
}

void hjjycsy::yznkpdizlqfoivpwr(int kjrltxahgffgcdi, string lcjglxr, string ceiho, bool etmbr, string easwghdwrnmth) {
	bool ysues = true;
	bool dkjpz = false;
	string zfuugbdfykfyjzb = "udhog";
	bool bvsidsdlfpsks = false;
	if (true == true) {
		int gjwwooka;
		for (gjwwooka = 47; gjwwooka > 0; gjwwooka--) {
			continue;
		}
	}
	if (false == false) {
		int vazsojbcr;
		for (vazsojbcr = 85; vazsojbcr > 0; vazsojbcr--) {
			continue;
		}
	}
	if (true != true) {
		int iyvomgw;
		for (iyvomgw = 42; iyvomgw > 0; iyvomgw--) {
			continue;
		}
	}

}

bool hjjycsy::bzlfbapmpaxsxdghavesbpui(int oruanw, int oaorqcnkyyx, double fbsgyrjl) {
	int hfnzedm = 5645;
	string jmziuh = "usutewmsvphcwssoqegqnvqajnzaywmqj";
	bool ibluu = true;
	double lveiv = 12753;
	int pkikobtzyrd = 4024;
	string evinkwm = "qbt";
	bool qhnnoyg = true;
	int nekgpfdszjx = 5994;
	return false;
}

hjjycsy::hjjycsy() {
	this->bzlfbapmpaxsxdghavesbpui(8880, 1384, 21621);
	this->xvymqtrkdmosdrp(20195, 4297, string("fdqsrlbqhlstomuokludpqfbztqqbasvueidumtuoyodbr"), true, 79665, true, string("xyqcyzrypugegkmtpbutzdejpave"));
	this->yznkpdizlqfoivpwr(1715, string(""), string("ijyiwgsosaoiowwpmupvlqnufpzheqiuxcpmajnvlyltvkunkofcgxyjvugafajkymhedxmvisr"), false, string(""));
	this->xfcynpokhktsdvg(31678, false, string("efjleaavuoqehbdcuqdynqbfczvhhlqvgvokzpxzflnbvwhevvgbnc"), 65, false, true, 48502, 30379);
	this->ornjozvwqewbufecbivepw(18273);
	this->rceltehbcbohwsxsbocxr(1298, 808, string("hpgarklogvx"), string("vzyrbdee"), string("sjmdwvjaiizsjsktwnlicwuvwruifiknjofhsgzaxqfetkaoyhomqxdweuianqsmhfippxrbimwtgioatzxhglwm"), 58021);
	this->luyiuacipjmk(false, 468, false, 7662, false, string("gxdzevuvmphhfpvkhwnjcerqeuiidoavtvpyftmiedeghhxffecdgegquecuxpgwsvxqedibmzetod"), string("bqprsjnskcyrbfxjceajytmxiahgkeerjyvjihadfmofxp"), 12);
}
