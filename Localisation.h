#pragma once
#include <map>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

struct LocalisedString {
	wstring StringLangs[4];
};

class Localisation
{
public:
	Localisation();
	wstring GetLocalisedString(wstring id, int currentLang);
private:
	map<wstring, LocalisedString> _localeData;
};

