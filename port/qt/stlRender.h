#ifndef STLRENDER
#define STLRENDER

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class stlRender
: public QOpenGLWidget
, protected QOpenGLFunctions
{

    public:
    explicit stlRender( QWidget* parent = nullptr );
    ~stlRender( ) = default;

    bool loadSTL( const QString& filePath );

    protected:
    void initializeGL( ) override;
    void resizeGL( int w, int h ) override;
    void paintGL( ) override;

    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void wheelEvent( QWheelEvent* event ) override;

    private:
    void setupScene( );
    void drawScene( );

    QVector< QVector3D > vertices; // ����
    QVector< QVector3D > normals;  // ����

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 modelMatrix;

    QPoint lastMousePosition;
    float rotationX, rotationY;
    float scale, translateX, translateY;
};

#endif // STLRENDER
