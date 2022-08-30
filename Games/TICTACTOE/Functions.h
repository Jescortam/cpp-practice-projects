#pragma once

void DrawTable(int array[9]);

void AskPlayer(int player, int& column, int& row, int& index);

void PlayerWon(int player);

void CheckSides(int a, int b, int c, int player);

void CheckVictory(int array[], int player);