#include "stdafx.h"
#include "HAPIH-2/HAPIH.h"
#include "offsets.h"
#include <iostream>


int main() {


	offsets Address;
	HiddenGlow g;
	SpottedGlow s_g;
	HackIH Game;
	Game.bind("csgo.exe");
	PVOID BaseAddress = Game.GetModuleAddress("client.dll");
	DWORD baseLocalPlayer = (DWORD)BaseAddress + Address.dwLocalPlayer;
	DWORD JumpAddr = (DWORD)BaseAddress + Address.dwForceJump;
	DWORD LocalPlayer = Game.Read<int>({ baseLocalPlayer });
	DWORD FlagBase = LocalPlayer + Address.m_fFlags;
	
	while (true) {
		if (GetKeyState(VK_F1)) {
			for (int i = 0; i < 65; i++) {
				DWORD Teammates =
					Game.Read<int>({ (DWORD)baseLocalPlayer, Address.m_iTeamNum });
				DWORD baseEntity = (DWORD)BaseAddress + Address.dwEntityList + i * 0x10;
				DWORD EntityList = Game.Read<int>({ (DWORD)baseEntity });
				
				DWORD baseGlowIndex = EntityList + Address.m_iGlowIndex;
				DWORD entityGlowIndex = Game.Read<bool>({ (DWORD)baseGlowIndex });
				DWORD baseGlowObj = (DWORD)BaseAddress + Address.dwGlowObjectManager;
				DWORD GlowObject = Game.Read<int>({ (DWORD)baseGlowObj });
		
				DWORD IsSpottedBase = EntityList + Address.m_bSpotted;
				DWORD IsSpotted = Game.Read<bool>({ IsSpottedBase });

				// Writing Section
				if (IsSpotted == 0) {
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x4)), g.r);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x8)), g.g);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0xC)), g.b);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x10)), g.a);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x24)), g.rwo);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x25)), g.rwuo);
				}

				else {
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x4)), s_g.r);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x8)), s_g.g);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0xC)), s_g.b);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x10)), s_g.a);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x24)), s_g.rwo);
					Game.Write((GlowObject + ((entityGlowIndex * 0x38) + 0x25)), s_g.rwuo);
				}
			}
		}//ESP
		if (GetKeyState(VK_F2)) {
			DWORD JumpAddr = (DWORD)BaseAddress + Address.dwForceJump;
			DWORD baseLocalPlayer = (DWORD)BaseAddress + Address.dwLocalPlayer;
			DWORD LocalPlayer = Game.Read<int>({ baseLocalPlayer });
			DWORD FlagBase = LocalPlayer + Address.m_fFlags;
			while (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				DWORD Flag = Game.Read<int>({ FlagBase });
				if (Flag & 1 << 0) {
					Game.Write(JumpAddr, 1);

				}
				else {
					Game.Write(JumpAddr, 0);
				}
				Sleep(10);
			}
		}//BHOP
		if (GetKeyState(VK_F4)) {
			DWORD baseLocalPlayer = (DWORD)BaseAddress + Address.dwLocalPlayer;
			DWORD LocalPlayer = Game.Read<int>({ baseLocalPlayer });
			DWORD noFlashBase = LocalPlayer + Address.m_flFlashMaxAlpha;
			float noFlash = Game.Read<float>({ noFlashBase });
			
			if (noFlash > 0.0f) {
					Game.Write(noFlashBase, 128.0f);
				}
			else if (noFlash == 0.0f) {
					Game.Write(noFlashBase, 255.0f);
				}

			}
	
		
		
	}
}