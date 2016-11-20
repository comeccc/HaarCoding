

#include "include.h"

using namespace std;



float** haarMatrice( unsigned char** imageInitiale,  int ligneMax, int colonneMax, int nbrePassage)
{
	
	
	if ( colonneMax >= 2 && ligneMax >= 2 )
	{
		if ( !estPuissanceDe2(colonneMax) || ! estPuissanceDe2(ligneMax) )
		{
			return NULL;
		}
	}
	
	else
	{
		return NULL;
	}
	
	
	
	int dimMinimum = min(ligneMax, colonneMax);
	
	if( nbrePassage == -1 || nbrePassage > (int)( (float) ( (float) log10(dimMinimum) / (float)log10(2) ) ))
	{
		
		nbrePassage = (int)( (float) ( (float) log10(dimMinimum) / (float)log10(2) ) );
	}

	
	
	float** imageTransformee = new float* [ligneMax];
	
	for(int i=0; i<ligneMax; ++i)
	{
		imageTransformee[i] = new float [colonneMax];
	}
	
	
	copieMatrice( imageInitiale, imageTransformee, ligneMax, colonneMax);
	
	
	
	
	   
	int dimMax = max(ligneMax, colonneMax);
	
	   
	
	float* vecteurTemporaire = new float [dimMax];
	float* vecteurExtrait = new float [dimMax];
	
	   
	
	for(int k=0; k<nbrePassage; ++k)
	{
		   
		int dimColonne = colonneMax / (int) pow( 2.0, k);
		int dimLigne	= ligneMax / (int) pow(2.0, k);
		
		   
		
		for(int i=0; i<dimLigne; ++i)
		{
			   
			extraireVecteurDeMatrice(imageTransformee, vecteurExtrait, V_LIGNE, dimColonne, dimLigne, dimColonne, i);
			   
			haarVecteur(vecteurExtrait, vecteurTemporaire, dimColonne);
			   
			remplaceVecteurMatrice(imageTransformee, vecteurTemporaire, V_LIGNE, dimColonne, dimLigne, dimColonne, i);
		}
		
		   
		
		for(int j=0; j<dimColonne; ++j)
		{
			   
			extraireVecteurDeMatrice(imageTransformee, vecteurExtrait, V_COLONNE, dimLigne, dimLigne, dimColonne, j);
			   
			haarVecteur(vecteurExtrait, vecteurTemporaire, dimLigne);		
			   
			remplaceVecteurMatrice(imageTransformee, vecteurTemporaire, V_COLONNE, dimLigne, dimLigne, dimColonne, j);
		}	
		

	}
	
	   
	delete[] vecteurTemporaire;
	delete[] vecteurExtrait;
	
	   
	return imageTransformee;
	
}

