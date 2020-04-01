#include "../include/freq.h"

Freq::Freq(char character, int frequency) : Character(character), Frequency(frequency) { }


void Freq::SetCharacter(char c) {
	Character = c;
}

char Freq::GetCharacter() {
	return Character;
}

void Freq::IncreaseFrequency() {
	Frequency++;
}

int Freq::GetFrequency() {
	return Frequency;
}