
//  Created by Dewan Choudhury.

#include <GLUT/GLUT.h>
#include <iostream>

GLfloat pos[] = {2,4,5,1};
GLfloat groundColor[] = {0.3,0.3,0.3,1.0}, bodyColor[] = {0.0,0.3,0.0,1.0}, wheelColor[]={1.0,0.0,0.0,1.0};
GLfloat doorColor[] = {0,0,0,1.0}, spec[] = {1,1,1,1.0} ;
GLfloat spikeColor[] = {1.0,0.0,0.0,1.0}, amb[] = {0.3,0.3,0.3,1.0};
GLfloat front_amb_diff[] = {0.7,0.5,0.1,1.0};
GLfloat back_amb_diff[] = {0.4,0.7,0.1,1.0};
GLfloat spe[] = {0.25,0.25,0.25,1.0};
GLfloat theta =0,legAngle = 0, dt = 0.5, axes[3][3]={{1,0,0},{0,1,0},{0,0,1}};
int axis =0;
double distance = 0, dx = 0.006;
double playerZ = 0,dz=0;
GLfloat collisionX, collisionY, collisionZ,colAngle;
GLfloat colX, colY, colZ, colA;
bool gameOver = false;


//--------------Shapes-----------//
void drawScooter(){
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_AMBIENT, doorColor);
    glTranslated(-0.08, -0.5, 0.01);
    glRotated(120, 1, 1, 1);
    
    GLUquadricObj * quadObj;
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluCylinder(quadObj, 0.04, 0.04, 0.2, 250, 250);//cylinder
    glPopMatrix();

}

void drawLegs(){
    glTranslated(0.78, -0.45, 2.5);
    glPushMatrix();
    glLineWidth(5);
    glTranslated(-0.02, -0.50, 0.04);
    glRotated(120, 1, 1, 1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.15, 0, 0);
    glEnd();
    glTranslated(0.0, 0, 0.07);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.15, 0, 0);
    glEnd();
    glPopMatrix();
    
}
void drawRunner(){
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_AMBIENT, bodyColor);
    glTranslated(0.78, -0.45, 2.5);
    glutSolidSphere(0.08, 60, 60);
    glPushMatrix();
    glLineWidth(5);
    glTranslated(0.0, -0.20, 0.04);
    glRotated(120, 1, 1, 1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.15, 0, 0);
    glEnd();
    glTranslated(-0.1, -0.15, 0);
    glRotated(35, 1, 1, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.15, 0, 0);
    glEnd();
    glTranslated(0.0, 0.0, 0.16);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.15, 0, 0);
    glEnd();
    glPopMatrix();
    
    glTranslated(-0.04, -0.35, 0.05);
    glBegin(GL_POLYGON);//flat surface
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.25, 0);
    glVertex3f(0.10, 0.25, 0);
    glVertex3f(0.10, 0, 0);
    glEnd();
    glPopMatrix();
    
}


void drawDoor(){
    
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_AMBIENT, doorColor);
    glTranslated(0.65, -0.85, 0.0);
    glLineWidth(4.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.95, 0);
    glVertex3f(0.35, 0.95, 0);
    glVertex3f(0.35, 0, 0);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glVertex3f(0.35, 0, 0);
    glVertex3f(0.35/2, 0.20, 0);
    glVertex3f(0.35/2, 0.75, 0);
    glVertex3f(0.35, 0.95, 0);
    glEnd();
    
    glPopMatrix();
}

void drawSpikes(){
    glPushMatrix();
    glTranslated(0.45, -0.75, 1.0);
    glRotated(120, 1, 1, 1);
    glutSolidCone(0.25, 0.25, 80, 80);//cone
    glPopMatrix();
}

void drawGround(){
    glPushMatrix();
    glTranslated(0, -4.2, 0);
    glutSolidCube(5.8);
    glPopMatrix();
}

void drawCarBody(){
    glPushMatrix();
    glTranslated(-0.30, -0.75, 1.0);
    glRotated(120, 1, 1, 1);
    GLUquadricObj * quadObj;
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluCylinder(quadObj, 0.35, 0.35, 0.75, 250, 250);
    glPopMatrix();
}

void drawWheels(){
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_AMBIENT, wheelColor);
    glTranslated(-0.18, -0.95, 1.50);
    glutSolidSphere(0.10, 60, 60);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.29, -0.95, 1.50);
    glutSolidSphere(0.10, 60, 60);
    glPopMatrix();
}
//--------------Shapes-----------//


//--------------Logic & Setup-----//

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawDoor();
    drawGround();
    
    glPushMatrix();
    glTranslated(distance, 0, 0);
    drawCarBody();
    drawWheels();
    drawSpikes();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0, playerZ);
    glPushMatrix();
    glTranslated(colX, colY, colZ);
    glRotated(colA, 1, 1, 0);
    drawRunner();
    glPopMatrix();
    glTranslated(legAngle, 0, 0);
    
    drawLegs();
    
    glRotated(colAngle, 1, 1, 1);
    glTranslated(collisionX, collisionY, collisionZ);
    drawScooter();
    glPopMatrix();
    glutSwapBuffers();
}

void idle(){
    distance+=dx;
    if(distance>2){
        distance=-2.5;
    }
    playerZ-=dz;
    if(playerZ<-2.30){
        dz = 0;
        playerZ=0.30;
    }
    if((distance>0.50 && distance<0.75)&&(playerZ>-1.50 && playerZ<-0.5)){
        dz=0;
        gameOver = true;
        collisionX=0.20;
        collisionY = -0.45;
        collisionZ = -0.20;
        colAngle = 50;
        
        colX = 0.20;
        colY=-0.65;
        colZ = 0.20;
        colA = 5;
        
    }
    glutPostRedisplay();
}
void reset(){
    collisionX=0;
    collisionY = 0;
    collisionZ = 0;
    colAngle = 0;
    
    colX = 0;
    colY=0;
    colZ = 0;
    colA = 0;
    gameOver = false;
    playerZ = 0.25;
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'd':
            if((dx<=0.016) && !gameOver){
                dx+=0.01;
            }
            break;
            
        case 'a':
            if(!gameOver){
            dz=0.008;
            }
            break;
            
        case 's':
            if(!gameOver){
            dz=0.0;
            }
            break;
            
        case 'r':
            if(gameOver){
                reset();
            }
    }
    glutPostRedisplay();
}


int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Cross the road");
    std::cout<<"Hello there!"<<std::endl;
    std::cout<<"Try to get to the door without getting hit by that...thing!"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Press 'a' to start crossing."<<std::endl;
    std::cout<<"Press 's' to stop in place."<<std::endl;
    std::cout<<"Press 'd' to increase the car's speed."<<std::endl;
    std::cout<<"Press 'r' to reset."<<std::endl;
    glClearColor(0.5, 0.5, 0.6, 0.0);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 2, 8);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -5);
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
