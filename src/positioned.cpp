///////////////////////////////////////////////////////////
/// This is free and unencumbered software released into the public domain.
///
/// Anyone is free to copy, modify, publish, use, compile, sell, or
/// distribute this software, either in source code form or as a compiled
/// binary, for any purpose, commercial or non - commercial, and by any
/// means.
///
/// In jurisdictions that recognize copyright laws, the author or authors
/// of this software dedicate any and all copyright interest in the
/// software to the public domain.We make this dedication for the benefit
/// of the public at large and to the detriment of our heirs and
/// successors.We intend this dedication to be an overt act of
/// relinquishment in perpetuity of all present and future rights to this
/// software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
/// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
/// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
/// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
/// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
/// OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to < http://unlicense.org/ >
///////////////////////////////////////////////////////////

#include "positioned.h"

//define constructor
Positioned::Positioned(unsigned int posX, unsigned int posY, char sprite)
	:m_positionX(posX), m_positionY(posY), m_oldPositionX(posX), m_oldPositionY(posY), m_sprite(sprite)
{
}

//define constructor
Positioned::~Positioned()
{
}

//define setter
void Positioned::newPositionX(unsigned int newPosition)
{
	//set old position
	m_oldPositionX = m_positionX;

	//set new position
	m_positionX = newPosition;
}

//define setter
void Positioned::newPositionY(unsigned int newPosition)
{
	//set old position
	m_oldPositionY = m_positionY;

	//set new position
	m_positionY = newPosition;
}

//define setter
void Positioned::newPosition(std::pair<unsigned int, unsigned int> newPosition)
{
	//set old positions
	m_oldPositionX = m_positionX;
	m_oldPositionY = m_positionY;

	//set new positions
	m_positionX = newPosition.first;
	m_positionY = newPosition.second;
}

//define getter
unsigned int Positioned::getPositionX() const
{
	return m_positionX;
}

//define getter
unsigned int Positioned::getPositionY() const
{
	return m_positionY;
}

//define getter
std::pair<unsigned int, unsigned int> Positioned::getPosition() const
{
	return std::pair<unsigned int, unsigned int>(m_positionX, m_positionY);
}

unsigned int Positioned::getOldPositionX() const
{
	return m_oldPositionX;
}

unsigned int Positioned::getOldPositionY() const 
{
	return m_oldPositionY;
}

std::pair<unsigned int, unsigned int> Positioned::getOldPosition() const
{
	return std::pair<unsigned int, unsigned int>(m_oldPositionX, m_oldPositionY);
}

//define setter
void Positioned::newSprite(char newSprite)
{
	m_sprite = newSprite;
}

//define getter
char Positioned::getSprite()
{
	return m_sprite;
}
