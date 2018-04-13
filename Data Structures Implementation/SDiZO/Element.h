#pragma once
class Element
{
public:
	Element(int value);
	~Element();
	int value;
	Element *nextElement;
	Element *previousElement;

};

