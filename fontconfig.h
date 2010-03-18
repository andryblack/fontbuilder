#ifndef FONTCONFIG_H
#define FONTCONFIG_H

#include <QObject>
#include <QColor>

class FontConfig : public QObject
{
Q_OBJECT
public:
    explicit FontConfig(QObject *parent = 0);

    const QString& path() const { return m_path; }
    void setPath(const QString& path);
    Q_PROPERTY( QString path READ path WRITE setPath );

    const QString& filename() const { return m_filename; }
    void setFilename(const QString& filename);
    Q_PROPERTY( QString filename READ filename WRITE setFilename );

    int faceIndex() const { return m_face_index;}
    void setFaceIndex(int indx);
    Q_PROPERTY( int faceIndex READ faceIndex WRITE setFaceIndex );

    int size() const { return m_size;}
    void setSize(int size);
    Q_PROPERTY( int size READ size WRITE setSize );

    const QString& characters() const { return m_characters; }
    void setCharacters(const QString& characters);
    Q_PROPERTY( QString characters READ characters WRITE setCharacters );

    bool autohinting() const { return m_autohinting;}
    void setAutohinting(bool b);
    Q_PROPERTY( bool autohinting READ autohinting WRITE setAutohinting );

    bool renderMissing() const { return m_render_missing;}
    void setRenderMissing(bool b);
    Q_PROPERTY( bool renderMissing READ renderMissing WRITE setRenderMissing );

    bool antialiased() const { return m_antialiased;}
    void setAntialiased(bool b);
    Q_PROPERTY( bool antialiased READ antialiased WRITE setAntialiased );

    int bold() const { return m_bold;}
    void setBold(int b);
    Q_PROPERTY( int bold READ bold WRITE setBold );

    int italic() const { return m_italic;}
    void setItalic(int b);
    Q_PROPERTY( int italic READ italic WRITE setBold );

    float width() const { return m_width;}
    void setWidth(float b);
    Q_PROPERTY( float width READ width WRITE setWidth );

    float height() const { return m_height;}
    void setHeight(float b);
    Q_PROPERTY( float height READ height WRITE setHeight );

private:
    QString m_path;
    QString m_filename;
    int m_face_index;
    int m_size;
    QString m_characters;
    bool    m_autohinting;
    bool    m_render_missing;
    bool    m_antialiased;
    int    m_bold;
    int    m_italic;
    float   m_width;
    float   m_height;
signals:
    void fileChanged();
    void faceIndexChanged();
    void sizeChanged();
    void charactersChanged();
    void renderingOptionsChanged();
public slots:

};

#endif // FONTCONFIG_H
