// Operátorok átdefiniálása

// Először nem kell azzal foglalkozni, hogy az operátorok mit csinálnak.
// Először csak annyit kell csinálniuk, hogy kiírjanak valamit a képernyőre, azaz átdefiniáljuk őket úgy,
// hogy értelmes művelet helyett valami hülységet csináljanak.
// Valójában a feladat nagy része ennyiből áll, át kell definiálni operátorokat barom módon és ennyi :D
// A kimenetet előre megírt makrók át fogják alakítani, teljesen idióta módon, ezzel sem kell foglalkozni.

// A feladat lényege, hogy lásd, hogy mikor hívodik konstruktor, destruktor, lásd, hogy hogyan lehet átdefiniálni operátorokat.
// Az, hogy mit csinálnak, az elején még MINDEGY! Utána is csak párat kell normálisan megírni.

#include <iostream>
#include <iomanip>
#include <cstring>

#define ELKESZULT 4 // Ez kizárólag arra szolgál, hogy mennyi kódszegmens hajtódjon végre, hogy több átdefiniált operátor működését is lásd

// 3. Feladat Definiálja a NEW makrót és figyelje meg a new, delete operatorok működését!
#define NEW         // Azért, hogy a lentebb lévő #ifdef NEW kódrész lefusson.

using std::cout;
using std::endl;

char mem1[1024];			// ezt a területet adja vissza a new. Ez egy faszság, de el kell fogadni, a new operátor sem működik normálisan, vonatkoztass el attól, hogy valójában mit csinál.
char mem2[1024];			// ezt a területet adja vissza a new[]. Szintén baromság.


/// Trükkös makrók, nem kell megértenie
#define _(x) cout << std::setiosflags(std::ios::left) << std::setw(20) << #x << " //";  x
#define __(x,y) cout << #x << " , " << std::setiosflags(std::ios::left) << std::setw(16) << #y << " //";  x, y
#define E cout << endl;


// A mûveletek bemutatatása a cél. Nem cél az értelmes megvalósítás. Értsd: az egész egy értelmetlen katyvaszos faszság,a mit szebi lusta volt normálisan megcsinálni.
// Az operatorok visszatérési értéke void. Természetesen ez sokszor nem áll összhangban szokásos mûködéssel.
// Szükség esetén ezt változtassa meg!
// %A kétoperandusú operátorok jobb oldali operandusát mindig konstans referenciaként adjuk át, bár ez is megváltoztatható lenne.

struct A {
    int  adat;              // adattag.  Az elõre elkészített kódban nincs funkciója
    enum { piros, zold };	// csak azért, hogy a :: meghívható legyen egy példára. Értsd: ennek sincs itt semmi értelme!

    // Konstruktor.
    // Kiírja, hogy mit hoz létre
    A(int i = -1)     {
        adat = i;
        cout << "  " << this << " letrejott" << endl;
    }

    // Másoló konstruktor.
    // Kiírja, hogy mit, hova másol
    A(const A& a)         {
        cout << "  " << this << " masolat errol: " << &a << endl;
    }

    // Értékadó operátor.
    // Kiírja, hogy kinek mit ad értékül
    // Ez az eredeti állapot kikommentezve
    // Alatta az átdefiniált egy későbbi feladathoz
    // Az eredeti az égvilágon semmit nem csinál, csak szöveget ír ki
    /*void operator=(const A& a) {
        cout << "  " << this << " ertet kap innen: " << &a << endl;
    }*/

    // Átdefiniált operator=
    A& operator=(const A& a) {  // A visszatérési érték referencia, hogy láncolható legyen ( a = b = c; )
        adat = a.adat;
        cout << "  ertekadas" << endl;    //kiírok valami, hogy a zseniális makróval működjön továbbra is a parancssorban a megjelenítés
        return *this;           // A this egy automatikusan létrejövő pointer, ami az aktuális objektumra mutat.
                                // Azért *this, mert pointerből nem tudok referenciát csinálni, így a this pointert dereferálom
    }

    // Desruktor
    ~A()                  {
        cout << "  " << this << " megszunt" << endl;
    }

    // Kétoperandusú * operátor (szorzás)
    void operator*(const A& a) {
        cout << "  " << this << " * " << &a << endl;
    }

    // Egyoperandusú + operátor
    void operator+()      {
        cout << "  +" << this << endl;
    }

    /// operátor ->
    /// Leginkább okos pointernek használható.
    /// Ez az egyik kakukktojás, mert nehezen használható másra.
    /// Érvényes címet kell, hogy visszaadjon a struktúrára, és nem az adattagra.
    /// Az adattag nem jelenik meg a szintaxisban, mert a -> egyoperandusú operátor.

    //Értsd: ne foglalkozz azzal, hogy baromság!

