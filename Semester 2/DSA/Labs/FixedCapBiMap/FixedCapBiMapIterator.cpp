#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->current = 0;
}
/// Theta(1): BC = WC = TC

void FixedCapBiMapIterator::first() {
	this->current = 0;
}
/// Theta(1): BC = WC = TC

void FixedCapBiMapIterator::next() {
	if (this->current >= this->map.nrPairs)
	{
		throw exception();
	}
	else
	{
		this->current++;
	}
}
/// Theta(1): BC = WC = TC

TElem FixedCapBiMapIterator::getCurrent() {
	if (this->current >= this->map.nrPairs)
	{
		throw exception();
	}
	return this->map.elements[this->current];
}
/// Theta(1): BC = WC = TC;

bool FixedCapBiMapIterator::valid() const {
	if (this->current < this->map.nrPairs)
	{
		return true;
	}
	else
	{
		return false;
	}
}
///Theta (1): BC = WC = TC

void FixedCapBiMapIterator::previous()
{
	if (this->current == 0)
	{
		throw exception();
	}
	else
	{
		this->current--;
	}
}