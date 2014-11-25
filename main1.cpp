#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <time.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cstdlib>
#include <unistd.h>
#include "expectimax.h"

using namespace std;

/*Define some colors*/
static const float quartz[]={0.847059,0.847059,0.74902};
static const float white[] = {1,1,1};
static const float wheat[]={0.83,0.847059,0.74902};
static const float yellow[]={0,0,0}; //2048
static const float red[]={1,0,0};  //1024
static const float yell_orng[]={1,0.9,0.2};  //512
static const float orng_yell[]={1,0.9,0.5};  //256
static const float orng[]={1,1,0.6};       //128
static const float orange[]={1,0.6,0};  //64
static const float orn[]={1,0.7,1};          //32
static const float orangish[]={0.8,0.5,0};  //16
static const float ong[]={1,0.7,0.5};           //8
static const float wheatish[]={0.9,0.8,0.6};           //4
static const float  grey[]={0.9,0.9,0.8};          //2

vector<float> yellow1(yellow, yellow+sizeof(yellow)/sizeof(yellow[0]));
vector<float> red1(red, red+sizeof(yellow)/sizeof(yellow[0]));
vector<float> yell_orng1(yell_orng, yell_orng+sizeof(yellow)/sizeof(yellow[0]));
vector<float> orng_yell1(orng_yell, orng_yell+sizeof(yellow)/sizeof(yellow[0]));
vector<float> orng1(orng, orng+sizeof(yellow)/sizeof(yellow[0]));
vector<float> orange1(orange, orange+sizeof(yellow)/sizeof(yellow[0]));
vector<float> orn1(orn, orn+sizeof(yellow)/sizeof(yellow[0]));
vector<float> orangish1(orangish, orangish+sizeof(yellow)/sizeof(yellow[0]));
vector<float> ong1(ong, ong+sizeof(yellow)/sizeof(yellow[0]));
vector<float> wheatish1(wheatish, wheatish+sizeof(yellow)/sizeof(yellow[0]));
vector<float> grey1(grey, grey+sizeof(yellow)/sizeof(yellow[0]));
vector<float> white1(white, white+sizeof(yellow)/sizeof(yellow[0]));
vector<float> wheat1(wheat, wheat+sizeof(yellow)/sizeof(yellow[0]));

/* Global variables */
char title[] = "ai-solver-2048";
map<int, vector<float> > colormap;
bool gameSolved = false;
int temp, direction;
Board br;
int rnum;
void printBoard();
void generateRNum();


