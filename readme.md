# Updated QDiscord 2020
QDiscord is a fantastic wrapper for the discord api written in C++, but it is lacking in some functionality and the project has been orphened. This repository is the most up-to-date version of this api (that I know of as of June 2020), with additional functionality added.

## Fixes

* Fixed login for Discord Api v6

## Added Functions

* Added `QDiscordEmbed` (Accessible under `QDiscordMessage`)
    * Provides full information of `embed` objects in messages

* Added `triggerTypingIndicator` under the REST api. 
    * Allows for 'Bot is typing..." indicator in requested channels.

* Added `getGuildEmojis` under the REST api.             
    * Allows to get custom emojis from servers

# QDiscord

QDiscord is a [Qt](https://www.qt.io/) wrapper for the [Discord API](https://discordapp.com/developers/docs) written in C++.
It was written to easily allow the creation of Discord bots.


**Currently it is in an incomplete state**, so expect things to either not work or not be available.

# Discord

[Discord](https://discordapp.com) is a proprietary Voice over IP application designed for gaming communities and is developed by [Hammer & Chisel](https://discordapp.com/company).

# Documentation

Most documentation can be found [here](http://george99g.github.io/QDiscord).

"New" documentation will be dropped in the 'added features' portion of this readme

# Related projects

A list of Discord API libraries in other languages can be found [here](https://discordapi.com/unofficial/libs.html).
