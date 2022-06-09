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

#include "board.h"
#include <algorithm>
#include <ctime>
#include <ncurses.h>

Board::Board(unsigned int sizeX, unsigned int sizeY, char spaceChar, bool addFrames, bool replaceSpaceByFrame, char frameChar)
	:m_frames(addFrames), m_space(spaceChar), m_frame(frameChar)
{
	//Enlarge value to avoid problems
	if (sizeX < 2) sizeX = 2;
	if (sizeY < 2) sizeY = 2;

	if (addFrames && replaceSpaceByFrame)
	{
		if (sizeX < 4) sizeX = 4;
		if (sizeY < 4) sizeY = 4;
	}

	//Setting _sizes
	m_sizeX = sizeX;
	m_sizeY = sizeY;

	//Preparing to make board
	m_gamePool = vector< vector<char >();

	//Declaring lambda that will help loops
	auto replaceSpace = [addFrames, replaceSpaceByFrame]()
	{
		if (addFrames && replaceSpaceByFrame)
			return true;

		else
			return false;
	};

	//===Adding top frame===
	if (addFrames)
	{
		m_gamePool.emplace_back();
		for (int i = 0; i < sizeX && replaceSpace() || i < sizeX + 2 && !replaceSpace(); i++)
		{
			m_gamePool.back().push_back(frameChar);
		}
	}

	//===Adding board and if need be side frames===

	//Start of loop
	for (int i = 0; i < sizeY - 2 && replaceSpace() || i < sizeY && !replaceSpace(); i++)
	{
		m_gamePool.emplace_back();

		//Adding left frame
		if (addFrames) m_gamePool.back().push_back(frameChar);

		//Adding board
		for (int i = 0; i < sizeX - 2 && replaceSpace() || i < sizeX && !replaceSpace(); i++)
		{
			m_gamePool.back().push_back(spaceChar);
		}

		//Adding right frame
		if (addFrames) m_gamePool.back().push_back(frameChar);
	}
	

	//===Adding bottom frame===
	if (addFrames)
	{
		m_gamePool.emplace_back();
		for (int i = 0; i < sizeX && replaceSpace() || i < sizeX + 2 && !replaceSpace(); i++)
		{
			m_gamePool.back().push_back(frameChar);
		}
	}

	//Reparing sizes
	if (addFrames && !replaceSpaceByFrame)
	{
		m_sizeX += 2;
		m_sizeY += 2;
	}
}

vector< vector<char> > Board::getCharacters(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd) const
{
	//preparing vector
	vector< vector<char > toReturn;

	//checking variables
	specialCheckVariables(xStart, yStart, xEnd, yEnd);

	//main loop working on axles y
	for (unsigned int i = yStart; i < yEnd; i++)
	{
		//adding new vector
		toReturn.emplace_back();

		//loop working on axles x
		for (unsigned int j = xStart; j < xEnd; j++)
		{
			//pushing to vector right value
			toReturn.back().push_back(m_gamePool.at(i).at(j));
		}
	}
	
	//returning
	return toReturn;
}

void Board::changeCharacters(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, char replacement) const
{
	//checking variables
	specialCheckVariables(xStart, yStart, xEnd, yEnd);

	//main loop working on axles y
	for (unsigned int i = yStart; i < yEnd; i++)
	{
		//loop working on axles x
		for (unsigned int j = xStart; j < xEnd; j++)
		{
			//changing right element with replacement
			m_gamePool.at(i).at(j) = replacement;
		}
	}
}

void Board::changeCharacter(char replacement, unsigned int positionX, unsigned int positionY)
{
	//checking variable x
	checkVariableX(positionX, false);
	//checking variable y
	checkVariableY(positionY, false);

	//replacing
	m_gamePool.at(positionY).at(positionX) = replacement;
}

void Board::display(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd) const
{
	//getting characters
	vector< vector<char > v = getCharacters(xStart, yStart, xEnd, yEnd);

	//===displaying===
	
	//main loop working on axle y
	for (int i = 0; i < v.size(); i++)
	{
		//loop working on axle x
		for (int j = 0; j < v[i].size(); j++)
		{
			//displaying on console
			printw(&v[i][j]);
		}
		//making new line
		printw("\n");
	}
}

unsigned int Board::getRanNumInsideOnX(bool setSeed) const
{
	//setting good seed
	if (setSeed)
		srand(time(NULL));

	//checking does board have frames
	if (m_frames)
		//returning value
		return rand() % (m_sizeX - 2)+1;
	else
		//returning value
		return rand() % m_sizeX;
}

unsigned int Board::getRanNumInsideOnY(bool setSeed) const
{
	//setting good seed
	if (setSeed)
		srand(time(NULL));

	//checking does board have frames
	if (m_frames)
		//returning value
		return rand() % (m_sizeY - 2) + 1;
	else
		//returning value
		return rand() % m_sizeY;
}

