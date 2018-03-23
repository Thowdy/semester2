#include <iostream>
#include <string>

using namespace std;

static string army="English"; //объявляем статические данные
static string insurgents="Polish";

class Unit //виртуальный класс юнита
{
public:
    int health;//здоровье
    Unit():health(10){}//конструтор по умолчанию
    Unit(int a): health(a){}//конструктор с параметром
    Unit(const Unit &other){this->health=other.health;} // конструктор копирования
    void showHealth(){cout<<"Unit health: "<<health<<endl;}; //функция показа здоровья
    ~Unit(){} //деструктор
};

class Soldier: virtual public Unit //класс наследник солдат
{
protected:
    int speed; //скорость юнита
public:
    int damage; //урон
    Soldier():damage(20),speed(10){} //конструтор по умолчанию
    Soldier(int a, int b, int c):Unit(a),damage(b),speed(c) {} //конструктор с параметром
    void nation(){cout<<insurgents<<endl;}  //нация юнита
    void showDamage(){cout<<"soldier damage: "<<damage<<endl;}
    void showSpeed(){cout<<"Soldier speed: "<<speed<<endl;}

    class citizen: virtual public Unit //вложенный класс фермера
    {
    public:
        void showHealth(){cout<<"hp fermer is: "<<health<<endl;} //только одна функция показа здоровья
    };
    ~Soldier(){}//деструктор
};

class Horse: virtual public Unit //класс лошади
{
protected:
    int speed;
public:
    Horse():speed(20){}//конструтор по умолчанию
    Horse(int a):speed(a){}//конструктор с параметром
    void showSpeed(){cout<<"Horse speed: "<<speed<<endl;}
    ~Horse(){}//деструктор
};

class Horseman :public Horse, public Soldier //класс всадника
{
private:
    int speed;
public:
    Horseman():speed(Horse::speed+Soldier::speed){}//конструтор по умолчанию
    void nation(){cout<<army<<endl;}
    void showDamage(){cout<<"Horseman damage: "<<damage<<endl;}
    void showSpeed(){cout<<"Horseman speed: "<<speed<<endl;}
    ~Horseman(){}//деструктор
};

class Battle :public Horseman // класс поединка
{
private:
    int Unit_1; //необходимая переменная
public:
    Battle():Unit_1(0){}//конструтор по умолчанию
    Battle(int first): Unit_1(first){} //конструктор с параметром
    void showBattle() //функция боя
    {
        cout<<"zhannaDark caused "<<damage<<" damage."<<endl;
        cout<<"achilles left "<<Unit_1<<" hp."<<endl;
    }

    friend Battle operator- (Battle&l, Battle& u1); //дружественная функция перегрузки
    ~Battle(){}//деструктор
};

Battle operator- (Battle&l, Battle& u1)//перегрузка оператора- для боя
    {
        return Battle (l.Unit_1-u1.Unit_1);
    }

int main()
{
    Soldier achilles(49,5,15);//выводим необходимые функции для солдата
    achilles.nation();
    achilles.showHealth();
    achilles.showDamage();
    achilles.showSpeed();

    cout<<endl;
    Horse sivka(40);//выводим необходимые функции для лошади
    sivka.showHealth();
    sivka.showSpeed();
    cout<<endl;

    Horseman zhannaDark;//выводим необходимые функции для всадника
    zhannaDark.nation();
    zhannaDark.showHealth();
    zhannaDark.showDamage();
    zhannaDark.showSpeed();
    cout<<endl;
    Battle Unit1(achilles.health);//выводим необходимые функции для боя
    Battle Unit2(zhannaDark.damage);
    Battle Unit3 = Unit1 - Unit2;
    Unit3.showBattle();
    cout<<endl;
    Soldier::citizen fermer;//выводим необходимые функции для фермера
    fermer.showHealth();

    return 0;
}
