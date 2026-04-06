#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include "MusicManager.h"

using namespace std;
using namespace sf;

MusicManager::MusicManager() {
	std::ifstream musicTSV("assets/dat/musicData.tsv");

	if (musicTSV.is_open()) {
		string line;
		while (std::getline(musicTSV, line)) {
			stringstream ss(line);

			string songName;
			float introLength;
			float loopLength;

			string temp;
			getline(ss, songName, '	');

			getline(ss, temp, '	');
			introLength = stof(temp);

			getline(ss, temp, '	');
			loopLength = stof(temp);

			loopLength -= introLength;

			SongData data;
			data.IntroPoint = introLength;
			data.LoopPoint = loopLength;

			_songList.insert(pair<string, SongData>(songName, data));
		}
	}
}

void MusicManager::Play(string songName) {
	if (songName == _currentSongName) return;

	_currentSong.stop();
	_currentSong.openFromFile("assets/snd/mus/" + songName + ".ogg");
	_currentSong.setLoopPoints({ seconds(_songList[songName].IntroPoint), seconds(_songList[songName].LoopPoint)});
	_currentSong.setLooping(true);
	_currentSong.play();
	_currentSongName = songName;
}

void MusicManager::Stop() {
	_currentSong.stop();
	_currentSongName = "";
}

void MusicManager::Pause() {
	_currentSong.pause();
}

void MusicManager::Resume() {
	if (_currentSong.getStatus() == SoundSource::Status::Paused) {
		_currentSong.play();
	}
}