    A    *operator->()    {
        cout << "  " << this << " visszadta ezt: " << this << endl;
        return this;
    }

// A 7, 8, 9 feladatoknál azt nézd meg, hogy mi íródik ki "kommentbe" (a parancssorban) a konstruktorok, destruktorok, new es delete hivasakor

#ifdef NEW
    /// operátor new
    /// A másik kakukktojás, mert nem nagyon használható másra, ráadásul statikus tagfüggvény.
    /// Csak void* lehet és kötelezõ visszaadni egy pointert, amivel mindenképpen meghívja
    /// az osztály konstruktorát. Így a visszaadott címnek és a hozzá tartozó területnek érvényesnek kell lennie.

    //Értsd: ezzel se foglalkozz, mert totális baromság. Annyit érts meg, hogy ezt is át lehet definiálni.

    static void *operator new(unsigned int size) {
        cout << "  new size: " << size << " return: " << (void*)mem1 << endl;
        return mem1;
    }

    /// operátor new[]
    /// Újabb kakukktojás, mert nem nagyon használható másra, ráadásul ez is statikus tagfüggvény.
    /// Csak void* lehet és kötelezõ visszaadni egy pointert.
    /// A visszaadott címnek és a hozzá tartozó területnek érvényesnek kell lennie, mert a területre beírja
    /// az tömb méretét, majd meghívja minden elemre a konstruktort, hogy minden elem létrejöjjön.

    //Értsd: ne foglalkozz azzal, hogy baromság! Teljesen értelmetlen dolgot csinál, de nem ez a lényeg.

    static void *operator new[](unsigned int size) {
        cout << "  new[] size: " << size << " return: " << (void*)mem2 << endl;
        return mem2;
    }

    /// operátor delete
    /// Újabb kakukktojás, mert nem nagyon használható másra (ez is statikus).
    /// A paramétere csak void* lehet. A destruktort meghívja a pointerrel.
    /// Csak ezután futtatja le a programozott törzset

    // Szokásos

    static void operator delete(void *p) {

    }

    /// operátor delete[]
    /// Újabb kakukktojás, mert nem nagyon használható másra (ez is statikus).
    /// A paramétere csak void* lehet. Meghívja minden elemre a destruktort, hogy minden elem megszûnjön.
    /// A darabszámot egyébként kapott memóriacímrõl veszi!
    /// Csak ezután futtatja le a programozott törzset

    // Szokásos

    static void operator delete[](void *p) {

    }
#endif // NEW

    /// Vesszõ operátor

    // Ez sem csinál most semmit

    void operator,(const A& a)  {
        cout << "  " << this << " , " << &a << endl;
    }

    // Na most következnek azok az operátorok, amik átdefiniálhatsz.
    // Nem kell értelmes dolgot csinálniuk először.
    // Alapból be lett állítva nekik valami működés, ezt kell átírni


    // ++ operátor átdefiniálva. Először a 10. feladatban semmit nem csinál, csak kiír
    void operator++(int) { /// A++ (post)
        cout << "  " << this << "++" << endl;
    }

    //Ez sem csinál semmit, csak átdefiniálom, hogy kiírjon valamit a képernyőre
    /*
    void operator++() { /// ++A (pre)
        cout << "  " << "++" << this << endl;
    }
    */
    //Ez már ténylegesen csinál valamit, az objektumban lévő változót növeli
    void operator++() { /// ++A (pre)
        adat++;         // vagy this->adat++
                        // mindegy, mert a this automatikusan jön létre, és ha nem írod oda,
                        // akkor is tudja a fordító, hogy arra az objektumra gondolsz,
                        // amin alkalmazod az operátort
        cout << "  ++ operator" << endl;    // azert, hogy a parancssorban lassam, mikor hajtodik vegre
    }

    //Az alábbiak sem csinálnak értelmes dolgot

    void operator--(int) { /// A-- (post)
        cout << "  " << this << "--" << endl;
    }

    void operator--() { /// --A (pre)
        cout << "  " << "--" << this << endl;
    }


    //ezeket nem definiálom át, mert lusta vagyok és a feladat sem kéri mindet

    operator int()              { E return 0;} ///< (int) cast
    void operator()()           { E } ///< függvényhívás

    // Ezt átdefiniálom, hogy értelmes legyen
    A operator+(const A& a)  { ///< Kétoperandusú + operátor   // Azért objektumot adok vissza, hogy lácolható lehessen ( a = b + c + d; )
        A temp(adat + a.adat);       //ugyanaz, mintha ezt írnám: A temp(this->adat + a.adat);
        cout << "  ketoperandusu + operator" << endl;   // azert, hogy a parancssorban lassam, mikor hajtodik vegre
        return temp;
    }

    // Ugyanígy a kivonásnál

    A operator-(const A& a)        { ///< Kétoperandusú - operátor
        A temp(adat - a.adat);
        cout << "  ketoperandusu - operator" << endl;   // azert, hogy a parancssorban lassam, mikor hajtodik vegre
        return temp;
    }

