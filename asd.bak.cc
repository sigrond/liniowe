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
 * wskaxnik na element za ostatnim zawsze jest NULL
 * first->internalDataPointer wskazuje na ostatni
 *
 * zakladam, ze wolno modyfikowac tylko te metody w ktorych jest to napisane,
 * a z tego wynika sporo ograniczeń
 * uznaje rowniez, ze lista rozni sie od stosu tym, ze jest na odwrot,
 * wiec nie wolno jej uzyc i first nie moze byc ostatni o ile nie jest jedyny
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

#define DEBUG if(true)

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////


ListMap::ListMap()
{
DEBUG std::cout<<"ListMap::ListMap()"<<std::endl;
    first = NULL;
}

ListMap::ListMap( const ListMap& m )
{
DEBUG std::cout<<"ListMap::ListMap( const ListMap& m )"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    if(m.first==NULL)//kopia pustego
    {
        first=NULL;
        return;
    }
    Node* aktualny=m.first;
    while(aktualny!=NULL && aktualny->next!=NULL && aktualny->next!=m.first)
    {
        unsafe_insert(aktualny->data);//chyba tak lepiej
DEBUG std::cout<<aktualny->prev->data.second <<std::endl;
DEBUG std::cout<<aktualny->data.second <<std::endl;
DEBUG std::cout<<aktualny->next->data.second <<std::endl;
        aktualny=aktualny->next;
//DEBUG std::cout<<size()<<std::endl;
//DEBUG system("pause");
    }
DEBUG std::cout<<aktualny->next->data.second <<std::endl;
DEBUG system("pause");
DEBUG std::cout<<"ListMap::ListMap( const ListMap& m )"<<std::endl;
}

ListMap::~ListMap()//tego tez nie ruszam
{
    DEBUG std::cout<<"ListMap::~ListMap()"<<std::endl;
   clear();
}

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
DEBUG std::cout<<"ListMap::insert(const std::pair<Key, Val>& entry)"<<std::endl;
    ///@todo Uzupe³niæ kod - zrobione
    iterator i;
    for(i=begin(); i!=end(); ++i)
    {//    <Key, Val>
        if(i->first==entry.first)//iterator Key == entry Key
        return std::make_pair(i, (bool)false);
    }
    i = unsafe_insert(entry);
    return std::make_pair(i, (bool)true);
}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)//na sam koniec listy
{
DEBUG std::cout<<"ListMap::unsafe_insert(const std::pair<Key, Val>& entry)"<<std::endl;
    ///@todo Uzupe³niæ kod - zrobione
    Node* new_node_ptr=new Node(entry);
    if(first==NULL)//jesli pusta
    {
DEBUG std::cout<<"if(first==NULL)"<<std::endl;
        first=new_node_ptr;//zaczepienie pierwszego elementu do xrodla
        first->internalDataPointer=first;//jedyny element jest pierwszym i ostatnim
        static_cast<Node*>(first->internalDataPointer)->next=new Node(P(0,"sentinel"),NULL,new_node_ptr);
    }
    new_node_ptr->next=static_cast<Node*>(first->internalDataPointer)->next;//nowy element zostanie wstawiony na "koniec"
    new_node_ptr->prev=static_cast<Node*>(first->internalDataPointer);//stary ostatni, jesli pierwszy to na siebie
    first->internalDataPointer=new_node_ptr;//zapamietanie ostatniego
    new_node_ptr->prev->next=new_node_ptr;//zapamietanie w poprzednim
    new_node_ptr->next->prev=new_node_ptr;
    //assert(0);
    return iterator(new_node_ptr);
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
DEBUG std::cout<<"ListMap::find(const Key& k)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    iterator i;
    for(i=begin(); i!=end(); ++i)
    {
        if(i->first==k)//iterator Key == Key
        {
            return i;
        }
    }
    //assert(0);
DEBUG std::cout<<"ListMap::find(const Key& k) return end();"<<std::endl;
    return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
DEBUG std::cout<<"ListMap::find(const Key& k) const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::const_iterator i;
    for(i=begin(); i!=end(); ++i)
    {
        if(i->first==k)//iterator Key == Key
        {
            return i;
        }
    }
    //assert(0);
    return end();
}

// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli
// nie istnia³.
// @returns Referencje do wartoœci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
DEBUG std::cout<<"ListMap::operator[](const Key& k)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    //assert(0);
    iterator i;
    i=find(k);//znajdx ten klucz
DEBUG std::cout<<"i=find(k);"<<std::endl;
    if(i==end())//jesli nie ma
    {
        i = unsafe_insert(ListMap::P(k,""));//wstaw pusty, zapewne bedzie np m[2] = "Merry";
    }
    return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
   return (first==NULL || first->next==NULL);
}

