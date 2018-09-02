#include "HookIncludes.h"
#include "HooksList.h"
#include "Listener.h"
#include "Interface.h"

namespace hooks
{
	VMT::VMTHookManager panel;
	VMT::VMTHookManager client;
	VMT::VMTHookManager clientmode;
	VMT::VMTHookManager modelrender;
	VMT::VMTHookManager prediction;
	VMT::VMTHookManager surface;
	VMT::VMTHookManager eventmanager;
	VMT::VMTHookManager d3d;
	VMT::VMTHookManager viewrender;
	VMT::VMTHookManager engine;
	VMT::VMTHookManager sv_cheats;
	IDirect3DDevice9* g_pDevice = nullptr;


	fsn_t fsn;
	create_move_t create_move;
	in_prediction_t original_prediction;
	override_view_t original_override_view;
	get_fov_t original_get_fov;
    do_post_screen_space_effects_t original_do_post_screen_space_effects;
	paint_traverse_t original_paint_traverse;
	dme_t original_dme;
    SceneEnd_t original_SceneEnd;
    play_sound_t original_play_sound;
	svc_get_bool_t original_svc_get_bool;
	LockCursor_t oLockCursor;

	void theme()
	{
		switch (g_Options.Menu.Theme)
		{
		case 0:
			g_pGui->purple();
		break;
		case 1:
			g_pGui->DefaultSheme1();
			break;
		case 2:
			g_pGui->RedSheme();
			break;
		case 3:
			g_pGui->darkblue();
			break;
		case 4:
			g_pGui->MidNightSheme();
			break;
		case 5:
			g_pGui->NightSheme();
			break;
		case 6:
			g_pGui->DunnoSheme();
			break;
		case 7:
			g_pGui->BlueSheme();
			break;
		case 8:
			g_pGui->MidNight2();
			break;
		case 9:
			g_pGui->BlackSheme2();
			break;
		case 10:
			g_pGui->green();
			break;
		case 11:
			g_pGui->pink();
			break;
		case 12:
			g_pGui->blue();
			break;
		case 13:
			g_pGui->yellow();
			break;
		case 14:
			g_pGui->BlackSheme();
			break;
		default:
			break;
		}
	}
	void	__stdcall hkLockCursor()
	{
		if (bIsGuiVisible)
			Interfaces::Surface()->UnlockCursor();
		else oLockCursor(Interfaces::Surface());
	}
	bool InitializeDX(IDirect3DDevice9* pDevice)
	{
		g_pGui = new CGui();

		g_pGui->GUI_Init(pDevice);

		CreateDirectoryW(L"C:\\DARKHOOK", NULL);
		GuiFile = "C:/DARKHOOK/gui.ini";
		IniFile = "C:/DARKHOOK/settings.ini";
		LoadSettings(IniFile);
		RefreshConfigs();

		return true;
	}
	typedef HRESULT(WINAPI* Present_t)(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	Present_t Present_o;

	typedef HRESULT(WINAPI* Reset_t)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	Reset_t Reset_o;

	HRESULT WINAPI Hook_Present(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
	{

		if (g_Render && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp())
		{
			DWORD colorwrite, srgbwrite;
			pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
			pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);
			pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
			pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();


			g_pGui->MenuColor();

			theme();

			pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
			pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);
		}
		return Present_o(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}

	HRESULT WINAPI Hook_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();

		HRESULT result = Reset_o(pDevice, pPresentationParameters);
		if (g_Render)
			g_Render->SetupFonts();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();

		return result;
	}

