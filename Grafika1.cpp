// Graf

#include <windows.h>
#include <iostream>
#include <math.h>
#include<time.h>
#include <gl/gl.h>
#include <gl/glut.h>

using namespace std;

typedef float point2[2];
float startSize = 243;
int startLevel = 4;
float noise = 1.5;
int color = 100;

void kwadrat(point2 p1, point2 p2, int level, bool flag) {
	float size = p2[0] - p1[0];
	float squareNoise = (noise * 1.0 / 1000) * startSize;//wartość przesunięć

	int displacement = rand() % 4;//wybór kierunku przesunięcia
	switch (displacement) {
	case 0:
		p1[0] += squareNoise;
		p1[1] += squareNoise;
		p2[0] += squareNoise;
		p2[1] += squareNoise;
		break;
	case 1:
		p1[0] += squareNoise;
		p1[1] -= squareNoise;
		p2[0] += squareNoise;
		p2[1] -= squareNoise;
		break;
	case 2:
		p1[0] -= squareNoise;
		p1[1] -= squareNoise;
		p2[0] -= squareNoise;
		p2[1] -= squareNoise;
		break;
	case 3:
		p1[0] -= squareNoise;
		p1[1] += squareNoise;
		p2[0] -= squareNoise;
		p2[1] += squareNoise;
		break;
	}

	if (flag == true) {//sprawdzenie czy to środek kwadratu ostatniej rekurencji

		glColor3f(0.0f, 0.0f, 0.0f);//malowanie na czarno
		glRectf(p1[0], p1[1], p2[0], p2[1]);
		glFlush();
		return;
	}

	if (level == 0) {  //sprawdzenie czy to ostatnia rekurencja
		glBegin(GL_POLYGON);//rozpoczęcie rysowania kwadratu

		if (color != 0) {
			glColor3f((rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100);//losowanie koloru 
			glVertex2f(p1[0], p1[1]);//rysowanie wierzchołka kwadratu

			glColor3f((rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100);
			glVertex2f(p1[0], p2[1]);

			glColor3f((rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100);
			glVertex2f(p2[0], p2[1]);

			glColor3f((rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100, (rand() % color) * 1.0 / 100);
			glVertex2f(p2[0], p1[1]);
		}
		else {
			glColor3f(1.0f, 1.0f, 1.0f);//biały przy color=0
			glVertex2f(p1[0], p1[1]);
			glVertex2f(p1[0], p2[1]);
			glVertex2f(p2[0], p2[1]);
			glVertex2f(p2[0], p1[1]);
		}


		glEnd();
		glFlush();
		return;
	}


	for (int i = 0; i < 3; i++) {//podział kwadratu na 9 mniejszych
		for (int j = 0; j < 3; j++) {
			point2 tp1, tp2;
			tp1[0] = p1[0] + (j)*size / 3;
			tp1[1] = p1[1] - (i)*size / 3;
			tp2[0] = tp1[0] + size / 3;
			tp2[1] = tp1[1] - size / 3;
			if (i == 1 && j == 1) {
				kwadrat(tp1, tp2, level - 1, true);//srodkowy kwadrat do usunięcia
			}
			else {
				kwadrat(tp1, tp2, level - 1, false);
			}



		}
	}
}


void RenderScene()

{
	glClear(GL_COLOR_BUFFER_BIT);
	point2 p1, p2;
	p1[0] = -startSize / 2;
	p1[1] = startSize / 2;
	p2[0] = startSize / 2;
	p2[1] = -startSize / 2;
	kwadrat(p1, p2, startLevel, false);
	glFlush();


}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania



void MyInit(void)

{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Kolor okna wnętrza okna - ustawiono na szary

}

/*************************************************************************************/

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna
	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// określenie okna obserwatora.
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-200.0, 200.0, -200.0 / AspectRatio, 200.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-200.0 * AspectRatio, 200.0 * AspectRatio, -200.0, 200.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych     

	glLoadIdentity();

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



void main(void)
{
	srand(time(NULL));
	cout << "dlugosc boku (preferowane 243), poziom rekurencji, perturbacje(0-1.5), kolor(0(brak koloru)-100(maksymalny kolor))" << endl;
	cin >> startSize;
	cin >> startLevel;
	cin >> noise;
	cin >> color;


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyświetlania
	// GLUT_SINGLE - pojedynczy bufor wyświetlania
	// GLUT_RGBA - model kolorów RGB
	glutCreateWindow("Dywan Sierpińskiego");
	// Utworzenie okna i określenie treści napisu w nagłówku okna
	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
	// zmiany rozmiaru okna
	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie 
	// inicjalizacje konieczneprzed przystąpieniem do renderowania
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/