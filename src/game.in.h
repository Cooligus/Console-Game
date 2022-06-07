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

#include "config.h"
#include "board.h"
#include "enemies.h"
#include "direction.h"
#include <fstream>

/// <summary>
/// Game class.
/// </summary>
class Game 
{
public:
    /// <summary>
    /// First type of constructor.
    /// </summary>
    /// <param name="sizeX">- Width of board.</param>
    /// <param name="sizeY">- Height of board.</param>
    /// <param name="spaceChar">- Character that will be used to create space of board.</param>
    /// <param name="addFrames">- Says does board will have frames.</param>
    /// <param name="replaceSpaceByFrame">- If it's true frames will contains in sizeX and sizeY and for this reason theese values have to equal 4 or more.</param>
    /// <param name="frameChar">- Character that will be used to create frames of board.</param>
    /// <param name="playerPositionX">- Position of player on board on axle x.</param>
    /// <param name="playerPositionY">- Position of player on board on axle Y.</param>
    /// <param name="playerSprite">- Character that will be used to create player.</param>
    /// <param name="pointSprite">- Character that will be used to create point.</param>
    Game(unsigned int sizeX = @sizeX_DEF@, unsigned int sizeY = @sizeY_DEF@, unsigned int playerPositionX = 0, unsigned int playerPositionY = 0, unsigned int enemiesAmount = @enemiesAmount_DEF@, bool addFrames = @addFrames_DEF@, bool replaceSpaceByFrame = @replaceSpaceByFrame_DEF@, char spaceChar = '@spaceChar_DEF@',  char frameChar = '@frameChar_DEF@',  char playerSprite = '@playerSprite_DEF@', char pointSprite = '@pointSprite_DEF@', char enemySprite = '@enemySprite_DEF@');
    
    /// <summary>
    /// Second type of constructor.
    /// </summary>
    /// <param name="configuration">- config object with all stuffs.</param>
    Game(nlohmann::json configuration);

    /// <summary>
    /// Destructor.
    /// </summary>
    ~Game();
    
    /// <summary>
    /// Makes a new "frame" of game.
    /// </summary>
    /// <returns>True if game continues or false if not.</returns>
    bool newFrame();

    /// <summary>
    /// It's drawing a board on console and if cleanBoard is true, clearing a last show of board.
    /// </summary>
    /// <param name="cleanBoard">- If it's true function cleans console. It's using system("cls").</param>
    /// <param name="showPosition">- If it's true function displays position of player under board.</param>
    void show(bool cleanBoard = true, bool showPoints = true, bool showPosition = false);
    
    /// <summary>
    /// It's telling do game has been ended. It's ending when player give 'e' character.
    /// </summary>
    /// <returns>True if game has been ended false if not.</returns>
    bool isEnded();

private:

    /// <summary>
    /// Set last index of enemies array if it is smaller than 0 or is bigger than biggest index.
    /// </summary>
    /// <param name="index">- Index to rapair.</param>
    /// <returns>Unchanged index or last possible.</returns>
    bool repairIndex(int& index);

    /// <summary>
    /// Special method for constructor that prepares board and not only
    /// </summary>
    /// <param name="playerPositionX">- Position of player on board on axle x.</param>
    /// <param name="playerPositionY">- Position of player on board on axle Y.</param>
    /// <param name="playerSprite">- Character that will be used to create player.</param>
    /// <param name="pointSprite">- Character that will be used to create point.</param>
    void prepareBoard(unsigned int playerPositionX, unsigned int playerPositionY, char playerSprite, char pointSprite, char enemySprite);

    /// <summary>
    /// Setup positions and characters of player, enemies and point.
    /// </summary>
    /// <param name="cleanObjects">- Whether trace of positioned objects have to be cleaned.</param>
    /// <param name="resetPoints">- Whether method have to reset points.</param>
    void setupObjects(bool cleanObjects = true, bool resetPoints = true);