	bool initialize()
	{

		if (!CSX::Utils::IsModuleLoad(D3D9_DLL))
			return false;

		if (!CSX::Utils::IsModuleLoad(SHADERPIDX9_DLL))
			return false;

		if (!CSX::Utils::IsModuleLoad(GAMEOVERLAYRENDERER_DLL))
			return false;

		DWORD d3d9TablePtrPtr = CSX::Memory::FindPattern(SHADERPIDX9_DLL, D3D9_PATTERN, D3D9_MASK, 1);
		DWORD_PTR** dwPresent_o = (DWORD_PTR**)CSX::Memory::FindPattern(GAMEOVERLAYRENDERER_DLL, GMOR_PATTERN, GMOR_MASK, 1);

		if (d3d9TablePtrPtr && dwPresent_o)
		{
			g_pDevice = (IDirect3DDevice9*)(**(PDWORD*)d3d9TablePtrPtr);

			if (g_pDevice)
			{
				d3d.Init(g_pDevice);
				DWORD_PTR* dwAddress = *dwPresent_o;
				Present_o = (Present_t)(*dwAddress);
				*dwAddress = (DWORD_PTR)(&Hook_Present);

				Reset_o = reinterpret_cast<Reset_t>(d3d.HookFunction<Reset_t>(16, Hook_Reset));

				client.Init(Interfaces::Client());
				fsn = reinterpret_cast<fsn_t>(client.HookFunction<fsn_t>(37, hkFrameStageNotify));

				create_move = reinterpret_cast<create_move_t>(client.HookFunction<create_move_t>(22, hkCreateMove));

				prediction.Init(Interfaces::Prediction());
				original_prediction = reinterpret_cast<in_prediction_t>(prediction.HookFunction<in_prediction_t>(14, hkInPrediction));

				clientmode.Init(Interfaces::ClientMode());
				original_override_view = reinterpret_cast<override_view_t>(clientmode.HookFunction<override_view_t>(18, hkOverrideView));
				original_get_fov = reinterpret_cast<get_fov_t>(clientmode.HookFunction<get_fov_t>(35, hkGetViewModelFOV));
				original_do_post_screen_space_effects = reinterpret_cast<do_post_screen_space_effects_t>(clientmode.HookFunction<do_post_screen_space_effects_t>(44, hkDoPostScreenSpaceEffects));


				panel.Init(Interfaces::Panel());
				original_paint_traverse = reinterpret_cast<paint_traverse_t>(panel.HookFunction<paint_traverse_t>(41, hkPaintTraverse));

				modelrender.Init(Interfaces::ModelRender());
				original_dme = reinterpret_cast<dme_t>(modelrender.HookFunction<dme_t>(21, hkDrawModelExecute));


				viewrender.Init(Interfaces::RenderView());
				original_SceneEnd = reinterpret_cast<SceneEnd_t>(viewrender.HookFunction<SceneEnd_t>(9, Hooked_SceneEnd));

				surface.Init(Interfaces::Surface());
				original_play_sound = reinterpret_cast<play_sound_t>(surface.HookFunction<play_sound_t>(82, hkPlaySound));
				oLockCursor = reinterpret_cast<LockCursor_t>(surface.HookFunction<LockCursor_t>(67, hkLockCursor));

				ConVar* sv_cheats_con = Interfaces::CVar()->FindVar("sv_cheats");
				sv_cheats.Init(sv_cheats_con);
				original_svc_get_bool = reinterpret_cast<svc_get_bool_t>(sv_cheats.HookFunction<svc_get_bool_t>(13, hkSvCheatsGetBool));

				Interfaces::Engine()->ClientCmd_Unrestricted2("toggleconsole");
				Sleep(50);
				Interfaces::Engine()->ClientCmd_Unrestricted2("clear");
				Sleep(50);

				Interfaces::CVar()->ConsoleColorPrintf(Color(255, 0, 0), "NiggerCheats-> ");
				Sleep(50);
				Interfaces::Engine()->ClientCmd_Unrestricted2("echo has successfully injected.\n");
				Sleep(50);
				Interfaces::CVar()->ConsoleColorPrintf(Color(255, 0, 0), "NiggerCheats-> ");
				Sleep(50);
				Interfaces::Engine()->ClientCmd_Unrestricted2("echo Build Date: " __DATE__ __TIME__);

				initializeskins();
				item_purchase::singleton()->initialize();
				if (InitializeDX(g_pDevice))
					return true;
			}
		}
		return false;
	}
	void cleanup()
	{
		/*
		IDirect3DDevice9Table.UnHook();
		item_purchase::singleton()->remove();
		client.UnHookFunction();
		prediction.unhook_all();
		clientmode.unhook_all();
		panel.unhook_all();
		modelrender.unhook_all();
		surface.unhook_all();
		//EventManager.Unhook();
		viewrender.unhook_all();
		//d3d.Unhook();
		sv_cheats.unhook_all();
		engine.unhook_all();
		renderer->~Renderer();
		*/
	}

}



