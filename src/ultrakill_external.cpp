#include "GuiWindow.h"
#include "Addresses.h"

int main(void) {
	try {
		GuiWindow wnd;
		Game game(L"ULTRAKILL.exe");
		LocalPlayerObject localPlayer(game);
		localPlayer.Update(game);
		std::atomic<bool> playerValid = true;

		wnd.OnHpSlider([&playerValid, &game, &localPlayer](int value) {
			logging::Info("Hp slider updated");
			playerValid = localPlayer.Update(game);
			playerValid = localPlayer.SetHp(value, game);
			});
		wnd.OnJumpspeedSlider([&playerValid, &game, &localPlayer](int value) {

			logging::Info("jumpspeed slider updated");
			playerValid = localPlayer.Update(game);
			playerValid = localPlayer.SetJumpspeed(static_cast<float>(value), game);
			});

		wnd.OnWalkspeedSlider([&playerValid, &game, &localPlayer](int value) {
			logging::Info("walkspeed slider updated");
			playerValid = localPlayer.Update(game);
			playerValid = localPlayer.SetJumpspeed(static_cast<float>(value), game);
			});

		wnd.OnImguiRender([&playerValid, &wnd]() {
			if (!playerValid) {
				ImVec4 redColor(1.0f, 0.0f, 0.0f, 1.0f);
				ImGui::TextColored(redColor, "Failed to get player! Are you in a level!?");
			}
			});
		wnd.Run();
	}
	catch (const std::exception& ex) {
		logging::Error("Error in main loop!");
		logging::Error(ex.what());
	}
}

