#include "mainwidget.h"
#include "mainwindow.h"
#include "quadtree.h"
#include <random>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    sprite(0),
    texture(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete sprite;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}


void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;


    }
    // Request an update
    update();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    // glEnable(GL_CULL_FACE);

    sprite = new Sprite;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}


void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures()
{
    QImage image(512, 512, QImage::Format_ARGB32);
    QPainter painter(&image);
    QPainterPath path;
    path.addEllipse(image.rect());
    QRadialGradient radialGrad(image.rect().center(), image.rect().width());
    radialGrad.setColorAt(0, Qt::white);
    radialGrad.setColorAt(0.5, qRgba(0,0,255,0));
    radialGrad.setColorAt(1, Qt::white);
    painter.fillPath(path, QBrush(radialGrad));

    // Load cube.png image
    texture = new QOpenGLTexture(image.mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::generateBubblesImageQuadTree(int distribution[],double radiuses[],int Nbubles, int max_dim)
{
    QuadTree* quadtree = new QuadTree(AABB(XY(max_dim/2,max_dim/2),
                                           XY(max_dim/2,max_dim/2)));
    std::uniform_int_distribution<int> distribution_coord(0,max_dim);
    std::uniform_real_distribution<float> distribution_rad(0.,1.);
    std::default_random_engine gen;
    gen.seed(QTime::currentTime().msecsSinceStartOfDay());

    long count=0,colisions=0;
    float N2_avg=0;
    for(int ri=0; ri < 5; ri++)
    {
        double r = radiuses[ri];
        int N = Nbubles * distribution[ri] / 1000;
        for(int i=0; i < N; i++)
        {
            int x = distribution_coord(gen);
            int y = distribution_coord(gen);
            Circle cir = Circle(r,x,y);
            std::vector<XY> circles_in_range = quadtree->queryRange(AABB(XY(x,y),XY(r,r)));
            N2_avg+=circles_in_range.size();
            bool intersect_flag=false;
            for(auto it=circles_in_range.begin(); it!=circles_in_range.end(); it++)
            {
                if( cir.intersect(Circle(it->r,it->x,it->y)) )
                {
                    intersect_flag = true;
                    break;
                }
            }
            if( !intersect_flag )
            {
               //cir.draw(painter);
               quadtree->insertCircle(cir);
               drawSprite(2*(cir.xc-cir.r)/max_dim,2*(cir.yc-cir.r)/max_dim,cir.r/max_dim);
               count++;
            }
            else
                colisions++;
        }
        N2_avg = N2_avg/N;
        qDebug() << "number of intersect operations per circle" << N2_avg;
    }
    delete quadtree;
    qDebug() << "count=" << count << " from " << Nbubles << " colisions=" << colisions;
}

void MainWidget::generateBubblesImageLinearSearch(int Nbubles, int max_dim)
{
    int distribution[] = {150,50,200,300,300};
    std::uniform_int_distribution<int> distribution_coord(0,max_dim);
    std::uniform_real_distribution<float> distribution_rad(0.,1.);
    double radiuses[] = {50,30,20,10,5};
    std::default_random_engine gen;
    gen.seed(QTime::currentTime().msecsSinceStartOfDay());
    Circles circles;

    long count=0,colisions=0;
    for(int ri=0; ri < 5; ri++)
    {
        double r = radiuses[ri];
        int N = Nbubles * distribution[ri] / 1000;
        for(int i=0; i < N; i++)
        {
            int x = distribution_coord(gen);
            int y = distribution_coord(gen);
            Circle cir = Circle(r,x,y);
            if(circles.add_not_intersect(cir))
            {
               //cir.draw(painter);
               drawSprite(2*(cir.xc-cir.r)/max_dim,2*(cir.yc-cir.r)/max_dim,cir.r/max_dim);
               count++;
            }
            else
                colisions++;
        }
    }
    qDebug() << "count=" << count << " from " << Nbubles << " colisions=" << colisions;
}


void MainWidget::drawSprite(float x, float y, float r)
{
    QMatrix4x4 matrix;
    matrix.translate(x-1, y-1, -3.0);
    matrix.rotate(rotation);
    matrix.scale(r,r,1.0);
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    // Draw sprite geometry
    sprite->render(&program);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    //glClearColor(0,0,1.0,1.0);

    texture->bind();
    //generateBubblesImageLinearSearch(5000, 800);
    int distribution[] = {150,50,200,300,300};
    double radiuses[] = {500,300,200,100,50};
    generateBubblesImageQuadTree(distribution,radiuses,50000,8000);

    // Calculate model view transformation

}
