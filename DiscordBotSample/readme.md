# Discord Bot Sample
This is a basic Discord bot showing how to use QDiscord in a barebones, but fully functional, C++ Qt Discord Bot

# How to get your discord bot login token
1. Go to your developer portal -> [Applications](https://discord.com/developers/applications/)
2. Select (or create) your bot
3. Select 'Bot' under its settings
4. 'Click to Reveal Token' and use that to login!

# How to setup
1. Compile [QDiscord](https://github.com/JohnCiubuc/QDiscord/tree/master/QDiscord)
2. Edit DiscordBotSample.pro and do the following changes:
    * Under comment `QDiscord Lib`, change directories to where [QDiscord](https://github.com/JohnCiubuc/QDiscord/tree/master/QDiscord) compiled library is located
    * Under comment `QDiscord Includes`, change directories to [QDiscord](https://github.com/JohnCiubuc/QDiscord/tree/master/QDiscord)'s source directory

# Structure

1. main.cpp launches bot with login tokin

2. `DiscordBot` is the main discord bot

3. `QDiscordInterpeter` serves as the communication between the 'Bot' and QDiscord. 

# Command Examples

Most bot commands can be found in `DiscordBot`. Commands requiring response from the server, will have their responses found under `QDiscordInterpreter`
