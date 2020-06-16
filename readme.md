# Updated QDiscord 2020
QDiscord is a fantastic wrapper for the discord api written in C++, but it is lacking in some functionality and the project has been orphened. This repository is the most up-to-date version of this api (that I know of as of June 2020), with additional functionality added.

## Fixes

* Fixed login for Discord Api v6

## Added Functions

### Extensions to QDiscordMessage

* Added `QDiscordEmbed` 

* Added `QDiscordAttachment` 


### Extensions to REST Api

* Added `triggerTypingIndicator` to specified `channel`

* Added `getGuildMember`

* Added `getGuild`

* Added `getGuildEmojis` 

* Added `patchGuildMember`
    * Allows for editing member's permissions/roles/etc 

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
