# Console-Game 
It's a really tiny project that is a game you can play in console. If you want to change settings without changing code, use [ConfigCG.json](rc/ConfigCG.json) file.

### Version
1.5.1

## Table of contents
* [General info](#general-info)
* [Building](#building)
* [Screenshots](#screenshots)
* [Config](#config)
* [Libraries](#libraries)
* [Contact](#contact)


## Building
To build Console-Game you need to have installed at last [cmake 3.0](https://cmake.org/download/) and use it to build. If you have installed Visual Studio 2019 or different IDE with cmake support simply build Console-Game with that. [See also](https://cmake.org/runningcmake/).

## General info
There you moving by a some face character or different, and you have to earn some points by moving on dollar or different character. There actually nothing more.

## Screenshots
![Example screenshot 1](rc/screenshots/First.png)
![Example screenshot 2](rc/screenshots/Second.png)
![Example screenshot 3](rc/screenshots/Third.png)
![Example screenshot 4](rc/screenshots/Fourth.png)

## Config
If you want to use config you must put it into same folder as Console-Game. There are all variables you can change. You delete them if you want and in this case game will use default content of delete variable. But remember config doesn't support emoji. [See config file.](rc/ConfigCG.json)

```
{
  "config": {
    "sizeX": 20,
    "sizeY": 10,
    "playerPositionX": 2,
    "playerPositionY": 2,
    "enemiesAmount": 3,
    "addFrames": true,
    "replaceSpaceByFrame": false,
    "spaceChar": " ",
    "frameChar": "#",
    "playerSprite": "P",
    "enemySprite": "E",
    "pointSprite": "$"
  }
}
```

## Libraries 
Project is created with:
* [PDCurses-3.9](https://github.com/wmcbrine/PDCurses)
* [JSON reader](https://github.com/nlohmann/json)
