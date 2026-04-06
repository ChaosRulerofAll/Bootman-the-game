#pragma once
#include <map>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

struct SongData {
	double IntroPoint;
	double LoopPoint;
};

class MusicManager
{
public:
	MusicManager();
	void Play(string songName);
	void Stop();
	void Pause();
	void Resume();
private:
	map<string, SongData> _songList;
	Music _currentSong;
	string _currentSongName = "";
};
