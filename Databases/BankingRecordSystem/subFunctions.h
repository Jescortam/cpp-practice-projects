#pragma once

void OptionsDisplay();
void InvalidInput();
void OpenFileError();
void AccountNumInput(int& account);
void NameInput(std::string& name, std::string typeName);
int SearchRecord(std::istream& file, int searchNumber);
