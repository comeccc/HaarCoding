#ifndef TRAITEMENT_20402013_1030
#define	TRAITEMENT_20402013_1030

	float** haarMatrice( unsigned char** imageInitiale,  int ligneMax, int colonneMax, int nbrePassage);
	unsigned char** reconstructionMatrice(float** matriceTransformee,  int ligneMax, int colonneMax, int nbrePassage);
	
	inline bool haarVecteur(float* vecteurInitial, float* vecteurFinal, int taille);
	inline bool reconstructionVecteur( float* vecteurInitial, float* vecteurFinal, int taille);
	
  bool estPuissanceDe2(int n);
	
	inline void copieMatrice(unsigned char** matriceInit, float** matriceVide, int L, int C);
	inline void copieMatrice(float** matriceInit, float** matriceVide, int L, int C);
  void copieMatrice(float** matriceInit, unsigned char**matriceVide, int L, int C);
	
	enum typeVecteur 
	{
		V_LIGNE,
		V_COLONNE
	}; 
	
	inline void remplaceVecteurMatrice(float** matrice, float* vecteur, typeVecteur type, int tailleVecteur, int L, int C, int position);
	inline void extraireVecteurDeMatrice(float** matrice, float* vecteur, typeVecteur type, int tailleVecteur, int L, int C, int position);
	
	float appliquerSeuil(float** imageHaar, float valeurMaxToleree, int ligneMax, int colonneMax);
	float determinerValeurMax(float** imageHaar, int ligneMax, int colonneMax);


    unsigned char** allouerMatriceChar(int width, int height);
    bool desallouerMatrice(unsigned char** matrice, int width);
    bool desallouerMatrice(float** matrice, int width);
    void redresserErreurMatrice(float** matriceFloat, unsigned char** matriceChar, int ligneMoy, int colonneMoy, int ligneMax, int colonneMax);

    void toGrayscale(QImage & image);

#endif


