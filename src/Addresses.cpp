#include "Addresses.h"


LocalPlayerObject::LocalPlayerObject(Game& game)
{
	auto moduleAddr = game.GetModuleBase(L"UnityPlayer.dll");
	if (moduleAddr) {
		this->m_unityPlayerAddr = *moduleAddr;
	}
}

bool LocalPlayerObject::Update(Game& game)
{
	if (m_unityPlayerAddr == 0xDEADC0DE) return false;
	auto startAdr = game.ReadMemory<uintptr_t>(m_unityPlayerAddr + offsets::localPlayer);
	if (!startAdr) return false;

	uintptr_t current = *startAdr;
	logging::Info("starting path with " + utilities::StringifyUintptr(current));
	// Follow the path
	for (const uintptr_t& addr : offsets::localPlayerPath) {
		auto result = game.ReadMemory<uintptr_t>(current + addr);
		if (result.has_value()) current = *result;
		else return false;
	}
	// Now we got the object's address at current

	this->m_baseAddr = current;
	this->m_hpAddr = current + offsets::hp;
	this->m_jumpspeedAddr = current + offsets::jumppower;
	this->m_walkspeedAddr = current + offsets::walkspeed;
	logging::Info("Local player address: " + utilities::StringifyUintptr(m_baseAddr));
	logging::Info("Hp at: " + utilities::StringifyUintptr(m_hpAddr));
	logging::Info("Jumpspeed at: " + utilities::StringifyUintptr(m_jumpspeedAddr));
	logging::Info("Walkspeed at: " + utilities::StringifyUintptr(m_walkspeedAddr));
	return true;
}


int LocalPlayerObject::GetHp(Game& game)
{
	if (this->m_hpAddr == 0xDEADC0DE) return -1.0f;

	auto result = game.ReadMemory<int>(this->m_hpAddr);
	if (result.has_value()) return *result;
	else return -1;
}

float LocalPlayerObject::GetWalkspeed(Game& game)
{
	if (this->m_walkspeedAddr == 0xDEADC0DE) return -1.0f;

	auto result = game.ReadMemory<float>(this->m_walkspeedAddr);
	if (result.has_value()) return *result;
	else return -1.0f;
}

float LocalPlayerObject::GetJumpspeed(Game& game)
{
	if (this->m_jumpspeedAddr == 0xDEADC0DE) return -1.0f;

	auto result = game.ReadMemory<float>(this->m_jumpspeedAddr);
	if (result.has_value()) return *result;
	else return -1.0f;
}

bool LocalPlayerObject::SetHp(int value, Game& game)
{
	if (this->m_hpAddr == 0xDEADC0DE) return false;
	
	bool good = game.WriteMemory<int>(m_hpAddr, value);
	return good;
}

bool LocalPlayerObject::SetWalkspeed(float value, Game& game)
{
	if (this->m_walkspeedAddr == 0xDEADC0DE) return false;

	bool good = game.WriteMemory<float>(m_walkspeedAddr, value);
	return good;
}

bool LocalPlayerObject::SetJumpspeed(float value, Game& game)
{
	if (this->m_jumpspeedAddr == 0xDEADC0DE) return false;

	bool good = game.WriteMemory<float>(m_jumpspeedAddr, value);
	return good;
}
