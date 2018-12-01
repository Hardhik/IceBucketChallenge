

/*
 * http://openglsamples.sourceforge.net/glutshapes.html
 * OpenGLSamples (openglsamples.sf.net) tutorials
 * VC++ users should create a Win32 Console project and link 
 * the program with glut32.lib, glu32.lib, opengl32.lib
 *
 * GLUT can be downloaded from http://www.xmission.com/~nate/glut.html
 * OpenGL is by default installed on your system.
 * For an installation of glut on windows for MS Visual Studio 2010 see: http://nafsadh.wordpress.com/2010/08/20/glut-in-ms-visual-studio-2010-msvs10/
 *
 *
 * main.cpp		
 *
 */

#include <stdio.h>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include "imageloader.h"

#define KEY_ESCAPE 27
#define BASE_HEIGHT 2 
#define BASE_RADIUS .5
#define HEAD_RADIUS .75/2
#define HAND_HEIGHT (2)/2
#define LEG_HEIGHT (2+0.4)/2
#define HANDLEG_RADIUS .25/2 
GLUquadricObj *p;
float angles[5]={0,60,-60,30,-30};

void drawMan();
//Makes the image into a texture, and returns the id of the texture

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;
glutWindow win;
float Rotation;


int counter=0;
int side=0;
int shiver;
int tu_meri=0;

/*MAN*/
void drawtrunk(){
	glRotatef(-90,1,0,0);
	gluQuadricDrawStyle(p, GLU_FILL);
	glColor3f(0.73,0.16,0.96); 
	gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);

}
void drawhead(){
	glTranslatef(0,0,HEAD_RADIUS);
	glColor3f(0.0,0.3,0.6);
	gluSphere(p,HEAD_RADIUS,20,20);
	glPushMatrix();
	glTranslatef(0,0,4*HEAD_RADIUS/5);
	glColor3f(1,1,0);
	gluCylinder (p, HEAD_RADIUS,HEAD_RADIUS/4,0.25,20, 20);
	glTranslatef(0,0,HEAD_RADIUS/5);
	gluSphere(p,0.25,20,20);
	glPopMatrix();


	glPushMatrix();//for nose

	glTranslatef(0,-(HEAD_RADIUS),0);
	glRotatef(90,1,0,0);
	glColor3f(0,1,1);
	gluCylinder (p, 0.1,0, 0.2, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.85,0.85,0.1);
	glTranslatef(HEAD_RADIUS/2,-HEAD_RADIUS/2,HEAD_RADIUS/2-0.1);
	gluSphere(p,0.12,20,20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.85,0.85,0.1);
	glTranslatef(-HEAD_RADIUS/2,-HEAD_RADIUS/2,HEAD_RADIUS/2-0.1);
	gluSphere(p,0.12,20,20);
	glPopMatrix();

}
void drawrightarm(){
	
	glTranslatef(-BASE_RADIUS-HANDLEG_RADIUS,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[1],1,0,0);
	glColor3f(0.0, 1.0, 0.0);                                  /*color*/
	gluSphere(p,HANDLEG_RADIUS,20,20);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
	glTranslatef(0,0,HAND_HEIGHT);
	glColor3f(0,0,1);
	gluSphere(p,HANDLEG_RADIUS+0.05,20,20);

}
void drawleftarm(){
	glTranslatef(BASE_RADIUS+HANDLEG_RADIUS,0,0);
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(180,1,0,0);
	glRotatef(angles[2],1,0,0);
	gluSphere(p,HANDLEG_RADIUS,20,20);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, HAND_HEIGHT, 20, 20);
	glTranslatef(0,0,HAND_HEIGHT);
	glColor3f(0,0,1);
	gluSphere(p,HANDLEG_RADIUS+0.05,20,20);

}
void drawrightleg(){
	glTranslatef(BASE_RADIUS/2,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[3],1,0,0);
	glColor3f(0,1,0);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
	glTranslatef(0,0,LEG_HEIGHT);
	glRotatef(-90,1,0,0);
	glColor3f(0,0,1);
	gluCylinder (p,0.1, 0.1, 0.3, 20, 20);
	glTranslatef(0,0,0.3);
	gluSphere(p,0.1,20,20);


}
void drawleftleg(){
	glTranslatef(-BASE_RADIUS/2,0,0);
	glRotatef(180,1,0,0);
	glRotatef(angles[4],1,0,0);
	glColor3f(0,1,0);
	gluCylinder (p,HANDLEG_RADIUS, HANDLEG_RADIUS, LEG_HEIGHT, 20, 20);
	glTranslatef(0,0,LEG_HEIGHT);
	glRotatef(-90,1,0,0);
	glColor3f(0,0,1);
	gluCylinder (p,0.1, 0.1, 0.3, 20, 20);
	glTranslatef(0,0,0.3);
	gluSphere(p,0.1,20,20);

}
/*MAN*/
#define num_ice 15
float ice_y[num_ice];
void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
	glLoadIdentity();
	gluLookAt( 10,3,0, 0,0,0, 0,1,0);					  // Define a viewing transformation
 p= gluNewQuadric();
	
	for (int i = 0; i < num_ice; ++i)
	{
		/* code */
	
		glPushMatrix();										  // Push the current matrix stack
			glColor3f(1,1,1);
			//glTranslatef(0,2,0);							  // Multiply the current matrix by a translation matrix
			glTranslatef(0, (i%( ((int)rand() )%3+1)) + (win.height/2-ice_y[i])/50,-3+i/2);							  // Multiply the current matrix by a translation matrix
			glRotatef(-Rotation,0,1,0);
			glRotatef((int)(rand()*10)%45,0,1,0);							  // Multiply the current matrix by a rotation matrix 
//			printf("%d\n",ice_y[0]);
	
			glutSolidCube(0.3); 
		glPopMatrix();										  // Pop the current matrix stack
	}
	

	/*			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation

					glEnable(GL_TEXTURE_GEN_T);
					//        glBindTexture(GL_TEXTURE_2D, theTexture[2]);
					glBindTexture(GL_TEXTURE_2D, _textureId);
					glutSolidCube(1.96);
					glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
					glDisable(GL_TEXTURE_GEN_T);
*/
	glPushMatrix();
	glTranslatef(0,3.5,-3);
	glRotatef(((counter)/3%5*5)*2+5,1,0,0);
	gluCylinder (p, HEAD_RADIUS,HEAD_RADIUS,1,20, 20);
	glPopMatrix();

	Rotation+=3;
	for(int i=0;i<num_ice;i++)
	{
		ice_y[i]+=7;
		ice_y[i] =(int)ice_y[i] % win.height;

	}
	drawMan();
	glutSwapBuffers();
}