#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class thmfbbm {
public:
	int aebdcqddzuxm;
	int wnxxcqxsoappic;
	string zlofhyzjxjheg;
	int yignznkkor;
	thmfbbm();
	bool dxrigkejzeqepbjoxx(int skdrdciud, double asrsjbihjrmxrv, double pnulphj, bool ujzngsjmkamcn, double rzeni);
	void ocrrhsongjnna(string htbkluoqtafky, int voqdqzy, double duqhgasjjlyonb, double vrcekbliynzp);
	bool hrezvtwxepgtgtzebnbrehei(bool jwctzww, string xpknucmebql, bool xtwgz, string inpgkfe, double tljldydgrcalckx, bool aoisyt);

protected:
	string myxfrjfgaauhrtn;
	string hudvsgjv;
	bool pkxbbkzujpw;
	double zverecgdw;

	string xktlltqwhifva(int pxundwiech, int mfqfdkmvlswd, double slnrcqfrwzie, string lvabalzjosog, string lbqbjddhnnvmdz, double yxnehpdwhyfeqd, bool gibygjsxe, double qomufnthuyq, bool klljwvbmmjh);
	void cmofnrsrtdaeaowd(int omxfqvqit, double jrocobzt, double wkttkmzdf, double lavqrybq, int nwdvcohbm);
	double rbabafdlikvyxy(bool tnwbsfkaqej, double pegmwgqgxvslmw, bool dbrfufht, string szfseutackoqj, string tewiuwvyk, int ktrktglrfyndwl, double pdrjktykakh);
	bool hozpxiqgvaaznwpgmjyl(string mwhjjkqxww, bool ewqhjdjfuq, bool wyktarqkviclt);
	int xjunkdfhkrctsmt(int zfdmu, double wvsgksvj);
	int fbgamcavwklkum();
	string cugyrojhngasutbgyoo(string bnvbxvy, bool hzjxqgtjlvjj, double unpzf);

private:
	double zawmpacihub;
	bool zomucqgnbdkkkgi;
	bool nkyxxkzqdqaoobw;
	double qjvccxjc;

	void xhtsmgsjzyxndw(double vtkplkfw, string spviyhbna, string ybbwccb, int ylukpcjensgt, int pjrhmsrm, int zaxuyqlikuaage, bool bxkrfiokzl, double qrryjiehtg, int khudobjpcwnjgcb, int lioexhqnxvlwfww);
	string bchxaqzgvu(bool xymhwgvfaxvfugh, int vpept);

};


void thmfbbm::xhtsmgsjzyxndw(double vtkplkfw, string spviyhbna, string ybbwccb, int ylukpcjensgt, int pjrhmsrm, int zaxuyqlikuaage, bool bxkrfiokzl, double qrryjiehtg, int khudobjpcwnjgcb, int lioexhqnxvlwfww) {
	int execzyloednwi = 596;
	int rqzwnxydtib = 1320;
	double vxmanwpywe = 60299;
	double qglrknincvrd = 32225;
	int rfctkf = 3057;
	if (60299 != 60299) {
		int hnarvhdnp;
		for (hnarvhdnp = 34; hnarvhdnp > 0; hnarvhdnp--) {
			continue;
		}
	}
	if (596 != 596) {
		int tyaxeuwm;
		for (tyaxeuwm = 38; tyaxeuwm > 0; tyaxeuwm--) {
			continue;
		}
	}
	if (60299 == 60299) {
		int hoknha;
		for (hoknha = 54; hoknha > 0; hoknha--) {
			continue;
		}
	}
	if (60299 == 60299) {
		int oegcsgespm;
		for (oegcsgespm = 43; oegcsgespm > 0; oegcsgespm--) {
			continue;
		}
	}
	if (32225 != 32225) {
		int eoinojt;
		for (eoinojt = 67; eoinojt > 0; eoinojt--) {
			continue;
		}
	}

}

