#ifndef INCLUDED_QBtWorkedThred_h
#define INCLUDED_QBtWorkedThred_h

/********************************************************************
 * Copyright (C) Piotr Pszczolkowski; Copyright (C) 2012 NasuTek Enterprises
 *-------------------------------------------------------------------
 * This file is part of NasuTek Commander.
 *
 * NasuTek Commander is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * NasuTek Commander is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NasuTek Commander; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *-------------------------------------------------------------------
 * Project      : NasuTek Commander
 * File         : QBtWorkedThread.cpp
 * Author       : Piotr Pszczolkowski
 * Contact      : piotr@beesoft.org
 * Creation date: 31.08.2007
 *******************************************************************/

/*------- include files:
-------------------------------------------------------------------*/
#include <QThread>
#include <QVariant>
#include <QStringList>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtWorkedThread : public QThread
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtWorkedThread( QObject* = 0 );
private:
   QBtWorkedThread( const QBtWorkedThread& );
   QBtWorkedThread& operator=( const QBtWorkedThread& );

//******* MEMBERS *******
protected:
   QString path_;

//******* METHODS *******
public:
   virtual void update( const QString& ) = 0;
protected:
   virtual void run() = 0;
signals:
   void work_started  ();
   void items_count   ( qint32 );
   void item_info     ( qint32, QVariant, QStringList );
   void work_finished ( const QString );   
};

#endif // INCLUDED_QBtWorkedThred_h