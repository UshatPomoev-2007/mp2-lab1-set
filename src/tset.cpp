// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
    return(BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return(MaxPower);
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return(BitField.GetBit(Elem));
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (&s == this) {
        return(*this);
    }   
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField==s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int len = MaxPower > s.MaxPower ? MaxPower : s.MaxPower;
    TSet res(len);
    res.BitField = (*this).BitField | s.BitField;
    return(res);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.BitField.SetBit(Elem);
    return(res);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.BitField.ClrBit(Elem);
    return(res);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(MaxPower);
    res.BitField = (*this).BitField & s.BitField;
    return(res);
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(MaxPower);
    res.BitField = ~(*this).BitField;
    return(res);
}

// перегрузка ввода/вывода

std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
