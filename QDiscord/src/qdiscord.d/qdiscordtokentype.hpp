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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QDISCORDTOKENTYPE_HPP
#define QDISCORDTOKENTYPE_HPP

/*!
 * \brief Specifies the type of a token passed to %QDiscord.
 *
 * See https://discordapp.com/developers/docs/reference#authentication for more
 * information and what the types are used for.\n
 * \n
 * If a type is not available here, use QDiscordTokenType::None and append the
 * type to the token manually.
 */
enum class QDiscordTokenType {
	None, Bot, Bearer
};

#endif // QDISCORDTOKENTYPE_HPP
