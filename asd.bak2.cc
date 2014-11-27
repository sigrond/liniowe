/**
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/materialy/AISDI/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif

#define DEBUG if(true)

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
   first = NULL;
};

ListMap::ListMap( const ListMap& m )
{
   ///@todo Zaimplementowaæ metode
    if(m.first==NULL)//kopia pustego
    {
        first=NULL;
        return;
    }
    Node* aktualny=m.first;
    do
    {
        unsafe_insert(aktualny->data);
        aktualny=aktualny->next;
    }
    while(aktualny!=m.first);
};

ListMap::~ListMap()
{
   clear();
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
   ///@todo Uzupe³niæ kod
   iterator i;
   for(i=begin(); i!=end(); ++i)
   {
      if(i->first==entry.first)
        return std::make_pair(i, (bool)false);
   }
   i=unsafe_insert(entry);
        return std::make_pair(i, (bool)true);
}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
DEBUG std::cout<<"ListMap::unsafe_insert(const std::pair<Key, Val>& entry)"<<std::endl;
   ///@todo Uzupe³niæ kod
   //assert(0);
   Node* new_node_ptr=new Node(entry);
   if(first==NULL)
   {
       first=new_node_ptr;
       first->prev=first;
       first->next=first;
   }
   else
   {
       first->prev->next=new_node_ptr;//dolaczenie na koniec
       new_node_ptr->prev=first->prev;//wskazanie poprzedniego
       first->prev=new_node_ptr;//nowy wsk konca
       new_node_ptr->next=first;//wsk na poczatek
   }

   return iterator(first);
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
DEBUG std::cout<<"ListMap::find(const Key& k)"<<std::endl;
   ///@todo Zaimplementowaæ metode
   //assert(0);
    if(first==NULL)
    {
        return iterator(first);
    }
    Node* aktualny=first;
    do
    {
        if(aktualny->data.first==k)
        {
            return iterator(aktualny);
        }
        aktualny=aktualny->next;
    }
    while(aktualny!=first);
    return iterator(first->prev);//end
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
DEBUG std::cout<<"ListMap::find(const Key& k) const"<<std::endl;
   ///@todo Zaimplementowaæ metode
   //assert(0);
    if(first==NULL)
    {
        return const_iterator(first);
    }
    Node* aktualny=first;
    do
    {
        if(aktualny->data.first==k)
        {
            return const_iterator(aktualny);
        }
        aktualny=aktualny->next;
    }
    while(aktualny!=first);
    return const_iterator(first->prev);//end
}

// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli
// nie istnia³.
// @returns Referencje do wartoœci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
DEBUG std::cout<<"ListMap::operator[](const Key& k)"<<std::endl;
   ///@todo Zaimplementowaæ metode
   //assert(0);
    iterator i=find(k);
    return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
   return first==NULL;
}

// Zwraca iloœæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return 0;
}

// Zwraza iloœæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
   ///@todo Zaimplementowaæ metode
   return 1;  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return end();
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okreœla pierwszy element do usuniêcia, a last okreœla element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
   ///@todo Zaimplementowaæ metode
   //assert(0);

   return l;
}

// Usuwa element z mapy.
// @returns Iloœæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return 0;
}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
   ///@todo Zaimplementowaæ metode
   //assert(0);
    erase(begin(),end());
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return false;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
bool ListMap::info_eq(const ListMap& another) const
{
   ///@todo Zaimplementowaæ metode
   assert(0);
   return false;
}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
   ///@todo Zaimplementowaæ metode
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
   ///@todo Zaimplementowaæ metode
   return *this;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   ///@todo Zaimplementowaæ metode
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
   ///@todo Zaimplementowaæ metode
   return *this;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
   ///@todo Zaimplementowaæ metode
   return iterator(NULL);
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
   ///@todo Zaimplementowaæ metode
   return iterator(NULL);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
   ///@todo Zaimplementowaæ metode
   return iterator(NULL);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
   ///@todo Zaimplementowaæ metode
   return iterator(NULL);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk³ad map'y z implementacj¹ podobn¹ do std::map.
/// To jest jedynie przyk³ad!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszuj¹c¹.
template <class Key, class Val>
class SmallMap
{
   std::pair<Key, Val> tab[2];
   int isOcupied[2];
public:

   SmallMap()
   {
      for(unsigned i=0; i<2; ++i)
      {
         isOcupied[i]=0;
      }
   }

   typedef std::pair<Key, Val>* iterator;   ///< Ka¿dy wskaŸnik jest te¿ iteratorem.

   iterator begin() { return tab; }
   iterator end() { return tab+2; }

   Val& operator[](const Key& k)
   {
      static Val val;
      for(unsigned i=0; i<2; ++i)
      {
         if(isOcupied[i]&&tab[i].first==k)
            return tab[i].second;
      }
      // create
      for(unsigned i=0; i<2; ++i)
      {
         if(!isOcupied[i])
         {
            tab[i].first=k;
            isOcupied[i]=1;
            return tab[i].second;
         }
      }
      //std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      //assert(0);
      return val;   // Ma³o sensowne, ale to jest tylko przyk³¹d
   }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// Testy u¿ytkownika
void test()
{
   // A typedef used by the test.
   //typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   typedef ListMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;
DEBUG system("pause");
   m[2] = "Merry";
DEBUG system("pause");
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";
DEBUG system("pause");
   //for_each(m.begin(), m.end(), print );
   //system("PAUSE");
}

