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

    bool bold() const { return m_bold;}
    void setBold(bool b);
    Q_PROPERTY( bool bold READ bold WRITE setBold );

    bool italic() const { return m_italic;}
    void setItalic(bool b);
    Q_PROPERTY( bool italic READ italic WRITE setBold );
private:
    QString m_path;
    QString m_filename;
    int m_face_index;
    int m_size;
    QString m_characters;
    bool    m_autohinting;
    bool    m_render_missing;
    bool    m_antialiased;
    bool    m_bold;
    bool    m_italic;
signals:
    void fileChanged();
    void faceIndexChanged();
    void sizeChanged();
    void charactersChanged();
    void renderingOptionsChanged();
public slots:

};

#endif // FONTCONFIG_H