    /// <summary>
    /// Draw character on board.
    /// </summary>
    /// <param name="toDraw">Object you want to draw.</param>
    void drawCharacter(Positioned toDraw);

    /// <summary>
    /// Cleans old position of Positioned.
    /// </summary>
    /// <param name="toClean">- m_point or m_player or enemy</param>
    void cleanTraceOfPositioned(Positioned toClean);

    /// <summary>
    /// It's getting a character, checking it out and then changing position of player.
    /// </summary>
    /// <param name="character">- Character from keyboard. A - left, W - up, D - right, S - down.</param>
    bool makeMove(char character);

    /// <summary>
    /// Set new position of all enemies on board.
    /// </summary>
    bool moveEnemies();

    /// <summary>
    /// Make new point's position.
    /// <param name="enemy">- If true there will be spawned enemy or point if false.</param>
    /// </summary>
    /// <param name="index">- Index of enemy that will get new position (it's last if value is bigger than size or is lesser than 0).</param>
    void spawnPositioned(bool enemy = false, int index = -1);

    /// <summary>
    /// Function made for spawnPoint() function use only. Tells is point in 'free space' (not on enemy or player)
    /// </summary>
    /// <param name="enemy">- If true there will be checked enemy or point if false.</param>
    /// <param name="enemy">- Index of enemy if enemy is checking out.</param>
    /// <returns> Wether positioned is free or not.</returns>
    bool isPositionedFree(bool enemy = false, int index = -1);

    /// <summary>
    /// It's checking out position of point and player and if they equal it's generating new position of point if makeNewPosition is true.
    /// </summary>
    /// <param name="addPoints">- If it's true and positions of m_point and m_player equal m_points are incrasing. Else it's not.</param>
    /// <param name="respawnEnemies">- Whether method have to set new position of enemy if it meets point or player.</param>
    bool checkCollisions(bool addPoints = true, bool respawnEnemies = false);

    /// <summary>
    /// Sets new random position of m_point.
    /// </summary>
    /// <param name="setSeed">- If it's set new seed using srand(time(NULL)).</param>
    /// <param name="setEnemy">- If true enemy will get new position don't point.</param>
    /// <param name="index">- Index of enemy that will get new position (it's last if value is bigger than size or is lesser than 0).</param>
    void newPositionOfPositioned(bool setSeed = true, bool setEnemy = false, int index = -1);

    /// <summary>
    /// Makes new move of player.
    /// </summary>
    /// <param name="direction">Direction which says where player will make move.</param>
    bool move(Direction direction);

    /// <summary>
    /// Checks is player on board's frame.
    /// </summary>
    /// <returns>True if it is on frames, false if not.</returns>
    bool positionCheck();

    /// <summary>
    /// First position x of player.
    /// </summary>
    unsigned int m_startPlayerPosX;

    /// <summary>
    /// First position y of player.
    /// </summary>
    unsigned int m_startPlayerPosY;

    /// <summary>
    /// Amount of enemies.
    /// </summary>
    unsigned int m_enemiesAmount;

    /// <summary>
    /// Whether player made first move.
    /// </summary>
    bool m_started;

    /// <summary>
    /// Tells is game ended.
    /// </summary>
    bool m_ended;

    /// <summary>
    /// Tells whether player has been killed by enemy.
    /// </summary>
    bool m_playerKilled;

    /// <summary>
    /// Says how many times m_point and m_player was on same position.
    /// </summary>
    int m_points;

    /// <summary>
    /// Point object.
    /// </summary>
    Positioned m_point;

    /// <summary>
    /// Object that will be moving on console.
    /// </summary>
    Positioned m_player;

    /// <summary>
    /// Vector with enemy objects.
    /// </summary>
    Enemies m_enemies;

    /// <summary>
    /// There are all character that make up the board
    /// </summary>
    Board m_board;

    /// <summary>
    /// Config file
    /// </summary>
    std::ofstream m_file;
};