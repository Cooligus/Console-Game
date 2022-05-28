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

#include "game.h"
#include <cctype>

Game::Game(unsigned int sizeX, unsigned int sizeY, unsigned int playerPositionX, unsigned int playerPositionY, unsigned int enemiesAmount, bool addFrames, bool replaceSpaceByFrame, char spaceChar, char frameChar, char playerSprite, char pointSprite, char enemySprite)
    :m_board(sizeX, sizeY, spaceChar, addFrames, replaceSpaceByFrame, frameChar), m_points(0), m_enemiesAmount(enemiesAmount), m_started(false), m_ended(false), m_playerKilled(false), m_startPlayerPosX(playerPositionX), m_startPlayerPosY(playerPositionY)
{    
    //prepare board
    prepareBoard(playerPositionX, playerPositionY, playerSprite, pointSprite, enemySprite);
}

Game::Game(nlohmann::json configuration)
    :m_board(configuration[SIZE_X].get<unsigned int>(),configuration[SIZE_Y].get<unsigned int>(),getchar(configuration[SPACE_CHAR].get<nlohmann::json::string_t>()), configuration[ADD_FRAMES].get<bool>(), configuration[REPLACE_SPACE].get<bool>(), getchar(configuration[FRAME_CHAR]))
{
    //prepare board
    prepareBoard(configuration[PLAYER_POSITION_X].get<unsigned int>(), configuration[PLAYER_POSITION_Y].get<unsigned int>(),
                 getchar(configuration[PLAYER_SPRITE]), getchar(configuration[POINT_SPRITE]), getchar(configuration[ENEMY_SPRITE]));

    m_file.open("output.txt", std::fstream::out);
    m_file << "lol";
}

Game::~Game()
{
m_file.close();
}

bool Game::newFrame()
{
    //end game
    if (m_ended)
        return false;
        
    //makes next m_player's move
    while(!makeMove(getch()));

    m_file << "lol";
        
    //checking m_player's, enemies' and m_point's positions
    if (m_started) checkCollisions();

    //move enemies
    if(!m_playerKilled && m_started)
        moveEnemies();

    //checking m_player's, enemies'  and m_point's positions
    if (m_started) checkCollisions();

    //shows board
    show();

    //return continuation
    return true;
}

void Game::cleanTraceOfPositioned(Positioned toClean)
{
    //"deleting" trace of old position of point
    m_board.changeCharacter(m_board.getCharOfSpace(), toClean.getPositionX(), toClean.getPositionY());
}

bool Game::makeMove(char character)
{
    //end game
    if (tolower(character) == 'e')
    {
        m_ended = true;
        return true;
    }

    //reload game
    if (tolower(character) == 'r' && m_playerKilled)
    {
        m_playerKilled = false;
        
        setupObjects();

        return true;
    }
    if(!m_playerKilled)
    {
        //set variable that will be returned
        bool toReturn = true;

        //cleaning old position
        cleanTraceOfPositioned(m_player);

        //setting new position of point
        if(!move(Direction(tolower(character))))
            toReturn = false;

        //checking is m_player on frame and if it is returning to old position
        if (positionCheck())
        {
            move(reverseDirection(Direction(tolower(character))));
            toReturn = false;
        } 

        //drawing new position on board
        drawCharacter(m_player);

        return toReturn;
    }
 }

void Game::show(bool cleanBoard, bool showPoints, bool showPosition)
{
    //cleaning
    if (cleanBoard)
    {
        clear();
    }


    //displaying board
    m_board.display();

    //showing points
    if (showPoints)
    {
        printw("Points: %i\n", m_points);
    }

    //displaying position
    if (showPosition)
    {
        printw("Points: %u %u\n", m_player.getPositionX(), m_player.getPositionY());
    }

    //show fail message
    if (m_playerKilled)
    {
        printw("Press 'R' to restart game.\n");
    }
}

bool Game::isEnded()
{
    return m_ended;
}

bool Game::repairIndex(int& index)
{
    //set temp variable
    int temp = index;

    //return biggest possible index if it is smaller than 0 or is bigger than biggest
    if (index < 0 || index >= m_enemies.elements.size())
        index = m_enemies.elements.size() - 1;

    //check whether array is empty
    if (m_enemies.elements.size() == 0)
        index = 0;

    //return index
    return temp != index;
}

