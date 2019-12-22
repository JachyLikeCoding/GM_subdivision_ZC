#include "display.h"
#include "processor.h"

deque<Face*> fqueue;
deque<Edge*> equeue;
deque<Vertex*> vqueue;
int width, height, level, mode;  // show face or line : 0->face; 1->line
bool in;
int angleX = 0, angleY = 0;
Object obj;
SubdivisionProcessor processor;

void zoom(bool in) {
    if (in) {
        // zoom in
        for (auto v : vqueue) {
            v->coord /= 2;
        }
    } else {
        for (auto v : vqueue) {
            v->coord *= 2;
        }
    }
}

void init(int argc, char* argv[]) {
    width = WinWidth;
    height = WinHeight;
    level = 1;
    mode = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Catmull-Clark Subdivision surface (by Chizhang)");
    initLights();
}

void initLights() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat Light_ambient[] = {0.5, 0.5, 0.5, 1.0};            //环境光参数
    GLfloat Light_specular[] = {0.8, 0.8, 0.8, 1.0f};          //镜面反射参数
    GLfloat Light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};        //漫反射参数
    GLfloat light0_position[] = {28.0f, 18.0f, 4.0f, 0.0f};    // 0：平行光，1：点光源
    GLfloat light1_position[] = {-28.0f, -18.0f, 4.0f, 0.0f};  // 0：平行光，1：点光源
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_diffuse);    //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light_specular);  //镜面反射光
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light_ambient);    //环境光参数
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_diffuse);    //散射光属性
    glLightfv(GL_LIGHT1, GL_SPECULAR, Light_specular);  //镜面反射光
    glLightfv(GL_LIGHT1, GL_AMBIENT, Light_ambient);    //环境光参数
    glEnable(GL_LIGHTING);
}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat cube_mat_ambient[] = {1.0, 0.8, 0.8, 1.0f};
    GLfloat cube_mat_diffuse[] = {0.5, 0.5, 0.5, 1.0f};
    GLfloat cube_mat_specular[] = {0.6, 0.6, 0.6, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_mat_specular);
    glPushMatrix();
    {
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);
        if (mode == 0) {
            glBegin(GL_QUADS);
            for (int i = 0; i < fqueue.size(); i++) {
                fqueue[i]->faceDisplay();
            }
        } else if (mode == 1) {
            glBegin(GL_LINES);
            GLfloat r = rand() % 100 / (double)101;
            GLfloat g = rand() % 100 / (double)101;
            GLfloat b = rand()%100/(double)101;
            // r = random[(n * 3) % randomCount];
            // g = random[(n * 3 + 1) % randomCount];
            // b = random[(n * 3 + 2) % randomCount];
            glColor3f(r, g, b);
            for (int i = 0; i < equeue.size(); i++) {
                equeue[i]->edgeDisplay();
            }
        }
    }
    glPopMatrix();
    glEnd();
    glFlush();
}

void reshape(int _width, int _height) {
    width = _width;
    height = _height;
    GLfloat scale = GLfloat(width) / GLfloat(height);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'm':  // add level
            level += 1;
            cout << "level =" << level << endl;
            glutPostRedisplay();
            break;
        case 'l':  // show line frame
            mode = 1;
            cout << "mode =" << mode << endl;
            glutPostRedisplay();
            break;
        case 'f':  // show face
            mode = 0;
            cout << "mode =" << mode << endl;
            glutPostRedisplay();
            break;
        case 'i':  // zoom in
            in = true;
            cout << "in =" << in << endl;
            zoom(in);
            glutPostRedisplay();
            break;
        case 'o':  // zoom out
            in = false;
            cout << "in =" << in << endl;
            zoom(in);
            glutPostRedisplay();
            break;
        default: break;
    }
}

void specialKeyCallback(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            angleX += 10;
            cout << "GLUT_KEY_UP" << endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            angleX -= 10;
            cout << "GLUT_KEY_DOWN" << endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            angleY += 10;
            cout << "GLUT_KEY_LEFT" << endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            angleY -= 10;
            cout << "GLUT_KEY_RIGHT" << endl;
            glutPostRedisplay();
            break;
        default: break;
    }
}

int main(int argc, char* argv[]) {
    string objPath = "Models/";
    string objName = objPath + "example.obj";
    init(argc, argv);
    obj.initObject(objName, vqueue, equeue, fqueue);
    obj.test();
    vqueue = obj.getVqueue();
    equeue = obj.getEqueue();
    fqueue = obj.getFqueue();
    processor.subdivision(1, vqueue, equeue, fqueue);
    cout << " faceQueue.size()" << fqueue.size() << endl;
    cout << " edgeQueue.size()" << equeue.size() << endl;
    cout << " vertexQueue.size()" << vqueue.size() << endl;
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();
    system("pause");
    return 0;
}
