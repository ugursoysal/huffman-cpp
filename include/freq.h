#ifndef HFREQ_H
#define HFREQ_H

class Freq {
private:
	char Character;
	int Frequency; // frequency of the specified character
public:
	Freq() : Character('?'), Frequency(0) { };
	Freq(const char character) : Character(character), Frequency(0) { };
	Freq(const char character, const int frequency);
	int GetFrequency();
	char GetCharacter();
	void SetCharacter(char c);
	void IncreaseFrequency();

	operator int() { return GetFrequency(); }
};
#endif