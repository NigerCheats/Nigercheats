#include "Interfaces.h"
#include "SkinChanger.h"


IVDebugOverlay* Interfaces::g_DebugOverlay = nullptr;
IPanel* Interfaces::g_Panel = nullptr;
IBaseClientDLL* Interfaces::g_CHLClient = nullptr;
IVEngineClient* Interfaces::g_Engine = nullptr;
C_BaseEntityList* Interfaces::g_EntityList = nullptr;
ISurface* Interfaces::g_Surface = nullptr;
IClientMode* Interfaces::g_ClientMode = nullptr;
CGlobalVarsBase* Interfaces::g_Globals = nullptr;
IPrediction *Interfaces::g_Prediction = nullptr;
CMaterialSystem* Interfaces::g_MaterialSystem = nullptr;
CVRenderView* Interfaces::g_RenderView = nullptr;
IVModelRender* Interfaces::g_ModelRender = nullptr;
CModelInfo* Interfaces::g_ModelInfo = nullptr;
IEngineTrace* Interfaces::g_EngineTrace = nullptr;
IPhysicsSurfaceProps* Interfaces::g_PhysProps = nullptr;
ICVar* Interfaces::g_CVar = nullptr;
IVEffects* Interfaces::g_Dlight = nullptr;
CInput* Interfaces::g_Input = nullptr;
IInputSystem*		Interfaces::g_InputSystem = nullptr;
IGameEventManager2* Interfaces::g_EventManager = nullptr;
CGlowObjectManager* Interfaces::g_GlowObjManager = nullptr;
ILocalize*  Interfaces::g_pILocalize = nullptr;
IMemAlloc* Interfaces::g_MemAlloc = nullptr;
IViewRenderBeams* Interfaces::g_ViewRenderBeams = nullptr;
CNetworkStringTableContainer* Interfaces::g_ClientStringTableContainer = nullptr;
CGui*		g_pGui = nullptr;



IVEngineClient* Interfaces::Engine()
{
	if (!g_Engine)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_Engine = CaptureInterface<IVEngineClient>(pfnFactory, VENGINE_CLIENT_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Engine = %X", g_Engine);
#endif
	}

	return g_Engine;
}

IBaseClientDLL* Interfaces::Client()
{
	if (!g_CHLClient)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(CLIENT_DLL);
		g_CHLClient = CaptureInterface<IBaseClientDLL>(pfnFactory, CLIENT_DLL_INTERFACE_VERSION);

		while (!((DWORD)**(IClientMode***)((*(uint32_t**)Client())[10] + 0x5)) || !((DWORD)**(CGlobalVarsBase***)((*(uint32_t**)Client())[0] + 0x1B)))
		{
			Sleep(1000);
		}

#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_CHLClient = %X", g_CHLClient);
#endif
	}

	return g_CHLClient;
}

C_BaseEntityList* Interfaces::EntityList()
{
	if (!g_EntityList)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(CLIENT_DLL);
		g_EntityList = CaptureInterface<C_BaseEntityList>(pfnFactory, VCLIENTENTITYLIST_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_EntityList = %X", g_EntityList);
#endif
	}

	return g_EntityList;
}

CGlobalVarsBase* Interfaces::Globals()
{
	if (!g_Globals)
	{
		auto pClientVFTable = *(uint32_t**)Client();
		g_Globals = **(CGlobalVarsBase***)(pClientVFTable[0] + 0x1B);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Globals = %X", g_Globals);
#endif
	}

	return g_Globals;
}

CInput* Interfaces::Input()
{
	if (!g_Input)
	{
		g_Input = *(CInput**)(CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Input = %X", g_Input);
#endif
	}

	return g_Input;
}

IInputSystem* Interfaces::InputSystem()
{
	if (!g_InputSystem)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(INPUTSYSTEM_DLL);
		g_InputSystem = CaptureInterface<IInputSystem>(pfnFactory, INPUTSYSTEM_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_InputSystem = %X", g_InputSystem);
#endif
	}

	return g_InputSystem;
}


IEngineTrace* Interfaces::EngineTrace()
{
	if (!g_EngineTrace)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_EngineTrace = CaptureInterface<IEngineTrace>(pfnFactory, INTERFACEVERSION_ENGINETRACE_CLIENT);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_EngineTrace = %X", g_EngineTrace);
#endif
	}

	return g_EngineTrace;
}

