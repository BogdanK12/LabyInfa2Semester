// ======================================================================
//  main.cpp
// ======================================================================
//                   This file is a part of the book 
//             "Qt 5.3 Professional programming with C++"
// ======================================================================
//  Copyright (c) 2014 by Max Schlee
//
//  Email : Max.Schlee@neonway.com
//  Blog  : http://www.maxschlee.com
//
//  Social Networks
//  ---------------
//  FaceBook : http://www.facebook.com/mschlee
//  Twitter  : http://twitter.com/Max_Schlee
//  2Look.me : http://2look.me/NW100003
//  Xing     : http://www.xing.com/profile/Max_Schlee
//  vk.com   : https://vk.com/max.schlee
// ======================================================================

#include <QtWidgets>
#include "Counter.h"

// ----------------------------------------------------------------------
int main (int argc, char** argv)
{
    QApplication app(argc, argv);

    QLabel      lbl("0");
    QPushButton cmd("ADD");
    Counter     counter;
    cmd.setObjectName("Послано от QPushButton");  // Даем имя объекту QPushButton
    lbl.move(400,250);
     qDebug() << lbl.pos().x();
     cmd.move(1000,250);
     //cmd.move(0,0);
     qDebug() << cmd.pos().x() << " " << cmd.pos().y();
    lbl.show();
    cmd.show();
    //cmd.blockSignals(true);
    qDebug() << cmd.signalsBlocked();
    QObject::connect(&cmd, SIGNAL(clicked()),
                     &counter, SLOT(slotInc())
                    );
//    QMetaObject::Connection x = QObject::connect(&cmd, &QPushButton::clicked,
//                     &counter, &Counter::slotInc
//                    );

    //blockSignals

    QObject::connect(&counter, SIGNAL(counterChanged(int)),
                     &lbl, SLOT(setNum(int))
                    );

    QObject::connect(&counter, SIGNAL(goodbye()), 
                     &app, SLOT(quit())
                    );

    return app.exec();
}
