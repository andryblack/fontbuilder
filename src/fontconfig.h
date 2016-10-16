/**
 * Copyright (c) 2010-2010 Andrey AndryBlack Kunitsyn
 * email:support.andryblack@gmail.com
 *
 * Report bugs and download new versions at http://code.google.com/p/fontbuilder
 *
 * This software is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FONTCONFIG_H
#define FONTCONFIG_H

#include <QObject>
#include <QColor>

class FontConfig : public QObject
{
Q_OBJECT
Q_ENUMS(HintingMethod)
Q_ENUMS(AAMethod)
public:
    explicit FontConfig(QObject *parent = 0);

    void normalize();

    enum HintingMethod {
        HintingDisable,
        HintingDefault,
        HintingForceFreetypeAuto,
        HintingDisableFreetypeAuto
    };

    enum AAMethod {
        AAliasingNormal,
        AAliasingLight,
        AAliasingLCDhor,
        AAliasingLCDvert
    };

    const QString& path() const { return m_path; }
    void setPath(const QString& path);
    Q_PROPERTY( QString path READ path WRITE setPath )

    const QString& filename() const { return m_filename; }
    void setFilename(const QString& filename);
    Q_PROPERTY( QString filename READ filename WRITE setFilename )

    const QString& family() const { return m_family; }
    void setFamily(const QString& family);
    Q_PROPERTY( QString family READ family WRITE setFamily )

    const QString& style() const { return m_style; }
    void setStyle(const QString& style);
    Q_PROPERTY( QString style READ style WRITE setStyle )

    int faceIndex() const { return m_face_index;}
    void setFaceIndex(int indx);
    Q_PROPERTY( int faceIndex READ faceIndex WRITE setFaceIndex )

    int size() const { return m_size;}
    void setSize(int size);
    Q_PROPERTY( int size READ size WRITE setSize )

    const QString& characters() const { return m_characters; }
    void setCharacters(const QString& characters);
    Q_PROPERTY( QString characters READ characters WRITE setCharacters )

    const QString& defaultCharacters() const;

    int hinting() const { return m_hinting;}
    void setHinting(int b);
    void resetHinting() { m_hinting = HintingDefault;}
    Q_PROPERTY( int hinting READ hinting WRITE setHinting RESET resetHinting )

    bool renderMissing() const { return m_render_missing;}
    void setRenderMissing(bool b);
    Q_PROPERTY( bool renderMissing READ renderMissing WRITE setRenderMissing )

    bool antialiased() const { return m_antialiased;}
    void setAntialiased(bool b);
    Q_PROPERTY( bool antialiased READ antialiased WRITE setAntialiased )

    int antialiasing() const { return m_aamethod;}
    void setAntiAliasing(int b);
    void resetAntiAliasing() {m_aamethod = AAliasingNormal;}
    Q_PROPERTY( int antialiasing READ antialiasing WRITE setAntiAliasing RESET resetAntiAliasing)

    int bold() const { return m_bold;}
    void setBold(int b);
    Q_PROPERTY( int bold READ bold WRITE setBold )

    int italic() const { return m_italic;}
    void setItalic(int b);
    Q_PROPERTY( int italic READ italic WRITE setItalic )

    float width() const { return m_width;}
    void setWidth(float b);
    Q_PROPERTY( float width READ width WRITE setWidth )

    float height() const { return m_height;}
    void setHeight(float b);
    Q_PROPERTY( float height READ height WRITE setHeight )

    int lineSpacing() const { return m_line_spacing;}
    void setLineSpacing(int s);
    Q_PROPERTY( int lineSpacing READ lineSpacing WRITE setLineSpacing )

    int charSpacing() const { return m_char_spacing;}
    void setCharSpacing(int s);
    Q_PROPERTY( int charSpacing READ charSpacing WRITE setCharSpacing )

    int DPI() const { return m_dpi;}
    void setDPI(int dpi);
    Q_PROPERTY( int DPI READ DPI WRITE setDPI )

    static QString defaultFontsPath();
    void emmitChange();
private:
    QString m_path;
    QString m_filename;
    QString m_family;
    QString m_style;
    int m_face_index;
    int m_size;
    QString m_characters;
    int    m_hinting;
    bool    m_render_missing;
    bool    m_antialiased;
    int     m_aamethod;
    int    m_bold;
    int    m_italic;
    float   m_width;
    float   m_height;
    int m_char_spacing;
    int m_line_spacing;
    int m_dpi;
signals:
    void nameChanged();
    void fileChanged();
    void faceIndexChanged();
    void sizeChanged();
    void charactersChanged();
    void renderingOptionsChanged();
    void spacingChanged();
public slots:

};


#endif // FONTCONFIG_H
