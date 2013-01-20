/*****************************************************************************
 * NasuTek Commander
 * Copyright (C) 2012 NasuTek Enterprises <mmanley@nasutek.com>
 * Copyright (C) 2005-2008 Piotr Pszczolkowski <piotr@beesoft.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef INCLUDED_QBtFileViewer_h
#define INCLUDED_QBtFileViewer_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTextBrowser;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtFileViewer : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtFileViewer( QWidget*, const QString& );
private:
   QBtFileViewer( const QBtFileViewer& );
   QBtFileViewer& operator=( const QBtFileViewer& );

//******* CONSTANTS ********
private:
   static const char* const CAPTION;
   static const char* const CANCEL;

//******* MEMBERS *******
private:
   const QString       path_;
   QTextBrowser* const browser_;
   QPushButton*  const cancel_;

//******* METHODS *******
private:
   void showEvent  ( QShowEvent* );
   void tar_file   ( const QString& );
   void zip_file   ( const QString& );
   void html_file  ( const QString& );
   void text_file  ( const QString& );
   void image_file ( const QString& );
   void other_file ( const QString& );
   void set_font   ();
   void load_file  ();
   void do_it      ( const QString& );
};

#endif // INCLUDED_QBtFileViewer_h