unsigned char** reconstructionMatrice(float** matriceHaar,  int ligneMax, int colonneMax, int nbrePassage)
{
	
	
	if ( colonneMax >= 2 && ligneMax >= 2 )
	{
		if ( !estPuissanceDe2(colonneMax) || ! estPuissanceDe2(ligneMax) )
		{
			return NULL;
		}
	}
	
	else
	{
		return NULL;
	}
	
	
	
	int dimMinimum = min(ligneMax, colonneMax);
	const int nbrePassageMaximum = (int)( (float) ( (float) log10(dimMinimum) / (float)log10(2) ) );
	
	if( nbrePassage == -1 || nbrePassage > nbrePassageMaximum)
	{
		
		nbrePassage = nbrePassageMaximum;
	}
	
	
	unsigned char** imageReconstruite = new unsigned char* [ligneMax];
	
	for(int i=0; i<ligneMax; ++i)
	{
		imageReconstruite[i] = new unsigned char [colonneMax];
	}
	
	
	float** matriceTravail = new float* [ligneMax];
	
	for(int i=0; i<ligneMax; ++i)
	{
		matriceTravail[i] = new float [colonneMax];
	}
	
	
	copieMatrice( matriceHaar, matriceTravail, ligneMax, colonneMax);
	
	   
	int dimMax = max(ligneMax, colonneMax);
	
	   
	
	float* vecteurTemporaire = new float [dimMax];
	float* vecteurExtrait = new float [dimMax];
	
	   
	
	for(int k=0; k<nbrePassage; ++k)
	{
		   
		int dimColonne = ( colonneMax / (int) pow( 2.0, nbrePassage - k  - 1) );
		int dimLigne	= ( ligneMax / (int) pow( 2.0, nbrePassage - k  - 1) );
		
		   
		
		for(int i=0; i<dimLigne; ++i)
		{
			   
			extraireVecteurDeMatrice(matriceTravail, vecteurExtrait, V_LIGNE, dimColonne, dimLigne, dimColonne, i);
			   
			reconstructionVecteur(vecteurExtrait, vecteurTemporaire, dimColonne);
			   
			remplaceVecteurMatrice(matriceTravail, vecteurTemporaire, V_LIGNE, dimColonne, dimLigne, dimColonne, i);
		}
		
		   
		
		for(int j=0; j<dimColonne; ++j)
		{
			   
			extraireVecteurDeMatrice(matriceTravail, vecteurExtrait, V_COLONNE, dimLigne, dimLigne, dimColonne, j);
			   
			reconstructionVecteur(vecteurExtrait, vecteurTemporaire, dimLigne);		
			   
			remplaceVecteurMatrice(matriceTravail, vecteurTemporaire, V_COLONNE, dimLigne, dimLigne, dimColonne, j);
		}	
		

	}
	
	   
	delete[] vecteurTemporaire;
	delete[] vecteurExtrait;

	   
	
	copieMatrice( matriceTravail, imageReconstruite, ligneMax, colonneMax);

	return imageReconstruite;

}



inline bool haarVecteur(float* vecteurInitial, float* vecteurFinal, int taille)
{
	if (taille <= 0 || ! estPuissanceDe2(taille))
		return 0;
		
	for(int i=0; i< (taille/2); ++i)
	{
		   
		float moyenne =  (vecteurInitial[ 2*i ] + vecteurInitial[ 2*i +1 ]) /2;
		float difference =  (vecteurInitial[ 2*i ] - vecteurInitial[ 2*i +1 ]) /2;
		
		   
		vecteurFinal[i] = moyenne;
		vecteurFinal[taille/2 + i] = difference;
	}
	
	return 1;
	
	
	
}

inline bool reconstructionVecteur( float* vecteurInitial, float* vecteurFinal, int taille)
{
	if (taille <= 0 || ! estPuissanceDe2(taille))
		return 0;	
		
	for(int i=0; i< (taille/2); ++i)
	{
		   
		float valeur_a =  (vecteurInitial[ i ] + vecteurInitial[ taille/2 + i ]);     
		float valeur_b =  (vecteurInitial[ i ] - vecteurInitial[ taille/2 + i  ]) ;    
		
		   
		vecteurFinal[ 2*i ] = valeur_a;
		vecteurFinal[ 2*i + 1 ] = valeur_b;
	}
	
	return 1;
}




bool estPuissanceDe2(int n)
{
	
	
	if( n == 0)
		return 0;
	
	if( (n & (n -1)) == 0 )
		return 1;
	
	else
		return 0;
	
}

inline void copieMatrice(float** matriceInit, float** matriceVide, int L, int C)
{
	for(int i=0; i<L; ++i)
	{
		for(int j=0; j<C; ++j)
		{
			matriceVide[i][j] = matriceInit[i][j];
		}
	}
}

inline void copieMatrice(unsigned char** matriceInit, float** matriceVide, int L, int C)
{
	for(int i=0; i<L; ++i)
	{
		for(int j=0; j<C; ++j)
		{
			matriceVide[i][j] = (float) (unsigned int) matriceInit[i][j];
		}
	}
}

void copieMatrice(float** matriceInit, unsigned char**matriceVide, int L, int C)
{
	for(int i=0; i<L; ++i)
	{
		for(int j=0; j<C; ++j)
		{
			matriceVide[i][j] = (unsigned char) (unsigned int) matriceInit[i][j];
		}
	}
}