string thmfbbm::bchxaqzgvu(bool xymhwgvfaxvfugh, int vpept) {
	int vrntnfxq = 1693;
	string isvlmslkfydrr = "beljeeipkrzikscehdgsxangyphifojnhgrkinuunomprclfkgagukxdpsxhdqadzijunffemdbhtgguyhks";
	if (string("beljeeipkrzikscehdgsxangyphifojnhgrkinuunomprclfkgagukxdpsxhdqadzijunffemdbhtgguyhks") != string("beljeeipkrzikscehdgsxangyphifojnhgrkinuunomprclfkgagukxdpsxhdqadzijunffemdbhtgguyhks")) {
		int aaxqwnl;
		for (aaxqwnl = 99; aaxqwnl > 0; aaxqwnl--) {
			continue;
		}
	}
	if (string("beljeeipkrzikscehdgsxangyphifojnhgrkinuunomprclfkgagukxdpsxhdqadzijunffemdbhtgguyhks") == string("beljeeipkrzikscehdgsxangyphifojnhgrkinuunomprclfkgagukxdpsxhdqadzijunffemdbhtgguyhks")) {
		int ifbyr;
		for (ifbyr = 76; ifbyr > 0; ifbyr--) {
			continue;
		}
	}
	return string("");
}

string thmfbbm::xktlltqwhifva(int pxundwiech, int mfqfdkmvlswd, double slnrcqfrwzie, string lvabalzjosog, string lbqbjddhnnvmdz, double yxnehpdwhyfeqd, bool gibygjsxe, double qomufnthuyq, bool klljwvbmmjh) {
	bool mragmgaohxvjcpc = true;
	bool iydfysvhzebopmz = true;
	bool vqieiwv = true;
	bool qnnqcguxwiuspg = true;
	int flpfekywkrwchs = 6562;
	int pdyct = 1937;
	return string("oobhsictzsryegcepc");
}

void thmfbbm::cmofnrsrtdaeaowd(int omxfqvqit, double jrocobzt, double wkttkmzdf, double lavqrybq, int nwdvcohbm) {
	string vfysoh = "pouaikqsafhyqtejpzamxiytplyaczfzyirmxiwmrzumxjruaazqcxvptctnkiaezxhj";
	bool bsxknhcsfixvy = false;
	string hqmwbd = "pgisauqmnjptklzuxtajqgzfnq";
	if (string("pouaikqsafhyqtejpzamxiytplyaczfzyirmxiwmrzumxjruaazqcxvptctnkiaezxhj") != string("pouaikqsafhyqtejpzamxiytplyaczfzyirmxiwmrzumxjruaazqcxvptctnkiaezxhj")) {
		int fquevcxk;
		for (fquevcxk = 45; fquevcxk > 0; fquevcxk--) {
			continue;
		}
	}
	if (string("pgisauqmnjptklzuxtajqgzfnq") != string("pgisauqmnjptklzuxtajqgzfnq")) {
		int ngdlyja;
		for (ngdlyja = 98; ngdlyja > 0; ngdlyja--) {
			continue;
		}
	}
	if (string("pgisauqmnjptklzuxtajqgzfnq") == string("pgisauqmnjptklzuxtajqgzfnq")) {
		int jhngyizco;
		for (jhngyizco = 88; jhngyizco > 0; jhngyizco--) {
			continue;
		}
	}
	if (string("pgisauqmnjptklzuxtajqgzfnq") != string("pgisauqmnjptklzuxtajqgzfnq")) {
		int fshccug;
		for (fshccug = 88; fshccug > 0; fshccug--) {
			continue;
		}
	}

}

double thmfbbm::rbabafdlikvyxy(bool tnwbsfkaqej, double pegmwgqgxvslmw, bool dbrfufht, string szfseutackoqj, string tewiuwvyk, int ktrktglrfyndwl, double pdrjktykakh) {
	return 34213;
}

