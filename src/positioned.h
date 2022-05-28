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

#pragma once

#include "libs.h"
#include <utility>

/// <summary>
/// Class that will be created with objects that will probably be showed on board.
/// </summary>
class Positioned
{
public:
    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="posX">- Set where point will be on axle x. </param>
    /// <param name="posY">- Set where point will be on axle y. </param>
    /// <param name="sprite">- Specifies which character will illustrate the positioned object. </param>
    Positioned(unsigned int posX = 1, unsigned int posY = 1, char sprite = '*');

    /// <summary>
    /// Destructor.
    /// </summary>
    ~Positioned();

    /// <summary>
    /// That function can be used to set new position of point on axis X.
    /// </summary>
    /// <param name="newPosition">- Value that is going to be position.</param>
    void newPositionX(unsigned int newPosition);

    /// <summary>
    /// That function can be used to set new position fo point on axis Y.
    /// </summary>
    /// <param name="newPosition">- Value that is going to be position.</param>
    void newPositionY(unsigned int newPosition);

    /// <summary>
    /// Use it to get position of point.
    /// </summary>
    /// <param name="newPosition">- Pair of uints that will be the position of positioned.</param>
    void newPosition(std::pair<unsigned int, unsigned int> newPosition);

    /// <summary>
    /// Use it to get position of point on axis X.
    /// </summary>
    /// <returns>Position of point on axis X.</returns>
    unsigned int getPositionX() const;

    /// <summary>
    /// Use it to get position of point on axis Y.
    /// </summary>
    /// <returns>Position of point on axis Y.</returns>
    unsigned int getPositionY() const;

    /// <summary>
    /// Use it to get position of point.
    /// </summary>
    /// <returns>Two values - position on axle X and position on axle Y.</returns>
    std::pair<unsigned int, unsigned int> getPosition() const;

    /// <summary>
    /// Use it to get position of point on axis X before change.
    /// </summary>
    /// <returns>Position of point on axis X before change.</returns>
    unsigned int getOldPositionX() const;

    /// <summary>
    /// Use it to get position of point on axis Y before change.
    /// </summary>
    /// <returns>Position of point on axis Y before change.</returns>
    unsigned int getOldPositionY() const;

    /// <summary>
    /// Use it to get position of point before change.
    /// </summary>
    /// <returns>Two values - position on axle X and position on axle Y.</returns>
    std::pair<unsigned int, unsigned int> getOldPosition() const;

    /// <summary>
    /// That function can be used to set new position of point on axis X.
    /// </summary>
    /// <param name="newPosition">- Value that is going to be position.</param>
    void newSprite(char newSprite);

    /// <summary>
    /// Use it to get position of point on axis X.
    /// </summary>
    /// <returns>Position of point on axis X.</returns>
    char getSprite();

private:
    /// <summary>
    /// It's positon of point on axis X.
    /// </summary>
    unsigned int m_positionX;

    /// <summary>
    /// It's positon of point on axis Y.
    /// </summary>
    unsigned int m_positionY;

    /// <summary>
    /// It's positon of point on axis X before last change.
    /// </summary>
    unsigned int m_oldPositionX;

    /// <summary>
    /// It's positon of point on axis Y before last change.
    /// </summary>
    unsigned int m_oldPositionY;

    /// <summary>
    /// Specifies which character will illustrate the positioned object.
    /// </summary>
    char m_sprite;
};