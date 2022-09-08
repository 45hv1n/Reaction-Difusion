#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>

void close_welcome(unsigned char k,int x,int y);
void window2();
void mouse(int button,int state ,int x,int y);
void mouseclicked(int button,int state ,int x,int y);
void keys(unsigned char k,int x,int y);
void mouse_second_window(int button,int state,int x,int y);
void init2();
void drawstring(int x,int y,char a[]);
void display();
void display1();

int win2,win1,x,y;
int cir_x=0,cir_y=0;

int wsize=400;

//float color[400*400*3];
GLfloat color[400][400][3];


float da=1.0,db=0.5,t=1.0;
float f,k;

struct pixel{
float a;
float b;
}pix[400][400],next[400][400];

//Initializing the pixels values or states[A or B]
void init_pixels(){
	for(y=0;y<wsize;y++){
		for(x=0;x<wsize;x++){
			pix[y][x].a=1.0;
			pix[y][x].b=0.0;
		}
	}
}

//Initializing the second solution B
void init_second_solution(){
	for(y=100;y<150;y++){
		for(x=100;x<150;x++){
			pix[y][x].b=1.0;
		}
	}
	for(y=100;y<150;y++){
		for(x=250;x<300;x++){
			pix[y][x].b=1.0;
		}
	}
	for(y=250;y<300;y++){
		for(x=100;x<150;x++){
			pix[y][x].b=1.0;
		}
	}
	
	for(y=250;y<300;y++){
		for(x=250;x<300;x++){
			pix[y][x].b=1.0;
		}
	}
	
}

//Copying the Pixels
void copy_pixels(){
	for(y=0;y<wsize;y++){
		for(x=0;x<wsize;x++){
			pix[y][x].a = next[y][x].a;
			pix[y][x].b = next[y][x].b;
		}
	}
}

//Drawing the pixels on to the screen
void setpixel(){
	float c,temp_a,temp_b;
	for(y=0;y<wsize;y++){
		for(x=0;x<wsize;x++){
		temp_a= pix[y][x].a;
		temp_b= pix[y][x].b;
		c= temp_a - temp_b;
		//pos= ((y+1)*wsize*3)-((wsize - x )*3);
		/*if(c<0.5){

				//BLUISH
				color[y][x][0]=(GLfloat)(0.5-c);
				color[y][x][1]=(GLfloat)(0.9-c);
				color[y][x][2]=(GLfloat)(1-c);



				// DARK BLUISH
				color[y][x][0]=(GLfloat)(0.5-c);
				color[y][x][1]=(GLfloat)(0.5-c);
				color[y][x][2]=(GLfloat)(1-c);


				//REDDISH
				color[y][x][0]=(GLfloat)(1.5-c);
				color[y][x][1]=(GLfloat)(0.9-c);
				color[y][x][2]=(GLfloat)(0.9-c);


		}
		else{
				color[y][x][0]=(GLfloat)0;
				color[y][x][1]=(GLfloat)0;
				color[y][x][2]=(GLfloat)0;
		}
		*/
		/*
		color[y][x][0]=(GLfloat)1-c;
	        color[y][x][1]=(GLfloat)0.387-c;
		color[y][x][2]=(GLfloat)1.25-c;
		*/
		color[y][x][0]=(GLfloat)(0.5-c);
		color[y][x][1]=(GLfloat)(0.5-c);
		color[y][x][2]=(GLfloat)(1-c);

		}
	}
	glDrawPixels(wsize,wsize,GL_RGB,GL_FLOAT,color);
}

