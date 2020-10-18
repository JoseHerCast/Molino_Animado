//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
#include "Main.h"

float transZ = -5.0f;
float transY = -4.0f;
float transX = 0.0f;
float angleY = 0.0f;
float anglez = 0.0f;
int screenW = 0.0;
int screenH = 0.0;
GLfloat Blanco[3] = { 1.0, 1.0, 1.0 },
		Cafe[3] = { 0.94,0.45,0.07 },
		Gris[3] = { 0.53,0.5,0.48 };

void ochopuntos_cilindro(GLfloat color[], int Xc, int Zc, int x, int z) {
	int i, j;
	float aux1, aux2;
	int sim[8][2] = { {x,z},{x,-z},{-x,z},{-x,-z},{z,x},{z,-x},{-z,x},{-z,-x} };//Arreglo de puntos de simetría
	//imprimir simetrías (Se dibujan los puntos simetricos deplazados
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 2; j++) {
			if (j == 0) {
				aux1 = sim[i][j] + Xc;
			}
			else {
				aux2 = sim[i][j] + Zc;
			}
		}
		//Relleno
		glBegin(GL_LINE_STRIP);//lineas del centro al perimetro
		glColor3fv(color);//Color
		glVertex3f(Xc, 3.5, Zc);
		glVertex3f(aux1 + Xc, 3.5, aux2 + Zc);
		glVertex3f(aux1 + Xc, -3.5, aux2 + Zc);
		glVertex3f(Xc, -3.5, Zc);
		glEnd();

	}
}

void Cilindro(GLfloat color[], int Xc, int Zc, int r) {
	int i, j, pk, xk, zk, a, b;
	float aux1, aux2;
	ochopuntos_cilindro(color, Xc, Zc, 0, r);
	pk = 1 - r;
	//Hacemos que el punto de partida sea (xk,yk)=(0,r)
	xk = 0;
	zk = r;
	//El ciclo while siguiente calculará cada punto del primer octante, y a su vez las 8 simetrías de cada uno
	while (zk > xk) {
		if (pk < 0) {
			pk = pk + 2 * xk + 3;
			xk++;
			ochopuntos_cilindro(color, Xc, Zc, xk, zk);//Sustituir por el dibujo del punto en OpenGL				
		}
		else {
			pk = pk + 2 * (xk - zk) + 5;
			xk++;
			zk--;
			ochopuntos_cilindro(color, Xc, Zc, xk, zk);//Sustituir por el dibujo del punto en OpenGL
		}
	}
}

void Soporte_aspas() {
	glColor3fv(Gris);
	glutSolidSphere(1,100,100);
}

void Aspas() {
	GLfloat vertice[6][3] = {
			{-0.5 ,-0.433, 0.125},    //Coordenadas Vértice 0 V0
			{0.5,-0.433, 0.125},    //Coordenadas Vértice 1 V1
			{0.0,0.433, 0.125},    //Coordenadas Vértice 2 V2
			{-0.5 ,-0.433, -0.125},    //Coordenadas Vértice 3 V3
			{0.5 ,-0.433, -0.125},    //Coordenadas Vértice 4 V4
			{0.0,0.433, -0.125}    //Coordenadas Vértice 5 V5
	};

	glColor3fv(Cafe);
	glBegin(GL_TRIANGLES);//Front
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_QUADS);//Right
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_QUADS);//Left
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_TRIANGLES);//Back
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glEnd();

	glBegin(GL_QUADS);//Bottom
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[3]);
	glEnd();

}

void Eje_molino() {
	
	glScalef(0.01, 1, 0.01);
	Cilindro(Blanco, 0, 0, 500);
}

void Base_molino() {
	GLfloat vertice[8][3] = {
				{-1.0 ,-1.5, 0.5},    //Coordenadas Vértice 0 V0
				{1.0,-1.5, 0.5},    //Coordenadas Vértice 1 V1
				{0.5 ,1.5, 0.5},    //Coordenadas Vértice 2 V2
				{-0.5 ,1.5, 0.5},    //Coordenadas Vértice 3 V3
				{-1.0 ,-1.5, -0.5},    //Coordenadas Vértice 4 V4
				{1.0 ,-1.5, -0.5},    //Coordenadas Vértice 5 V5
				{0.5 ,1.5, -0.5},    //Coordenadas Vértice 6 V6
				{-0.5 ,1.5, -.5},    //Coordenadas Vértice 7 V7
	};

	glColor3fv(Gris);
	glBegin(GL_POLYGON);	//Front		
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

}

void Dibuja_Molino() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(angleY, 0, 1.0f, 0);
	glTranslatef(transX, transY, transZ);
	glTranslatef(0, 4.5, 0);
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0, -3.5, 0.0);
			glScalef(2, 0.66, 2);
			Base_molino();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 2.75, 0);
			glRotatef(anglez,0.0,0.0,1.0);
			glPushMatrix();
				glScalef(0.5, 0.5, 0.5);
				Soporte_aspas();
			glPopMatrix();
			//Aspa1
			glPushMatrix();
				glTranslatef(0.0, -0.5, 0.625);
				Aspas();
			glPopMatrix();
			//Aspa2
			glPushMatrix();
				glTranslatef(-0.5, 0.0, 0.625);
				glRotatef(-90, 0.0, 0.0, 1.0);
				Aspas();
			glPopMatrix();
			//Aspa3
			glPushMatrix();
				glTranslatef(0.0, 0.5, 0.625);
				glRotatef(180, 0.0, 0.0, 1.0);
				Aspas();
			glPopMatrix();
			//Aspa4
			glPushMatrix();
				glTranslatef(0.5, 0.0, 0.625);
				glRotatef(90, 0.0, 0.0, 1.0);
				Aspas();
			glPopMatrix();
		glPopMatrix();
	glScalef(0.1, 0.71, 0.1);
	Eje_molino();
	glPopMatrix();

}

void Rotacion() {//Actualiza el valor de la rotación
	anglez += 0.5;
}

void onIdle() {//Llama a la función que actualiza el valor de la rotación y redibuja
	Rotacion();
	glutPostRedisplay();
}

void InitGL(void)     // Inicializamos parametros
{

	//glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	//glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	//glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void)   // Creamos la funcion donde se dibuja
{
	Dibuja_Molino();
	onIdle();
	glutSwapBuffers();
  // Swap The Buffers
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'a':
		case 'A':
			angleY += 0.5;
			break;
		case 'd':
		case 'D':
			angleY -= 0.5;
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
		break;        
		default:        // Cualquier otra
		break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		transZ -= 0.3f;
		break;
    case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		transZ += 0.3f;
		break;
	case GLUT_KEY_LEFT:
		transX -= 0.3f;
		break;
	case GLUT_KEY_RIGHT:
		transX += 0.3f;
		break;
    default:
      break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  //glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  screenW = glutGet(GLUT_SCREEN_WIDTH);
  screenH = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Molino"); // Nombre de la Ventana
  printf("Resolution H: %i \n", screenW);
  printf("Resolution V: %i \n", screenH);
  printf("Rotacion en Y con teclas A y D.\n");
  printf("Movimiento en eje X y Z con felchas de direccion\n");
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutMainLoop        ( );          // 

  return 0;
}



