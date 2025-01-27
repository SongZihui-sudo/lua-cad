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
    setFocusPolicy( Qt::StrongFocus ); // ����������¼�
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

    // ������������
    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh *mesh = scene->mMeshes[m];

        // ����������
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace face = mesh->mFaces[f];

            // ȷ�����������Σ�STL �ļ��е���Ӧ���������Σ�
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
    glEnable( GL_DEPTH_TEST );              // ������Ȳ���
    glEnable( GL_LIGHTING );                // ���ù���
    glEnable( GL_LIGHT0 );                  // ���ù�Դ0
    glEnable( GL_COLOR_MATERIAL );          // ���ò�����ɫ
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f ); // ���ñ�����ɫ
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

    // ����ģ����ͼ����
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity( );
    modelViewMatrix.translate( 0.0f, 0.0f, -5.0f );            // ��ģ������ƶ�
    modelViewMatrix.translate( translateX, translateY, 0.0f ); // ƽ��ģ��
    modelViewMatrix.rotate( rotationX, 1, 0, 0 );              // ��X����ת
    modelViewMatrix.rotate( rotationY, 0, 1, 0 );              // ��Y����ת
    modelViewMatrix.scale( scale );                            // ����ģ��

    // ����ͶӰ����
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glMultMatrixf( projectionMatrix.data( ) );

    // ����ģ����ͼ����
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glMultMatrixf( modelViewMatrix.data( ) );

    // ��Ⱦ����
    drawScene( );
}

void stlRender::mousePressEvent( QMouseEvent* event )
{
    lastMousePosition = event->pos( ); // ��¼��갴��ʱ��λ��
}

void stlRender::mouseMoveEvent( QMouseEvent* event )
{
    int dx = event->x( ) - lastMousePosition.x( );
    int dy = event->y( ) - lastMousePosition.y( );

    if ( event->buttons( ) & Qt::LeftButton )
    {
        // ����϶�����תģ��
        rotationX += dy * 0.5f;
        rotationY += dx * 0.5f;

        // ������ת�Ƕȷ�Χ
        rotationX = qBound( -90.0f, rotationX, 90.0f );
        rotationY = qBound( -180.0f, rotationY, 180.0f );
    }
    else if ( event->buttons( ) & Qt::RightButton )
    {
        // �Ҽ��϶���ƽ��ģ��
        translateX += dx * 0.01f;
        translateY -= dy * 0.01f;
    }

    lastMousePosition = event->pos( ); // �������λ��
    update( );                         // �����ػ�
}

void stlRender::wheelEvent( QWheelEvent* event )
{
    // ���ݹ����¼��������ű���
    if ( event->angleDelta( ).y( ) > 0 )
    {
        scale *= 1.1f; // �Ŵ�
    }
    else
    {
        scale *= 0.9f; // ��С
    }

    scale = qBound( 0.1f, scale, 10.0f ); // �������ŷ�Χ
    update( );                            // �����ػ�
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