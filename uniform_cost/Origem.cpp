#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#define n_cities 20
using namespace std;
//map is the adjacency matrix of the map from the problem. the columns is the cost to each node
//from the current node, each line represents the cost from the current node to each of the other nodes
//the columns and lines indexes is equivalent, this mean, the column 1 line 1, represents the cost of an node  to itself
//if an node doesnt have connection to other, the cost is 0.

//the o,rder of nodes used in this case is
//0 ORADEA -1 ZERIND -2 ARAD -3 SIBIU -4 FAGARAS -5 TIMISOARA -6 LUGOJ -7 RIMNICU VILCEA -
//8 PITESTI -9 MEHADIA -10 DOBRETA -11 CRAIOVA -12 BUCHAREST -13 GIURGIU -14 URZICENI -15 HIRSOVA - 
//16 EFORIE -17 VASLUI -18 LASI -19 NEAMT
int map[n_cities][n_cities] = {
	{ 0 ,71,0,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//oradea
	{71,0,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//zerind
	{0,75,0,140,0,118,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//arad
	{151,0,140,99,0,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0},//sibiu
	{0,0,0,99,0,0,0,0,0,0,0,0,211,0,0,0,0,0,0,0},//fagaras
	{0,0,118,0,0,0,111,0,0,0,0,0,0,0,0,0,0,0,0,0},//timisoara
	{0,0,0,0,0,111,0,0,0,70,0,0,0,0,0,0,0,0,0,0},//lugoj
	{0,0,0,80,0,0,0,0,97,0,0,146,0,0,0,0,0,0,0,0},//rimnicu vilcea
	{0,0,0,0,0,0,0,97,0,0,0,138,101,0,0,0,0,0,0,0},//pitesti
	{0,0,0,0,0,0,70,0,0,0,75,0,0,0,0,0,0,0,0,0},//mehadia
	{0,0,0,0,0,0,0,0,0,75,0,120,0,0,0,0,0,0,0,0},//dobreta
	{0,0,0,0,0,0,0,146,138,0,120,0,0,0,0,0,0,0,0,0},//craiova
	{0,0,0,0,211,0,0,0,101,0,0,0,0,90,85,0,0,0,0,0},//bucharest
	{0,0,0,0,0,0,0,0,0,0,0,0,90,0,0,0,0,0,0,0},//giurgiu
	{0,0,0,0,0,0,0,0,0,0,0,0,85,0,0,98,0,142,0,0},//urziceni
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,0,86,0,0,0},//hirsova
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,0,0,0,0},//eforte
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,92,0},//vaslui
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,92,0,87},//lasi
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,0} }; // neamt

//precisarei calcular o custo do n� a cada itera��o no array at� encontrar o n� final
struct path {
public:
	int cost;
	int current;
	string path_to;
	path(int a, int b, string c) {
		cost = a; current = b; path_to = c;
	}
	bool operator<(path b) {
		return cost < b.cost;
	}
};

auto cmp = [](path a, path b) {return a.cost < b.cost; };

path uniformCost(int source, int destination, int matrix[n_cities][n_cities]) {

	vector<path> work_arr;
	if (source == destination) {
		return path(0, source, " " + to_string(source));
	}
	else {
		vector<int> visited;
		work_arr.push_back({ 0,source," " + to_string(source)+" "});
		while (1) {
			for (int j = 0; j < work_arr.size(); j++) {
				
					
					cout << work_arr[j].path_to <<"cost "<<work_arr[j].cost << " current: " << work_arr[j].current << endl;
					
			}
			cout << "iteration" << endl;
			bool already_visited = false;
			for (int j = 0; j < visited.size(); j++) {
				if (visited[j] == work_arr[0].current) {
					already_visited = true;
					
				}
				cout << visited[j]<<" ";
			}
			cout << "--------------------"<<endl;
			if (already_visited == false) {
				for (int i = 0; i < n_cities; i++) {
					if (matrix[work_arr[0].current][i] > 0) {
						{

							work_arr.push_back({ matrix[work_arr[0].current][i] + work_arr[0].cost,	i,	(work_arr[0].path_to + to_string(i) + " ") });
							
						}

					}

				}

				visited.push_back(work_arr[0].current);
			}

			work_arr.erase(work_arr.begin());
			sort(work_arr.begin(), work_arr.end());
			if (work_arr[0].current == destination) {
				return work_arr[0];
			}
		}
	}
}
	//primeiro passo, checar se meu n� source � igual meu n� destino, ou seja, se eu j� estou onde quero chegar
	//em caso positivo apenas retorno.

	//o ponto mais importante � o comportamento do algoritmo, ele � muito parecido com uma busca em largura normal.
	//eu preciso navegar dentre os n�s que eu ainda n�o expandi e que eu�j� encontrei.

	//� necess�rio armazenar os n�s que eu j� expandi de alguma forma
	//primeiro passo, expandir o n� raiz. os n�s encontrados devem ser colocados numa fila.
	//essa fila ser� ordenada por ordem de custo, nesse caso, o primeiro custo � o valor para sair do n� raiz at� os n�s que eu adicionei.

	//a cada n� que eu expandir, ele ser� removido da fila, e seus filhos adicionados, fazendo o c�lculo do custo de cada filho.
	//a cada n� expandido, a fila deve ser reordenda por ordem de custo, para garantir que o n� de menor custo ser� o escolhido.
	//nesse caso, bastar� apenas remover o primeiro n�.

	//a condi��o de parada � o n� de menor custo ser o n� buscado, nesse caso, o caminho para chegar nesse n� deve ser armazenado tamb�m. 
	//uma forma de armazenar o custo � ter uma estrutura de dados, capaz de armazenar o caminho, o n� atual, e o custo total.

	//como a estrutura que trabalhar� no grafo ser� a lista ligada de n�s j� expandidos, o caminho pode ser armazenado na forma de uma string, com os �ndices dos n�s j� visitados. 
	//essa lista ligada que armazenar� os dados que retornaremos, tanto o n� atual, quanto  o pre�o para esse n� quanto o caminho.

	//ou seja, a estrutura de trabalho ser� uma lista ligada de uma estrutura "path." um path cont�m seu custo, seu current node e seu path.
	//existir� ainda uma lista ligada de inteiros que representar� os n�s j� expandidos.
	

int main() {
	path result = uniformCost(3,13, map);
	cout <<"caminho com menor custo" << result.path_to << endl;
	cout << result.cost;
	return 0;
}