//Lapcian function inorder to get th values of the morse's neighbours
float laplacian(char ch,int i,int j){
	float sum=0.0;

	if(ch=='a'){

		sum+=pix[i][j].a *(-1);

		sum+=pix[i-1][j].a * 0.2;
		sum+=pix[i+1][j].a * 0.2;
		sum+=pix[i][j-1].a * 0.2;
		sum+=pix[i][j+1].a * 0.2;

		sum+=pix[i-1][j-1].a * 0.05;
		sum+=pix[i-1][j+1].a * 0.05;
		sum+=pix[i+1][j+1].a * 0.05;
		sum+=pix[i+1][j-1].a * 0.05;

	}
	else if(ch=='b'){

		sum+=pix[i][j].b *(-1);

		sum+=pix[i-1][j].b * 0.2;
		sum+=pix[i+1][j].b * 0.2;
		sum+=pix[i][j-1].b * 0.2;
		sum+=pix[i][j+1].b * 0.2;

		sum+=pix[i-1][j-1].b * 0.05;
		sum+=pix[i-1][j+1].b * 0.05;
		sum+=pix[i+1][j+1].b * 0.05;
		sum+=pix[i+1][j-1].b * 0.05;
	}

	return sum;
}

//Actual reaction Function
void reaction(){
	for(y=1;y<wsize-1;y++){
		for(x=1;x<wsize-1;x++){

			float A= pix[y][x].a;
			float B= pix[y][x].b;
			next[y][x].a = A + (da * laplacian('a',y,x)) - (A * B * B) + (f*(1-A)) * t;
			next[y][x].b = B + (db * laplacian('b',y,x)) + (A * B * B) - ((k+f) * B) * t;

		}
	}

	copy_pixels();
	glutPostRedisplay();
}


void init(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1800,0,950);
}

void mouse_second_window(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        int coord_y= wsize-y;
        for(int i=coord_y-20;i<coord_y+20;i++){
            for(int j=x-20;j<x+20;j++){
                pix[j][i].b=1;
                printf("%d,%d \t",j,i);
            }
            printf("\n");
        }
        printf("clicked:%d %d\n",x,y);
    }
    glutPostRedisplay();
}


