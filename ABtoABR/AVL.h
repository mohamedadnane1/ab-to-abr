class noeud {
	friend class AVL ; 
	int cle ;
	int N;
	int d;
	int h;
	noeud * fg; noeud * fd; noeud * pere ;
	public :
		noeud(int x) ;
		~noeud() ;
		void affiche() ; 
};


class AVL {

	noeud * r; 
	public :

	AVL(noeud* r) ; 
	AVL(char* filename, bool option);
	~AVL();
	
	noeud* root() ;
	void prefixe(noeud* x) ; 
	void prefixe();

	void insertion(int x) ; 
	void inserer_feuille(noeud * x, noeud *b);
	void inserer_racine(noeud * a, noeud *b);

	void rotationDroite(noeud *r);
	void rotationDroite();
	void rotationGauche(noeud *r);
	void rotationGauche();

	noeud* partition(noeud* x, int k);
	void partition( int k);
	
	int noeuds(noeud* x);
	int hauteur(noeud* x) ;
	void desequilibres(noeud* x);
	void equilibre(noeud* x);

	void hauteur();
	void nb_noeuds();
	void desequilibres();
	void equilibre();
	bool est_desiquilibre(noeud* x);
	
	};