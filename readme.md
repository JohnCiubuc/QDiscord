# Updated QDiscord 2020
QDiscord is a fantastic wrapper for the Discord API written in C++, but it is lacking in some functionality and the project has been orphaned. This repository is the most up-to-date version of this API (that I know of as of June 2020), with additional functionality added.

# Sample Bot

A basic Discord bot has been written using QDiscord to show how to setup connections, receive messages (and guild specific emojis!) and how to respond back to them. 

You can read more information on the bot [Here](https://github.com/JohnCiubuc/QDiscord/tree/master/DiscordBotSample)
## Fixes

* Fixed login for Discord Api v6

## Added Functions

* Added `put` to REST Api

### Extensions to QDiscordMessage

* Added `QDiscordEmbed` 

* Added `QDiscordAttachment` 


### Extensions to REST Api

* Added `sendEmbed`

* Added `sendEmbedAndMessage`
    * Both `sendEmbed` and `sendEmbedAndMessage` allows the bot to send 'embed' objects

* Added `triggerTypingIndicator` to specified `channel`

* Added `getGuildMember`

* Added `getGuild`

* Added `getGuildEmojis` 

* Added `patchGuildMember`
    * Allows for editing member's permissions/roles/etc 

* Added `getPinnedMessages`

* Added `addPinnedMessage`

* `createReaction`

* `deleteReaction`

* `deleteUserReaction`

* `getReactions`

* `deleteAllReactions`

* `deleteAllReactionsForEmoji`

# QDiscord

QDiscord is a [Qt](https://www.qt.io/) wrapper for the [Discord API](https://Discordapp.com/developers/docs) written in C++.
It was written to easily allow the creation of Discord bots.


**Currently it is in an incomplete state**, so expect things to either not work or not be available.

# Discord

[Discord](https://Discordapp.com) is a proprietary Voice over IP application designed for gaming communities and is developed by [Hammer & Chisel](https://Discordapp.com/company).

# Documentation

Most documentation can be found [here](http://george99g.github.io/QDiscord).

"New" documentation will be dropped in the 'added features' portion of this readme

# Related projects

A list of Discord API libraries in other languages can be found [here](https://DiscordAPI.com/unofficial/libs.html).
