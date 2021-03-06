#pragma once
#include "stdafx.h"
#include "NativeDLL.h"

int alpha = 0, alpha2 = 0, alpha3 = 0;
float scroll = -0.50;
float fade = 0, zoom = 0.40;
int playerid = 0;
int weapon = 0;
float xscroll = 0.25;
bool t = false;
float yscroll;
int closest = -1;

// Functions
VOID Reset()
{
	bInitialized = FALSE;
}
DWORD GET_HASH_KEY(PCHAR Key)
{
	// Jenkins one at a time :P
	size_t len = strlen(Key);
	DWORD hash, i;
	for(hash = i = 0; i < len; ++i)
	{
		hash += tolower(Key[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
DWORD GetNativeFunctionAddress(DWORD NativeHash)
{
	for(INT i = 0; i < NATIVES->size(); i++)
	{
		if(NATIVES->operator[](i).NativeHash == NativeHash)
		{
			return NATIVES->operator[](i).NativeFunctionAddress;
		}
	}
	return NULL;
}
void SetPlayerModel(int playerId, DWORD hash) 
{
	Args[2][0] = playerId;
	Args[2][1] = hash;
	int (__cdecl *set_player_model)(void *) = (int (__cdecl *)(void *))GetNativeFunctionAddress(0x774A4C54);
}
void draw_rect(float xpos, float ypos, float xlen, float ylen, int r, int g, int b, int a) {
    Args[2][0] = *(DWORD *)(&xpos);
    Args[2][1] = *(DWORD *)(&ypos);
    Args[2][2] = *(DWORD *)(&xlen);
    Args[2][3] = *(DWORD *)(&ylen);
    Args[2][4] = r;
    Args[2][5] = g;
    Args[2][6] = b;
    Args[2][7] = a;
    ((void(*)(void *))GetNativeFunctionAddress(0xDD2BFC77))(Args);
}
VOID SET_TEXT_FONT(INT Font)
{
	Args[2][0] = Font;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x80BC530D))(Args);
}
VOID SET_TEXT_SCALE(FLOAT X, FLOAT Y)
{
	Args[2][0] = *(DWORD*)(&X);
	Args[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))GetNativeFunctionAddress(0xB6E15B23))(Args);
}
VOID SET_TEXT_COLOUR(BYTE R, BYTE G, BYTE B, BYTE A = 255)
{
	Args[2][0] = R;
	Args[2][1] = G;
	Args[2][2] = B;
	Args[2][3] = A;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0xE54DD2C8))(Args);
}
VOID SET_TEXT_OUTLINE()
{
	((VOID(*)(PVOID))GetNativeFunctionAddress(0xC753412F))(Args);
}
VOID SET_TEXT_WRAP(FLOAT X, FLOAT Y)
{
	Args[2][0] = *(DWORD*)(&X);
	Args[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x6F60AB54))(Args);
}
VOID SET_TEXT_CENTRE(INT Value)
{
	Args[2][0] = Value;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0xE26D39A1))(Args);
}
VOID _0x3E35563E(PCHAR String)
{
	Args[2][0] = (DWORD)String;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x3E35563E))(Args);
}
VOID _0x27A244D8(PCHAR String)
{
	Args[2][0] = (DWORD)String;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x27A244D8))(Args);
}
VOID _0x6F8350CE(FLOAT X, FLOAT Y)
{
	Args[2][0] = *(DWORD*)(&X);
	Args[2][1] = *(DWORD*)(&Y);
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x6F8350CE))(Args);
}

INT GET_PLAYER_PED(INT PlayerIndex)
{
	Args[2][0] = PlayerIndex;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x6E31E993))(Args);
	return (INT)(*Args[0]);
}
INT GET_NUMBER_OF_PLAYERS()
{
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x4C1B8867))(Args);
	return (INT)(*Args[0]);
}
PCHAR GET_PLAYER_NAME(INT PlayerIndex)
{
	PCHAR Return;
	DWORD VM[] = { PlayerIndex };
	PDWORD ArgsAlt[3] = { (PDWORD)&Return, (PDWORD)1, VM };
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x406B4B20))(ArgsAlt);
	return Return;
}

