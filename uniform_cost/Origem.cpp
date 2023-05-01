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

string cities[20] = { "Oradea","Zerind","Arad","Sibiu","Fagaras","Timisoara","Lugoj","Rimnicu-Vilcea","Pitesti","Mehadia","Dobreta","Craiova","Bucharest","Giurgiu","Urziceni","Hirsova","Eforie","Valsui","Lasi","Neamt" };


//precisarei calcular o custo do nó a cada iteração no array até encontrar o nó final
struct path {
public:
	int cost;
	int current;
	vector<int> path_to;
	path(int a, int b, vector<int> c) {
		cost = a; current = b; path_to = c;
	}
	bool operator<(path b) {
		return cost < b.cost;
	}
};
string convertPath(vector<int> a) {
	string output;
	for (int i = 0; i < a.size(); i++) {
		output += (cities[a[i]]);
		if (i < (a.size() - 1) ){
			output+=" - ";
		}
	}
	return output;
}

int findCityIndex(string c) {
	for (int i = 0; i < n_cities; i++) {
		if (c == cities[i]) {
			return i;
		}
	}
	return -1;
}
auto cmp = [](path a, path b) {return a.cost < b.cost; };

path uniformCost(int source, int destination, int matrix[n_cities][n_cities]) {

	vector<path> work_arr;
	if (source == destination) {
		return path(0, source, {source});
	}
	else {
		vector<int> visited;
		work_arr.push_back({ 0,source,{source} });
		while (1) {
			// Debug Only Line: 
			/*for (int j = 0; j < work_arr.size(); j++) {
				for (int k = 0; k < work_arr[j].path_to.size(); k++) {
					cout << work_arr[j].path_to[k] << " ";
				}

				cout <<"cost "<<work_arr[j].cost << " current: " << work_arr[j].current << endl;
			}
			cout << "iteration" << endl;
			*/
			bool already_visited = false;
			for (int j = 0; j < visited.size(); j++) {
				if (visited[j] == work_arr[0].current) {
					already_visited = true;
					
				}
				//cout << visited[j]<<" ";
			}
			//cout << "--------------------"<<endl;
			if (already_visited == false) {
				for (int i = 0; i < n_cities; i++) {
					if (matrix[work_arr[0].current][i] > 0) {
						{	
							path temp = { matrix[work_arr[0].current][i] + work_arr[0].cost,	i,	work_arr[0].path_to };
							temp.path_to.push_back(i);
							work_arr.push_back(temp);
							
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
	//primeiro passo, checar se meu nó source é igual meu nó destino, ou seja, se eu já estou onde quero chegar
	//em caso positivo apenas retorno.

	//o ponto mais importante é o comportamento do algoritmo, ele é muito parecido com uma busca em largura normal.
	//eu preciso navegar dentre os nós que eu ainda não expandi e que eu´já encontrei.

	//é necessário armazenar os nós que eu já expandi de alguma forma
	//primeiro passo, expandir o nó raiz. os nós encontrados devem ser colocados numa fila.
	//essa fila será ordenada por ordem de custo, nesse caso, o primeiro custo é o valor para sair do nó raiz até os nós que eu adicionei.

	//a cada nó que eu expandir, ele será removido da fila, e seus filhos adicionados, fazendo o cálculo do custo de cada filho.
	//a cada nó expandido, a fila deve ser reordenda por ordem de custo, para garantir que o nó de menor custo será o escolhido.
	//nesse caso, bastará apenas remover o primeiro nó.

	//a condição de parada é o nó de menor custo ser o nó buscado, nesse caso, o caminho para chegar nesse nó deve ser armazenado também. 
	//uma forma de armazenar o custo é ter uma estrutura de dados, capaz de armazenar o caminho, o nó atual, e o custo total.

	//como a estrutura que trabalhará no grafo será a lista ligada de nós já expandidos, o caminho pode ser armazenado na forma de uma string, com os índices dos nós já visitados. 
	//essa lista ligada que armazenará os dados que retornaremos, tanto o nó atual, quanto  o preço para esse nó quanto o caminho.

	//ou seja, a estrutura de trabalho será uma lista ligada de uma estrutura "path." um path contém seu custo, seu current node e seu path.
	//existirá ainda uma lista ligada de inteiros que representará os nós já expandidos.
	

int main() {
	int map[n_cities][n_cities] = {
	{ 0 ,71,0,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//oradea 0
	{71,0,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//zerind    1
	{0,75,0,140,0,118,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//arad   2
	{151,0,140,0,99,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0},//sibiu 3
	{0,0,0,99,0,0,0,0,0,0,0,0,211,0,0,0,0,0,0,0},//fagaras  4
	{0,0,118,0,0,0,111,0,0,0,0,0,0,0,0,0,0,0,0,0},//timisoara 5
	{0,0,0,0,0,111,0,0,0,70,0,0,0,0,0,0,0,0,0,0},//lugoj      6
	{0,0,0,80,0,0,0,0,97,0,0,146,0,0,0,0,0,0,0,0},//rimnicu vilcea 7
	{0,0,0,0,0,0,0,97,0,0,0,138,101,0,0,0,0,0,0,0},//pitesti       8
	{0,0,0,0,0,0,70,0,0,0,75,0,0,0,0,0,0,0,0,0},//mehadia          9
	{0,0,0,0,0,0,0,0,0,75,0,120,0,0,0,0,0,0,0,0},//dobreta         10
	{0,0,0,0,0,0,0,146,138,0,120,0,0,0,0,0,0,0,0,0},//craiova      11
	{0,0,0,0,211,0,0,0,101,0,0,0,0,90,85,0,0,0,0,0},//bucharest    12
	{0,0,0,0,0,0,0,0,0,0,0,0,90,0,0,0,0,0,0,0},//giurgiu           13
	{0,0,0,0,0,0,0,0,0,0,0,0,85,0,0,98,0,142,0,0},//urziceni       14
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,0,86,0,0,0},//hirsova          15
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,0,0,0,0},//eforte            16
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,92,0},//vaslui          17
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,92,0,87},//lasi             18
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,87,0} }; // neamt         19
	
	bool exit = false;

	while (!exit) {
		string cityA, cityB;
		int idxA=-1, idxB=-1;
		while (idxA == -1 || idxB == -1) {
			cout << "Insira o nome da cidade origem: ";
			cin >> cityA;
			cout << "Insira o nome da cidade destino: ";
			cin >> cityB;

			idxA = findCityIndex(cityA);
			idxB = findCityIndex(cityB);
		}
		path result = uniformCost(idxA, idxB, map);
		cout << "caminho com menor custo: " << endl << convertPath(result.path_to) << endl;
		cout << "Custo do caminho: " << result.cost<<endl;
		cout << "------------ " << endl << endl;

	}
	return 0;
}