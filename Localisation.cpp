#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include "Localisation.h"

using namespace std;

Localisation::Localisation() {
	std::ios::sync_with_stdio(false);
	std::locale loc("jp-JP.utf8");
	std::wcout.imbue(loc);
	std::wfstream localeTSV("assets/dat/lang.tsv");
	localeTSV.imbue(loc);

	if (localeTSV.is_open()) {
		wstring line;
		while (std::getline(localeTSV, line)) {
			wstringstream ss(line);

			wstring stringID;
			wstring engString;
			wstring espString;
			wstring jpnString;

			getline(ss, stringID, L'	');
			getline(ss, engString, L'	');
			getline(ss, espString, L'	');
			getline(ss, jpnString, L'	');

			wcout << line << endl;

			LocalisedString locale;
			locale.StringLangs[0] = engString;
			locale.StringLangs[1] = espString;
			locale.StringLangs[2] = jpnString;

			_localeData.insert(pair<wstring, LocalisedString>(stringID, locale));
		}
	}
}

wstring Localisation::GetLocalisedString(wstring id, int currentLang) {
	return _localeData[id].StringLangs[currentLang];
}