INT PLAYER_PED_ID()
{
	((VOID(*)(PVOID))GetNativeFunctionAddress(0xFA92E226))(Args);
	return (INT)(*Args[0]);
}
VOID GET_ENTITY_COORDS(INT PED_ID, PFLOAT Out)
{
	Args[2][0] = PED_ID;
	Args[2][1] = 1;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x1647F1CB))(Args);
	memcpy(Out, Args[0], 12);
}
VOID CREATE_AMBIENT_PICKUP(INT Hash, PFLOAT Origin, INT r5, INT r6, INT r7, INT r8, INT r9)
{
	Args[2][0] = Hash;
	Args[2][1] = *(DWORD*)(&Origin[0]);
	Args[2][2] = *(DWORD*)(&Origin[1]);
	Args[2][3] = *(DWORD*)(&Origin[2]);
	Args[2][4] = r5;
	Args[2][5] = r6;
	Args[2][6] = r7;
	Args[2][7] = r8;
	Args[2][8] = r9;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x17B99CE7))(Args);
}

// Misc
VOID SET_CINEMATIC_BUTTON_ACTIVE(BOOL Active)
{
	Args[2][0] = Active;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x3FBC5D00))(Args);
}
VOID DISABLE_CONTROL_ACTION(DWORD Unknown, INT Control)
{
	Args[2][0] = Unknown;
	Args[2][1] = Control;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x3800C0DC))(Args);
}
VOID _0x4E8E29E6(DWORD Unknown1, DWORD Unknown2)
{
	Args[2][0] = Unknown1;
	Args[2][1] = Unknown2;
	((VOID(*)(PVOID))GetNativeFunctionAddress(0x4E8E29E6))(Args);
}
VOID DisableControls()
{
	SET_CINEMATIC_BUTTON_ACTIVE(0);
	DISABLE_CONTROL_ACTION(0, 0);
	DISABLE_CONTROL_ACTION(0, 90);
	DISABLE_CONTROL_ACTION(0, 69);
	DISABLE_CONTROL_ACTION(0, 73);
	_0x4E8E29E6(2, 176);
	_0x4E8E29E6(2, 174);
	_0x4E8E29E6(2, 175);
	DISABLE_CONTROL_ACTION(0, 46);
	_0x4E8E29E6(2, 161);
	_0x4E8E29E6(2, 162);
	DISABLE_CONTROL_ACTION(2, 174);
	DISABLE_CONTROL_ACTION(2, 175);
	DISABLE_CONTROL_ACTION(2, 163);
	DISABLE_CONTROL_ACTION(2, 164);
	DISABLE_CONTROL_ACTION(2, 161);
	DISABLE_CONTROL_ACTION(2, 162);
	_0x4E8E29E6(2, 163);
	_0x4E8E29E6(2, 164);
	DISABLE_CONTROL_ACTION(0, 37);
	DISABLE_CONTROL_ACTION(0, 136);
	DISABLE_CONTROL_ACTION(0, 137);
	DISABLE_CONTROL_ACTION(0, 138);
	DISABLE_CONTROL_ACTION(0, 139);
	DISABLE_CONTROL_ACTION(0, 140);
	DISABLE_CONTROL_ACTION(0, 141);
	DISABLE_CONTROL_ACTION(0, 142);
	DISABLE_CONTROL_ACTION(0, 143);
	DISABLE_CONTROL_ACTION(0, 144);
	DISABLE_CONTROL_ACTION(0, 14);
	DISABLE_CONTROL_ACTION(0, 15);
	DISABLE_CONTROL_ACTION(0, 50);
	DISABLE_CONTROL_ACTION(0, 51);
	DISABLE_CONTROL_ACTION(0, 120);
	DISABLE_CONTROL_ACTION(0, 121);
	DISABLE_CONTROL_ACTION(0, 123);
	DISABLE_CONTROL_ACTION(0, 45);
	DISABLE_CONTROL_ACTION(0, 67);
	DISABLE_CONTROL_ACTION(0, 76);
	DISABLE_CONTROL_ACTION(0, 49);
	DISABLE_CONTROL_ACTION(0, 43);
	DISABLE_CONTROL_ACTION(0, 52);
	DISABLE_CONTROL_ACTION(0, 73);
	DISABLE_CONTROL_ACTION(0, 22);
	DISABLE_CONTROL_ACTION(0, 90);
	DISABLE_CONTROL_ACTION(0, 103);
	DISABLE_CONTROL_ACTION(0, 146);
	DISABLE_CONTROL_ACTION(0, 145);
	DISABLE_CONTROL_ACTION(0, 147);
	DISABLE_CONTROL_ACTION(0, 148);
	DISABLE_CONTROL_ACTION(0, 19);
}

