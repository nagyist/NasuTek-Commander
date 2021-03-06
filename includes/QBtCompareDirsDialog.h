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

#ifndef INCLUDED_QBtCompareDirsDialog_h
#define INCLUDED_QBtCompareDirsDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>
#include <QHash>
#include <QMap>
#include <QFileInfo>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QPushButton;
class QTreeWidget;
class QBtInfoLabel;
class QTreeWidgetItem;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtCompareDirsDialog : public QDialog
{
   Q_OBJECT

//******* TYPES *******
private:
   typedef QHash< QString, QFileInfo > FileMap;
   typedef QHash< QString, FileMap   > DirMap;
   typedef QMap < QString, QString   > AllItems;
   class RowData {
      public:
         RowData()
         : name1_     ( QString() )
         , name2_     ( QString() )
         , path1_     ( QString() )
         , path2_     ( QString() )
         , separator_ ( QString() )
         , is_lft_    ( false )
         , is_rgt_    ( false )
         , is_dir_    ( false )
         {}
         ~RowData() {}
      private:
         RowData( const RowData& );
         RowData& operator=( const RowData& );
         
      //******* MEMBERS *******
      private:
         QString name1_;
         QString name2_;
         QString path1_;
         QString path2_;
         QString separator_;
         bool    is_lft_;
         bool    is_rgt_;
         bool    is_dir_;
      public:
         const QString& name1    () const { return name1_;     }
         const QString& name2    () const { return name2_;     }
         const QString& path1    () const { return path1_;     }
         const QString& path2    () const { return path2_;     }
         const QString& separator() const { return separator_; }
         bool           is_lft   () const { return is_lft_;    }
         bool           is_rgt   () const { return is_rgt_;    }
         bool           is_dir   () const { return is_dir_;    }
         bool           are_both () const { return ( is_lft_ && is_rgt_ ); }

         void name1    ( const QString& in_text ) { name1_     = in_text; }
         void name2    ( const QString& in_text ) { name2_     = in_text; }
         void path1    ( const QString& in_text ) { path1_     = in_text; }
         void path2    ( const QString& in_text ) { path2_     = in_text; }
         void separator( const QString& in_text ) { separator_ = in_text; }
         void is_lft   ( const bool     in_flag ) { is_lft_    = in_flag; }
         void is_rgt   ( const bool     in_flag ) { is_rgt_    = in_flag; }
         void is_dir   ( const bool     in_flag ) { is_dir_    = in_flag; }

         void reset () {
            name1_ = name2_ = path1_ = path2_ = separator_ = QString();
            is_lft_ = is_rgt_ = is_dir_ = false;
         }
         void set_lft( const QString& in_name, const QString& in_path ) {
            is_lft_ = true;
            name1_  = in_name;
            path1_  = in_path;
         }
         void set_rgt( const QString& in_name, const QString& in_path ) {
            is_rgt_ = true;
            name2_  = in_name;
            path2_  = in_path;
         }
   };
   
//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtCompareDirsDialog( QWidget* );
private:
   QBtCompareDirsDialog( const QBtCompareDirsDialog& );
   QBtCompareDirsDialog& operator=( const QBtCompareDirsDialog& );

//******* CONSTANTS *******
private:
   static const char* const Caption;
   static const char* const DirsCaption;
   static const char* const ResultCaption;
   static const char* const LftPanel;
   static const char* const RgtPanel;
   static const char* const Run;
   static const char* const Compare;
   static const char* const Close;
   static const char* const Break;
   static const char* const LeftDir;
   static const char* const RightDir;
   static const char* const NotPresent;
   static const char* const TheSame;
   static const char* const ReadError;
   static const char* const CantOpen;
   static const QString     Dir;
   static const QString     Equal;
   static const QString     NotEqual;
   static const QString     Error;
   

//******* MEMBERS *******
private:
   QTreeWidget*  const view_;
   QPushButton*  const run_btn_;
   QPushButton*  const close_btn_;
   QBtInfoLabel* const left_dirinfo_;
   QBtInfoLabel* const right_dirinfo_;
   QString             left_path_;
   QString             right_path_;
   bool                runned_;
   bool                continue_;
   bool                ready_;

//******** METHODS *******
public:
   void set_dirs( const QString&, const QString& );
private:
   void    showEvent    ( QShowEvent* );
   void    add_row      ( const RowData& ) const;
   QString check_files  ( const QFileInfo&, const QFileInfo& );
   QString cmp_contents ( const QString&, const QString& );
   void    set_focus    ();
   void    diff         ( const QString& , const QString& ) const;
   void    read_dir     ( const QString& , const QString&, DirMap& ) const;
   void    compare      ( const QString& , const QString&   );
   void    compare_files( const FileMap& , const FileMap&   );
   void    join_dirs    ( AllItems&      , const DirMap&    ) const;
   void    join_files   ( AllItems&      , const FileMap&   ) const;

private slots:
   void start_slot();
   void close_slot();
};

 #endif // INCLUDED_QBtCompareDirsDialog_h