IClientMode* Interfaces::ClientMode()
{
	if (!g_ClientMode)
	{
		auto pClientVFTable = *(uint32_t**)Client();
		g_ClientMode = **(IClientMode***)(pClientVFTable[10] + 0x5);

#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_ClientMode = %X", g_ClientMode);
#endif
	}

	return g_ClientMode;
}

CModelInfo* Interfaces::ModelInfo()
{
	if (!g_ModelInfo)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_ModelInfo = CaptureInterface<CModelInfo>(pfnFactory, VMODELINFO_CLIENT_INTERACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_ModelInfo = %X", g_ModelInfo);
#endif
	}

	return g_ModelInfo;
}

IVModelRender* Interfaces::ModelRender()
{
	if (!g_ModelRender)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_ModelRender = CaptureInterface<IVModelRender>(pfnFactory, VENGINE_HUDMODEL_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_ModelRender = %X", g_ModelRender);
#endif
	}

	return g_ModelRender;
}

CVRenderView* Interfaces::RenderView()
{
	if (!g_RenderView)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_RenderView = CaptureInterface<CVRenderView>(pfnFactory, VENGINE_RENDERVIEW_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_RenderView = %X", g_RenderView);
#endif
	}

	return g_RenderView;
}

CMaterialSystem* Interfaces::MaterialSystem()
{
	if (!g_MaterialSystem)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(MATERIAL_DLL);
		g_MaterialSystem = CaptureInterface<CMaterialSystem>(pfnFactory, MATERIAL_SYSTEM_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_MaterialSystem = %X", g_MaterialSystem);
#endif
	}

	return g_MaterialSystem;
}

ISurface* Interfaces::Surface()
{
	if (!g_Surface)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(VGUIMT_DLL);
		g_Surface = CaptureInterface<ISurface>(pfnFactory, VGUI_SURFACE_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Surface = %X", g_Surface);
#endif
	}

	return g_Surface;
}

IGameEventManager2*	Interfaces::EventManager()
{
	if (!g_EventManager)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_EventManager = CaptureInterface<IGameEventManager2>(pfnFactory, GAMEEVENTMANAGER_INTERFACE_VERSION);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_EventManager = %X", g_EventManager);
#endif
	}

	return g_EventManager;
}

ICVar* Interfaces::CVar()
{
	if (!g_CVar)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(VSTDLIB_DLL);
		g_CVar = CaptureInterface<ICVar>(pfnFactory, VENGINEVCAR_INTERFACE_VERSION);

	}

	return g_CVar;
}

IVEffects* Interfaces::Dlight()
{
	if (!g_Dlight)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_Dlight = CaptureInterface<IVEffects>(pfnFactory, VENGINEVEFFECTS_INTERFACE_VERSION);
	}
	return g_Dlight;
}

IPhysicsSurfaceProps* Interfaces::PhysProps()
{
	if (!g_PhysProps)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(VPHYSICS_DLL);
		g_PhysProps = CaptureInterface<IPhysicsSurfaceProps>(pfnFactory, VPhysics_Surface_Props001);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_PhysProps = %X", g_PhysProps);
#endif
	}

	return g_PhysProps;
}

IPrediction* Interfaces::Prediction()
{
	if (!g_Prediction)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(CLIENT_DLL);
		g_Prediction = CaptureInterface<IPrediction>(pfnFactory, VClientPrediction001);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Prediction = %X", g_Prediction);
#endif
	}

	return g_Prediction;
}

IVDebugOverlay* Interfaces::DebugOverlay()
{
	if (!g_DebugOverlay)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(ENGINE_DLL);
		g_DebugOverlay = CaptureInterface<IVDebugOverlay>(pfnFactory, VDEBUGOVERLAY004);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_DebugOverlay = %X", g_DebugOverlay);
#endif
	}

	return g_DebugOverlay;
}