void mouse(int button,int state,int x, int y){
	//0,0 coordinates in the top left corner
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		//FIRST OPTION CORAL REEF
		if(x>=160 && x<=690 && y>=160 && y<=260 ){
			f=0.055;
			k=0.062;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Coral Reef");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutMouseFunc(mouse_second_window);
			glutIdleFunc(reaction);
		}
		//SECOND OPTION CHAOS AND HOLES
		if(x>=160 && x<=690 && y>=320 && y<=420 ){
			f=0.034;
			k=0.056;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Chaos and holes");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//THIRD OPTION DEfault
		if(x>=160 && x<=690 && y>=470 && y<=570 ){
			f=0.037;
			k=0.06;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("DEFAULT");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//FORTH OPTION MAZE
		if(x>=160 && x<=690 && y>=630 && y<=730 ){
			f=0.029;
			k=0.057;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Maze");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//FIFTH OPTION HOLES
		if(x>=160 && x<=690 && y>=790 && y<=890 ){
			f=0.039;
			k=0.058;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Holes");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}

		//SIXTH OPTION MITOSIS
		if(x>=900 && x<=1430 && y>=160 && y<=260 ){
			f=0.0367;
			k=0.0637;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("MITOSIS");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//SEVENTH OPTION CHAOS AND HOLES
		if(x>=900 && x<=1430 && y>=320 && y<=420 ){
			f=0.0367;
			k=0.0627;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Pattern 7");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//EIGHTH OPTION DEfault
		if(x>=900 && x<=1430 && y>=470 && y<=570 ){
			f=0.018;
			k=0.051;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Pattern 8");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//NINTH OPTION MAZE
		if(x>=900 && x<=1430 && y>=630 && y<=730 ){
			f=0.0367;
			k=0.061;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Pattern 9");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
		//TENTH OPTION HOLES
		if(x>=900 && x<=1430 && y>=790 && y<=890 ){
			f=0.062;
			k=0.061;
			glutDestroyWindow(glutGetWindow());
			printf("clicked %d %d \n",x,y);
			glutInitWindowSize(wsize,wsize);
			win2 = glutCreateWindow("Pattern 10");
			glutSetWindow(win2);
			glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
			glutDisplayFunc(window2);
			init();
			init_pixels();
			init_second_solution();
			glutIdleFunc(reaction);
		}
	}
	glutPostRedisplay();
	printf("coord:%d %d\n",x,y);

}

void close_menu(unsigned char k,int x,int y){
	if(k=='q' || k=='Q'){
		glutDestroyWindow(glutGetWindow());
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);	

	glColor3f(0,0,1);

	    //BORDER DESIGN
	glBegin(GL_POLYGON);
		glVertex2i(1600,950);
		glVertex2i(1600,0);
		glVertex2i(1620,0);
		glVertex2i(1620,950);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2i(1640,950);
		glVertex2i(1640,0);
		glVertex2i(1660,0);
		glVertex2i(1660,950);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2i(0,910);
		glVertex2i(1800,910);
		glVertex2i(1800,930);
		glVertex2i(0,930);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2i(0,860);
		glVertex2i(1800,860);
		glVertex2i(1800,880);
		glVertex2i(0,880);
	glEnd();

	//FIRST MENU ITEM
	glBegin(GL_POLYGON);
	glVertex2i(150,800);
	glVertex2i(150,700);
	glVertex2i(650,700);
	glVertex2i(650,800);
	glEnd();
	glColor3f(1,1,1);
	char m1[]= "Corel Reef";
	glRasterPos2i(360,740);
	for(int i=0;i<strlen(m1);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m1[i]);
	}

	//SECOND MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(150,550);
	glVertex2i(150,650);
	glVertex2i(650,650);
	glVertex2i(650,550);
	glEnd();
	glColor3f(1,1,1);
	char m2[]= "Chaos And Holes";
	glRasterPos2i(320,590);
	for(int i=0;i<strlen(m2);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m2[i]);
	}

	//THIRD MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(150,400);
	glVertex2i(150,500);
	glVertex2i(650,500);
	glVertex2i(650,400);
	glEnd();
	glColor3f(1,1,1);
	char m3[]= "Default";
	glRasterPos2i(360,440);
	for(int i=0;i<strlen(m3);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m3[i]);
	}

	//Forth MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(150,250);
	glVertex2i(150,350);
	glVertex2i(650,350);
	glVertex2i(650,250);
	glEnd();
	glColor3f(1,1,1);
	char m4[]= "Maze";
	glRasterPos2i(360,290);
	for(int i=0;i<strlen(m4);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m4[i]);
	}

	//Fifth MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(150,100);
	glVertex2i(150,200);
	glVertex2i(650,200);
	glVertex2i(650,100);
	glEnd();
	glColor3f(1,1,1);
	char m5[]= "Holes";
	glRasterPos2i(360,140);
	for(int i=0;i<strlen(m5);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m5[i]);
	}


	    //SIXTH MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(850,800);
	glVertex2i(850,700);
	glVertex2i(1350,700);
	glVertex2i(1350,800);
	glEnd();
	glColor3f(1,1,1);
	char m6[]= "Mitosis";
	glRasterPos2i(1050,750);
	for(int i=0;i<strlen(m6);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m6[i]);
	}

	//SEVENTH MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(850,550);
	glVertex2i(850,650);
	glVertex2i(1350,650);
	glVertex2i(1350,550);
	glEnd();
	glColor3f(1,1,1);
	char m7[]= "Custom 7";
	glRasterPos2i(1050,600);
	for(int i=0;i<strlen(m7);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m7[i]);
	}

	    //EIGHT MENU ITEM
	    glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(850,400);
	glVertex2i(850,500);
	glVertex2i(1350,500);
	glVertex2i(1350,400);
	glEnd();
	glColor3f(1,1,1);
	char m8[]= "Custom 8";
	glRasterPos2i(1050,440);
	for(int i=0;i<strlen(m8);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m8[i]);
	}

	//NINTH MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(850,250);
	glVertex2i(850,350);
	glVertex2i(1350,350);
	glVertex2i(1350,250);
	glEnd();
	glColor3f(1,1,1);
	char m9[]= "Custom 9";
	glRasterPos2i(1050,290);
	for(int i=0;i<strlen(m9);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m9[i]);
	}

	//Tenth MENU ITEM
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(850,100);
	glVertex2i(850,200);
	glVertex2i(1350,200);
	glVertex2i(1350,100);
	glEnd();
	glColor3f(1,1,1);
	char m10[]= "Custom 10";
	glRasterPos2i(1050,140);
	for(int i=0;i<strlen(m10);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,m10[i]);
	}

	glutKeyboardFunc(close_menu);
	glutMouseFunc(mouse);
	glutSwapBuffers();
}

