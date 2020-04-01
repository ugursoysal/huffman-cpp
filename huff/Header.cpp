#include "../include/pch.h"
#include "../include/header.h"
#include <vector>
#include <fstream>
#include <iostream>
std::ostream &operator<<(std::ostream &os, Header const &m) {
	return os << m.CharCount << " | " << m.Filename << " | " << m.Frequencies.size() << " | " << m.Length << " | " << m.LastChar << '\n'; // can print header nicely
}
Header::Header(std::ifstream &f) : CharCount(0), Length(0), Filename("no"), LastChar('.')
{ // if there is an input file stream reference in the constructor parameter list, this is a decompression activity
	Read(f);
}

Header::Header(long CharCount, long Length, std::string original_filename, std::vector<Freq> &FreqArr, char LastCharacter) 
	: CharCount(CharCount), Length(Length), Filename(original_filename), LastChar(LastCharacter) 
{ // compression
	for (size_t i = 0; i < FreqArr.size(); i++) {
		Frequencies.push_back(header_pair(FreqArr[i].GetCharacter(),FreqArr[i].GetFrequency()));
	}
}

std::string Header::GetOriginalFilename() {
	return Filename;
}

long Header::GetLength() {
	return Length;
}

char Header::GetLastCharacter() {
	return LastChar;
}
std::vector<Freq> Header::GetFreqArr() {
	std::vector<Freq> newfreqarr;
	for (size_t i = 0; i < Frequencies.size(); i++) {
		newfreqarr.push_back(Freq(Frequencies[i].first, Frequencies[i].second));
	}
	return newfreqarr;
}

bool Header::Write(std::ofstream &f) {
	if (!f.is_open())
		return false;
	f.write((char*)&CharCount, sizeof(long));
	f.write((char*)&Length, sizeof(long));
	f.write(&LastChar, sizeof(char));
	std::size_t x = Filename.size();
	f.write((char*)&x, sizeof(std::size_t));
	for (size_t i = 0; i < x; i++)
		f.write(&Filename[i],sizeof(char));
	for (size_t i = 0; i < Frequencies.size(); i++) {
		f.write((char*)&Frequencies[i],sizeof(header_pair));
	}
	return true;
}
bool Header::Read(std::ifstream &f) {
	f.read((char*)&CharCount, sizeof(long));
	f.read((char*)&Length, sizeof(long));
	f.read(&LastChar, sizeof(char));
	std::size_t b;
	f.read((char*)&b, sizeof(std::size_t));
	Filename.resize(b);
	char w;
	for (size_t i = 0; i < b; i++) {
		f.read(&w, sizeof(char));
		Filename[i] = w;
	}

	header_pair bow;
	for (long a = 0; a < CharCount; a++) {
		f.read((char*)&bow, sizeof(header_pair));
		Frequencies.push_back(bow);
	}
	return true;
}