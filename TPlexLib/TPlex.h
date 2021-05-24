#pragma once
#include "TBase.h"
#include "TPoint.h"
#include "TLine.h"
#include "TSquare.h"
#include "TCanvas.h"
#include "Stack.h"

#include <string>
#include <iostream>

class TPlex : public TBase {
protected:
	TBase* left;
	TBase* right;
public:
	TPlex();
	TPlex(TPoint* a, TPoint* b);
	TPlex(char* s);
	TPlex(const TPlex& p);

	virtual void Print();
	virtual double GetVal(int i);
	virtual void SetVal(double val, int i);
	virtual double& operator[](char* name);
	virtual double& operator[](int i);

	virtual TBase* GetChild(int i);
	virtual void SetChild(TBase* c, int i);
	virtual TBase* PrintAll();
	TBase* GetLeft();
	TBase* GetRight();

	TPlex* GetLeftPlex();
	TPlex* GetRightPlex();

	void SetLeft(TBase* x);
	void SetRight(TBase* x);
	bool AddLine(TPoint* a, TPoint* b);

	virtual int GetChildCount()
	{
		return 2;
	}

	virtual TBase* Clone();

	friend std::ostream& operator<<(std::ostream& out, const TPlex& _plex);
};

TPlex::TPlex() 
{
	left = new TPoint();
	right = new TPoint();
}

TPlex::TPlex(char* s)
{
	int count = 1;
	int cc = 0;
	int i = 0;
	int j = 0;


	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			count++;
		i++;
		cc++;
	}


	if (count % 2 != 0 && count < 4)
	{
		throw "Error";
	}

	double* mass = new double[count];

	std::string temp = "";


	i = 0;
	for (int q = 0; q < cc; q++)
	{
		if (s[q] != ' ' && s[q] != ',')
			temp += s[q];
		else if (temp != "")
		{
			mass[j] = atoi(temp.c_str());
			j++;
			temp = "";
		}
	}


	TPoint *a = new TPoint(mass[0], mass[1]);
	TPoint *b = new TPoint(mass[2], mass[3]);

	left = a;
	right = b;

	for (int q = 4; q < count; q++)
	{
		TPoint *temp_left = new TPoint(mass[q-2], mass[q-1]);
		TPoint *temp_right = new TPoint(mass[q], mass[q + 1]);

		this->AddLine(temp_left, temp_right);
		q++;
	}
}

TPlex::TPlex(TPoint* a, TPoint* b) 
{
	if (a != NULL)
		left = a;

	if (b != NULL)
		right = b;
}

TPlex::TPlex(const TPlex& p) 
{
	left = p.left->Clone();
	right = p.right->Clone();
}

void TPlex::Print()
{
	PrintAll();
};

TBase* TPlex::PrintAll()
{
	std::cout << *this << "\n";
	return 0;
}

double TPlex::GetVal(int i) {
	throw - 1;
}

void TPlex::SetVal(double val, int i) {
	throw - 1;
}

double& TPlex::operator[](char* name) {
	throw - 1;
}

double& TPlex::operator[](int i) {
	throw - 1;
}

TBase* TPlex::GetChild(int i) {
	if (i == 0)
		return left;
	else if (i == 1)
		return right;
	else
		throw - 1;
}

void TPlex::SetChild(TBase* c, int i)
{
	if (i == 0)
		left = c;
	else if (i == 1)
		right = c;
	else
		throw - 1;
}

TBase* TPlex::GetLeft()
{
	return left;
}
TBase* TPlex::GetRight()
{
	return right;
}

TPlex* TPlex::GetLeftPlex()
{
	return dynamic_cast<TPlex*>(left);
}
TPlex* TPlex::GetRightPlex()
{
	return dynamic_cast<TPlex*>(right);
}

void TPlex::SetLeft(TBase* x)
{
	left = x;
}
void TPlex::SetRight(TBase* x)
{
	right = x;
}
bool TPlex::AddLine(TPoint* a, TPoint* b)
{
	TStack<TBase*> stack(200);
	stack.Push(this);
	bool result = false;

	while (!stack.IsEmpty())
	{

		TBase* top_base = stack.Get();
		TBase* right_base = top_base->GetChild(0);
		TBase* left_base = top_base->GetChild(1);


		if (right_base->GetChildCount() != 0)
		{
			stack.Push(right_base);
		} 
		else if (right_base == a)
		{

			TPlex* new_plex = new TPlex(a, b);
			top_base->SetChild(new_plex, 0);
			result = true;
			break;
		}

	
		if (left_base->GetChildCount() != 0)
		{
			stack.Push(left_base);
		}
		else if (left_base == b)
		{
		
			TPlex* new_plex = new TPlex(b, a);
			top_base->SetChild(new_plex, 1);
			result = true;
			break;
		}
	}
	return result;
}

TBase* TPlex::Clone()
{
	return new TPlex(*this);
}

std::ostream& operator<<(std::ostream& out, const TPlex& _plex)
{
	TBase* base = const_cast<TPlex*>(&_plex);
	TPoint* point_first = NULL;
	TPoint* point_second = NULL;


	TStack<TBase*> stack(200);
	stack.Push(base);

	while (!stack.IsEmpty())
	{

		base = stack.Get();

		while (point_first == NULL)
		{

			TBase* left_base = base->GetChild(0);
			TPlex* plex = dynamic_cast<TPlex*>(left_base);
			if (plex == NULL)
			{

				point_first = dynamic_cast<TPoint*>(left_base);
			}
			else
			{

				stack.Push(base);
				base = left_base;
			}
		}

		while (point_second == NULL)
		{

			TBase* right_base = base->GetChild(1);
			TPlex* plex = dynamic_cast<TPlex*>(right_base);

			if (plex == NULL)
			{
	
				point_second = dynamic_cast<TPoint*>(right_base);
			}
			else
			{

				stack.Push(base);
				base = right_base;
			}
		}


		if (point_first != NULL && point_second != NULL) 
		{

			out << "Point left: " << *point_first << "\n";
			out << "Point right: " << *point_second << "\n\n";
			TBase* tmp_base = point_second;
			

			if (!stack.IsEmpty()) 
			{

				base = stack.Get(); 
	
				TBase* base_left = base->GetChild(0);
				TBase* base_right = base->GetChild(1);

				TPlex* plex_left = dynamic_cast<TPlex*>(base_left);
				TPlex* plex_right = dynamic_cast<TPlex*>(base_right);

		
				if (plex_left != NULL && plex_right != NULL)
				{
				
					TPlex* plex_new = new TPlex(point_second, 0);
				
					plex_new->SetChild(base_right, 1);
					
					stack.Push(plex_new);
				
					point_second = NULL;
					point_first = NULL;
				}
				else 
				{
					if (plex_left != NULL) 
					{
						point_first = dynamic_cast<TPoint*>(tmp_base);
						point_second = NULL;
					}
					else 
					{
						point_second = dynamic_cast<TPoint*>(tmp_base);
						point_first = NULL;
					}

					stack.Push(base);
				}
			}
		}
	}
	return out;
}