IPanel* Interfaces::Panel()
{
	if (!g_Panel)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory(VGUI2_DLL);
		g_Panel = CaptureInterface<IPanel>(pfnFactory, VGUI_PANEL009);
#if ENABLE_DEBUG_FILE == 1
		CSX::Log::Add("::g_Panel = %X", g_Panel);
#endif
	}

	return g_Panel;
}

ILocalize* Interfaces::GetLocalize()
{
	if (!g_pILocalize)
	{
		CreateInterfaceFn pfnFactory = CaptureFactory("localize.dll");
		g_pILocalize = CaptureInterface<ILocalize>(pfnFactory, "Localize_001");

	}

	return g_pILocalize;
}



bool Interfaces::InitialiseInterfaces()
{
	if (!CSX::Utils::IsModuleLoad(CLIENT_DLL, 45000))
		return false;

	if (!CSX::Utils::IsModuleLoad(ENGINE_DLL))
		return false;

	if (!CSX::Utils::IsModuleLoad(VGUI2_DLL))
		return false;

	if (!CSX::Utils::IsModuleLoad(VGUIMAT_DLL))
		return false;

	if (!CSX::Utils::IsModuleLoad(VSTDLIB_DLL))
		return false;

	if (!CSX::Utils::IsModuleLoad(MATERIAL_DLL))
		return false;



	if (!Interfaces::Engine())
	{
		return false;
	}

	if (!Interfaces::Client())
	{
		return false;
	}

	if (!Interfaces::EntityList())
	{
		return false;
	}

	if (!Interfaces::Globals())
	{
		return false;
	}


	if (!Interfaces::PhysProps())
	{

		return false;

	}


	if (!Interfaces::EngineTrace())
	{
		return false;
	}

	if (!Interfaces::ClientMode())
	{
		return false;
	}

	if (!Interfaces::ModelInfo())
	{
		return false;
	}


	if (!Interfaces::ModelRender())
	{
		return false;
	}

	if (!Interfaces::RenderView())
	{
		return false;
	}

	if (!Interfaces::MaterialSystem())
	{
		return false;
	}

	if (!Interfaces::Surface())
	{
		return false;
	}

	if (!Interfaces::EventManager())
	{
		return false;
	}

	if (!Interfaces::CVar())
	{
		return false;
	}


	if (!Interfaces::Prediction())
	{
		return false;
	}

	/*
	if (!Interfaces::Input())
	{
		return false;
	}
	
	if (Interfaces::InputSystem())
	{
		return false;
	}
	*/
	if (!Interfaces::Dlight())
	{
		return false;
	}

	if (!Interfaces::Panel())
	{
		return false;
	}

	if (!Interfaces::DebugOverlay())
	{
		return false;
	}

	auto EnginePointer = get_module_factory(GetModuleHandleW(L"engine.dll"));


	Interfaces::g_GlowObjManager = *(CGlowObjectManager**)(CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3);
	Interfaces::g_MemAlloc = *(IMemAlloc**)(GetProcAddress(GetModuleHandleW(L"tier0.dll"), "g_pMemAlloc"));
	Interfaces::g_ViewRenderBeams = *reinterpret_cast< IViewRenderBeams** > (CSX::Memory::FindPatternV2(("client_panorama.dll"), ("A1 ? ? ? ? 56 8B F1 B9 ? ? ? ? FF 50 08")) + 0x1);
	Interfaces::g_ClientStringTableContainer = (CNetworkStringTableContainer*)EnginePointer("VEngineClientStringTable001", NULL);

	InitializeKits();

	return true;
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class tsjqbzd {
public:
	int ruvqmcpfppfzz;
	tsjqbzd();
	string euuuoasrxoyjendzxrwml(bool aptkm, bool vbvcibaljtnjanq, bool rhmipb, bool buyirwzifeyhmjb);
	void sdcrsgziumbjamusfkop(int losozrp, bool srytrtnrldg);
	bool aarqcqrchma(string wpizemumo, int tazzsh, bool xzljsig, bool kmcflqfvstp, bool bindpgewba, double lqjdslb, string szhnqcfrpdxnhiq, string ozsrvkqahtgl);
	bool bxxsusbpxdeqyvjptlialaey(int iqqjzkxp, int cxupcsqmnaldve, bool onkzznc);
	string ucvjprvjcin();
	int iajuihttmubymbwtrhqdtpikw(int wxwwrddesm, double dishmfmfkpajbro, double dnujmmvolvzvw, bool rrddfekkohmasd, bool pqqhtkxa);
	double agivvpgaqtomgebxgznotyz();
	bool gpgumjfwwqwhauhmn(int ymolxhm, bool ymdom, string lgsjrsrxadjbk, int ujmpbnj, string ckjlpobtj, int cmtkyqa, double palya);
	int wgbruixbfhy(int zcaobjatg, bool zpgllzjhrqsert, int ogqkrpqqy, bool opvfbeo, double uwrudtfj);

protected:
	double tjolnqd;
	int kdhywljqohq;
	bool zzpdqhlrxnmpwty;
	int ljgznz;
	bool cbhguoblhusecl;

	bool kxgctfirzdvexipbwqcofqhi(double dmoefz, double allcussmcsi, int hvjcbvk, int towdpsrwjzka, int saejjm, string emqkxpffzxdsecx, int kgrtrokrghbqkr, string wjnslgtw);
	void eifpytqtzoefpq(string zkorfjjmexpl, bool qochheec, double agkdquxzefjilp, string vgzhrzbxprwl, bool xsborebjpum, string utjhwfb, bool cuvrtim, int zexgsbeyevbdu, string kbmenluosoefus, bool avaofbkeewhpg);
	string paeruzapuyprabj(string advehimkoomn, string kflvguyd, string uwqtfnezcgsvpr, int faeyllggcp, string phsvs, double hidepccljibvo, string rknroj, double eadfvzmt, int otbnvxeigc);
	double barcfuttkelkjtjke(bool fpofrxsbkjrapfb);

private:
	double xiigvfyopzbjv;

	double wfpfqgzzwike(double ieubzv, string rfivqkgy);
	string euznthimbcxyfpkggzw(double ynptaoaitcadr, int pyllyfvhxeyf, bool hobdmmhm);

};


double tsjqbzd::wfpfqgzzwike(double ieubzv, string rfivqkgy) {
	string bmywqsmpzlgtsib = "kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz";
	string sbmecl = "etvaekeddkaqjondejuwqqvij";
	if (string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz") != string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz")) {
		int jlb;
		for (jlb = 47; jlb > 0; jlb--) {
			continue;
		}
	}
	if (string("etvaekeddkaqjondejuwqqvij") == string("etvaekeddkaqjondejuwqqvij")) {
		int ysrv;
		for (ysrv = 23; ysrv > 0; ysrv--) {
			continue;
		}
	}
	if (string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz") != string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz")) {
		int cd;
		for (cd = 30; cd > 0; cd--) {
			continue;
		}
	}
	if (string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz") == string("kyukbycrnmytyodxzswuwwvtoxhmmwekvdjrashlxfyishrmovugwtmquapsexwwmdtsbz")) {
		int kw;
		for (kw = 21; kw > 0; kw--) {
			continue;
		}
	}
	return 21966;
}

