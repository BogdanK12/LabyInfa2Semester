// ======================================================================
//  Counter.cpp
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
#include <QtDebug>
#include <QSignalMapper>
#include "Counter.h"

// ----------------------------------------------------------------------
Counter::Counter() : QObject()
                   , m_nValue(0)
{
    QSignalMapper* psigMapper = new QSignalMapper(this);
    connect(psigMapper, SIGNAL(mappedString(const QString&)),
            this, SLOT(slotShowAction(const QString&))
           );

    QPushButton* pcmd1 = new QPushButton("Buttonl");
    connect(pcmd1, SIGNAL(clicked() ), psigMapper, SLOT(map() )) ;
    psigMapper->setMapping(pcmd1, "Buttonl Action");
    QPushButton* pcmd2 = new QPushButton("Button2");
    connect(pcmd2, SIGNAL(clicked() ), psigMapper, SLOT(map() ));
    psigMapper->setMapping(pcmd2, "Button2 Action");
    pcmd1->show();
    pcmd2->show();
}

void Counter::slotShowAction(const QString& str)
  {
   qDebug() << str;
  }
// ----------------------------------------------------------------------
void Counter::slotInc()
{
    emit counterChanged(++m_nValue);
    qDebug() << sender()->objectName();
    qDebug() << "I'm a slot";
    if (m_nValue == 5) {
        {   qDebug() << "Пока";
            emit goodbye();
        }
    }
}
