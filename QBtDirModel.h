#ifndef INCLUDED_QBtDirModel_h
#define INCLUDED_QBtDirModel_h

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
 * File         : QBtDirModel.h
 * Author       : Piotr Pszczolkowski
 * Contact      : piotr@beesoft.org
 * Creation date: 27.08.2007
 *******************************************************************/

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtViewModel.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtFileInfo;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDirModel : public QBtViewModel
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDirModel( QObject* = 0 );
   ~QBtDirModel();
private:
   QBtDirModel( const QBtDirModel& );
   QBtDirModel& operator=( const QBtDirModel& );

//******* METHODS *******
public:
   void update              ( const QString& );
   void update              ( const QModelIndex& );
   void refresh             ();
   bool is_dir              ( const QModelIndex& );
   bool is_readable         ( const QModelIndex& );
   void cdup                ();
private:
   void append_row          ( qint32, const QBtFileInfo&, const QStringList& );
private slots:
   void work_started_slot   ();
   void items_count_slot    ( qint32 );
   void item_info_slot      ( qint32, QVariant, QStringList );
   void work_finished_slot  ( QString );
};

#endif // INCLUDED_QBtDirModel_h