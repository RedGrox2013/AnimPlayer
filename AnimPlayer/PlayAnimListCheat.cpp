#include "stdafx.h"
#include "PlayAnimListCheat.h"
#include <Spore/Properties.h>

using namespace App;

PlayAnimListCheat::PlayAnimListCheat()
{
}


PlayAnimListCheat::~PlayAnimListCheat()
{
}

void PlayAnimListCheat::AddCheat()
{
	CheatManager.AddCheat("playAnimList", new PlayAnimListCheat());
}

void PlayAnimListCheat::ParseLine(const ArgScript::Line& line)
{
	const uint32_t GROUP_ID = id("AnimPlayer");

	vector<uint32_t> propIDs;
	if (!PropManager.GetPropertyListIDs(GROUP_ID, propIDs))
		return;

	ConsolePrintF("Type \"playAnim <animation>\" to play the animation. List of some animations:");
	for (size_t i = 0; i < propIDs.size(); i++) {
		PropertyListPtr prop;
		PropManager.GetPropertyList(propIDs.at(i), GROUP_ID, prop);

		size_t count;
		string16* animationsNames;
		Property::GetArrayString16(prop.get(), id("animationsNames"), count, animationsNames);
		for (size_t i = 0; i < count; i++)
			ConsolePrintF("playAnim %ls", *(animationsNames + i));
	}
	ConsolePrintF("\nYou can also find the animation in the tlsa file. Type \"help playAnim\" for more info.");
}

const char* PlayAnimListCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Get a list of animations available in the \"AnimPlayer\" mod. Type \"help playAnim\" for more info.";
	}
	else {
		return "playAnimList: get a list of animations available in the \"AnimPlayer\" mod. Type \"help playAnim\" for more info.";
	}
}
