#ifndef INCLUDED_QBtView_h
#define INCLUDED_QBtView_h

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
 * File         : QBtView.h
 * Author       : Piotr Pszczolkowski
 * Contact      : piotr@beesoft.org
 * Creation date: 27.08.2007
 *******************************************************************/

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QTreeView>
#include <stack>
#include <queue>


/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtViewModel;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtView : public QTreeView
{
   Q_OBJECT

//******** TYPES *******
private:
   enum {
      UNKNOWN = 0,
      INITIAL_FILE_SELECT,
      RESIZE_COLUMNS,
      GOTO_TOP,
      REFRESH,
   };

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtView( const QString&, QWidget* = 0 );
   ~QBtView();
private:
   QBtView( const QBtView& );
   QBtView& operator=( const QBtView& );
   
//****** MEMBERS *******
private:
   QBtViewModel*         model_;
   std::queue< qint32 >  requests_;
   std::stack< QString > initial_file_stack_;

//******* CONSTANTS *******
private:
   static const char* const MKDIR_CAPTION;
   static const char* const MKDIR_PROMPT;
   static const char* const MKDIR_ERROR;
   static const char* const RENAME_CAPTION;
   static const char* const RENAME_PROMPT;
   static const char* const RENAME_ERROR;

//******* METHODS *******
public:
   QString  selected_file_full_name  () const;
   QString  selected_file_path       () const;
   void           set_initial_file_request ( const QString& );
   void           set_initial_file         ();
   void           update                   ( const QString& );
   const QString& current_path             () const;
   void           goto_top                 ();
   const SelectionsSet&  get_selected_items() const;
   void           refresh                  ( const QString& = QString());
   void           unselect_all             ();
private:
   void    settings          ();
   void    keyPressEvent     ( QKeyEvent* );
   void    customEvent       ( QEvent* );
   void    find              ();
   void    enter_key         ();
   void    one_level_up      ();
   void    jump_to_home      ();
   void    resize_columns    ();
   void    select            ();
   void    select_mask       ();
   void    deselect_mask     ();
   void    revert_selection  ();
   void    select_all        ();
   void    remove_selected   ();
   void    access_permissions();
   void    mkdir             ();
   void    rename            ();
   void    view              ();
   void    edit              ();
   void    console_start     () const;
   bool    is_ext_declared   ( const QString&, QString&, QString& ) const;
private slots:
   void    enter            ( const QModelIndex& );
signals:
   void    dir_count        ( qint32 );
   void    file_count       ( qint32 );
   void    select_count     ( qint32 );
   void    path_changed     ( const QString& );
private slots:
   void    request_finished();
};

#endif // INCLUDED_QBtView_h