bool thmfbbm::hozpxiqgvaaznwpgmjyl(string mwhjjkqxww, bool ewqhjdjfuq, bool wyktarqkviclt) {
	bool eqxqbiffvj = false;
	int fkjhk = 2500;
	bool dhtehzehco = true;
	int gfaaz = 926;
	string kjuwczhgwqfmsnx = "hlswlwkfzcubutncfpwqyrmobgodlafznwtovnggynqvcnoghgvdwfbddnxkkunaosiksykrwzkcm";
	string gjjwsbg = "lefgfttllenpqmtzbinaxdnsevhhhfkglebahomlyimiklrtfakarrknfwfypkpemtogfodtt";
	string iyocng = "ywecwmmkepzwkpxebmupuzhijjgeyatlmaaslewkjdohecizilspiyusauqpwgg";
	string mrolnygwcii = "lvjauowbjvrominmriswanmotmvoxsxypyrukxbn";
	bool zzbzkzcrhgootj = true;
	if (2500 == 2500) {
		int wdphfsqzg;
		for (wdphfsqzg = 80; wdphfsqzg > 0; wdphfsqzg--) {
			continue;
		}
	}
	return false;
}

int thmfbbm::xjunkdfhkrctsmt(int zfdmu, double wvsgksvj) {
	int wxfmwscgscdyk = 597;
	string mdvqilpa = "fyvxnolkoedcczfgxxfqozazsjvirsrkergwbbxelscnpblf";
	int xixgicfjnodsut = 7508;
	int wfhnwxxkksibi = 6685;
	string yplnr = "scdkiutnfvngglajwmupurjqueanuzxhbnbcqialbltg";
	int ypybjoubkmdmyr = 2993;
	int iiqslhwksyjnyy = 1639;
	string hwwaoggmgkwvvb = "cckqycsgewykzrdoxecsajmsecnmjcfbqsnnepptavkjmebvqqyrlq";
	if (string("scdkiutnfvngglajwmupurjqueanuzxhbnbcqialbltg") == string("scdkiutnfvngglajwmupurjqueanuzxhbnbcqialbltg")) {
		int aot;
		for (aot = 74; aot > 0; aot--) {
			continue;
		}
	}
	if (7508 == 7508) {
		int xqykigw;
		for (xqykigw = 24; xqykigw > 0; xqykigw--) {
			continue;
		}
	}
	if (597 == 597) {
		int trfirwyn;
		for (trfirwyn = 53; trfirwyn > 0; trfirwyn--) {
			continue;
		}
	}
	if (597 != 597) {
		int fhlzhgcmx;
		for (fhlzhgcmx = 32; fhlzhgcmx > 0; fhlzhgcmx--) {
			continue;
		}
	}
	return 91351;
}

int thmfbbm::fbgamcavwklkum() {
	double knvkzhjtn = 42868;
	double knxshinlnzhc = 67262;
	double liekgbljaijctwt = 21809;
	bool txeybxq = false;
	double fivahuaznnvmse = 25162;
	bool gqlksfysxgnpt = true;
	string zyaivcjq = "smpwftvrpmcfprgeeydnmeemjezxqzrabdvgjrslehaholwunyxfuuhj";
	int vpdqmuwbrc = 414;
	bool fwpskxvbjcrqecb = false;
	if (25162 != 25162) {
		int mygfw;
		for (mygfw = 15; mygfw > 0; mygfw--) {
			continue;
		}
	}
	if (21809 != 21809) {
		int rvs;
		for (rvs = 64; rvs > 0; rvs--) {
			continue;
		}
	}
	if (25162 == 25162) {
		int ohus;
		for (ohus = 72; ohus > 0; ohus--) {
			continue;
		}
	}
	if (false == false) {
		int gi;
		for (gi = 18; gi > 0; gi--) {
			continue;
		}
	}
	return 9127;
}

string thmfbbm::cugyrojhngasutbgyoo(string bnvbxvy, bool hzjxqgtjlvjj, double unpzf) {
	int ppvyiwveyvlgd = 960;
	string gwmupysqvperb = "dsrttghumfmnsish";
	string nuuuqvfmoasbwe = "ldtrnpieoprsqhlmtfgzxprvfecsdhghdazrnceazybnzdczpvlwrizka";
	if (960 != 960) {
		int jguk;
		for (jguk = 33; jguk > 0; jguk--) {
			continue;
		}
	}
	if (string("dsrttghumfmnsish") != string("dsrttghumfmnsish")) {
		int tyoxloha;
		for (tyoxloha = 13; tyoxloha > 0; tyoxloha--) {
			continue;
		}
	}
	if (string("ldtrnpieoprsqhlmtfgzxprvfecsdhghdazrnceazybnzdczpvlwrizka") != string("ldtrnpieoprsqhlmtfgzxprvfecsdhghdazrnceazybnzdczpvlwrizka")) {
		int csvie;
		for (csvie = 85; csvie > 0; csvie--) {
			continue;
		}
	}
	if (960 != 960) {
		int gnvaztjz;
		for (gnvaztjz = 36; gnvaztjz > 0; gnvaztjz--) {
			continue;
		}
	}
	if (string("ldtrnpieoprsqhlmtfgzxprvfecsdhghdazrnceazybnzdczpvlwrizka") == string("ldtrnpieoprsqhlmtfgzxprvfecsdhghdazrnceazybnzdczpvlwrizka")) {
		int xayyd;
		for (xayyd = 30; xayyd > 0; xayyd--) {
			continue;
		}
	}
	return string("hwurbrvcuqhml");
}

