#pragma once
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "HAPIH.h"
#include <iostream>
#include <string>

//insert your offsets here

class offsets{

public:
	
	DWORD dwGlowObjectManager;
	DWORD m_iGlowIndex;
	DWORD dwLocalPlayer;
	DWORD dwEntityList;
	DWORD m_iTeamNum;
	DWORD m_iHealth;
	DWORD m_fFlags;
	DWORD dwForceJump;
	DWORD m_bSpotted;
	DWORD m_flFlashMaxAlpha;

};
class HiddenGlow {
public:
	
	PVOID playerEnt;
	float r = 1;
	float g = 0;
	float b = 0;
	float a = 1;
	uint8_t unk1[16];
	bool rwo = true; //render when occluded
	bool rwuo = false; //render when unoccluded
	bool FB; //Full Bloom
	uint8_t unk2[14];
	
};

class SpottedGlow {
public:
	
	PVOID playerEnt;
	float r = 0;
	float g = 1;
	float b = 0;
	float a = 1;
	uint8_t unk1[16];
	bool rwo = true; //render when occluded
	bool rwuo = false; //render when unoccluded
	bool FB; //Full Bloom
	uint8_t unk2[14];
	
};
#endif