    //hasonlóképp, csak itt egy operandus van

    A operator-()            { ///< Egyoperandusú - operátor
        A temp(-adat);
        cout << "  egyoperandusu - operator" << endl;   // azert, hogy a parancssorban lassam, mikor hajtodik vegre
        return temp;
    }


    // Ezeket hagyom a francba

    void operator[](int i)      { E } ///< indexelés
    void operator*()            { E } ///< Egyoperandusú * operátor (indirekció)
    void operator/(const A& a)  { E } ///< / operátor
    void operator%(const A& a)  { E } ///< % operátor
    void operator^(const A& a)  { E } ///< ^ operátor
    void operator&(const A& a)  { E } ///< Kétoperandusú & (bitenkénti és)
    void operator&()            { E } ///< Egyoperandusú & (címképzés)
    void operator|(const A& a)  { E } ///< | operátor
    void operator~()            { E } ///< ~ operátor
    void operator!()            { E } ///< ! operátor
    void operator<<(const A& a) { E } ///< << operátor
    void operator>>(const A& a) { E } ///< >> operátor
    void operator<(const A& a)  { E } ///< < operátor
    void operator>(const A& a)  { E } ///< > operátor
    void operator<=(const A& a) { E } ///< <= operátor
    void operator>=(const A& a) { E } ///< >= operátor
    void operator==(const A& a) { E } ///< == operátor
    void operator!=(const A& a) { E } ///< == operátor

    // Ezt megvalósítom

    void operator+=(const A& a) { ///< += operátor
        adat += a.adat;
        cout << "  += operator" << endl;    // because fuck you that's why
        return;
    }

    // Az összes többit hagyom a francba

    void operator-=(const A& a) { E } ///< -= operátor
    void operator*=(const A& a) { E } ///< *= operátor
    void operator/=(const A& a) { E } ///< /= operátor
    void operator%=(const A& a) { E } ///< %= operátor
    void operator^=(const A& a) { E } ///< ^= operátor
    void operator&=(const A& a) { E } ///< &= operátor
    void operator|=(const A& a) { E } ///< |= operátor
    void operator<<=(const A& a){ E } ///< <<= operátor
    void operator>>=(const A& a){ E } ///< >>= operátor
    void operator&&(const A& a) { E } ///< && operátor
    void operator||(const A& a) { E } ///< || operátor
};

/**
 * Minden operator meghívásra kerül. Azok is, amelyek nem definiálhatók át.
 * Melyek ezek?
 * Az _ makró az utasítás kiírását végzi.
 */
int main() {
_(  A a(1);                 )
_(  A b(2);                 )
_(  A c = b;                )
//-----------------------
_(  a++;                    )
_(  b--;                    )
_(  a[13];                  )
_(  a();                    )
_(  a.adat = 5;             ) E
_(  a->adat = 5;            )
_(  A::piros;               ) E
//-----------------------
#if ELKESZULT > 1
_(  sizeof(b);              ) E
_(  ++b;                    )
_(  --a;                    )
_(  &a;                     )
_(  *a;                     )
_(  +a;                     )
_(  -a;                     )
_(  ~a;                     )
_(  !a;                     )
_(  (int)a;                 )
#endif // ELKESZULT > 1
#ifdef NEW
_(  A *p = new A;           )
_(  A *pt = new A[2];       )
_(  delete p;               )
_(  delete[] pt;            )

#endif
//-----------------------
_(  a * b;                  )
#if ELKESZULT > 2
_(  a / b;                  )
_(  a % b;                  )
//-----------------------
_(  a + b;                  )
_(  a - b;                  )
//-----------------------
_(  a << b;                 )
_(  a >> b;                 )
//-----------------------
_(  a < b;                  )
_(  a <= b;                 )
_(  a > b;                  )
_(  a >= b;                 )
//-----------------------
_(  a == b;                 )
_(  a != b;                 )
//-----------------------
_(  a & b;                  )
//-----------------------
_(  a ^ b;                  )
//-----------------------
_(  a | b;                  )
//-----------------------
_(  a && b;                 )
//-----------------------
_(  a || b;                 )
//-----------------------
_(  a ? a : b;              ) E
//-----------------------
#endif // ELKESZULT > 2
_(  a = b;                  )
#if ELKESZULT > 3
_(  c = a + b - b;          )   // Itt próbálom ki, hogy láncolható a +, - operátor
_(  a *= b;                 )
_(  a /= b;                 )
_(  a %= b;                 )
_(  a += b;                 )
_(  a -= b;                 )
_(  a &= b;                 )
_(  a ^= b;                 )
_(  a |= b;                 )
_(  a <<= b;                )
_(  a >>= b;                )
#endif // ELKESZULT > 3
//-----------------------
__(  a , b;                 )
//-----------------------
    return 0;
}
