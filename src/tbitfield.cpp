// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	try {
		if (len < 0) {
			int except = 1;
			throw except;
		}
		BitLen = len;
		MemLen = len / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		if (len % 32 != 0) {
			MemLen++;
		};

		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}

	}
	catch (int except) {
		cout << "Error 1" << endl;
		throw;

	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	try {
		if (n < 0) {
			int except = 1;
			throw except;
		}
		if (n > BitLen) {
			int except = 1;
			throw except;
		}
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	catch (int except) {
		cout << "Error SetB" << endl;
		throw;
	}
	}

void TBitField::ClrBit(const int n) // очистить бит
{
	try {
		if (n < 0) {
			int except = 1;
			throw except;
		}
		if (n > BitLen) {
			int except = 1;
			throw except;
		}
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	catch (int except) {
		cout << "Error ClrB" << endl;
		throw;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	try {
		if (n < 0) {
			int except = 1;
			throw except;
		}
		if (n > BitLen) {
			int except = 1;
			throw except;
		}
		TELEM value = pMem[GetMemIndex(n)] & GetMemMask(n);
		if (value == 0) return 0;
		else return 1;
	}
	catch (int except) {
		cout << "Error GetB" << endl;
		throw;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this == bf)
		return *this;

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) return 0;
		}
		return 1;
	}
	else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) return 1;
		}
		return 0;
	}
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MaxBitLen;
	if (BitLen > bf.BitLen)
		MaxBitLen = BitLen;
	else MaxBitLen = bf.BitLen;

	TBitField tmp(MaxBitLen);

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MaxBitLen;
	if (BitLen > bf.BitLen)
		MaxBitLen = BitLen;
	else MaxBitLen = bf.BitLen;

	TBitField tmp(MaxBitLen);

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < tmp.MemLen - 1; i++)
	{
		tmp.pMem[i] = ~pMem[i];
	}
	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
	{
		if (!GetBit(i))
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char bit;
	while (i < bf.BitLen)
	{
		istr >> bit;
		if (bit == '0') bf.ClrBit(i);
		else if (bit == '1') bf.SetBit(i);
		else return istr;
		i++;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}