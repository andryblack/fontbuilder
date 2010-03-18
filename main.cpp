/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#include <QtGui/QApplication>
#include "fontbuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FontBuilder w;
    w.show();
    return a.exec();
}