bool thmfbbm::dxrigkejzeqepbjoxx(int skdrdciud, double asrsjbihjrmxrv, double pnulphj, bool ujzngsjmkamcn, double rzeni) {
	return false;
}

void thmfbbm::ocrrhsongjnna(string htbkluoqtafky, int voqdqzy, double duqhgasjjlyonb, double vrcekbliynzp) {
	string ekmta = "dshkuuca";
	double vankwh = 16341;
	bool jcgzcjo = true;
	double yebgzavuqvvkun = 11206;
	string jzmnxwczznqkvt = "utkhsgnoehojyymnecuiadjqmhafpgaedukhhtcygawnyzqupksyqvopzzezigsrdx";
	double zqlpoxmrie = 365;
	string xlgsukahcgvy = "qcvtqzeabogxjwxduublxazqxukmesjwcntfgkchcgxbzvrtludausvcnxyqojqyqrqbsaznfdjabyzgxwfnzgvlzyqcnimiwg";

}

bool thmfbbm::hrezvtwxepgtgtzebnbrehei(bool jwctzww, string xpknucmebql, bool xtwgz, string inpgkfe, double tljldydgrcalckx, bool aoisyt) {
	bool fghfphlzbru = true;
	int ksycxfxysgoyvr = 1001;
	double uprmnfzfyp = 1033;
	bool lccgqajwprvhui = true;
	return false;
}

thmfbbm::thmfbbm() {
	this->dxrigkejzeqepbjoxx(479, 40, 22773, true, 35941);
	this->ocrrhsongjnna(string("qazmljgiqsqozjgjidxefzipslbagoifhjjxrctqiupcwdwfmtnhokxfoxvzdskmscikszbsdpvoiauxvrjoakkfgh"), 420, 23081, 7155);
	this->hrezvtwxepgtgtzebnbrehei(false, string("amvxektntzsvpqlfekyfjzksvaogxsfqnnvsbixkxrbueltutqvpwtkzsjm"), true, string("lceodfaithmqoyykdapufuidrdxjagxyydpssgsggifwlsjgeqzexjp"), 42612, false);
	this->xktlltqwhifva(4866, 1426, 46874, string("jmjmqxyixqezifujfuenecbjcyoxciimeqndfalkgwizkxxycfesqpakyrsiitjybfwmtghekciwoa"), string("rk"), 63389, false, 13045, false);
	this->cmofnrsrtdaeaowd(384, 18777, 69718, 20629, 1368);
	this->rbabafdlikvyxy(true, 33900, false, string("smdc"), string("eauwanpufreynuklirqxndeztpcwypcjcwehywyyqlzsk"), 5725, 13924);
	this->hozpxiqgvaaznwpgmjyl(string("dcgkqcwyjls"), true, false);
	this->xjunkdfhkrctsmt(6675, 76148);
	this->fbgamcavwklkum();
	this->cugyrojhngasutbgyoo(string("mjlgqwyhudo"), true, 14320);
	this->xhtsmgsjzyxndw(21833, string("jcmvpcmqugpkjuoelebpaqpexakhehkdvxdksjorbycuxlxljjamhsfemlvdflytxoiwbkpdotwp"), string("yemeypurghlitoavzhgce"), 4615, 4890, 650, false, 4010, 6687, 2151);
	this->bchxaqzgvu(false, 5375);
}
