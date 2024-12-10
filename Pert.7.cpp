#include <glut.h>
#include <cmath>

// Variabel kamera
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f;

// Variabel untuk animasi
float fishX = -2.0f;
float bubbleY = -1.0f;

// Fungsi untuk menggambar kapal selam
void drawSubmarine() {
    glPushMatrix();

    // Badan kapal selam (elips horizontal)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Kuning
    glScalef(1.5f, 0.7f, 0.7f);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();

    // Jendela kapal selam (kanan dan kiri)
    glPushMatrix();
    glColor3f(0.6f, 0.8f, 1.0f); // Biru muda
    glTranslatef(0.5f, 0.0f, 0.7f);
    glutSolidSphere(0.2f, 20, 20); // Jendela pertama (kanan)
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20); // Jendela kedua (kanan)
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20); // Jendela ketiga (kanan)
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.7f); // Geser ke kiri
    glutSolidSphere(0.2f, 20, 20); // Jendela pertama (kiri)
    glTranslatef(0.5f, 0.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20); // Jendela kedua (kiri)
    glTranslatef(0.5f, 0.0f, 0.0f);
    glutSolidSphere(0.2f, 20, 20); // Jendela ketiga (kiri)
    glPopMatrix();

    // Menara kapal selam
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f); // Silver
    glTranslatef(0.3f, 0.9f, 0.0f);
    glScalef(0.5f, 0.8f, 0.5f);
    glutSolidSphere(0.6f, 30, 30);
    glPopMatrix();

    // Baling-baling kapal
    glPushMatrix();
    glTranslatef(1.4f, 0.0f, -0.5f);

    // Poros baling-baling
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.3f); // Kuning terang
    glPopMatrix();

    // Baling-baling
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        if (i % 2 == 0) glColor3f(1.0f, 0.3f, 0.3f); // Merah
        else glColor3f(0.3f, 1.0f, 0.3f); // Hijau

        glRotatef(90.0f * i, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, 0.4f);
        glScalef(1.5f, 0.1f, 0.2f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix();

    // Sirip kapal selam
    glPushMatrix();
    glColor3f(0.9f, 0.3f, 0.1f); // Merah terang
    glTranslatef(-0.8f, 0.7f, 0.0f);
    glScalef(0.8f, 0.1f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Fungsi untuk menggambar gelembung udara
void drawBubble(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor4f(0.6f, 0.8f, 1.0f, 0.6f); // Transparan
    glutSolidSphere(0.1f, 20, 20);
    glPopMatrix();
}

// Fungsi untuk menampilkan objek
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
    drawSubmarine();
    drawBubble(0.0f, bubbleY, -2.0f);

    glutSwapBuffers();
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk animasi
void timer(int) {
    fishX += 0.02f;
    if (fishX > 2.0f) fishX = -2.0f;

    bubbleY += 0.02f;
    if (bubbleY > 2.0f) bubbleY = -1.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 FPS
}

// Fungsi untuk kontrol kamera menggunakan keyboard
void keyboard(unsigned char key, int x, int y) {
    float step = 0.2f;
    switch (key) {
    case 'w': camY += step; break; // Naik
    case 's': camY -= step; break; // Turun
    case 'a': camX -= step; break; // Kiri
    case 'd': camX += step; break; // Kanan
    case 'z': camZ -= step; break; // Zoom in
    case 'x': camZ += step; break; // Zoom out
    case 27: exit(0); break; // ESC untuk keluar
    }
    glutPostRedisplay();
}

// Fungsi utama program
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simulasi Kapal Selam 3D");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glClearColor(0.0f, 0.6f, 1.0f, 1.0f); // Latar biru laut

    glutMainLoop();
    return 0;
}
