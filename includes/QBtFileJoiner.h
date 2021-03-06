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

#ifndef INCLUDED_QBtFileJoiner_h
#define INCLUDED_QBtFileJoiner_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>
#include "BtTypes.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QPushButton;
class QRadioButton;
class QTreeWidget;
class QFile;
class QGroupBox;
class QProgressBar;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtFileJoiner : public QDialog
{
   Q_OBJECT

//******* TYPES *******
private:
   enum {
      OverwriteId = 0,
      AppendId = 1,
      AtTopId = 0,
      AtEndId = 1,
      FullPath = Qt::UserRole
   };

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtFileJoiner( QWidget*, const SelectionsSet&, const QString& );
private:
   QBtFileJoiner( const QBtFileJoiner& );
   QBtFileJoiner& operator=( const QBtFileJoiner& );

//******* CONSTANTS *******
private:
   static const char* const Caption;
   static const char* const SourceCaption;
   static const char* const DestinationCaption;
   static const char* const ProgressCaption;
   static const char* const Start;
   static const char* const Cancel;
   static const char* const Break;
   static const char* const Path;
   static const char* const Overwrite;
   static const char* const Append;
   static const char* const AtTop;
   static const char* const AtEnd;
   static const char* const Up;
   static const char* const Down;
   static const char* const CantRemove;
   static const char* const CantCreateTmp;
   static const char* const ReadError;
   static const char* const WriteError;

//******* MEMBERS *******
private:
   const SelectionsSet files_;
   const QString       dst_fpath_;
   const bool          dst_exists_;
   
   QPushButton*  const start_btn_;
   QPushButton*  const cancel_btn_;
   QRadioButton* const overwrite_btn_;
   QRadioButton* const append_btn_;
   QRadioButton* const at_top_btn_;
   QRadioButton* const at_end_btn_;
   QTreeWidget*  const list_;
   QPushButton*  const up_btn_;
   QPushButton*  const down_btn_;
   QGroupBox*    const src_box_;
   QGroupBox*    const dst_box_;
   QGroupBox*    const progress_box_;
   QProgressBar* const progress_;

   QString             bak_fpath_;
   bool                runned_;
   bool                break_;

//******* METHODS *******
private:
   void create_list( const SelectionsSet& );
   bool init       ( QFile& );
   void finish     ( QFile& );
   bool append     ( QFile&, const QString& );
   void disable    () const;
private slots:
   void start_slot ();
   void cancel_slot();
   void mode_slot  ( int );
   void up_slot    ();
   void down_slot  ();
};

 #endif // INCLUDED_QBtFileJoiner_h