std::pair<unsigned int, unsigned int> Board::getRanNumInside(bool setSeed) const
{
	//returning value
	return std::pair<unsigned int, unsigned int>(getRanNumInsideOnX(setSeed), getRanNumInsideOnY(setSeed));
}

unsigned int Board::getSizeX(bool withFrames) const
{
	//returning value without frames
	if (withFrames && m_frames)
		return m_gamePool.back().size()-2;

	//returning value with frames
	return m_gamePool.back().size();
}

unsigned int Board::getSizeY(bool withFrames) const
{
	//returning value without frames
	if (withFrames && m_frames)
		return m_gamePool.size() - 2;

	//returning value with frames
	return m_gamePool.size();
}

std::pair<unsigned int, unsigned int> Board::getSize(bool withFrames) const
{
	//returning value without frames
	if (withFrames && m_frames)
		return std::pair<unsigned int, unsigned int>(m_gamePool.back().size() - 2, m_gamePool.size() - 2);

	//returning value with frames
	return std::pair<unsigned int, unsigned int>(m_gamePool.back().size(), m_gamePool.size());
}

char Board::getCharOfSpace()
{
	return m_space;
}

bool Board::isOnFrame(unsigned int positionX, unsigned int positionY)
{
	//checks are there frames at all
	if (m_frames)
	{
		//return true if position is on frame X
		if (positionX == 0 || positionX == m_sizeX-1) return true;
		//return true if position is on frame Y
		if (positionY == 0 || positionY == m_sizeY-1) return true;
	}
	else
	{
		//return true if position is on frame X
		if (positionX == (unsigned int)-1 || positionX == m_sizeX) return true;
		//return true if position is on frame Y
		if (positionY == (unsigned int)-1 || positionY == m_sizeY) return true;
	}
	//returns value
	return false;
}


void Board::checkVariableX(unsigned int& position, bool takeFramesIntoAccount) const
{
	//cheking does m_frames equal true
	if (takeFramesIntoAccount && m_frames)
	{
		//cheking are start values too small
		if (position == 0) position = 1;
		//cheking are start values too big
		else if (position >= m_gamePool.back().size()) position = m_gamePool.back().size()-1;
	}
	else if (position >= m_gamePool.back().size())
	{
		//cheking are start values too big
		position = m_gamePool.back().size();
	}
}

void Board::checkVariableY(unsigned int& position, bool takeFramesIntoAccount) const
{
	//cheking does m_frames equal true
	if (takeFramesIntoAccount && m_frames)
	{
		//cheking are start values too small
		if (position == 0) position = 1;
		//cheking are start values too big
		else if (position >= m_gamePool.size()) position = m_gamePool.size()-1;
	}
	else if (position > m_gamePool.size())
	{
		//cheking are start values too big
		position = m_gamePool.size();
	}
}

void Board::specialCheckVariables(unsigned int& xStart, unsigned int& yStart, unsigned int& xEnd, unsigned int& yEnd, bool takeFramesIntoAccount, bool swap, bool zeroIsAll) const
{	
	//greating values is there are frames
	if (takeFramesIntoAccount && m_frames)
	{
		//replacing xStart
		if (xStart == 0)
			xStart++;
		//replacing yStart
		if (yStart == 0)
			yStart++;
	}


	//Declarating lambda that will help and bool variable that help lambda
	auto getSubtrahend = [takeFramesIntoAccount, this](){
		//returning 2 if there are rames
		if (takeFramesIntoAccount && m_frames)
			return 2;
		//returning 0
		else
			return 0;
	};


	//replacing zeros by biggest possible size if zeroIsllAll equals true
	if (zeroIsAll)
	{
		//replacing xEnd
		if (xEnd == 0)
			xEnd = m_gamePool.back().size() - getSubtrahend();

		//replacing yEnd
		if (yEnd == 0)
			yEnd = m_gamePool.size() - getSubtrahend();
	}
	//reducing values if that is necessity
	else
	{
		//replacing xEnd
		if (xEnd != 0) 
			xEnd -= getSubtrahend();

		//replacing yEnd
		if (yEnd != 0) 
			yEnd -= getSubtrahend();
	}
	

	//checking variables on x
	checkVariableX(xStart, false);
	checkVariableX(xEnd, false);

	//checking variables on y
	checkVariableY(yStart, false);
	checkVariableY(yEnd, false);

	//swaping values if need to
	if (xStart > xEnd && swap) std::swap(xStart, xEnd);
	if (yStart > yEnd && swap) std::swap(yStart, yEnd);

	//you can uncomment it to check is method working well
	//printw("Points: %u %u %u %u\n", xStart, yStart, xEnd, yEnd);
}