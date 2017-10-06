#include <iostream>
#include <bitset>

using namespace std;

const int nLayers = 8;
const int nColumns = 8;
const int nRows = 8;
const int cubeSize = nLayers * nColumns * nRows;

bitset<cubeSize> cube;

int getBitFromCube(int layer, int column, int row) {
	if (layer > nLayers) layer = nLayers;
	else if (layer < 1) layer = 1;
	if (column > nColumns) column = nColumns;
	else if (column < 1) column = 1;
	if (row > nRows) row = nRows;
	else if (row < 1) row = 1;

	return cube[(layer - 1) * 64 + (column - 1) * 8 + (row - 1)];
}

unsigned long getByteFromCube(int layer, int column) {
	bitset<8> byte;
	for (int i = 1; i <= 8; i++) {
		byte[i - 1] = getBitFromCube(layer, column, i);
	}
	return byte.to_ulong();
}

int main() {
	for (int i = 0; i < 512; i++) {
		cube[i] = (i / 8) % 2;
	}
	cout << cube << endl;
	int layer = 100;
	int column = 8;
	int row = 8;
	cout << getByteFromCube(1, 2) << endl;
}
