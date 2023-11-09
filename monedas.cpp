#include <iostream>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <sys/wait.h>

int infinito = std::numeric_limits<int>::max();

int coinChange_recursive(int w[], int i, int j) {
	if (j == 0) {
		return 0;
	} else if (i == 0) {
		if (w[0] > j) {
			return infinito;
		} else {
			return 1 + coinChange_recursive(w, 1, j - w[0]);
		}
	} else {
		if (w[i - 1] > j) {
			return coinChange_recursive(w, i - 1, j);
		} else {
			return std::min(coinChange_recursive(w, i - 1, j), 1 + coinChange_recursive(w, i, j - w[i - 1]));
		}
	}
}


int* coin_change_solution(int w[], int N, int W, int** matrix){
	int* x = new int[N];

	int i = N-1, j = W;

	while(i>=0 && j>0){
		if(matrix[i][j] == 1+matrix[i][j-w[i]]){
			x[i]++;
			j -= w[i];
		} else{
			i--;
		}
	}

	return x;
}


int* coin_change_DP(int w[], int N, int W){
	int** matrix = new int*[W+1];

	for(int i = 0; i < N; i++){
		matrix[i] = new int[W+1];
	}

	//Caso base
	for(int i = 0; i < N; i++){
		matrix[i][0] = 0;
	}


	//Caso general
	for(int i = 0; i < N; i++){
		for(int j = 1; j < W+1; j++){
			if     (i==0 && w[0]> j) matrix[0][j] = infinito;
			else if(i==0 && w[0]<=j) matrix[0][j] = 1 + matrix[0][j-w[0]];
			else if(i> 0 && w[i]> j) matrix[i][j] = matrix[i-1][j];
			else if(i> 0 && w[i]<=j) matrix[i][j] = std::min(matrix[i-1][j], 1+matrix[i][j-w[i]]);
		}
	}

	return coin_change_solution(w, N, W, matrix);
}

int* coin_change_solution_adm(int w[], int N, int W, int** matrix, int*** pointers){

	std::cout << "solution_adm\n";
	int* x = new int[N];

	int i = N-1, j = W;

	while(pointers[i][j] != nullptr){

		int ii = pointers[i][j][0];
		int jj = pointers[i][j][1];

		std::cout << ii << "  " << jj << "\n";
		sleep(1);

		if (jj != j) x[i] = x[i] + 1;
	}

	i = pointers[i][j][0];
	j = pointers[i][j][1];

	return x;
}


int* coin_change_DP_adm(int w[], int N, int W){ // Pointers no se crea correctamente.

	int** matrix = new int*[W+1];
	int*** pointers= new int**[W+1];

	for(int i = 0; i < N; i++){
		matrix[i] = new int[W+1];
		pointers[i] = new int*[W+1];
		for(int j = 0; j <= W; j++){
			pointers[i][j] = new int[2];
		}
	}

	//Caso base
	for(int i = 0; i < N; i++){
		matrix[i][0] = 0;
		pointers[i][0] = nullptr;
	}

	//Caso general
	for(int i = 0; i < N; i++){
		for(int j = 1; j < W+1; j++){
			if (i==0 && w[0]> j){
				matrix[0][j] = infinito;
				pointers[0][j] = nullptr;
			}else if(i==0 && w[0]<=j){
				matrix[0][j] = 1 + matrix[0][j-w[0]];
				pointers[0][j][0] = 0;
				pointers[0][j][1] = j-w[0];
			}else if(i> 0 && w[i]> j){
				matrix[i][j] = matrix[i-1][j];
				pointers[0][j][0] = i-1;
				pointers[0][j][1] = j;
			}else if(i> 0 && w[i]<=j){
				matrix[i][j] = std::min(matrix[i-1][j], 1+matrix[i][j-w[i]]);
				if(matrix[i-1][j] < 1+matrix[i][j-w[i]]){
					pointers[0][j][0] = i-1;
					pointers[0][j][1] = j;
				}else{
					pointers[i][j][0] = i;
					pointers[0][j][1] = j-w[i];
				}
			}
		}
	}

	std::cout << "Matriz punteros:\n|";
	for(int i = 0; i < N; i++){
		for(int j = 0; j < W+1; j++){
			if(pointers[i][j] != nullptr){
				std::cout << pointers[i][j][0] << "," << pointers[i][j][1] << "|";
			}else{
				std::cout << "NUL|";
			}
		}
		std::cout << "\n|";
	}
	std::cout << "\n";

	return coin_change_solution_adm(w, N, W, matrix, pointers);
}


int main() {
	int w[] = {1, 4, 6}; // Aquí debes proporcionar tu conjunto de monedas
	int N = 3; // N es el número de monedas
	int W = 8; // j es la cantidad para el cambio
	int* result = new int[N];
	result = coin_change_DP(w, N, W);

	std::cout << "\nLa solucion del problema es: [ ";

	int total = 0;
	for(int i = 0; i < N; i++){
		std::cout << result[i] << " ";
		total += result[i];
	}
	std::cout << "] en total " << total << " monedas.\n\n";

	return 0;
}
