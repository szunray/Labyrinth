//============================================================================
// Name        : Maze.cpp
// Author      : Dillon Belton
// Version     :
// Copyright   : ain't got no copyright, steal away
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <gl/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
int material=1;
float xpos=-31, ypos=-3,zpos=-34;
float xrot=5.00003, yrot=216, angle=0.0;
float sizex=2.0,sizez=2.0;

int index=0;

struct wall{
	int x1,z1,x2,z2;
	int wallsizez,wallsizex;
	int wallx,wallz;
};

struct wall list[20];


//Test Targets
float positionz[10];
float positionx[10];
void cubepositions (void) { //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
    positionz[i] = rand()%5 + 5;
    positionx[i] = rand()%5 + 5;
    }
}

void cube (void) {
    for (int i=0;i<10;i++)
    {
    glPushMatrix();
    glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] *
10); //translate the cube
    glutSolidCube(2); //draw the cube
    glPopMatrix();
    }
}

void init(){
	cubepositions();
}

void camera(){
	 glRotatef(xrot,1.0,0.0,0.0);//rotate the camera on the  x-axis (left and right)
	 glRotatef(yrot,0.0,1.0,0.0); //rotate the camera on the y-axis (up and down)
	 glTranslatef(xpos,ypos,zpos);// //translate the screen to the position of the camera
}
void drawFloor(){
	GLfloat mat_diffuseRed[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuseRed);
	glBegin(GL_POLYGON);
			glNormal3f(0,1,0);
			glVertex3f(-70,0,-70);
			glVertex3f(-70,0,70);
			glVertex3f(70,0,70);
			glVertex3f(70,0,-70);
			glEnd();
}
void drawWall(int x1,int z1,int x2,int z2){
	GLfloat mat_diffuseBlue[]={0.0f,0.0f,1.0f,0.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_diffuseBlue);
	glBegin(GL_POLYGON);
		//glNormal3f(0,1,0);
		glVertex3f(x1,0,z1);
		glVertex3f(x1,10,z1);
		glVertex3f(x2,10,z2);
		glVertex3f(x2,0,z2);
		glEnd();
}
struct wall listWall(int x1,int z1,int x2,int z2){
struct wall temp;
temp.x1=x1;
temp.x2=x2;
temp.z1=z1;
temp.z2=z2;
temp.wallsizex=abs(x1-x2);
temp.wallsizez=abs(z1-z2);
temp.wallx=temp.x1;
temp.wallz=temp.z1;
drawWall(x1,z1,x2, z2);
return temp;
}
void drawMaze(){
	list[0]=listWall(0,0,30,0);//from bottom of image


	list[1]=listWall(0,0,0,70);// Vertical Border on left.


	list[2]=listWall(70,0,70,70);//Vertical Border on Right


	list[3]=listWall(40,0,70,0);//Horizontal lines first

	list[4]=listWall(10,10,40,10);
	list[5]=listWall(50,10,70,10);
	list[6]=listWall(0,20,30,20);
	list[7]=listWall(40,20,60,20);
	list[8]=listWall(20,30,50,30);
	list[9]=listWall(0,40,10,40);
	list[10]=listWall(40,40,60,40);
	list[11]=listWall(10,50,40,50);
	list[12]=listWall(50,50,60,50);
	list[13]=listWall(0,60,10,60);
	list[14]=listWall(30,60,50,60);

	// Vertical shtuff
	list[15]=listWall(40,0,40,20);
	list[16]=listWall(30,20,30,30);
	list[17]=listWall(60,30,60,50);
	list[18]=listWall(10,30,10,40);
	list[19]=listWall(20,30,20,40);
	list[20]=listWall(30,40,30,50);
	list[21]=listWall(50,40,50,60);
	list[22]=listWall(20,50,20,70);
	list[23]=listWall(60,60,60,70);
	drawWall(0,70,30,70);// Top border

}
int CheckCollision(struct wall temp){


	int camPos=xpos*-1;
	int camPosz=zpos*-1;
	bool collisionX= (camPos+sizex>=temp.wallx)&&(temp.wallx+temp.wallsizex>=camPos);
	bool collisionZ=camPosz+sizez>=temp.wallz&&temp.wallz+temp.wallsizez>=camPosz;



	if((collisionX&&collisionZ)){
		if (temp.wallsizex==0){
			cout<<"Collision with Zwall"<<endl;
			return 1;
		}
	else if(temp.wallsizez==0)
		cout<<"Collision with Xwall"<<endl;
			return 2;
	}
	return 0;
}


int checkAll(){
int typeCollision=0;
for(int x=0;x<23;x++){
	typeCollision=CheckCollision(list[x]);
	if (CheckCollision(list[x])>0)
		break;
}
return typeCollision;

}
void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_FLAT); //set the shader to smooth shader

}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void keyboard(unsigned char key, int x,int y){
	if (key=='q')
	    {
		cout<<"xrot: "<<xrot<< "zrot: "<<yrot<<"xpos "<< xpos<< "zpos"<<zpos<<endl;
	    xrot += 1;
	    if (xrot >360)
	    	xrot -= 360;
	    }
	if(key=='z')
	{
		xrot-=1;
		if(xrot>360)
			xrot-=360;
	}
	if(key=='s')
	{
		float xrotrad,yrotrad;
		yrotrad=(yrot/180*3.141592654f);
		xrotrad=(xrot/180*3.141592654f);
		 if(checkAll()==0 || checkAll()==2)
		xpos+=float(sin(yrotrad));
		 if(checkAll()==0 || checkAll()==1)
		zpos-=float(cos(yrotrad));
		//ypos-=float(sin(xrotrad));
	}
	if (key=='w')
	    {
	    float xrotrad, yrotrad;

	    //cout<<-xpos<<"\t z:"<<-zpos<<endl;//THEN check X or Z (not implemented)
	    yrotrad = (yrot / 180 * 3.141592654f);
	    xrotrad = (xrot / 180 * 3.141592654f);

	    if(checkAll()==0 || checkAll()==2)
	    xpos -= float(sin(yrotrad));

	    if(checkAll()==0 || checkAll()==1)
	    zpos += float(cos(yrotrad)) ;
	    //ypos += float(sin(xrotrad));
	    }

	    if (key=='d')
	    {
	    yrot += 4;
	    if (yrot >360) yrot -= 360;
	    }

	    if (key=='a')
	    {
	    yrot -= 4;
	    if (yrot < -360)yrot += 360;
	    }
}

void displaySolid(void) {
	//set properties of the surface material
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen toblack
	    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	    glLoadIdentity();
	    camera();
	    enable();
	    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	    drawFloor();
	    drawMaze();

	    glutSwapBuffers(); //swap the buffers
	    angle++; //increase the angle
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("shaded example - 3D scene");
	init();
	//glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displaySolid);
	glutIdleFunc(displaySolid);
	glutReshapeFunc(reshape);
	//glEnable(GL_LIGHTING); // enable the light source
	//glEnable(GL_LIGHT0);
	//glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST); // for hidden surface removal
	//glEnable(GL_NORMALIZE); // normalize vectors for proper shading
	//glClearColor(0.1f, 0.1f, 0.1f, 0.0f);  // background is light gray
	//glViewport(0, 0, 640, 480);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Draw only lines no fill

	glutMainLoop();
	return 0;

}
