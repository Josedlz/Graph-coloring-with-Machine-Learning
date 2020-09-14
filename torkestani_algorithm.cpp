//Entrega final del proyecto, corre para todos los grafos
#include <bits/stdc++.h>
using namespace std;
 
int V, E;
//lista de adyacencia
vector<int> adj[1000];
//vector de probabilidades para cada vertice
double probs[2000][2000];
//dynamic threshold para cada vertice
//guarda la cardinalidad minima de todos los 
//color localsets vistos hasta el momento
int T[1000];
//color de cada vertice;
int color[1000];
//grado de cada vertice
int degree[1000];
//supero el threshold
bool over[1000];
double learning_rate = 0.1; 

void penalize(int v, int co){
	//if(probs[v][co] < 0.001) 
		//return;
	for(int i = 0; i < V; i++){
    if(i == co){
      probs[v][i] -= 0.05;
    }
    else{
      probs[v][i] += 0.01;
    }
  }
}
 
void reward(int v, int co){
	if(probs[v][co] > 0.99)
		return;
	for(int i = 0; i < V; i++){
    if(i == co){
      probs[v][i] += 0.01;
    }
    else{
      probs[v][i] -= 0.05;
    }
  }
}
 
void find_degrees(){
	for(int i = 0; i < V; i++){
    degree[i] = int(adj[i].size());
	}
}
 
void set_probs(){
	for(int i = 0; i < V; i++){
		for(int j = 0; j < (degree[i] + 1); j++){
			probs[i][j] = 1.0 / (degree[i] + 1);
    }
	}
}
 
bool neighboor_same_color(int v, int co){
	for(int w : adj[v])
		if(color[w] == co) 
			return 1;
	return 0;
}
 
int compute_color_degree(int v, int co){
	set<int> colors;
	colors.insert(co);
	for(int w : adj[v]){
		colors.insert(color[w]);
	}
	cout << "compute color set: " << colors.size() << endl;
	return colors.size();
}
 
bool check_local_reward(int v, int co){
	for(int w : adj[v]){
		set<int> colors;
		colors.insert(co);
		for(int nb : adj[w]){
			colors.insert(color[nb]);
		}
		if(int(colors.size()) > T[w]){
			return 0;
		}
	}
	return 1;
}
 
bool check_threshold_passed(double t){
  bool end = true;
	for(int v = 0; v < V; v++){
    if(over[v]) continue;
		double mx = probs[v][0];
    //let's find the max probability
		for(int i = 1; i < (degree[v] + 1); i++){
			if(probs[v][i] > mx){
				mx = probs[v][i];
			}
		}
    //let's check if one vertex still doesn't reach it
		if(mx < t){
			end = false;
		}
    else{
      over[v] = true;
    }
	}
	return end;
}

int max_prob(int cell){
	double mx = -1;
	size_t mx_idx = 0;
	for(int i = 0; i < int(degree[cell] + 1); i++){
		if(probs[cell][i] > mx){
			mx = probs[cell][i];
			mx_idx = i;
		}
	}
	return mx_idx;
}

//esto es si queremos quwe elija al azar

int randint(int a, int b){
	random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<std::mt19937::result_type> dist6(a, b); // distribution in range [a,b]
	
	return dist6(rng);
}

bool are_two_the_same(int x){
	int y;
	do{
		y = randint(0, V - 1);	
	}while(over[y]);
	
	if(x == y) return false;

	int range = min(degree[x] + 1, degree[y] + 1);

	for(int i = 0; i < range; i++){
		if(probs[x][i] != probs[y][i])
			return false;
	}
	//elijo uno al azar
	int mx = max_prob(x);
	int r = randint(0, degree[x] + 1);
	probs[x][r] = probs[x][mx] + 0.05;
	return true;
}
 
void torkestani(double threshold){
	bool threshold_passed = false;
	while(!threshold_passed){
		for(int cell = 0; cell < V; cell++){
      if(over[cell]) continue;
			
			//int selected_color = (are_two_the_same(cell) ? randint(0, V - 1) : max_prob(cell));
			int selected_color = max_prob(cell);

			cout << "vertex : " << cell << endl;
			cout << "selected color : " << selected_color << endl;
			//verifico si algun vecino tiene el mismo color
			if(neighboor_same_color(cell, selected_color)){
				cout << "vecino con mismo color, penalizando" << endl;
				penalize(cell, selected_color);
			}
			else{
				cout << "vecinos dif color" << endl;
				int color_degree = compute_color_degree(cell, selected_color);
				//si el color_degree es menor que el minimo
				//local visto hasta el momento
				if(color_degree <= T[cell]){
					cout << "color optimo, recompensando" << endl;
					reward(cell, selected_color);
					//checkeo si mis vecinos tambien son 
					//recompensados con esta eleccion
					if(check_local_reward(cell, selected_color)){
						cout << "vecinos recompensados, minimizando" << endl;
						T[cell] = color_degree;
						color[cell] = selected_color;
					}
				}
				else{
					cout << "color no optimo, penalizando" << endl;
					penalize(cell, selected_color);
				}
			}
		}
		//checkeo si ya han superado todos el threshold
		threshold_passed = check_threshold_passed(threshold);
		for(int v = 0; v < V; v++){
      if(over[v]) continue;
      cout << "probability vector for vertex " << v << ": ";
      for(int i = 0; i < degree[v] + 1; i++){
        cout << probs[v][i] << " ";	
      }
      cout << "\n";
		}
	}

	cout << endl;
	cout << endl;
	cout << "\n";
}
 
int main() {
	ifstream archivo;
	archivo.open("abc.txt");

	archivo >> V >> E;
	int e = E;
	//leemos las aristas y las agregamos a la lista de 
	//adyacencia
	while(e--){
		int t1, t2;
		archivo >> t1 >> t2;
		adj[t1].push_back(t2);
		adj[t2].push_back(t1);
	}
	//hallamos los grados de cada vertice
	find_degrees();
	//asignamos una probabilidad para cada color en cada vertice
	set_probs();	

  //inicializar over
  memset(over, false, sizeof over);

	//inicializamos el dynamic threshold para cada vertice
	for(int i = 0; i < V; i++){
		T[i] = degree[i] + 1;
	}
	//escogemos un color diferente para cada vertice
	for(int v = 0; v < V; v++){
		color[v] = v;
	}

  unsigned int t, t_;
 
  t = clock();
	//aplicamos el algoritmo
	double lim = 0.8;
	torkestani(lim);
  t_ = clock();
 
  double time = (double(t_ - t)/CLOCKS_PER_SEC);
  cout << "Execution Time: " << time << endl;
  archivo.close();

  //contamos cuantos colores usamos
	bool used[V];
	memset(used, false, sizeof used);
	int cnt = 0;
  for(int i = 0; i < V; i++){
		for(int j = 0; j < (degree[i] + 1); j++){
			if((probs[i][j] > lim) && !used[j]){
				used[j] = true;
				cnt++;
			}
		}
  }
	cout << "El grafo fue coloreado con " << cnt << " colores" << endl;
}
