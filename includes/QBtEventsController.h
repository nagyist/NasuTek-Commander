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

#ifndef INCLUDED_QBtEventsController_h
#define INCLUDED_QBtEventsController_h

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtEvent.h"
#include <QVariant>
#include <QObject>
#include <QMutex>
#include <map>
#include <set>

/*------- class declaration:
-------------------------------------------------------------------*/
/**
* @brief  Klasa <b>singleton</b> obslugujaca wysylanie i odbior zdarzen zdefiniowanych
*         przez uzytkownika.
* @author Piotr Pszczolkowski
* @date   2007.08.24
*
* Funkcje tego obiektu pozwalaja na wysylania zdarzen przez dowolna funkcje.<br>
* Zdarzenia beda odbierane tylko przez klasy ktore zarejestrowaly chec ich odbierania.<br>
* Odbierac zdarzenia moga tylko i wylacznie obiekty dziedziczace klase QObject i ktore na
* poczatku deklaracji klasy maja wpisane makro Q_OBJECT.<br>
* Klasa chcaca odbierac zdarzenie moze to robic uzywajac wlasnej implementacji
* funkcji customEvent( QEvent* const in_event )
*/
class QBtEventsController : public QObject
{
   Q_OBJECT

// ******* CONSTRUCTION/DESTRUCTION *******
private:
   /**
   * @brief Prywatny konstruktor.
   *
   * Jest on prywatny ze wzgledu na implementacje singletona.<br>
   * Jednym mozliwym miejscem jego wywolania jest funkcja instance().<br>
   * Klasa nie zawiera zadnego publicznego konstruktora.<br>
   *
   * @see instance()
   */
   QBtEventsController();

   /**
   * @brief Prywatny destruktor.
   */
   ~QBtEventsController();

   /**
   * @brief Zablokowany copy-construktor.
   */
   QBtEventsController( const QBtEventsController& );

   /**
   * @brief Zablokowany operator przypisania.
   */
   QBtEventsController& operator=( const QBtEventsController& );

// ******* TYPES *******
private:
   /**
   * @brief Nazwa na posortowany zbior wskaznikow do zarejestrowanych 
   *        obiektow chcacych odbierac sygnaly.
   * @see EventsRegister
   */
   typedef std::set< QObject* > Objects;

   /**
   * @brief Nazwa na posortowany zbior sygnalow i zainteresownych nimi obiektow.
   *
   * Kluczem zbioru sa numery sygnalow. Kazdemu sygnalowi odpowiada zbior
   * obiektow, ktore chca go otrzymywac.
   *
   * @see append(), Objects
   */
   typedef std::map< qint32, Objects > EventsRegister;

// ******* MEMBERS *******
private:
   /**
   * @brief Rejestr zawierajacy informacje o obiektach i sygnalach.
   * @see EventsRegister
   */
   EventsRegister evreg_;

   /**
   * @brief Muteks sluzacy do blokowania wielodostepu do rejestru.
   * @see evreg_
   */
   QMutex mutex_;

// ******* METHODS *******
public:
   /**
   * @brief Funkcja zwracajaca wskaznik do obiektu (singletona).
   *
   * Funkcja ta jest gwarantem tego, ze obiekt zostanie utworzony tylko jeden raz.<br>
   * Jesli obiekt zostal wczesniej utworzony to zostanie zwrocony wskaznik do niego.<br>
   * Jesli obiekt jeszcze nie istnieje zostanie on najpierw utworzony, a nastepnie
   * zostanie zwrocony wskaznik do niego.<br>
   * Kazde odwolanie sie do metod tego obiektu musi miec postac
   * QBtEventsController::instance()->nazwa_metody.
   *
   * @see QBtEventsController()
   */
   static QBtEventsController* instance();

