#include "stdafx.h"
#include "PlayAnimCheat.h"
#include <Spore/Properties.h>
#include "ShellAPI.h"

using namespace App;
using namespace Simulator;

PlayAnimCheat::PlayAnimCheat()
{
}


PlayAnimCheat::~PlayAnimCheat()
{
}

void PlayAnimCheat::AddCheat()
{
	CheatManager.AddCheat("playAnim", new PlayAnimCheat());
}

void PlayAnimCheat::ParseLine(const ArgScript::Line& line)
{
	if (line.GetArgumentsCount() == 1) {
		ConsolePrintF("Enter animation name. For example: playAnim Physical");
		return;
	}
	/*if (!IsCreatureGame() && !IsScenarioMode())
		return;*/

	cCreatureAnimalPtr avatar = GameNounManager.GetAvatar();
	if (avatar == nullptr)
		return;

	uint32_t animID;
	try {
		animID = mpFormatParser->ParseUInt(line.GetArgumentAt(1));
	}
	catch (...) {
		animID = id(line.GetArgumentAt(1));
	}

	auto index = avatar->PlayAnimation(animID);

#ifdef _DEBUG
	ConsolePrintF("Animation index: %d", index);
#endif // _DEBUG

	if (index == 0)
		ConsolePrintF("Animation \"%d\" not found", line.GetArgumentAt(1));
}

const char* PlayAnimCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Play animation by name or ID. Type \"help playAnim\" for more info or type \"playAnimList\" to get a list of some animations from this mod.";
	}
	else {
		ShellExecute(NULL, L"open", L"https://github.com/RedGrox2013/AnimPlayer#readme", NULL, NULL, SW_SHOW);
		return "PlayAnimCheat: play animation by name or ID. Type \"playAnimList\" to get a list of some animations from this mod. You can also find the animation in the tlsa file.";
	}
}
