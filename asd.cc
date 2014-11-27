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

/**
 * Tomasz Jakubczyk
 * grupa 3I3
 * data: 8.11.2014
 *
 * moja ListMap jest implementowana jako lista dwukierunkowa
 * wskaxnik na pierwszy element pamiętany jest przez pole first
 * wskaxnik na element za ostatnim zawsze jest na straznika
 * element->internalDataPointer wskazuje na straznika
 *
 *
 */

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/materialy/AISDI/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif

#define DEBUG if(false)

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
DEBUG std::cout<<"ListMap::ListMap()"<<std::endl;
    first=new Node(P(-1,"sentinel"));
    first->next=first;
    first->prev=first;
    first->internalDataPointer=first;
};

ListMap::ListMap( const ListMap& m )
{
    first=new Node(P(-1,"sentinel"));
    first->next=first;
    first->prev=first;
    first->internalDataPointer=first;
    Node* tmp=m.first;
    while(tmp->next!=tmp)
    {
        unsafe_insert(tmp->data);
        tmp=tmp->next;
    }
};

ListMap::~ListMap()
{
    clear();
    delete first;
    first=NULL;
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
DEBUG std::cout<<"ListMap::insert(const std::pair<Key, Val>& entry)"<<std::endl;
    iterator i;
    for(i=begin(); i!=end(); ++i)
    {//    <Key, Val>
        if(i->first==entry.first)//iterator Key == entry Key
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
    Node* new_node_ptr=new Node(entry);
    Node* sentinel=static_cast<Node*>(first->internalDataPointer);//dla czytelnosci
    Node* last=sentinel->prev;//zapamietanie starego ostatniego
    if(first==sentinel)
    {
        first=new_node_ptr;
        sentinel->prev=new_node_ptr;
        new_node_ptr->next=sentinel;
        new_node_ptr->prev=new_node_ptr;
    }
    else
    {
        sentinel->prev=new_node_ptr;//sentinel jest za ostatnim (1)
        new_node_ptr->next=sentinel;//za nowym jest sentinel (2)
        last->next=new_node_ptr;//nowy wstawiony za starym (3)
        new_node_ptr->prev=last;//za nowym jest stary ostatni (4)
    }
    new_node_ptr->internalDataPointer=sentinel;//kazdy moze byc pierwszym wiec wskazuje na sentinela
    return iterator(new_node_ptr);
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
DEBUG std::cout<<"ListMap::find(const Key& k)"<<std::endl;
    iterator i;
    for(i=begin(); i!=end(); ++i)
    {
DEBUG std::cout<<i->first<<" "<<k<<std::endl;
        if(i->first==k)//iterator Key == Key
        {
            return i;
        }
    }
    return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
DEBUG std::cout<<"ListMap::find(const Key& k)"<<std::endl;
    const_iterator i;
    for(i=begin(); i!=end(); ++i)
    {
        if(i->first==k)//iterator Key == Key
        {
            return i;
        }
    }
    return end();
}

// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli
// nie istnia³.
// @returns Referencje do wartoœci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
DEBUG std::cout<<"ListMap::operator[](const Key& k)"<<std::endl;
    iterator i=find(k);
    if(i==end())
    {
        i=unsafe_insert(P(k,"domyslna"));
    }
    return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
    return first==first->next;
}

// Zwraca iloœæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
    size_type l=0;
    for(const_iterator i=begin();i!=end();i++)
    {
        l++;
    }
    return l;
}

// Zwraza iloœæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
    if(find(_Key)==end())
    return 0;
    return 1;  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
DEBUG std::cout<<"ListMap::erase(ListMap::iterator i)"<<std::endl;
    iterator nastepny=i;
    nastepny++;
DEBUG std::cout<<nastepny->first<<" "<<nastepny->second<<std::endl;
    if(i==end())
    {
DEBUG std::cout<<"if(i==end())"<<std::endl;
        return end();
    }
DEBUG std::cout<<i->first<<" "<<i->second<<std::endl;
    if(i.node==first)
    {
DEBUG std::cout<<"if(i.node==first)"<<std::endl;
        first=i.node->next;
        i.node->next->prev=i.node->next->prev;
    }
    else
    {
        i.node->next->prev=i.node->prev;
        i.node->prev->next=i.node->next;
    }
    delete i.node;
    return nastepny;
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okreœla pierwszy element do usuniêcia, a last okreœla element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
DEBUG std::cout<<"ListMap::erase(ListMap::iterator f, ListMap::iterator l)"<<std::endl;
    iterator i=f;
    for(;i!=l;)
    {
        i=erase(i);
    }
    return l;
}

