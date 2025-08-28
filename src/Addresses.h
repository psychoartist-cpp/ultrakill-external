#pragma once

#include "Game.h"

// 28.08.2025
// Obtained with cheat engine
namespace offsets {
	const std::vector<uintptr_t> localPlayerPath = {
		0x8, 0x90, 0x10, 0x60, 0x20
	};
	constexpr uintptr_t localPlayer = 0x01cb1640;
	constexpr uintptr_t hp = 0x2b0; // int
	constexpr uintptr_t walkspeed = 0x244; // float
	constexpr uintptr_t jumppower = 0x248; // float
}

struct LocalPlayerObject {
private:
	uintptr_t m_baseAddr = 0xDEADC0DE;
	uintptr_t m_hpAddr = 0xDEADC0DE;
	uintptr_t m_walkspeedAddr = 0xDEADC0DE;
	uintptr_t m_jumpspeedAddr = 0xDEADC0DE;
	uintptr_t m_unityPlayerAddr = 0xDEADC0DE;
public:
	LocalPlayerObject(Game& game);
	~LocalPlayerObject() = default;

	bool Update(Game& game);

	int GetHp(Game& game);
	float GetWalkspeed(Game& game);
	float GetJumpspeed(Game& game);

	bool SetHp(int value, Game& game);
	bool SetWalkspeed(float value, Game& game);
	bool SetJumpspeed(float value, Game& game);

};