// Stats
VOID SET_STAT_INT(DWORD Stat, INT Value)
{
    Args[2][0] = Stat;
    Args[2][1] = Value;
    ((VOID(*)(PVOID))GetNativeFunctionAddress(0xC9CC1C5C))(Args);
}
VOID SET_STAT_BOOL(DWORD Stat, BOOL Value)
{
    Args[2][0] = Stat;
    Args[2][1] = Value;
    ((VOID(*)(PVOID))GetNativeFunctionAddress(0x55D79DFB))(Args);
}

// Hooks

VOID LoadNative(DWORD r3, DWORD r4)
{
 if(NATIVES == NULL)
 { NATIVES = new std::vector<NATIVE>; }

 NATIVE TempNative;
 TempNative.NativeHash = r3;
 TempNative.NativeFunctionAddress = r4;
 NATIVES->push_back(TempNative);

 if(r3 < 2) { r3 += 2; }
 ((VOID(*)(DWORD, DWORD, DWORD))0x83517720)(0x83DCC0D8, r3, r4);
}   

__declspec(naked) UINT64 VM_ExecuteStub(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6)
{
	__asm
	{
		li r3, 1
		nop
		nop
		nop
		nop
		nop
		nop
		blr
	}
}
UINT64 VM_Execute(UINT64 r3, UINT64 r4, UINT64 r5, UINT64 r6)
{
	//DWORD LinkRegister; __asm { mflr LinkRegister }
	//DbgPrint("VM_Execute[%X] - r3[%X] r4[%i] r5[%X] r6[%X]\n", LinkRegister, r3, r4, r5, r6);
	//draw_rect(0.15, 0.22, 0.19, 0.17, 0, 0, 0, 150);

	SET_TEXT_FONT(7);
	SET_TEXT_SCALE(0.60, 0.60);
	SET_TEXT_COLOUR(255, 51, 51);
	SET_TEXT_OUTLINE();
	SET_TEXT_WRAP(0, 1);
	SET_TEXT_CENTRE(1);
	_0x3E35563E("STRING");
	_0x27A244D8("R1NZLR/XeXunbound");//CHANGE WHEN TU CHANGES
	_0x6F8350CE(0.85, 0.85);

	//SET_TEXT_FONT(4);
	//SET_TEXT_SCALE(0.60, 0.60);
	//SET_TEXT_COLOUR(255, 255, 255);
	//SET_TEXT_OUTLINE();
	//SET_TEXT_WRAP(0, 1);
	//SET_TEXT_CENTRE(1);
	//_0x3E35563E("STRING");
	//_0x27A244D8("Menu : DPAD DOWN");
	//_0x6F8350CE(0.15, 0.15);

	//SET_TEXT_FONT(4);
	//SET_TEXT_SCALE(0.60, 0.60);
	//SET_TEXT_COLOUR(255, 255, 255);
	//SET_TEXT_OUTLINE();
	//SET_TEXT_WRAP(0, 1);
	//SET_TEXT_CENTRE(1);
	//_0x3E35563E("STRING");
	//_0x27A244D8("Cash Drop On : A");
	//_0x6F8350CE(0.15, 0.20);

	//SET_TEXT_FONT(4);
	//SET_TEXT_SCALE(0.60, 0.60);
	//SET_TEXT_COLOUR(255, 255, 255);
	//SET_TEXT_OUTLINE();
	//SET_TEXT_WRAP(0, 1);
	//SET_TEXT_CENTRE(1);
	 //_0x3E35563E("STRING");
	//_0x27A244D8("Cash Drop Off : B");
   //_0x6F8350CE(0.15, 0.25);

	if(CashClient != -1)
	{
		FLOAT Coords[3];
		GET_ENTITY_COORDS(GET_PLAYER_PED(CashClient), Coords);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_VEHICLE_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_VEHICLE_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_PAPER_BAG"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_VARIABLE"), Coords, 0, 100000, 1, 0, 1);
		CREATE_AMBIENT_PICKUP(GET_HASH_KEY("PICKUP_MONEY_PAPER_BAG"), Coords, 0, 100000, 1, 0, 1);
	}

	if(MenuOpen == TRUE)
	{
		DisableControls();

	SET_TEXT_FONT(7);
	SET_TEXT_SCALE(1, 1);
	SET_TEXT_COLOUR(0, 0, 255);
	SET_TEXT_OUTLINE();
	SET_TEXT_WRAP(0, 1);
	SET_TEXT_CENTRE(1);
	_0x3E35563E("STRING");
	_0x27A244D8("Make it Rain");
	_0x6F8350CE(0.5, 0.08);

	draw_rect(0.75, 0.25, 0.25, 1, 0, 0, 0, 150);
		//DbgPrint("GET_NUMBER_OF_PLAYERS[%i]\n", GET_NUMBER_OF_PLAYERS());
		for(INT PlayerIndex = 0; PlayerIndex < 16; PlayerIndex++)
		{
			//DbgPrint("GET_PLAYER_NAME[%i][%s]\n", PlayerIndex, GET_PLAYER_NAME(PlayerIndex));
			//CHAR Buffer[1024];
			//sprintf(Buffer, "PlayerIndex %i", PlayerIndex);

			SET_TEXT_FONT(6);
			SET_TEXT_SCALE(0.8, 0.8);
			if(PlayerIndex == MenuScroll)
			{
				SET_TEXT_COLOUR(255, 0, 0);
			}
			else if(PlayerIndex == CashClient)
			{
				SET_TEXT_COLOUR(0, 255, 255);
			}
			else
			{
				SET_TEXT_COLOUR(255, 255, 255);
			}
			SET_TEXT_OUTLINE();
			SET_TEXT_WRAP(0, 1);
			SET_TEXT_CENTRE(1);
			_0x3E35563E("STRING");
			_0x27A244D8(GET_PLAYER_NAME(PlayerIndex));
			_0x6F8350CE(0.5, 0.17 + (PlayerIndex * 0.047));
		}
	}
	else
	//{
		//fade = 0; 
		//zoom = 0.40;
		//t = false;
		//xscroll = 0.125;
	//}

	//SET_TEXT_FONT(4);
	//SET_TEXT_SCALE(0.60f, 0.60f);
	//SET_TEXT_COLOUR(0, 155, 255, 255);
	//SET_TEXT_OUTLINE();
	//SET_TEXT_WRAP(0, 1);
	//SET_TEXT_CENTRE(1);
	//_0x3E35563E("STRING");
	//_0x27A244D8("Cash Dropper");//CHANGE WHEN TU CHANGES
	//if(scroll < 1.9f) scroll += 0.001; else scroll = -0.50;
	//_0x6F8350CE(scroll, 0.015f);

	if(DoUnlockAll == TRUE)
	{
		SET_STAT_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), 2165850);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_RACES_WON"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_PISTOL_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CMBTPISTOL_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_APPISTOL_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MICROSMG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SMG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSHTGN_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_PUMP_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_GRNLAUNCH_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_RPG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MINIGUNS_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CMBTMG_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_PISTOL_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600);
		SET_STAT_INT(GET_HASH_KEY("MP0_USJS_COMPLETED"), 50);
		SET_STAT_INT(GET_HASH_KEY("MP0_USJS_FOUND"), 50);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1);
		SET_STAT_INT(GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000);
		SET_STAT_INT(GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_RACES_WON"), 101);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
		SET_STAT_INT(GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50);
		SET_STAT_INT(GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50);
		//SET_STAT_INT(GET_HASH_KEY(ConvertString(("NO_MASKS_UNLOCK"), 25);
		//SET_STAT_INT(GET_HASH_KEY(ConvertString(("NO_TATTOOS_UNLOCK"), 61);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMMOSTKILLSSURVIVE"), 1);
		//SET_STAT_INT(GET_HASH_KEY(ConvertString(("AWD_ENEMYDRIVEBYKILLS"), 10);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 2);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_TIMES_RACE_BEST_LAP"), 101);
		SET_STAT_INT(GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 100);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 101);
		SET_STAT_INT(GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 105);
		//SET_STAT_INT(GET_HASH_KEY("MP0_CASH_GIFT_CREDITED"), 999);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_START"), 130);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_END"), 119);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_QUIT"), 11);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_START"), 140);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_END"), 115);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_QUIT"), 25);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_START"), 113);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_END"), 97);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_QUIT"), 16);
		SET_STAT_INT(GET_HASH_KEY("MP0_MPPLY_OVERALL_CHEAT"), 0);
		SET_STAT_INT(GET_HASH_KEY("MP0_LAP_DANCED_BOUGHT"), 50);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMKILLBOUNTY"), 50);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMKILL3ANDWINGTARACE"),  1);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_FMREVENGEKILLSDM"), 60);
		SET_STAT_INT(GET_HASH_KEY("MP0_AWD_SECURITY_CARS_ROBBED"), 40);
		SET_STAT_BOOL(GET_HASH_KEY("MP0_AWD_FMPICKUPDLCCRATE1ST"), 1);

		DoUnlockAll = FALSE;
	}

	return VM_ExecuteStub(r3, r4, r5, r6);
}

