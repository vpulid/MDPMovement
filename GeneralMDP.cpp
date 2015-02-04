# include <stdlib.h>
# include <iostream>
# include <fstream>
# include <vector>
# include <new>
# include <iomanip>
# include <math.h>
# include "Cell.h"

using namespace std;

bool isRepeated(vector <int> list, int num) {

	bool r = false;
	for(int i = 0; i < list.size(); i++) {
		if(list[i] == num) { r = true; }
			
	}

	return r;
}


int main () {


	int m = 3, n = 4, g1= 0, g2=3, f1 = 1, f2 = 3, n1=1, n2=1, iteration = 1000;
	double lambda = .9;
	//Initialize Cells
	vector<Cell*> grid;
	Cell * newCell = (Cell*) ::operator new (sizeof(Cell*)*m*n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			newCell = new Cell(i*n+j,-5);
			grid.push_back(newCell);
		}
	}

	//Set Terminal States
	grid[g1*n+g2]->setAsTerminal(100);
	grid[f1*n+f2]->setAsTerminal(-100);

	//Set Blocking States
	grid[n1*n+n2]->setAsBlocked();
	
	//Connect Cells
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

		


			//Edges
			if( i==0 && (j!=0 || j!=n) ) { grid[i*n+j]->setOrientation(NULL,grid[i*n+(j+1)],grid[(i+1)*n+j],grid[i*n+(j-1)]); } //North Edge
			if( i==m && (j!=0 || j!=n) ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],grid[i*n+(j+1)],NULL,grid[i*n+(j-1)]); } //South Edge
			if( j==0 && (i!=0 || i!=m) ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],grid[i*n+(j+1)],grid[(i+1)*n+j],NULL); } //West Edge
			if( j==n && (i!=0 || i!=m) ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],NULL,grid[(i+1)*n+j],grid[i*n+(j-1)]); } //East Edge
			//Corners
			if( i==0 && j==0 ) { grid[i*n+j]->setOrientation(NULL,grid[i*n+(j+1)],grid[(i+1)*n+j],NULL); }	//Upper Left
			if( i==m && j==0 ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],grid[i*n+(j+1)],NULL,NULL); }	//Lower Left
			if( i==0 && j==n ) { grid[i*n+j]->setOrientation(NULL,NULL,grid[(i+1)*n+j],grid[i*n+(j-1)]); }	//Upper Right
			if( i==m && j==n ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],NULL,NULL,grid[i*n+(j-1)]); }	//Lower Right
			//Interior
			if( (i>0 && i<m) && (j>0 && j<n) ) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],grid[i*n+(j+1)],grid[(i+1)*n+j],grid[i*n+(j-1)]); }

			//if( i !=0 || i!= m || j != 0 || j!= n) { grid[i*n+j]->setOrientation(grid[(i-1)*n+j],grid[i*n+(j+1)],grid[(i+1)*n+j],grid[i*n+(j-1)]); }
		}
		
	}


	//Checked grid[0]
	//if( grid[1*n+1]->blocked ){
	//	cout<<grid[1*n+1]->blocked<<endl;
	//}
	for (int i = 0; i < m; i++ ) {
		for (int j = 0; j < n; j++) {
			grid[i*n+j]->V = grid[i*n+j]->R;
		}
	}


	//INITIALIZE GRID


	
	for (int k = 0; k < iteration; k++) {
		for (int i = 0; i < m; i++ ) {
			for (int j = 0; j < n; j++) {

				for(int r = 0; r <4; r++) {
					grid[i*n+j]->Q[r] = 0;

				}
				//TERMINAL ACTION
				if (  grid[i*n+j]->terminal ) {
					for (int r = 0; r < 4; r++ ) {
						grid[i*n+j]->V = grid[i*n+j]->R;
					}
				} else {

					//NORTH ACTION
					//P(North)
					if( grid[i*n+j]->North != 0 ) {
						if ( !grid[i*n+j]->North->blocked ) {
							grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .8*(grid[i*n+j]->North)->V;
						} else { grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .8*(grid[i*n+j])->V; }
				
					} else {
						grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .8*(grid[i*n+j])->V;
					}
					//P(East)
					if ( grid[i*n+j]->East != 0 ) {
						if ( !grid[i*n+j]->East->blocked ) {
							grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j]->East)->V;
						} else { grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j])->V;
					}
					//P(South)
					if ( grid[i*n+j]->South != 0 ) {  						//IF East direction is not NULL (or is out of bounds) THEN (1), ELSE (2) AND
						if ( !grid[i*n+j]->South->blocked ) {					//IF East direction is not Blocked THEN 
							grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + 0*(grid[i*n+j]->South)->V;		//(1)
						} else { grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + 0*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + 0*(grid[i*n+j])->V;				//(2)
					}
					//P(West)
					if (grid[i*n+j]->West != 0) {
						if ( !grid[i*n+j]->West->blocked ) {
							grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j]->West)->V;
						} else { grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[0] = grid[i*n+j]->Q[0] + .1*(grid[i*n+j])->V;
					}

			
					//EAST ACTION
					//P(North)
					if( grid[i*n+j]->North != 0 ) {
						if ( !grid[i*n+j]->North->blocked ) {
							grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j]->North)->V;
						} else { grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j])->V; } 	//NO MOVE
				
					} else {
						grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j])->V;		//NO MOVE
					}
					//P(East)
					if ( grid[i*n+j]->East != 0 ) {
						if ( !grid[i*n+j]->East->blocked ) {
							grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .8*(grid[i*n+j]->East)->V;
						} else { grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .8*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .8*(grid[i*n+j])->V;
					}
					//P(South)
					if ( grid[i*n+j]->South != 0 ) {
						if ( !grid[i*n+j]->South->blocked ) {
							grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j]->South)->V;
						} else { grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + .1*(grid[i*n+j])->V;
					}
					//P(West)
					if (grid[i*n+j]->West != 0) {
						if ( !grid[i*n+j]->West->blocked ) {
							grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + 0*(grid[i*n+j]->West)->V;
						} else { grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + 0*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[1] = grid[i*n+j]->Q[1] + 0*(grid[i*n+j]->V);
					}


					//SOUTH ACTION
					//P(North)
					if( grid[i*n+j]->North != 0 ) {
						if ( !grid[i*n+j]->North->blocked ) {
							grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + 0*(grid[i*n+j]->North)->V;
						} else { grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + 0*(grid[i*n+j])->V; } 	//NO MOVE
				
					} else {
						grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + 0*(grid[i*n+j])->V;		//NO MOVE
					}
					//P(East)
					if ( grid[i*n+j]->East != 0 ) {
						if ( !grid[i*n+j]->East->blocked ) {
							grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .1*(grid[i*n+j]->East)->V;
						} else { grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .1*(grid[i*n+j])->V;
					}
					//P(South)
					if ( grid[i*n+j]->South != 0 ) {
						if ( !grid[i*n+j]->South->blocked ) {
							grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .8*(grid[i*n+j]->South)->V;
						} else { grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2]+ .8*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .8*(grid[i*n+j])->V;
					}
					//P(West)
					if (grid[i*n+j]->West != 0) {
						if ( !grid[i*n+j]->West->blocked ) {
							grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .1*(grid[i*n+j]->West)->V;
						} else { grid[i*n+j]->Q[2] = grid[i*n+j]->Q[2] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j])->V;
					}


					//WEST ACTION
					//P(North)
					if( grid[i*n+j]->North != 0 ) {
						if ( !grid[i*n+j]->North->blocked ) {
							grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j]->North)->V;
						} else { grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j])->V; } 	//NO MOVE
				
					} else {
						grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] +.1*(grid[i*n+j])->V;		//NO MOVE
					}
					//P(East)
					if ( grid[i*n+j]->East != 0 ) {
						if ( !grid[i*n+j]->East->blocked ) {
							grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + 0*(grid[i*n+j]->East)->V;
						} else { grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + 0*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + 0*(grid[i*n+j])->V;
					}
					//P(South)
					if ( grid[i*n+j]->South != 0 ) {
						if ( !grid[i*n+j]->South->blocked ) {
							grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j]->South)->V;
						} else { grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .1*(grid[i*n+j])->V;
					}
					//P(West)
					if (grid[i*n+j]->West != 0) {
						if ( !grid[i*n+j]->West->blocked ) {
							grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .8*(grid[i*n+j]->West)->V;
						} else { grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .8*(grid[i*n+j])->V; }
					} else {
						grid[i*n+j]->Q[3] = grid[i*n+j]->Q[3] + .8*(grid[i*n+j])->V;
					}
				
					for (int r=0; r < 4; r++) {
						grid[i*n+j]->Q[r] = lambda*grid[i*n+j]->Q[r]+grid[i*n+j]->R;
					}

			
				}
			

			
			}
		}
		double temp= -9999;
		for(int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (!grid[i*n+j]->terminal && !grid[i*n+j]->blocked){
					for( int r = 0; r < 4; r++) {
						if (grid[i*n+j]->V < grid[i*n+j]->Q[r]){
							grid[i*n+j]->V = grid[i*n+j]->Q[r];
						}
					}
				}
			}			
		}
	
		for(int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout<<grid[i*n+j]->V<<"\t\t";
			}
			cout<<endl<<endl;
		}
		cout<<k+1<<": "<<endl;
	}

	
	//cout<<grid[(g1+1)*n+g2-1]->East<<endl;
	//cout<<.8*grid[(g1+1)*n+g2-1]->North->R+.1*grid[g1*n+g2-1]->East->R+.1*grid[g1*n+g2-1]->R+grid[g1*n+g2-1]->R<<endl<<endl;
	//cout<<grid[g1*n+g2-1]->V<<endl;
	//cout<<grid[(g1+1)*n+(g2-1)]<<endl;


	return 0;
}