   /**
   * @brief Fukcja dopisuje do rejestru obiekt chcacy odbierac wskazany sygnal.
   * @param in_receiver Wskaznik do obiektu, ktory chce odebrac sygnal,
   * @param in_event_id Identyfikator(numer) sygnalu, ktory chce odbierac ten obiekt.
   *
   * Jesli jakis obiekt chce odbierac wieksza ilosc sygnalow, tyle razy musi sie
   * rejestrowac ile sygnalow chce odbierac. Dla kazdego z sygnalow osobno.<br>
   * Typowym miejscem uzycia tej funkcji jest konstruktor obiektu chcacego
   * odbierac sygnaly.
   *
   * @see remove
   */
   bool append( QObject* in_receiver, qint32 in_event_id );

   /**
   * @brief Funkcja usuwa z rejestru wszystkie informacje o wskazanym obiekcie.
   * @param in_receiver Wskaznik do obiektu, ktory ma byc usuniety z rejestru.
   *
   * Po usunieciu wksazanego obiektu z rejestru, nie bedzie on juz otrzymywal
   * zadnych sygnalow.<br>
   * Typowym miejscem uzycia tej funkcji jest destruktor usuwanego obiektu.
   *
   * @see append
   */
   void remove( QObject* in_receiver );

   /**
   * @brief Wyslanie wskazanego sygnalu bez danych.
   * @param in_event_id Identyfikator(numer) wysylanego sygnalu.
   */
   void send_event( qint32 in_event_id );

   /**
   * @brief Wyslanie wskazanego sygnalu wraz z jedna dana.
   * @param in_event_id Identyfikator(numer) wysylanego sygnalu.
   * @param in_val Dana przekazywana wraz sygnalem.
   */
   void send_event( qint32 in_event_id, QVariant in_val );

   /**
   * @brief Wyslanie wskazanego sygnalu wraz z dwoma danymi.
   * @param in_event_id Identyfikator(numer) wysylanego sygnalu.
   * @param in_val1 Dana nr. 1 przekazywana wraz sygnalem.
   * @param in_val2 Dana nr. 2 przekazywana wraz sygnalem.
   */
   void send_event( qint32 in_event_id, QVariant in_val1, QVariant in_val2 );
   
   /**
   * @brief Wyslanie wskazanego sygnalu wraz z trzema danymi.
   * @param in_event_id Identyfikator(numer) wysylanego sygnalu.
   * @param in_val1 Dana nr. 1 przekazywana wraz sygnalem.
   * @param in_val2 Dana nr. 2 przekazywana wraz sygnalem.
   * @param in_val3 Dana nr. 3 przekazywana wraz sygnalem.
   */
   void send_event(  qint32   in_event_id,
                     QVariant in_val1,
                     QVariant in_val2,
                     QVariant in_val3 );

   /**
   * @brief Wyslanie wskazanego sygnalu wraz z czterema danymi.
   * @param in_event_id Identyfikator(numer) wysylanego sygnalu.
   * @param in_val1 Dana nr. 1 przekazywana wraz sygnalem.
   * @param in_val2 Dana nr. 2 przekazywana wraz sygnalem.
   * @param in_val3 Dana nr. 3 przekazywana wraz sygnalem.
   * @param in_val4 Dana nr. 4 przekazywana wraz sygnalem.
   */
   void send_event(  qint32   in_event_id,
                     QVariant in_val1,
                     QVariant in_val2,
                     QVariant in_val3,
                     QVariant in_val4 );
private:
   /**
   * @brief Sprawdzenie czy para obiekt-sygnal jest juz zarejestrowana w rejestrze.
   * @param in_receiver Wskaznik do obiektu chcacego odbierac wkazany sygnal,
   * @param in_event_id Identyfikatior(numer) sygnalu.
   *
   * @return
   *   @arg false rejestr nie zawiera pary obiekt-sygnal,
   *   @arg true  para obiekt-sygnal znajduje sie w rejestrze.
   *
   * @see append
   */
   bool exists( QObject* in_receiver, qint32 in_event_id );
   
   //void     print  ();
};

#endif // INCLUDED_QBtEventsController_h
