#include "stlRender.h"
#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QtOpenGL/QOpenGLShaderProgram>

stlRender::stlRender( QWidget* parent )
: QOpenGLWidget( parent )
, rotationX( 0 )
, rotationY( 0 )
, scale( 1.0f )
, translateX( 0.0f )
, translateY( 0.0f )
{
    setFocusPolicy( Qt::StrongFocus ); // 允许捕获键盘事件
}

bool stlRender::loadSTL(const QString &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath.toStdString(),
                                             aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

    if (!scene || !scene->HasMeshes()) {
        qWarning() << "Failed to load STL file:" << importer.GetErrorString();
        return false;
    }

    vertices.clear();
    normals.clear();

    // 遍历所有网格
    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh *mesh = scene->mMeshes[m];

        // 遍历所有面
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace face = mesh->mFaces[f];

            // 确保面是三角形（STL 文件中的面应该是三角形）
            if (face.mNumIndices == 3) {
                for (unsigned int i = 0; i < 3; ++i) {
                    int vertexIndex = face.mIndices[i];
                    vertices.append(QVector3D(mesh->mVertices[vertexIndex].x,
                                             mesh->mVertices[vertexIndex].y,
                                             mesh->mVertices[vertexIndex].z));
                    normals.append(QVector3D(mesh->mNormals[vertexIndex].x,
                                            mesh->mNormals[vertexIndex].y,
                                            mesh->mNormals[vertexIndex].z));
                }
            }
        }
    }

    update();
    return true;
}

void stlRender::initializeGL( )
{
    initializeOpenGLFunctions( );
    glEnable( GL_DEPTH_TEST );              // 启用深度测试
    glEnable( GL_LIGHTING );                // 启用光照
    glEnable( GL_LIGHT0 );                  // 启用光源0
    glEnable( GL_COLOR_MATERIAL );          // 启用材质颜色
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f ); // 设置背景颜色
}

void stlRender::resizeGL( int w, int h )
{
    glViewport( 0, 0, w, h );
    projectionMatrix.setToIdentity( );
    projectionMatrix.perspective( 45.0f, float( w ) / float( h ), 0.1f, 100.0f );
}

void stlRender::paintGL( )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // 设置模型视图矩阵
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity( );
    modelViewMatrix.translate( 0.0f, 0.0f, -5.0f );            // 将模型向后移动
    modelViewMatrix.translate( translateX, translateY, 0.0f ); // 平移模型
    modelViewMatrix.rotate( rotationX, 1, 0, 0 );              // 绕X轴旋转
    modelViewMatrix.rotate( rotationY, 0, 1, 0 );              // 绕Y轴旋转
    modelViewMatrix.scale( scale );                            // 缩放模型

    // 设置投影矩阵
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glMultMatrixf( projectionMatrix.data( ) );

    // 设置模型视图矩阵
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glMultMatrixf( modelViewMatrix.data( ) );

    // 渲染场景
    drawScene( );
}

void stlRender::mousePressEvent( QMouseEvent* event )
{
    lastMousePosition = event->pos( ); // 记录鼠标按下时的位置
}

void stlRender::mouseMoveEvent( QMouseEvent* event )
{
    int dx = event->x( ) - lastMousePosition.x( );
    int dy = event->y( ) - lastMousePosition.y( );

    if ( event->buttons( ) & Qt::LeftButton )
    {
        // 左键拖动：旋转模型
        rotationX += dy * 0.5f;
        rotationY += dx * 0.5f;

        // 限制旋转角度范围
        rotationX = qBound( -90.0f, rotationX, 90.0f );
        rotationY = qBound( -180.0f, rotationY, 180.0f );
    }
    else if ( event->buttons( ) & Qt::RightButton )
    {
        // 右键拖动：平移模型
        translateX += dx * 0.01f;
        translateY -= dy * 0.01f;
    }

    lastMousePosition = event->pos( ); // 更新鼠标位置
    update( );                         // 触发重绘
}

void stlRender::wheelEvent( QWheelEvent* event )
{
    // 根据滚轮事件调整缩放比例
    if ( event->angleDelta( ).y( ) > 0 )
    {
        scale *= 1.1f; // 放大
    }
    else
    {
        scale *= 0.9f; // 缩小
    }

    scale = qBound( 0.1f, scale, 10.0f ); // 限制缩放范围
    update( );                            // 触发重绘
}

void stlRender::drawScene( )
{
    glBegin( GL_TRIANGLES );
    for ( int i = 0; i < vertices.size( ); ++i )
    {
        glNormal3f( normals[i].x( ), normals[i].y( ), normals[i].z( ) );
        glVertex3f( vertices[i].x( ), vertices[i].y( ), vertices[i].z( ) );
    }
    glEnd( );
}