void keys(unsigned char k,int x,int y){
	if(k == 'x' && win2==glutGetWindow()){
		glutDestroyWindow(glutGetWindow());
		glutIdleFunc(NULL);
		printf("id %d \n",glutGetWindow());
		glutInitWindowSize(1800,950);
		win1=glutCreateWindow("Menu");
		glutSetWindow(win1);
		printf("id %d \n",glutGetWindow());
		glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
		glutDisplayFunc(display);
		init();
		if(k=='q' || k=='Q'){
		    exit(0);
		}
	}
	glutPostRedisplay();
}

void window2(){
	glClear(GL_COLOR_BUFFER_BIT);
	setpixel();
	glutSwapBuffers();
	glutKeyboardFunc(keys);
}

void init3(){
	glClearColor(1.0,1.0,1.0,1.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1800,0,900);
}

void drawstring(int x,int y,char a[]){

	glRasterPos2i(x,y);
	for(int i=0;i<strlen(a);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,a[i]);
	}
}

void close_welcome(unsigned char k,int x,int y){
	if(k){
		glutDestroyWindow(glutGetWindow());
		glutIdleFunc(NULL);
		//printf("id %d \n",glutGetWindow());

		glutInitWindowSize(1800,950);
		win1=glutCreateWindow("Menu");
		glutSetWindow(win1);
		//printf("id %d \n",glutGetWindow());
		glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
		glutDisplayFunc(display);
		init();
		glutPostRedisplay();
	}

}

void display1(){
	glClear(GL_COLOR_BUFFER_BIT);
	init3();

		glColor3f(0.901,0.709,0.541);
	drawstring(570,855,"SAHYADRI COLLAGE OF ENGINEERING AND MANAGEMENT");

	drawstring(575,800,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");

		glColor3f(0.847,0.901,0.541);
	drawstring(800,700,"A MINI PROJECT ON");

	drawstring(785,650 ,"REACTION DIFFUSION");

	glColor3f(0.478,0.329,0.968);
	drawstring(480,550,"BY:");

	glColor3f(1.0,1.0,1.0);
	drawstring(580,500,"KAILASHNATH N C                                         4SF19CS079");

	drawstring(580,450,"ASHVIN ALVA VINOD                                     4SF19CS038");

	glColor3f(0.478,0.329,0.968);
	drawstring(480,375,"UNDER THE GUIDANCE OF:");

	glColor3f(1.0,1.0,1.0);
	drawstring(580,320 ,"Ms.SHIJI ABRAHAM");


	glColor3f(0.152,0.811,0.764);
	drawstring(780,250,"PRESS ENTER TO START!!");

	drawstring(500,180,"CLICK ON THE PATTERNS INORDER TO VIEW THE PATTERNS");
	drawstring(500,130,"PRESS 'X' TO RETURN TO THE MENU");

	glutKeyboardFunc(close_welcome);
	glutSwapBuffers();
}


int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(1800,950);
	glutCreateWindow("Welcome");
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	//glutMouseFunc(mousemouse);
	glutDisplayFunc(display1);

	glutMainLoop();
	return 0;
}