void initialize () 
{
	for (int i = 0; i < num_ice; ++i)
	{
		ice_y[i]=i;
	}
	printf("%d\n",win.height );
    glMatrixMode(GL_PROJECTION);												// select projection matrix
    glViewport(0, 0, win.width, win.height);									// set the viewport
    glMatrixMode(GL_PROJECTION);												// set matrix mode
    glLoadIdentity();															// reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
	glClearColor(0.0, 0.0, 1.0, 1.0);

}


void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;      

    default:      
      break;
  }
}
void drawMan()
{
	//tu_meri=1;
	if(counter%15==0)
	{

		shiver= ~shiver;
		if(side%4==0)
			tu_meri=~tu_meri;
		side++;
		side%=40;
	}
	
	
		

	glRotatef(90,0,1,0);

	glPushMatrix();
	//glTranslatef(0,-2,0);
		drawtrunk();
		gluDisk(p,0,BASE_RADIUS,20,20);
		
		glPushMatrix();
		glTranslatef(0,0,BASE_HEIGHT);
		gluDisk(p,0,BASE_RADIUS,20,20);
		
		glPushMatrix();//head
		drawhead();
		glPopMatrix();
		
		glPushMatrix(); //right arm
		
		if(shiver)
		{
			glRotatef(90,0,0,1);
			glTranslatef(0,HAND_HEIGHT/2+0.5,0);
		}
		
		glRotatef(-180,1,0,0);
		drawrightarm();
		
		if(shiver)
			glRotatef(-90,0,0,1);
		
		glPopMatrix();
		

		glPushMatrix(); //left arm
	
//		glRotatef(45,1,0,0);		
		if(shiver)
		{
			glRotatef(90,0,0,1);
//			glTranslatef(0,HAND_HEIGHT/2+0.5,0);
		}

		drawleftarm();
		if(shiver)
			glRotatef(-90,0,0,1);
	
		
		glPopMatrix();
		
		glPopMatrix();
	if(tu_meri)		
	{
			glPushMatrix(); //right leg
			if(shiver)
			{
//				printf("if\n");
				glRotatef(-90,0,0,1);
				glTranslatef(0,-HAND_HEIGHT/2-0.5,0);
			}
			
			drawrightleg();
			if(shiver)
				glRotatef(-90,0,0,1);
			
			glPopMatrix();
			
			glPushMatrix(); //left leg
				
				if(shiver)
				{
					glRotatef(-90,0,1,0);
					glTranslatef(0,-HAND_HEIGHT/2-0.5,0);
				}
					
				drawleftleg();	
			if(shiver)
				glRotatef(-90,0,1,0);
			glPopMatrix();
	}
	else
	{
			glPushMatrix(); //right leg
			if(shiver)
			{
				glRotatef(90,0,0,1);
				glTranslatef(0,-HAND_HEIGHT/2-0.5,0);
			}
			
			drawrightleg();
			if(shiver)
				glRotatef(-90,0,0,1);
			
			glPopMatrix();
			
			glPushMatrix(); //left leg
				
				if(shiver)
				{
					glRotatef(90,0,1,0);
					glTranslatef(0,-HAND_HEIGHT/2-0.5,0);
				}
					
				drawleftleg();	
			if(shiver)
				glRotatef(-90,0,1,0);
			glPopMatrix();
		}


	glPopMatrix();
counter=(counter+1)%100000;
}
int main(int argc, char **argv) 
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "OpenGL/GLUT Window.";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

		Image* image = loadBMP("meme.bmp");
		_textureId = loadTexture(image);
		delete image;


	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc( display );									// register Idle Function
    glutKeyboardFunc( keyboard );								// register Keyboard Handler
	initialize();
	//PlaySound("tu_meri.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	glutMainLoop();												// run GLUT mainloop
	return 0;
}