inline void remplaceVecteurMatrice(float** matrice, float* vecteur, typeVecteur type, int tailleVecteur, int L, int C, int position)
{
	if( type == V_LIGNE)
	{
		   
		if( tailleVecteur > C || position > L || position < 0 )
			return;
			
		for(int i=0; i<tailleVecteur; ++i)
		{
			matrice[position][i] = vecteur[i];
		}
	}
	
	else if (type == V_COLONNE)
	{
		if( tailleVecteur > L || position > C || position < 0)
			return;
			
		for(int i=0; i<tailleVecteur; ++i)
		{
			matrice[i][position] = vecteur[i];
		}
	}
	
	else
		return;
	
	
}

inline void extraireVecteurDeMatrice(float** matrice, float* vecteur, typeVecteur type, int tailleVecteur, int L, int C, int position)
{
	if( type == V_LIGNE)
	{
		   
		if( tailleVecteur > C || position > L || position < 0 )
			return;
			
		for(int i=0; i<tailleVecteur; ++i)
		{
			vecteur[i] = matrice[position][i];
		}
	}
	
	else if (type == V_COLONNE)
	{
		if( tailleVecteur > L || position > C || position < 0)
			return;
			
		for(int i=0; i<tailleVecteur; ++i)
		{
			vecteur[i] = matrice[i][position];
		}
	}
	
	else
		return;
}



float appliquerSeuil(float** imageHaar, float valeurMaxToleree, int ligneMax, int colonneMax)
{
	float tauxCompression = ligneMax*colonneMax;
	
	for(int i=0; i<ligneMax; ++i)
	{
		for(int j=0; j<colonneMax; ++j)
		{
			if( i==0 && j==0)
				continue;
				
			else
			{
				if( abs( imageHaar[i][j] ) < valeurMaxToleree )
				{
					imageHaar[i][j] = 0.0;
					tauxCompression--;
				}
			}
		}
	}
	
	tauxCompression = tauxCompression / (ligneMax*colonneMax);
	return tauxCompression;
}

float determinerValeurMax(float** imageHaar, int ligneMax, int colonneMax)
{
	
	float max = 0;
	
	for(int i=0; i<ligneMax; ++i)
	{
		for(int j=0; j<colonneMax; ++j)
        {
			if( i!= 0 && j != 0)
			{
                if( abs(imageHaar[i][j]) > max )
                    max = abs(imageHaar[i][j]);    
			}
		}
	}
	
	return max;
	
}


unsigned char** allouerMatriceChar(int width, int height)
{
    unsigned char** matrice = new unsigned char* [width];
    for(int i=0; i<width; ++i)
    {
            matrice[i] = new unsigned char [height];
    }
    return matrice;
}

bool desallouerMatrice(unsigned char** matrice, int width)
{
    for(int i=0; i<width; ++i)
    {
            delete[] matrice[i];
    }
    delete[] matrice;
    return 0;
}

bool desallouerMatrice(float** matrice, int width)
{
    for(int i=0; i<width; ++i)
    {
            delete[] matrice[i];
    }
    delete[] matrice;
    return 0;
}

void redresserErreurMatrice(float** matriceFloat, unsigned char** matriceChar, int ligneMoy, int colonneMoy, int ligneMax, int colonneMax)
{
    for(int i=0; i<ligneMax; ++i)
    {
        for(int j=0; j<colonneMax; ++j)
        {
               
            if (i<ligneMoy && j<colonneMoy)
                matriceChar[i][j] = (unsigned char) matriceFloat[i][j];
               
            else
                matriceChar[i][j] = (unsigned char) (matriceFloat[i][j] + 127.5);
        }
    }
}

void toGrayscale(QImage & image)
{
    Q_ASSERT(!image.isNull());
    Q_ASSERT(image.width() > 0 && image.height() > 0);

    QRgb col;
    int gray;
    int width = image.width();
    int height = image.height();
    QImage alpha = image.alphaChannel();    
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    image.setAlphaChannel(alpha);
}



