/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qdiscordgame.hpp"

QDiscordGame::QDiscordGame(QString name,
                           QString url,
                           QDiscordGame::GameType type)
{
    _name = name;
    _url = url;
    _type = type;

//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordGame("<<this<<") constructed";
//#endif
}

QDiscordGame::QDiscordGame(const QJsonObject& object)
{
    _name = object["name"].toString("");
    _url = object["url"].toString("");
    switch (object["type"].toInt(-1))
    {
    case 1:
        _type = GameType::Streaming;
        break;
    case 0:
        _type = GameType::None;
        break;
    default:
        _type = GameType::UnknownType;
    }

//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordGame("<<this<<") constructed";
//#endif
}

QDiscordGame::~QDiscordGame()
{
//#ifdef QDISCORD_LIBRARY_DEBUG
//  qDebug()<<"QDiscordGame("<<this<<") destroyed";
//#endif
}