// Zwraca iloœæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
DEBUG std::cout<<"ListMap::size( ) const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::size_type licznik=0;
    Node* aktualny=first;
    while(aktualny!=NULL && aktualny->next!=NULL && aktualny->next!=first)
    {
DEBUG std::cout<<aktualny->data.second<<" ";
        licznik++;//zliczenie wszystkich nie NULLowych elementow
        aktualny=aktualny->next;
DEBUG std::cout<<aktualny->prev->data.second<<std::endl;
    }
    //assert(0);
    if(licznik>0)
        licznik--;
    return licznik;
}

// Zwraza iloœæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
DEBUG std::cout<<"ListMap::count(const Key& _Key) const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    //unsafe_insert jest metoda publiczna wiec uzytkownik moze dodac wiele wartosci o tym samym kluczu
    ListMap::size_type licznik=0;
    ListMap::const_iterator i;
    for(i=begin(); i!=end(); ++i)
    {
        if(i->first==_Key)//iterator Key == Key
        licznik++;//zliczenie wszystkich nie NULLowych elementow
    }
    return licznik;  // this is not a multimap - niby nie ale unsafe_insert jest
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
DEBUG std::cout<<"ListMap::erase(ListMap::iterator i)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
DEBUG std::cout<<i.node->data.second<<std::endl;
DEBUG system("pause");
    ListMap::iterator pierwszy_za;
    if(ListMap::empty())
    {
DEBUG std::cout<<"if(ListMap::empty())"<<std::endl;
        return i;
    }
    if(i.node->next==NULL || i.node->next==first)//koniec nie jest prawdziwym elementem i nie mozna go usuwac
    {
DEBUG std::cout<<"i.node->next==NULL || i.node->next==first"<<std::endl;
        return i;
    }
    if(i.node==ListMap::first)//jesli jest to pierwszy element
    {
DEBUG std::cout<<"i.node==ListMap::first"<<std::endl;
        i.node->next->internalDataPointer=i.node->internalDataPointer;//wsk na ostatni
        ListMap::first=i.node->next;//wsk na pierwszy
    }
    if(i.node->prev!=i.node)//jesli mialby z tylu samego siebie
    {
DEBUG std::cout<<"if(i.node->prev!=i.node)"<<std::endl;
        if(i.node->next!=NULL)
        {
DEBUG std::cout<<"if(i.node->next!=NULL)"<<std::endl;
            i.node->next->prev=i.node->prev;//element za i wskazujacy(prev) na i teraz wskazuje na element przed i
        }
        else
        {
DEBUG std::cout<<"if(i.node->next==NULL)"<<std::endl;
        }
        if(i.node->prev!=NULL)
        {
DEBUG std::cout<<"if(i.node->prev!=NULL)"<<std::endl;
DEBUG std::cout<<i.node->data.second<<std::endl;
DEBUG system("pause");
DEBUG std::cout<<i.node->next->data.second<<std::endl;
            Node* tmp=i.node->next;//teraz bypass z tylu i na jego przod
DEBUG std::cout<<"Node* tmp=i.node->next;"<<std::endl;
            i.node->prev->next=tmp;
DEBUG std::cout<<"Node* tmp=i.node->next;"<<std::endl;
        }
        else
        {
DEBUG std::cout<<"if(i.node->prev==NULL)"<<std::endl;
        }
    }
    else
    {
DEBUG std::cout<<"if(i.node->prev==i.node)"<<std::endl;
        i.node->next->prev=i.node->next;//poczatek w prev ma siebie
    }
DEBUG std::cout<<"pierwszy_za=i;"<<std::endl;
    pierwszy_za=i;
    pierwszy_za++;
    delete i.node;//usuniecie elementu wskazywanego przez i
    /*if(begin()==end())//lepsze beda 2 stany puste
    {
        delete end();//stan pusty jest bez straznika
        first=NULL;
        return ListMap::iterator(NULL);
    }*/
    //assert(0);
    return pierwszy_za;
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okreœla pierwszy element do usuniêcia, a last okreœla element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
DEBUG std::cout<<"ListMap::erase(ListMap::iterator f, ListMap::iterator l)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    iterator i;
    for(i=f; i.node!=NULL&&i!=l; ++i)//zakladam, ze f nie jest za l
    {
        erase(i);
    }
    //assert(0);
    return l;//zakladam tez, ze l jest poprawny
}