/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
   glShadeModel(GL_SMOOTH);              // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void drawCube( int c )
{
  glColor3f(colormap[c][0],colormap[c][1],colormap[c][2]);
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)

  glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)

  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)

  glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)

  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)

  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
  glVertex3f( -1.0f, 1.0f, 1.0f);   // Top Left Of The Quad (Right)
  glVertex3f( -1.0f,-1.0f, 1.0f);   // Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
}


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

  while(hasMove(br))
  {
    for(int i=0; i<16; ++i)
    {
      if(br.cells[i]==2048)
      {
        gameSolved = true;
        break;
      }
    }

    if(gameSolved)
    {
      break;
    }

    direction = findBestDirection( br.cells[0], br.cells[1], br.cells[2], br.cells[3],
                                   br.cells[4], br.cells[5], br.cells[6], br.cells[7],
                                   br.cells[8], br.cells[9], br.cells[10],br.cells[11],
                                   br.cells[12],br.cells[13],br.cells[14],br.cells[15],
                                   3 );

    cout<<"direction=="<<direction<<"\n";
    move(br, direction);
    generateRNum();

    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                 // Reset the model-view matrix
    glScalef(2.0f, 2.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      drawCube(-1);
    glEnd();  // End of drawing color-cube

    glScalef(0.20f, 0.2f,1.0f);
    glPushMatrix();
    glTranslatef(-3.6f,3.6f,0.0f); //0,0

    glBegin(GL_QUADS);
     drawCube(br.cells[0]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,3.6f,0.0f); //0,1
    glBegin(GL_QUADS);
     drawCube(br.cells[1]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f,3.6f,0.0f); //0,2
    glBegin(GL_QUADS);
     drawCube(br.cells[2]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6f,3.6f,0.0f); //0,3
    glBegin(GL_QUADS);
     drawCube(br.cells[3]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.6f,1.2f,0.0f); //1,0
    glBegin(GL_QUADS);
     drawCube(br.cells[4]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,1.2f,0.0f); //1,1
    glBegin(GL_QUADS);
     drawCube(br.cells[5]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f,1.2f,0.0f); //1,2
    glBegin(GL_QUADS);
     drawCube(br.cells[6]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6f,1.2f,0.0f); //1,3
    glBegin(GL_QUADS);
     drawCube(br.cells[7]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.6f,-1.2f,0.0f); //2,0
    glBegin(GL_QUADS);
     drawCube(br.cells[8]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,-1.2f,0.0f); //2,1
    glBegin(GL_QUADS);
     drawCube(br.cells[9]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f,-1.2f,0.0f); //2,2
    glBegin(GL_QUADS);
     drawCube(br.cells[10]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6f,-1.2f,0.0f); //2,3
    glBegin(GL_QUADS);
     drawCube(br.cells[11]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.6f,-3.6f,0.0f); //3,0
    glBegin(GL_QUADS);
     drawCube(br.cells[12]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,-3.6f,0.0f); //3,1
    glBegin(GL_QUADS);
     drawCube(br.cells[13]);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f,-3.6f,0.0f); //3,2
    glBegin(GL_QUADS);
     drawCube(br.cells[14]);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.6f,-3.6f,0.0f); //3,3
    glBegin(GL_QUADS);
     drawCube(br.cells[15]);
    glEnd();
    glPopMatrix();


    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)\

    printBoard();

    for(int i=0; i<10000; i++); //wait .....
  }
}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{
  // Compute aspect ratio of the new window
  if (height == 0)
    height = 1;                // To prevent divide by 0
  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  // Set the viewport to cover the new window
  glViewport(0, 0, width, height);

  // Set the aspect ratio of the clipping volume to match the viewport
  glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
  glLoadIdentity();             // Reset
  // Enable perspective projection with fovy, aspect, zNear and zFar
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


void mouseFunction( int button, int state, int x, int y )
{
  if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) //if left button is clicked, zoomin
  {

  }
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
  //intitalize
  colormap[2048] = yellow1;
  colormap[1024] = red1;
  colormap[512] = yell_orng1;
  colormap[256] = orng_yell1;
  colormap[128] = orng1;
  colormap[64] = orange1;
  colormap[32] = orn1;
  colormap[16] = orangish1;
  colormap[8] = ong1;
  colormap[4] = wheatish1;
  colormap[2] = grey1;
  colormap[0] = white1;
  colormap[-1] = wheat1;

  srand(time(NULL));
  rnum = rand()%16;
  temp =rnum;
  br.cells[rnum] = 2;
  generateRNum();
  printBoard();                     //display the board in std output

  glutInit(&argc, argv);            // Initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
  glutInitWindowSize(640, 480);     // Set the window's initial width & height
  glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner
  glutCreateWindow(title);          // Create window with the given title
  glutDisplayFunc(display);         // Register callback handler for window re-paint event
  glutReshapeFunc(reshape);         // Register callback handler for window re-size event
  //glutMouseFunc(mouseFunction);
  initGL();                         // Our own OpenGL initialization
  glutMainLoop();                   // Enter the infinite event-processing loop
  return 0;
}


void printBoard()
{
  cout<<"\n";
  for(int i=0; i<16; ++i)
  {
    cout<<br.cells[i]<<" ";

    if(i%4==3)
    {
      cout<<"\n";
    }
  }
  cout<<"\n";
}


/*generate a random number*/
void generateRNum()
{
  rnum = rand()%16;

  while(br.cells[rnum]!=0)
  {
    rnum = rand()%16;
  }

  br.cells[rnum] = 2;
}