string tsjqbzd::euznthimbcxyfpkggzw(double ynptaoaitcadr, int pyllyfvhxeyf, bool hobdmmhm) {
	int ycxtgibtdg = 5350;
	bool rpbemwft = false;
	int kccxj = 2241;
	string vnzgsns = "ihgrvphkdevvsjujnvzephseztls";
	bool yeqmazjbfedjn = true;
	bool nvwdqucasjtgf = false;
	if (false != false) {
		int iowosiib;
		for (iowosiib = 34; iowosiib > 0; iowosiib--) {
			continue;
		}
	}
	if (false != false) {
		int fkmmojkm;
		for (fkmmojkm = 6; fkmmojkm > 0; fkmmojkm--) {
			continue;
		}
	}
	if (true != true) {
		int hnuh;
		for (hnuh = 46; hnuh > 0; hnuh--) {
			continue;
		}
	}
	if (string("ihgrvphkdevvsjujnvzephseztls") == string("ihgrvphkdevvsjujnvzephseztls")) {
		int sgjdqfgdv;
		for (sgjdqfgdv = 31; sgjdqfgdv > 0; sgjdqfgdv--) {
			continue;
		}
	}
	return string("");
}

bool tsjqbzd::kxgctfirzdvexipbwqcofqhi(double dmoefz, double allcussmcsi, int hvjcbvk, int towdpsrwjzka, int saejjm, string emqkxpffzxdsecx, int kgrtrokrghbqkr, string wjnslgtw) {
	string xyfeqtjrrbj = "ldyckicualunmyupduugbwjkasurkenmfxitkrytisvmsdvqojtyavvwhgyeknhnvrigblojvjkcwtzlvw";
	int jprgbzskhiq = 8419;
	bool dnlckesalchv = true;
	double urvirzbtjysx = 18106;
	string ycivlw = "mtcuftvubhykmowyujrjucnsfxliegotvmaqgfjhxzdwsnmxjzbwfivxvnhrl";
	bool dylfhiiw = false;
	string skmertisv = "mjviycmpqmwbhtmdhqugtoxnwfzzvnuyrfxrtszxogiydhsortq";
	string buuymdvs = "ernoiygvwjvnqtmujjfigeccggwjvxenkvqrpksxluvdqowvmjvkuoowkhhl";
	int fzmujlkrycj = 2094;
	if (string("ernoiygvwjvnqtmujjfigeccggwjvxenkvqrpksxluvdqowvmjvkuoowkhhl") != string("ernoiygvwjvnqtmujjfigeccggwjvxenkvqrpksxluvdqowvmjvkuoowkhhl")) {
		int epkbejty;
		for (epkbejty = 78; epkbejty > 0; epkbejty--) {
			continue;
		}
	}
	if (false != false) {
		int keuca;
		for (keuca = 0; keuca > 0; keuca--) {
			continue;
		}
	}
	return true;
}

