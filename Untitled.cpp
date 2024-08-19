#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>

#define SPEED 30.0

float i = 0.0, m = 0.0, n = 0.0, o = 0.0, c = 0.0;
int light = 1, day = 1, plane = 0, comet = 0, xm = 900, train = 0;

void plotpixels(GLint h, GLint k, GLint x, GLint y);

void draw_circle(GLint h, GLint k, GLint r) {
    GLint d = 1 - r, x = 0, y = r;
    while (y > x) {
        for (int dx = -1; dx <= 1; dx += 2)
            for (int dy = -1; dy <= 1; dy += 2)
                plotpixels(h, k, x * dx, y * dy);
        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            --y;
        }
        ++x;
    }
    for (int dx = -1; dx <= 1; dx += 2)
        for (int dy = -1; dy <= 1; dy += 2)
            plotpixels(h, k, x * dx, y * dy);
}

void plotpixels(GLint h, GLint k, GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x + h, y + k);
    glVertex2i(-x + h, y + k);
    glVertex2i(x + h, -y + k);
    glVertex2i(-x + h, -y + k);
    glVertex2i(y + h, x + k);
    glVertex2i(-y + h, x + k);
    glVertex2i(y + h, -x + k);
    glVertex2i(-y + h, -x + k);
    glEnd();
}

void draw_object() {
    int l;
    if (day == 1) {
        // Draw sky
        glColor3f(0.0, 0.9, 0.9);
        glBegin(GL_POLYGON);
        glVertex2f(0, 380);
        glVertex2f(0, 700);
        glVertex2f(1100, 700);
        glVertex2f(1100, 380);
        glEnd();

        // Draw sun
        for (l = 0; l <= 35; l++) {
            glColor3f(1.0, 0.9, 0.0);
            draw_circle(100, 625, l);
        }

        // Draw clouds
        int cloud_positions[] = {160, 200, 225, 265, 370, 410, 435, 470, 500};
        for (int pos : cloud_positions) {
            for (l = 0; l <= 20; l++) {
                glColor3f(1.0, 1.0, 1.0);
                draw_circle(pos + m, 625, l);
            }
        }

        // Draw grass
        glColor3f(0.0, 0.9, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0, 160);
        glVertex2f(0, 380);
        glVertex2f(1100, 380);
        glVertex2f(1100, 160);
        glEnd();
    } else {
        // Draw night sky
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0, 380);
        glVertex2f(0, 700);
        glVertex2f(1100, 700);
        glVertex2f(1100, 380);
        glEnd();

        // Draw moon
        for (l = 0; l <= 35; l++) {
            glColor3f(1.0, 1.0, 1.0);
            draw_circle(100, 625, l);
        }

        // Draw stars
        int star_positions[][2] = {{575, 653}, {975, 643}, {875, 543}, {375, 598}, {750, 628}, {200, 628}, {100, 528}, {300, 468}, {500, 543}};
        for (int i = 0; i < sizeof(star_positions) / sizeof(star_positions[0]); i++) {
            glBegin(GL_TRIANGLES);
            for (int j = 0; j < 3; j++) {
                glVertex2f(star_positions[i][0] + ((j == 1) ? -5 : (j == 2) ? 5 : 0), star_positions[i][1]);
            }
            glEnd();
        }

        // Draw comet
        if (comet == 1) {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_POLYGON);
            glVertex2f(600 + n, 710);
            glVertex2f(610 + n, 705);
            glVertex2f(620 + n, 700);
            glVertex2f(630 + n, 695);
            glVertex2f(640 + n, 690);
            glEnd();

            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_POLYGON);
            glVertex2f(620 + n, 700);
            glVertex2f(630 + n, 700);
            glVertex2f(640 + n, 700);
            glVertex2f(650 + n, 700);
            glVertex2f(660 + n, 700);
            glEnd();

            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_POLYGON);
            glVertex2f(630 + n, 705);
            glVertex2f(640 + n, 705);
            glVertex2f(650 + n, 705);
            glVertex2f(660 + n, 705);
            glVertex2f(670 + n, 705);
            glEnd();
        }
    }

    // Draw railway tracks
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 70);
    glVertex2f(0, 140);
    glVertex2f(1100, 140);
    glVertex2f(1100, 70);
    glEnd();

    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0, 40);
    glVertex2f(0, 70);
    glVertex2f(1100, 70);
    glVertex2f(1100, 40);
    glEnd();

    // Draw platform
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0, 140);
    glVertex2f(0, 160);
    glVertex2f(1100, 160);
    glVertex2f(1100, 140);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();

    draw_object();
    glFlush();
    glutSwapBuffers();
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1100.0, 0.0, 700.0);
}

void update(int value) {
    if (light == 1) {
        if (i == 1)
            i = 0.0;
        else
            i += 0.001;
        if (m > 1100)
            m = 0.0;
        else
            m += SPEED;
        if (n < -600)
            n = 0.0;
        else
            n -= SPEED / 2;
        if (o > 900)
            o = 0.0;
        else
            o += SPEED / 5;
        if (c > 900)
            c = 0.0;
        else
            c += SPEED / 10;
    } else {
        if (i < 0)
            i = 1.0;
        else
            i -= 0.001;
        if (m > 1100)
            m = 0.0;
        else
            m += SPEED;
        if (n < -600)
            n = 0.0;
        else
            n -= SPEED / 2;
        if (o > 900)
            o = 0.0;
        else
            o += SPEED / 5;
        if (c > 900)
            c = 0.0;
        else
            c += SPEED / 10;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Train Animation");

    glutDisplayFunc(display);
    myInit();
    glutTimerFunc(25, update, 0);
    glutMainLoop();
}
