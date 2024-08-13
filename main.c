#include "bst.h"
#include <GL/freeglut.h>

// Função para desenhar um círculo
void drawCircle(float x, float y, float radius) {
    int num_segments = 100;
    float angle_step = 2 * 3.1415 / num_segments;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; ++i) {
        float angle = i * angle_step;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Função para desenhar o texto centralizado
void drawCenteredText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    void* font = GLUT_BITMAP_HELVETICA_12;
    int len = (int)strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// Função para desenhar um nó da árvore
void drawNode(float x, float y, int value) {
    glColor3f(1.0, 1.0, 1.0); // Cor do círculo (branco)
    drawCircle(x, y, 0.05); // Desenha o círculo

    // Desenha o valor do nó
    glColor3f(0.0, 0.0, 0.0); // Cor do texto (preto)
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", value);
    
    // Calcular o tamanho do texto para centralizar
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)buffer);
    drawCenteredText(x - textWidth / 2 / 72.0, y - 0.015, buffer);
}

// Função recursiva para desenhar a árvore BST
void drawBST(Node* root, float x, float y, float offsetX, float offsetY) {
    if (root == NULL) return;

    // Desenha o nó atual
    drawNode(x, y, root->key);

    // Desenha a conexão com o filho esquerdo
    if (root->left != NULL) {
        glColor3f(1.0, 1.0, 1.0); // Cor da linha (branco)
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - offsetX, y - offsetY);
        glEnd();
        drawBST(root->left, x - offsetX, y - offsetY, offsetX / 2, offsetY);
    }

    // Desenha a conexão com o filho direito
    if (root->right != NULL) {
        glColor3f(1.0, 1.0, 1.0); // Cor da linha (branco)
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + offsetX, y - offsetY);
        glEnd();
        drawBST(root->right, x + offsetX, y - offsetY, offsetX / 2, offsetY);
    }
}


void display(BST *bt) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Exemplo de árvore BST
    // Node* root = createNode(10);
    // root->left = createNode(5);
    // root->right = createNode(15);
    // root->left->left = createNode(3);
    // root->left->right = createNode(7);
    // root->right->left = createNode(12);
    // root->right->right = createNode(18);

    // Desenha a árvore BST
    
    drawBST(bt->root, 0.0, 0.0, 0.2, 0.1);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Cor de fundo preta
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Configura o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char const *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("BST Tree Visualization");



    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