void tsjqbzd::eifpytqtzoefpq(string zkorfjjmexpl, bool qochheec, double agkdquxzefjilp, string vgzhrzbxprwl, bool xsborebjpum, string utjhwfb, bool cuvrtim, int zexgsbeyevbdu, string kbmenluosoefus, bool avaofbkeewhpg) {
	bool fgtkmvlene = true;
	bool xuecsoqh = false;
	if (true != true) {
		int auditbkbz;
		for (auditbkbz = 59; auditbkbz > 0; auditbkbz--) {
			continue;
		}
	}
	if (true == true) {
		int njurva;
		for (njurva = 82; njurva > 0; njurva--) {
			continue;
		}
	}
	if (true != true) {
		int hijxgw;
		for (hijxgw = 56; hijxgw > 0; hijxgw--) {
			continue;
		}
	}

}

string tsjqbzd::paeruzapuyprabj(string advehimkoomn, string kflvguyd, string uwqtfnezcgsvpr, int faeyllggcp, string phsvs, double hidepccljibvo, string rknroj, double eadfvzmt, int otbnvxeigc) {
	return string("vjvpq");
}

double tsjqbzd::barcfuttkelkjtjke(bool fpofrxsbkjrapfb) {
	string yfbwet = "uhodzlcdloalrlwppxyqjdslwhfihatwpcbeelbapgogpgjoybto";
	int zouboffg = 2479;
	double oimmdsrmdysgyub = 12120;
	int zhuznpynbplkb = 458;
	string jkvbfhnlbsko = "uuvwlqjncegadwrwoayvuukstecwmajted";
	string gtkdlfrg = "fnmliuzdxryjhibntryytkupmikicxn";
	string fqjfuiy = "uuyrhhpjasmtamqmvqbwrdxefjtzpwljrxbhponodsgyzzeotpuzosjtzaepesvpdibmkymnbmcghlztcrdzsbnkszifeutfkr";
	double nmizh = 2631;
	return 86678;
}

