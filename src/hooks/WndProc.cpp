#include <pch.h>
#include <base.h>
#include "gamehook.hpp"

int GameHook::messageTimer = 200;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_DELETE:
			Data::ShowMenu = !Data::ShowMenu;
			if (Data::ShowMenu) {
				ImGui::GetIO().MouseDrawCursor = true;
				GameHook::disableClicking_toggle = true; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			else {
				ImGui::GetIO().MouseDrawCursor = false;
				GameHook::disableClicking_toggle = false; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			break;
		case VK_F1:
			GameHook::enemyHP_no_damage_toggle = !GameHook::enemyHP_no_damage_toggle;
			GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			if (GameHook::enemyHP_no_damage_toggle)
				GameHook::enemyHP_one_hit_kill_toggle = false;
			GameHook::showMessageTimerF1 = GameHook::messageTimer;
			break;
		case VK_F2:
			GameHook::takeNoDamage_toggle = !GameHook::takeNoDamage_toggle;
			GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
			GameHook::showMessageTimerF2 = GameHook::messageTimer;
			break;
		case VK_F3:
			GameHook::enemyHP_one_hit_kill_toggle = !GameHook::enemyHP_one_hit_kill_toggle;
			if (GameHook::enemyHP_one_hit_kill_toggle) {
				GameHook::enemyHP_no_damage_toggle = false;
				GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			}
			GameHook::showMessageTimerF3 = GameHook::messageTimer;
			break;
		case VK_F4:
			GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
			GameHook::InfJumps(GameHook::infJumps_toggle);
			GameHook::showMessageTimerF4 = GameHook::messageTimer;
			break;
		case VK_F5:
			GameHook::noClip_toggle = !GameHook::noClip_toggle;
			GameHook::NoClip(GameHook::noClip_toggle);
			GameHook::showMessageTimerF5 = GameHook::messageTimer;
			break;
		case VK_HOME:
			GameHook::SaveStates_SaveState();
			break;
		case VK_END:
			GameHook::SaveStates_LoadState();
			break;
		}
	}
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}
