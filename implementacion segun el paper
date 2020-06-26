#include <bits/stdc++.h>
 
using namespace std;
 
int V, E;
//lista de adyacencia
vector<int> adj[100];
//grado maximo hallado en el grafo
int max_degree = 0;
//vector de probabilidades para cada vertice
vector<double> probs[100];
//dynamic threshold para cada vertice
//guarda la cardinalidad minima de todos los 
//color localsets vistos hasta el momento
int T[100];
//color de cada vertice;
int color[100];
int degree[100];
bool vis[100];
double learning_rate = 0.1;
 
//distribucion de probabilidad uniforme
int randint(int first, int last) {
	random_device dev;
	default_random_engine eng(dev());
	uniform_int_distribution<int> dis(first, last);
	return dis(eng);
}
void penalize(int v, int co){
	if(probs[v][co] - learning_rate < 0.00) 
		return;
	for(int i = 0; i < V; i++){
    if(i == co){
      probs[v][i] = (1.0 - learning_rate) * probs[v][i]; 
    }
    else{
      probs[v][i] = (learning_rate / max_degree) + (1.0 - learning_rate) * probs[v][i];
    }
  }
}
 
void reward(int v, int co){
	if(probs[v][co] + learning_rate > 1.00) 
		return;
	for(int i = 0; i < V; i++){
    if(i == co){
      probs[v][i] = probs[v][i] + learning_rate * (1.0 - probs[v][i]);
    }
    else{
      probs[v][i] = (1.0 - learning_rate) * probs[v][i];
    }
  }
}
 
int find_max_degree(){
	int mx = -1;
	for(int i = 0; i < V; i++){
    degree[i] = adj[i].size();
		if(int(adj[i].size()) > mx){
			mx = adj[i].size();
		}
	}
	return mx;
}
 
void set_probs(){
	for(int i = 0; i < V; i++){
		probs[i].clear();
		for(int j = 0; j < degree[i] + 1; j++){
			probs[i].push_back( 1.0 / (max_degree + 1));
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
	cout << "compute :" << colors.size() << endl;
	return colors.size();
}
 
bool check_local_reward(int v, int co){
	for(int w : adj[v]){
		set<int> colors;
		colors.insert(co);
		for(int nb : adj[w]){
			colors.insert(color[nb]);
		}
		if(colors.size() > T[w]){
			return 0;
		}
	}
	return 1;
}
 
bool check_threshold_passed(double t){
	bool ret = true;
	for(int v = 0; v < V; v++){
		double mx = probs[v][0];
		for(int i = 1; i < degree[v] + 1; i++){
			if(probs[v][i] > mx){
				mx = probs[v][i];
			}
		}
		if(mx >= t){
			vis[v] = true;
		}
		else{
			ret = false;
		}
	}
	return ret;
}
 
void torkestani(double threshold){
	bool threshold_passed = false;
	while(!threshold_passed){
		cout << "array T: ";
		for(int i = 0; i < V; i++){
			cout << T[i] << " ";
		}
		cout << endl;
		for(int i = 0; i < V; i++)
			cout << color[i];
		for(int cell = 0; cell < V; cell++){
			cout << "visitados :";
			for(int i = 0; i < V; i++)
				cout << vis[i] << " ";
			cout << endl;
			if(vis[cell]) continue;
			int selected_color = randint(0, degree[cell]);
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
				cout << color_degree <<  "&" <<T[cell] << endl; 
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
	cin >> V >> E;
	int e = E;
	//leemos las aristas y las agregamos a la lista de 
	//adyacencia
	while(e--){
		int t1, t2;
		cin >> t1 >> t2;
		adj[t1].push_back(t2);
		adj[t2].push_back(t1);
	}
	//hallamos el grado maximo del grafo
	max_degree = find_max_degree();
	//asignamos una probabilidad para cada color en cada vertice
	set_probs();	
	//inicializamos el dynamic threshold para cada vertice
	for(int i = 0; i < V; i++){
		T[i] = max_degree + 1;
	}
	//escogemos un color al azar para cada vertice
	for(int v = 0; v < V; v++){
		color[v] = v;
	}
	memset(vis, false, sizeof vis);
	//aplicamos el algoritmo
	torkestani(0.95);
	cout << endl << endl << endl;
 
	for(int v = 0; v < V; v++){
		cout << "probability vector for vertex " << v << ": ";
		for(int i = 0; i < degree[v] + 1; i++){
			cout << probs[v][i] << " ";	
		}
		cout << "\n";
	}
}
