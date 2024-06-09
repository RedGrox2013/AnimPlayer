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
	auto args = line.GetOption("id", 1);
	if (!args && line.GetArgumentsCount() == 1) {
		ConsolePrintF("Enter animation name or ID. For example: playAnim -id Physical");
		return;
	}

	auto strAnimID = args ? args[0] : line.GetArgumentAt(1);
	uint32_t animID;
	try {
		animID = mpFormatParser->ParseUInt(strAnimID);
	}
	catch (...) {
		animID = id(strAnimID);
	}

	Anim::AnimIndex index = -1;
	if (line.HasFlag("all")) {
		tGameDataVectorT<cCreatureAnimal> creatures = GetData<cCreatureAnimal>();
		if (creatures.empty())
			return;

		for (cCreatureAnimalPtr c : creatures) {
			index = c->PlayAnimation(animID);
			if (index == 0)
				break;
		}
	}
	else {
		cCreatureAnimalPtr avatar = GameNounManager.GetAvatar();
		if (!avatar)
			return;
		index = avatar->PlayAnimation(animID);
	}

	if (index == 0)
		ConsolePrintF("Animation \"%s\" not found", strAnimID);
}

const char* PlayAnimCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Play animation by name or ID. Type \"help playAnim\" for more info or type \"playAnimList\" to get a list of some animations from this mod.";
	}
	else {
		AppSystem.OpenURL(u"https://github.com/RedGrox2013/AnimPlayer#readme");
		return "PlayAnimCheat: play animation by name or ID. Type \"playAnimList\" to get a list of some animations from this mod. You can also find the animation in the tlsa file.";
	}
}