// Usuwa element z mapy.
// @returns Iloœæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
DEBUG std::cout<<"ListMap::erase(const Key& key)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    iterator i=find(key);
    if(i==end())
    {
        return 0;
    }
    erase(i);
    //assert(0);
    return 1;//tym razem skoro to ma byc mapa to nie szukam dalszych elementow
}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
DEBUG std::cout<<"ListMap::clear( )"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    iterator i=begin();
    while(i!=NULL)//zakladam, ze f nie jest za l
    {
        i=erase(i);
    }
    if(first!=NULL)
    {
        delete first;//zadbanie o zwolnienie straznika
        first=NULL;
    }
    //assert(0);
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
DEBUG std::cout<<"ListMap::struct_eq(const ListMap& another) const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::const_iterator i;
    ListMap::const_iterator j=another.begin();
    if(size()!=another.size())
    {
        return false;
    }
    for(i=begin(); i!=end() && j!=another.end(); ++i)
    {
        j++;
        if(i->first!=j->first || i->second!=j->second)//porownanie na tych samych pozycjach
        {
            return false;
        }
    }
    //assert(0);
    return true;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
bool ListMap::info_eq(const ListMap& another) const
{
DEBUG std::cout<<"ListMap::info_eq(const ListMap& another) const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::const_iterator i;
    ListMap::const_iterator j;
    if(size()!=another.size())
    {
        return false;
    }
    for(i=begin(); i!=end(); ++i)
    {
        j=another.find(i->first);//znajdz klucz
        if(j==another.end())
        {
            return false;
        }
        if(i->second!=j->second)//porownaj wartosci
        {
            return false;
        }
    }
    //assert(0);
    return true;
}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
DEBUG std::cout<<"ListMap::const_iterator::operator++()"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    if(node->next==NULL)//jesli ostatni ++end()
    {
        return *this;
    }
    node=node->next;//zwieksza i zwraca
    return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
DEBUG std::cout<<"ListMap::const_iterator::operator++(int)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::const_iterator i=*this;
    ++(*this);
    return i;//zwieksza ze wskazania, ale zwraca wczesniejsza kopie do operacji
}

//predekrementacja
ListMap::const_iterator& ListMap::const_iterator::operator--()
{
DEBUG std::cout<<"ListMap::const_iterator::operator--()"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    if(node==NULL)
    {
DEBUG std::cout<<"node==NULL"<<std::endl;
        return *this;
    }
    if(node->prev!=NULL)
    {
DEBUG std::cout<<"node->prev!=NULL"<<std::endl;
        node=node->prev;//zmniejsza, a jesli to pierwszy to i tak wskazuje na siebie
    }
DEBUG std::cout<<"return *this;"<<std::endl;
    return *this;
}

// postdecrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
DEBUG std::cout<<"ListMap::const_iterator::operator--(int)"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    ListMap::const_iterator i=*this;
    --(*this);//analogicznie do postinkrementacji
    return i;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
DEBUG std::cout<<"ListMap::begin()"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    /*if(ListMap::empty())
    {
        return NULL;
    }*/
    return iterator(first);
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
DEBUG std::cout<<"ListMap::begin() const"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    /*if(ListMap::empty())
    {
        return NULL;
    }*/
    return const_iterator(first);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
DEBUG std::cout<<"ListMap::end()"<<std::endl;
    ///@todo Zaimplementowaæ metode - zrobione
    if(first==NULL)
    {
DEBUG std::cout<<"first==NULL"<<std::endl;
        return iterator(first);
    }
    return iterator((static_cast<Node*>(first->internalDataPointer))->next);
    /*iterator i=begin();
    while(i.node->next!=NULL)
    {
        i++;
    }
    return i;*/
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
DEBUG std::cout<<"ListMap::end() const"<<std::endl;
    ///@todo Zaimplementowaæ metode
    if(ListMap::empty())
    {
        return NULL;
    }
    return const_iterator((static_cast<Node*>(first->internalDataPointer))->next);
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
   //m[2] = "Merry";
   //m[4] = "Jane";
   //m[8] = "Korwin";
   //m[4] = "Magdalena";
    std::cout << "Wciskanie wartości" << std::endl;
    for(int i = 1; i < 20; i++)
    {
        m[i] = (char)('Z' + i);
    }
    m[1000] = "EXTRA";
    std::cout << m.size() << std::endl;
//DEBUG system("pause");
    /*
    std::cout << "Wypisywanie wartości" << std::endl;
    for(int i = -10; i < 10; i++)
    {
        std::cout << i << " ===> " << m[i] << std::endl;
    }
    */
    TEST_MAP m2(m);
DEBUG system("pause");
    std::cout << m2.size() << std::endl;
DEBUG system("pause");


    ListMap::iterator itt = m2.begin();
    ListMap::iterator itt2 = m2.end();
    //itt++;
    //itt++;
    //itt++;
    //itt2--;
    //itt2--;
    //itt2--;
DEBUG system("pause");
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
   system("PAUSE");
}