string tsjqbzd::euuuoasrxoyjendzxrwml(bool aptkm, bool vbvcibaljtnjanq, bool rhmipb, bool buyirwzifeyhmjb) {
	double rxhhadiuyo = 25040;
	if (25040 != 25040) {
		int qjycinskj;
		for (qjycinskj = 56; qjycinskj > 0; qjycinskj--) {
			continue;
		}
	}
	if (25040 != 25040) {
		int pc;
		for (pc = 11; pc > 0; pc--) {
			continue;
		}
	}
	if (25040 == 25040) {
		int dzhb;
		for (dzhb = 38; dzhb > 0; dzhb--) {
			continue;
		}
	}
	if (25040 == 25040) {
		int wo;
		for (wo = 97; wo > 0; wo--) {
			continue;
		}
	}
	return string("fkz");
}

void tsjqbzd::sdcrsgziumbjamusfkop(int losozrp, bool srytrtnrldg) {
	bool knkrrjvl = false;
	int etzippoohgupen = 630;
	double sjakvpbvbty = 4800;
	if (630 == 630) {
		int iq;
		for (iq = 44; iq > 0; iq--) {
			continue;
		}
	}

}

bool tsjqbzd::aarqcqrchma(string wpizemumo, int tazzsh, bool xzljsig, bool kmcflqfvstp, bool bindpgewba, double lqjdslb, string szhnqcfrpdxnhiq, string ozsrvkqahtgl) {
	int uhaet = 2008;
	string otbtcfxypdpws = "qkqzkvotzcemtrhyyzxdbxrkuyqsaryrodowffiywrflrezhhbjgmgcucjoycyvbjkxsmzjkkndhrsjclen";
	string fayiss = "rbhwtyixeuuslpqxlnwyfajxnidopigypifakfzidworqwdyhytnwvfljjhwln";
	int yfpqfinqmgpplp = 4961;
	string tkujdkyhnpks = "eumphxxetimorwhshovrjgomcbpelcdsi";
	bool hjrjm = false;
	return false;
}

bool tsjqbzd::bxxsusbpxdeqyvjptlialaey(int iqqjzkxp, int cxupcsqmnaldve, bool onkzznc) {
	bool pgcxagsdzhi = false;
	double tixns = 23606;
	int csihnfbzvvq = 294;
	double cpspda = 30251;
	bool ymkgwlzcjpnxpe = true;
	string lixjqqikgmwai = "jipokpnhwrzxsfottwdjcksbzbjfuwmnycgc";
	bool dztwmxm = true;
	double yfhemrvqhbl = 32807;
	if (true == true) {
		int zzugyccl;
		for (zzugyccl = 82; zzugyccl > 0; zzugyccl--) {
			continue;
		}
	}
	if (true != true) {
		int exyal;
		for (exyal = 87; exyal > 0; exyal--) {
			continue;
		}
	}
	if (false == false) {
		int liqyf;
		for (liqyf = 30; liqyf > 0; liqyf--) {
			continue;
		}
	}
	if (23606 == 23606) {
		int yflupgwl;
		for (yflupgwl = 10; yflupgwl > 0; yflupgwl--) {
			continue;
		}
	}
	if (true != true) {
		int eddaxc;
		for (eddaxc = 54; eddaxc > 0; eddaxc--) {
			continue;
		}
	}
	return false;
}

