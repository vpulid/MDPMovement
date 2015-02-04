#include <math.h>
#include <vector>



struct Cell
{

public:
	
	int m_id;
	double Q[4];
	double R;
	double V;
	bool terminal;
	bool blocked;
	Cell *North;
	Cell *East;
	Cell *South;
	Cell *West;


	
	Cell(int id, double r) {
		m_id=id;
		V=0;
		terminal = false;
		blocked = false;
		Q[0]=0;
		Q[1]=0;
		Q[2]=0;
		Q[3]=0;
		R = r;
		
	}
		

	void setAsTerminal(double r) {
		terminal = true;
		R = r;
	}

	void setAsBlocked() {
		blocked = true;
		R = 0;
	}
	void setOrientation (Cell* N, Cell* E, Cell* S, Cell* W) {
		North = N;
		East = E;
		South = S;
		West = W;
	}

	/*void iterateQ() {
		

	}*/
	
};
