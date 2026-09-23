// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw("Error");
    }
    BitLen = len;
    if (len  % (sizeof(TELEM) * 8) == 0) {
        MemLen = len / (sizeof(TELEM) * 8);
    }
    else {
        MemLen = len / (sizeof(TELEM) * 8) + 1;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen;i++) {
        pMem[i] = (TELEM)0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen;i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[](pMem);
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{   
    return (n/(8*sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return ((TELEM)1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0||n > BitLen) {
        throw("Error");
}
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen) {
        throw("Error");
    }
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen) {
        throw("Error");
    }
    TELEM piece= pMem[GetMemIndex(n)] & GetMemMask(n);
    if (piece == 0) {
        return(0);
    }
    else {
        return(1);
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) {
        return(*this);
    }
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen;i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return(0);
    }
    for (int i = 0;i < MemLen;i++) {
        if (pMem[i] != bf.pMem[i]) {
            return(0);
        }
    }
    return(1);
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return(1);
    }
    for (int i = 0;i < MemLen;i++) {
        if (pMem[i] != bf.pMem[i]) {
            return(1);
        }
    }
    return(0);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField res(len);
    for (int i = 0; i < res.MemLen; i++) {
        TELEM a = (i < MemLen) ? pMem[i] : 0;//Подобное нужно, если размеры операндов не совпадают.
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        res.pMem[i] = a | b;
    }
    return (res);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len = BitLen > bf.BitLen ? BitLen : bf.BitLen;
    TBitField res(len);
    for (int i = 0; i < res.MemLen; i++) {
        TELEM a = (i < MemLen) ? pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        res.pMem[i] = a & b;
    }
    return (res);
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    int tail = sizeof(TELEM) * 8 * MemLen - BitLen;
    if (tail != 0) {
        res.pMem[MemLen - 1] = (res.pMem[MemLen - 1]) << tail >> tail;
    }
    return (res);
}

// ввод/вывод

std::istream &operator>>(std::istream &istr, TBitField &bf) 
{
    std::string s;
    istr >> s; 
    for (int i = 0; i < bf.BitLen; i++) {
        char c = s[i];
        int bitIndex = bf.BitLen - 1 - i;  
        if (c == '1') {
            bf.SetBit(bitIndex);
        }
        else {
            bf.ClrBit(bitIndex);
        }
    }
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