VOID NativeDLL()
{
	Sleep(1000);
	for(;;)
	{
		if(XamGetCurrentTitleId() == 0x545408A7) // GTA V
		{
			if(bInitialized == FALSE)
			{
			    DbgPrint("NativeDLL Loaded!\n");
				XNotify(L"Make it Rain");
				//Hook Game Functions
				// TU23
				DetourFunction((PDWORD)0x835180C8, (DWORD)LoadNative);

				// TU23
				HookFunctionStart((PDWORD)0x83518708, (PDWORD)VM_ExecuteStub, (DWORD)VM_Execute);
				
				bInitialized = TRUE;
			}

			XInputGetState(0, &InputState);
			if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)
			{
				MenuOpen = !MenuOpen;
			}
			//if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT) { }
			if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN)
			{
				MenuScroll--;
				if(MenuScroll == -1)
				{
					MenuScroll = 15;
				}
			}
			if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				MenuScroll++;
				if(MenuScroll == 16)
				{
					MenuScroll = 0;
				}
			}

			if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_A)
			{
				if(MenuOpen == TRUE)
				{
					CashClient = MenuScroll;
				}
			}

			if(InputState.Gamepad.wButtons == XINPUT_GAMEPAD_B)
			{
				if(MenuOpen == TRUE)
				{
					CashClient = -1;
				}
			}

			if(InputState.Gamepad.wButtons == (XINPUT_GAMEPAD_LEFT_THUMB & XINPUT_GAMEPAD_RIGHT_THUMB))
			{
				DoUnlockAll = TRUE;
			}

		} else { Reset(); };
		Sleep(100);
	}
}
BOOL WINAPI DllMain(HANDLE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		HANDLE hThread; DWORD hThreadID;
		ExCreateThread(&hThread, 0, &hThreadID, (PVOID)XapiThreadStartup , (LPTHREAD_START_ROUTINE)NativeDLL, NULL, 0x2);
		XSetThreadProcessor(hThread, 4);
		ResumeThread(hThread);
		CloseHandle(hThread);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