void Game::prepareBoard(unsigned int playerPositionX, unsigned int playerPositionY, char playerSprite, char pointSprite, char enemySprite)
{
    //repair sizes
    unsigned int sizeX = m_board.getSizeX();
    unsigned int sizeY = m_board.getSizeY();

    //checking player position
    if (sizeX <= playerPositionX) playerPositionX = sizeX - 1;
    if (sizeY <= playerPositionY) playerPositionY = sizeY - 1;
    if (0 == playerPositionX) playerPositionX = 1;
    if (0 == playerPositionY) playerPositionY = 1;

    //set start positions
    m_startPlayerPosX = playerPositionX;
    m_startPlayerPosY = playerPositionY;

    //setting up objects
    m_player = Positioned(0, 0, playerSprite);
    m_point = Positioned(0, 0, pointSprite);
    m_enemies.elements = std::vector<Positioned>();
    m_enemies.sprite = enemySprite;

    //get size of board
    unsigned int size = m_board.getSizeX(false)* m_board.getSizeY(false);
    
    //change enemies amount
    if (0 > size - (m_enemiesAmount + 2))
        m_enemiesAmount = size - 2;

    //proper object setup
    setupObjects(false, false);
}

void Game::setupObjects(bool cleanObjects, bool resetPoints)
{
    //clean board from positioned
    if (cleanObjects)
    {
        cleanTraceOfPositioned(m_point);
        cleanTraceOfPositioned(m_player);

        for (int i = 0; i < m_enemies.elements.size(); i++)
            cleanTraceOfPositioned(m_enemies.elements[i]);
    }
  

    //setting up objects
    m_player = Positioned(m_startPlayerPosX, m_startPlayerPosY, m_player.getSprite());
    m_point = Positioned(m_board.getRanNumInsideOnX(true), m_board.getRanNumInsideOnY(), m_point.getSprite());
    m_enemies.elements = std::vector<Positioned>();

    //spawn enemies
    if (m_enemiesAmount != 0)
        for (int i = 0; i < m_enemiesAmount; i++)
            spawnPositioned(true);

    //check collisions without adding points
    checkCollisions(false, true);

    //drawing Positioned objects
    drawCharacter(m_player);
    drawCharacter(m_point);

    for (int i = 0; i < m_enemies.elements.size(); i++)
        drawCharacter(m_enemies.elements[i]);

    //reset points
    if (resetPoints)
        m_points = 0;

    m_started = false;
}

void Game::drawCharacter(Positioned toDraw)
{
    //change character
    m_board.changeCharacter(toDraw.getSprite(), toDraw.getPositionX(), toDraw.getPositionY());
}

bool Game::checkCollisions(bool addPoints, bool respawnEnemies)
{
    //does enemy or point met player
    bool met = false;

    //checking are position equal
    if (m_player.getPosition() == m_point.getPosition())
    {
        //incrasing points
        if(addPoints) m_points++;

        //generates new position
        spawnPositioned();

        //return info: point and player met
        met = true;
    }
    else
    {
        //check is any enemy on player or point
        for (int i = 0; i < m_enemies.elements.size(); i++)
        {
            //if player and enemy are on the same place end game
            if (m_player.getPosition() == m_enemies.elements[i].getPosition())
            {
                //set better position of enemy is user want it 
                if (respawnEnemies) spawnPositioned(false, i);

                //else kill player
                else
                {
                    drawCharacter(m_enemies.elements[i]);
                    m_playerKilled = true;
                    met = true;
                }
            }
            //else if player and point are on the same positions decrase points and spawn new point
            else if (m_enemies.elements[i].getPosition() == m_point.getPosition())
            {
                //decrasing points
                if (addPoints) m_points--;

                //generates new position
                spawnPositioned();
            }
        }
    }

    //return info does anything met player
    return met;
}

void Game::newPositionOfPositioned(bool setSeed, bool setEnemy, int index)
{
    //generate new position for point if user want it
    if (!setEnemy)
        m_point.newPosition(m_board.getRanNumInside(setSeed));

    //else new position is going for enemy
    else
    {
        //repair index
        repairIndex(index);

        //set new position
        m_enemies.elements[index].newPosition(m_board.getRanNumInside(setSeed));
    }            
}

bool Game::move(Direction direction)
{    
    //switch that checks direction
    switch (direction)
    {
    //left checking
    case Direction::LEFT:
        m_player.newPositionX(m_player.getPositionX() - 1);
        m_started = true;
        return true;
        break;

    //up checking
    case Direction::UP:
        m_player.newPositionY(m_player.getPositionY() - 1);
        m_started = true;
        return true;
        break;

    //right checking
    case Direction::RIGHT:
        m_player.newPositionX(m_player.getPositionX() + 1);
        m_started = true;
        return true;
        break;

    //down checking
    case Direction::DOWN:
        m_player.newPositionY(m_player.getPositionY() + 1);
        m_started = true;
        return true;
        break;
    }
    return false;
}

bool Game::positionCheck()
{
    //checking is m_player on frame
    if (m_board.isOnFrame(m_player.getPositionX(), m_player.getPositionY()))
        //returning true if it is
        return true;
    else
        //returning false if it not
        return false;
}