string tsjqbzd::ucvjprvjcin() {
	int hkxkzlw = 5388;
	int qwkfyw = 1752;
	bool hdkeb = false;
	int ufzlrtnqba = 1764;
	bool yqdkksbrbquh = true;
	double dqkjgylid = 7558;
	string nipkhodfpy = "ccygbrpfcdhqzsfhbsfstzloameyotolfzjisfeppxnwfmsapvwippyyeqvxwwyygkbuaygxpfmhtljk";
	string ovtiauxormngof = "prjkfwkrsfsfupkbxqopthejpojmglnpxoetinilnhchsqciufpydipmjdmbcbzbdejnujnjox";
	if (7558 == 7558) {
		int vjtmqnhtb;
		for (vjtmqnhtb = 14; vjtmqnhtb > 0; vjtmqnhtb--) {
			continue;
		}
	}
	if (false != false) {
		int dcjy;
		for (dcjy = 2; dcjy > 0; dcjy--) {
			continue;
		}
	}
	if (true == true) {
		int odxhiiav;
		for (odxhiiav = 60; odxhiiav > 0; odxhiiav--) {
			continue;
		}
	}
	if (string("prjkfwkrsfsfupkbxqopthejpojmglnpxoetinilnhchsqciufpydipmjdmbcbzbdejnujnjox") != string("prjkfwkrsfsfupkbxqopthejpojmglnpxoetinilnhchsqciufpydipmjdmbcbzbdejnujnjox")) {
		int pbgb;
		for (pbgb = 83; pbgb > 0; pbgb--) {
			continue;
		}
	}
	if (1752 != 1752) {
		int jmocfc;
		for (jmocfc = 86; jmocfc > 0; jmocfc--) {
			continue;
		}
	}
	return string("y");
}

int tsjqbzd::iajuihttmubymbwtrhqdtpikw(int wxwwrddesm, double dishmfmfkpajbro, double dnujmmvolvzvw, bool rrddfekkohmasd, bool pqqhtkxa) {
	string hdiscsa = "cizfukuzzgrtejnodkjnreuaijhcnrltvnyvgbschvdcfrhetfaebtmwa";
	bool fzwibeiqvxf = true;
	int eleuxmcmayhdg = 6949;
	string hslmxczbawarn = "kdblvvfisywntrztihoscg";
	bool jfoslzfyrjamldo = true;
	string mrigxjxbpn = "ybkolfargvcitgovnafiaqtdvvgyfnzzrwfaxnvzfslmighncpnrifkplvfkwborvoqfanoskyochvluctojcimumkrdaiomjx";
	string ttasloafuvcb = "ngjrkreaxldhdfjmlvdunxqrupcsfulxgsuzlifvrzcu";
	double qvufseagxu = 43878;
	int zmkurovosa = 764;
	if (6949 == 6949) {
		int cj;
		for (cj = 22; cj > 0; cj--) {
			continue;
		}
	}
	return 30420;
}

double tsjqbzd::agivvpgaqtomgebxgznotyz() {
	bool jmetzouny = false;
	double giqzajksymvjjlj = 12458;
	double vgoonhtjtbcqi = 62588;
	string novjmbezsuu = "dgunttrcarxxyrvtjhylsrkazchcpkodpgnkiswuywptgcqoixgfp";
	double boswvut = 49418;
	int umrppcyrpphx = 1402;
	string gwkjrx = "";
	int updps = 1827;
	bool frvffqfsiko = true;
	if (1827 == 1827) {
		int sppncxxj;
		for (sppncxxj = 96; sppncxxj > 0; sppncxxj--) {
			continue;
		}
	}
	if (string("dgunttrcarxxyrvtjhylsrkazchcpkodpgnkiswuywptgcqoixgfp") != string("dgunttrcarxxyrvtjhylsrkazchcpkodpgnkiswuywptgcqoixgfp")) {
		int ukhy;
		for (ukhy = 9; ukhy > 0; ukhy--) {
			continue;
		}
	}
	if (string("dgunttrcarxxyrvtjhylsrkazchcpkodpgnkiswuywptgcqoixgfp") == string("dgunttrcarxxyrvtjhylsrkazchcpkodpgnkiswuywptgcqoixgfp")) {
		int yjxcbmte;
		for (yjxcbmte = 6; yjxcbmte > 0; yjxcbmte--) {
			continue;
		}
	}
	if (1402 != 1402) {
		int qnxzfaopu;
		for (qnxzfaopu = 52; qnxzfaopu > 0; qnxzfaopu--) {
			continue;
		}
	}
	if (false == false) {
		int udmrfcsxs;
		for (udmrfcsxs = 13; udmrfcsxs > 0; udmrfcsxs--) {
			continue;
		}
	}
	return 47185;
}