// Usuwa element z mapy.
// @returns Iloœæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
    iterator i=find(key);
    if(i==end())
    return 0;
    erase(i);
    return 1;
}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
    erase(begin(),end());
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
    ListMap::const_iterator i=begin();
    ListMap::const_iterator j=another.begin();
    if(size()!=another.size())
    {
DEBUG std::cout<<"if(size()!=another.size())"<<std::endl;
        return false;
    }
    for(; i!=end() && j!=another.end(); )
    {
        ++i;
        ++j;
DEBUG std::cout<<i->first<<" "<<j->first<<" "<<i->second<<" "<<j->second<<std::endl;
        if(i->first!=j->first || i->second!=j->second)//porownanie na tych samych pozycjach
        {
DEBUG std::cout<<"if(i->first!=j->first || i->second!=j->second)"<<std::endl;

            return false;
        }
    }
    return true;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
bool ListMap::info_eq(const ListMap& another) const
{
    ListMap::const_iterator i;
    ListMap::const_iterator j;
    if(size()!=another.size())//sa to mapy wiec jesli maja rozne rozmiary to musza roznic sie informacyjnie
    {
DEBUG std::cout<<"if(size()!=another.size())"<<std::endl;
        return false;
    }
    for(i=begin(); i!=end(); ++i)
    {
        j=another.find(i->first);//znajdz klucz
        if(j==another.end())
        {
DEBUG std::cout<<"if(j==another.end())"<<std::endl;
            return false;
        }
        if(i->second!=j->second)//porownaj wartosci
        {
DEBUG std::cout<<"if(i->second!=j->second)"<<std::endl;
            return false;
        }
    }
    return true;
}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
DEBUG std::cout<<"ListMap::const_iterator::operator++()"<<std::endl;
    node=node->next;
    return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
DEBUG std::cout<<"ListMap::const_iterator::operator++(int)"<<std::endl;
    const_iterator i=*this;
    ++(*this);
    return i;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
DEBUG std::cout<<"ListMap::const_iterator::operator--()"<<std::endl;
    node=node->prev;
    return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
DEBUG std::cout<<"ListMap::const_iterator::operator--(int)"<<std::endl;
    const_iterator i=*this;
    --(*this);
    return i;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
DEBUG std::cout<<"ListMap::begin()"<<std::endl;
    return iterator(first);
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
DEBUG std::cout<<"ListMap::begin() const"<<std::endl;
    return const_iterator(first);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
DEBUG std::cout<<"ListMap::end()"<<std::endl;
    Node* sentinel=static_cast<Node*>(first->internalDataPointer);
    return iterator(sentinel);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
DEBUG std::cout<<"ListMap::end() const"<<std::endl;
    Node* sentinel=static_cast<Node*>(first->internalDataPointer);
    return const_iterator(sentinel);
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
    //m.unsafe_insert(std::make_pair(1,"a"));
    //std::cout << m[1] << std::endl;
    //m[2];
   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";
   if(m.find(2)!=m.end())
   std::cout <<m.find(2)->second<< std::endl;
   std::cout <<m.find(4)->second<< std::endl;
   std::cout <<m.find(8)->second<< std::endl;
DEBUG system("pause");
    std::cout << "Wciskanie wartości" << std::endl;
    for(int i = 0; i < 20; i++)
    {
        m[i] = (char)('Z' + i);
    }
    m[1000] = "EXTRA";
//DEBUG system("pause");
    std::cout << m.size() << std::endl;
//DEBUG system("pause");
    /*
    std::cout << "Wypisywanie wartości" << std::endl;
    for(int i = -10; i < 10; i++)
    {
        std::cout << i << " ===> " << m[i] << std::endl;
    }
    */
//DEBUG system("pause");
    TEST_MAP m2(m);
//DEBUG system("pause");
    std::cout << m.size() << std::endl;
    std::cout << m2.size() << std::endl;
//DEBUG system("pause");
    if(m.info_eq(m2))
    {
        std::cout << "if(m.info_eq(m2))" << std::endl;
    }
//DEBUG system("pause");
    if(m2.struct_eq(m))
    {
        std::cout << "if(m2.struct_eq(m))" << std::endl;
    }
//DEBUG system("pause");


    ListMap::iterator itt = m2.begin();
    ListMap::iterator itt2 = m2.end();
//DEBUG system("pause");
    itt++;
    itt++;
    itt++;
    itt2--;
    itt2--;
    itt2--;
//DEBUG system("pause");
    m2.erase(itt, itt2);

    for(ListMap::iterator iter = m2.begin(); iter != m2.end(); iter++)
    {
        std::cout << iter -> first << "\t ===> \t\t" << iter -> second << std::endl;
    }

    std::cout << "m ma " << m2.size() << " elementów" << std::endl;
    std::cout << "ostatni " << (--(++m2.end())) -> second << std::endl;
    std::cout << "tysieczny " << m2.find(1000) -> second << std::endl;

    std::cout << "Koniec Testów!" << std::endl;

   //for_each(m.begin(), m.end(), print );
DEBUG system("PAUSE");
}

