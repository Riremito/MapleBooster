#include"../Share/Simple/Simple.h"
#include"../Share/Hook/SimpleHook.h"
#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

std::vector<std::wstring> img_path_list;

void* (__thiscall *_IWzResMan__GetObjectA)(void *ecx, void *v1, void *v2, void *v3, void *v4) = NULL;
void* __fastcall IWzResMan__GetObjectA_Hook(void *ecx, void *edx, void *v1, void *v2, void *v3, void *v4) {
	static LARGE_INTEGER cpuFreq = { 0 };
	static LARGE_INTEGER start = { 0 };
	if (!cpuFreq.QuadPart) {
		QueryPerformanceFrequency(&cpuFreq);
		QueryPerformanceCounter(&start);

	}
	LARGE_INTEGER current = { 0 };
	QueryPerformanceCounter(&current);
	int time = ((double)(current.QuadPart - start.QuadPart) / cpuFreq.QuadPart) * 1000.0;
	WCHAR *img_path = (WCHAR *)(*(DWORD *)v2);

	DEBUG(L"timeline : + " + std::to_wstring(time) + L" [ms] | ret = " + DWORDtoString((DWORD)_ReturnAddress()) + L" | " + img_path);

	return _IWzResMan__GetObjectA(ecx, v1, v2, v3, v4);
}

#define JMS_v308 0x00404EE0
#define JMS_v327 0x0045A000
#define JMS_v334

bool Hook() {
	Rosemary r;
	ULONG_PTR uIWzResMan__GetObjectA = r.Scan(L"6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC ?? 53 55 56 A1 ?? ?? ?? ?? 33 C4 50 8D 44 24 ?? 64 A3 00 00 00 00 8B F1 C7 44 24 ?? 00 00 00 00 8D 44 24 ?? 50 C7 44 24 ?? 00 00 00 00 FF 15");
	if (!uIWzResMan__GetObjectA) {
		DEBUG(L"IWzResMan__GetObjectA hook is failed.");
		return false;
	}
	SHookFunction(IWzResMan__GetObjectA, uIWzResMan__GetObjectA);
	DEBUG(L"IWzResMan__GetObjectA is hooked.");

	switch (uIWzResMan__GetObjectA) {
	case JMS_v308: {
		r.Patch(0x006D29F2, L"B8 01 00 00 00"); // String/Map.img
		r.Patch(0x006D29F9, L"B8 01 00 00 00"); // String/Eqp.img
		r.Patch(0x006D2A15, L"B8 01 00 00 00"); // String/
		r.Patch(0x006D2A1C, L"B8 01 00 00 00"); // Item/Consume/
		r.Patch(0x006D2A3F, L"B8 01 00 00 00"); // Item/Cash/
		r.Patch(0x00DF6163, L"B8 01 00 00 00"); // Item/ItemOption.img
		r.Patch(0x006DD4E0, L"B8 01 00 00 00"); // Item/FamiliarOption.img
		r.Patch(0x00DF6231, L"B8 01 00 00 00"); // String/PetDialog.img
		r.Patch(0x00DF6100, L"B8 01 00 00 00"); // Skill/Recipe_*.img
		r.Patch(0x00DF6222, L"B8 01 00 00 00"); // Morph/*.img
		r.Patch(0x00DF6242, L"B8 01 00 00 00"); // Etc/FamiliarInfo.img
		r.Patch(0x00DF63F1, L"B8 01 00 00 00"); // Character/Familiar/*.img

		//r.Patch(0x00DF6480, L"B8 01 00 00 00"); // String/Skill.img, something wrong
		r.Patch(0x00DF64DE, L"B8 01 00 00 00");
		r.Patch(0x00DF653C, L"B8 01 00 00 00");
		r.Patch(0x00DF659A, L"B8 01 00 00 00");
		r.Patch(0x00DF65F8, L"B8 01 00 00 00");
		r.Patch(0x00DF6662, L"B8 01 00 00 00");
		r.Patch(0x00DF66CC, L"B8 01 00 00 00");
		r.Patch(0x00DF673B, L"B8 01 00 00 00");

		r.Patch(0x00DF8213, L"B8 01 00 00 00"); // Item/Consume/0238.img
		r.Patch(0x008F1940, L"B8 01 00 00 00"); // Skill/JOB_ID.img/skill/SKILL_ID/skillpet
		r.Patch(0x00DF7479, L"B8 01 00 00 00"); // Quest

		// test
		r.Patch(0x00E2CEED, L"EB"); // Block Monster Book Open
		break;
	}
	case JMS_v327: {
		//r.Patch(0x0087BC52, L"B8 01 00 00 00");
		//r.Patch(0x0087BC59, L"B8 01 00 00 00");
		//r.Patch(0x0087BC75, L"B8 01 00 00 00");
		//r.Patch(0x00, L"B8 01 00 00 00");
		r.Patch(0x01346B32, L"B8 01 00 00 00"); // String/PetDialog.img
		r.Patch(0x01346B8B, L"B8 01 00 00 00"); // Etc/FamiliarInfo.img
		r.Patch(0x01346C9E, L"B8 01 00 00 00"); // Character/Familiar/*.img
		r.Patch(0x009C1293, L"B8 01 00 00 00"); // Item/Consume/0238.img
		r.Patch(0x00B5BEF2, L"B8 01 00 00 00"); // Skill/JOB_ID.img/skill/SKILL_ID/skillpet


		r.Patch(0x00859452, L"B8 01 00 00 00"); // Item/ItemOption.img
		r.Patch(0x01346A01, L"B8 01 00 00 00"); // Skill/Recipe_*.img
		r.Patch(0x01346AC7, L"B8 01 00 00 00"); // Item/FamiliarOption.img
		r.Patch(0x01346B23, L"B8 01 00 00 00"); // Morph/*.img
		r.Patch(0x01348359, L"B8 01 00 00 00"); // Quest
		r.Patch(0x01349B52, L"B8 01 00 00 00");// String/MonsterBook.img
		r.Patch(0x0087BC52, L"B8 01 00 00 00");// String/Map.img
		r.Patch(0x0087BC83, L"B8 01 00 00 00"); // Etc/ScanBlock.img
		r.Patch(0x0087BCB4, L"B8 01 00 00 00"); // Item/Cash/
		r.Patch(0x0134698D, L"B8 01 00 00 00"); // Item/Consume/


		//r.Patch(0x01346DE4, L"B8 01 00 00 00"); // skill
		r.Patch(0x01346E42, L"B8 01 00 00 00"); //
		r.Patch(0x01346EA0, L"B8 01 00 00 00"); //
		r.Patch(0x01346EFE, L"B8 01 00 00 00"); //
		r.Patch(0x01346F68, L"B8 01 00 00 00"); //
		r.Patch(0x01346FD5, L"B8 01 00 00 00"); //
		r.Patch(0x0134703F, L"B8 01 00 00 00"); //
		r.Patch(0x013470A9, L"B8 01 00 00 00"); //
		r.Patch(0x01347113, L"B8 01 00 00 00"); //
		r.Patch(0x013471BA, L"B8 01 00 00 00"); //
		r.Patch(0x013471FC, L"B8 01 00 00 00"); //

		break;
	}
	default: {
		break;
	}
	}
	return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);
		Hook();
	}
	return TRUE;
}