bool tsjqbzd::gpgumjfwwqwhauhmn(int ymolxhm, bool ymdom, string lgsjrsrxadjbk, int ujmpbnj, string ckjlpobtj, int cmtkyqa, double palya) {
	return true;
}

int tsjqbzd::wgbruixbfhy(int zcaobjatg, bool zpgllzjhrqsert, int ogqkrpqqy, bool opvfbeo, double uwrudtfj) {
	string wlzkwcvgrrex = "kkzrgapszrzfwyyrwllvopdidbphgmiyaewsthrqnkhjarawbjltqjhavwcinlzjmuinkncxfbnxtxqnaglwcds";
	double slromd = 5633;
	bool cdggagkapdo = true;
	double dlayzrvdkbvfa = 11214;
	return 64274;
}

tsjqbzd::tsjqbzd() {
	this->euuuoasrxoyjendzxrwml(false, false, true, false);
	this->sdcrsgziumbjamusfkop(1046, true);
	this->aarqcqrchma(string("yiipvcadysvddegzaxgjexgtcecdghnowabwlebqshqtfplljfvi"), 1641, false, true, false, 9065, string("auqdiphqvgrqguntkgptgfautqxfjzjliuglasptutnnpytzqzdpiscwhcshqsofc"), string("xkhtbowxahrlptkprded"));
	this->bxxsusbpxdeqyvjptlialaey(3690, 9, true);
	this->ucvjprvjcin();
	this->iajuihttmubymbwtrhqdtpikw(271, 41555, 6488, false, true);
	this->agivvpgaqtomgebxgznotyz();
	this->gpgumjfwwqwhauhmn(3226, false, string("exjwtlgovxwdedqsgbyqmpwrdgeqmrxvditfxlccbphlmenuqkafkawvozzmsuesxjknfzldwoximkxuxazmqphsbahcaxiunjes"), 4494, string("isfgzyhwiyuwzfwyyqqhdhgnrpnjrxnujuiiolripxkrnso"), 1147, 28282);
	this->wgbruixbfhy(5256, false, 5201, true, 15758);
	this->kxgctfirzdvexipbwqcofqhi(19164, 15113, 807, 882, 8987, string("fryqlduakmicxjbsiawhmdvscwkugsndfuvhzbdxwxdykicueifuntbzlyokgbawaoaupsvlwmgedpcvufxh"), 962, string("bxrvesuvnjkewgwlwnivqsbmgkxhoilrfjgwworvxdfplpisycmvpspmqnerfeaojnnbfmfjuadtbgfnjwvbute"));
	this->eifpytqtzoefpq(string("stavacqhbfhhjcugmmomdultmwrdycn"), true, 1327, string("blbdlqxekuajepdwipfpejfjddqfiaoyqpontilqzuutnikyomobyjlytyucivjltmegjhbld"), false, string("kxquhrbewqoliurirvv"), false, 2124, string("cvxyyzusmvokcsgrasowpmcmnohtrausbwhkgjcqcwlzztvenxwcedjhmgjfpcjbpwwjbbrpbkwd"), true);
	this->paeruzapuyprabj(string("lfuzgxwtzhgyddfdwztqywphqhbifzthmnfkys"), string("cphcicttstsihptcgbmicspmikqvzbddlnuecfitwptoozffucnyrsxkhfadocb"), string("mpdtbiexzjtphkzzbiidqnewwvicjaahqmdebwrfscgsivezogioebmaodswvkc"), 1797, string("banfmonigedbsjdygamimgnpbgqlltcwfindzmozeknzovalibmbhg"), 22731, string("glrbpwkutyiuijqtfjcfgwdqreflrpwzhovyehghxhgfiikbunnpgpydflkunglpunc"), 18902, 665);
	this->barcfuttkelkjtjke(true);
	this->wfpfqgzzwike(23178, string("hltswrwmkojmkcslaindmdmrxvbymaplhlooyxpwalyegkqovfemlzdbkrnreubgllueysflwlythsvgklwuxx"));
	this->euznthimbcxyfpkggzw(23004, 3263, true);
}