bool Game::moveEnemies()
{
    // set variable with amount of enemies
    unsigned int size = m_enemies.elements.size();

    //check is there any enemy
    if (size > 0)
    {
        //do move for all enemies
        for (int i = 0; i < size; i++)
        {
            //boolean that will help to make enemies not too op
            bool moved = false;

            //get enemy's positions
            int enPosX = m_enemies.elements[i].getPositionX();
            int enPosY = m_enemies.elements[i].getPositionY();

            //get point's positions
            int poPosX = m_point.getPositionX();
            int poPosY = m_point.getPositionY();

            //define lambda
            auto checkEnemies = [size, i](std::vector<Positioned> enemies, Direction dir)
            { 
                //check out all enemies
                for (int j = 0; j < size; j++)
                {
                    //check whether current enemy is now checking enemy and if yes skip this check
                    if (i == j)
                        continue;

                    //return false is enemies will meet after next move
                    if (dir == Direction::LEFT && enemies[i].getPositionX() - 1 == enemies[j].getPositionX() && enemies[i].getPositionY() == enemies[j].getPositionY())
                        return false;

                    //return false is enemies will meet after next move
                    if (dir == Direction::RIGHT && enemies[i].getPositionX() + 1 == enemies[j].getPositionX() && enemies[i].getPositionY() == enemies[j].getPositionY())
                        return false;

                    //return false is enemies will meet after next move
                    if (dir == Direction::UP && enemies[i].getPositionY() - 1 == enemies[j].getPositionY() && enemies[i].getPositionX() == enemies[j].getPositionX())
                        return false;

                    //return false is enemies will meet after next move
                    if (dir == Direction::DOWN && enemies[i].getPositionY() + 1 == enemies[j].getPositionY() && enemies[i].getPositionX() == enemies[j].getPositionX())
                        return false;
                }

                //return true is enemies will not meet after next move
                return true;
            };


            //move enemy's position x
            //right if there is a point or
            if (enPosX < poPosX && checkEnemies(m_enemies.elements, Direction::RIGHT))
            {
                enPosX++;
                moved = true;
            } 
            //left if there is a point
            else if (enPosX > poPosX && checkEnemies(m_enemies.elements, Direction::LEFT))
            {
                enPosX--;
                moved = true;
            }  

            //move enemy's position y
            //upward if there is a point or
            if (!moved && enPosY > poPosY && checkEnemies(m_enemies.elements, Direction::UP))
            {
                enPosY--;
            }
                
            //down if there is a point
            else if (!moved && enPosY < poPosY && checkEnemies(m_enemies.elements, Direction::DOWN))
            {
                enPosY++;
            }
                

            //clean old position
            cleanTraceOfPositioned(m_enemies.elements[i]);

            //set new positions
            m_enemies.elements[i].newPosition(std::pair<unsigned int, unsigned int>(enPosX, enPosY));

            //drawing new position on board
            drawCharacter(m_enemies.elements[i]);
        }

        //return success
        return true;
    }
    //return failure
    return false;
}

void Game::spawnPositioned(bool enemy, int index)
{
    //make new enemy
    if (enemy && repairIndex(index))
    {
        m_enemies.elements.push_back(Positioned(1, 1, m_enemies.sprite));
        index++;
    }
        

    //generates new position
    newPositionOfPositioned(true, enemy, index);

    //if generating faild generates new position while position is wrong
    while (!isPositionedFree(enemy, index))
    {
        //generates new position
        newPositionOfPositioned(false, enemy, index);
    }

    //drawing new
    //enemy if user want it
    if (enemy)
        drawCharacter(m_enemies.elements.back());
    //or point
    else
        drawCharacter(m_point);
}

bool Game::isPositionedFree(bool enemy, int index)
{
    //setup index if enemy is setted to true
    if (enemy)
        repairIndex(index);
    
    //check is point on player or is enemy on player and if it is return false
    if (!enemy && m_point.getPosition() == m_player.getPosition() ||
        enemy && m_enemies.elements[index].getPosition() == m_player.getPosition())
        return false;

    //check is point on any of enemies
    for (int i = 0; i < m_enemies.elements.size(); i++)
    {
        //check is enemy setted to true
        if (enemy)
        {
            //skip if index of current enemy equal to index of checked enemy
            if (i == index)
                continue;

            //reutn false if position of current enemy equals to position of checked enemy
            else if (m_enemies.elements[index].getPosition() == m_enemies.elements[i].getPosition())
                return false;
        }
        else
            //return false if position of current checking enemy equals to point's position
            if (m_point.getPosition() == m_enemies.elements[i].getPosition())
                return false;
    }


    //return success and point's freedom
    return true;
}
