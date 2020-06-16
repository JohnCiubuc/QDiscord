/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 inathero
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

#ifndef QDISCORDEMBED_HPP
#define QDISCORDEMBED_HPP

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

namespace DiscordEmbeds
{
struct thumbnail
{
    QString url;
    QString proxy_url;
    int height;
    int width;
};
struct video
{
    QString url;
    int height;
    int width;
};
struct image
{
    QString url;
    QString proxy_url;
    int height;
    int width;
};
struct provider
{
    QString name;
    QString url;
};
struct author
{
    QString name;
    QString url;
    QString icon_url;
    QString proxy_icon_url;
};
struct footer
{
    QString text;
    QString icon_url;
    QString proxy_icon_url;
};
struct field
{
    QString name;
    QString value;
    bool b_inline;
};
}

class QDiscordEmbed
{
public:
    /*!
     * \brief Creates an instance from the provided parameters.
     * \param object A JSON object of a Discord message.
     * \param channel A pointer to the channel the message was sent to.
     */
    QDiscordEmbed(
        const QJsonArray & array);
    QDiscordEmbed();
    QDiscordEmbed(const QDiscordEmbed & other);
    ~QDiscordEmbed();
    DiscordEmbeds::footer footer() const
    {
        return _footer;
    }
    DiscordEmbeds::image image() const
    {
        return _image;
    }
    DiscordEmbeds::thumbnail thumbnail() const
    {
        return _thumbnail;
    }
    DiscordEmbeds::video video() const
    {
        return _video;
    }
    DiscordEmbeds::provider provider() const
    {
        return _provider;
    }
    DiscordEmbeds::author author() const
    {
        return _author;
    }
    QList<DiscordEmbeds::field> fields() const
    {
        return _fields;
    }
    QString description() const
    {
        return _description;
    }
    QString title() const
    {
        return _title;
    }
    QString type() const
    {
        return _type;
    }
    QString url() const
    {
        return _url;
    }
    int color() const
    {
        return _color;
    }
    bool isValid() const
    {
        return _fields.size() > 0;
    }
private:
    // functions
    DiscordEmbeds::footer get_footer(const QJsonObject object);
    DiscordEmbeds::image get_image(const QJsonObject object);
    DiscordEmbeds::thumbnail get_thumbnail(const QJsonObject object);
    DiscordEmbeds::video get_video(const QJsonObject object);
    DiscordEmbeds::provider get_provider(const QJsonObject object);
    DiscordEmbeds::author get_author(const QJsonObject object);
    QList<DiscordEmbeds::field> get_fields(const QJsonArray array);
    // variables
    QString _title;
    QString _type;
    QString _description;
    QString _url;
    int _color;
    DiscordEmbeds::footer _footer;
    DiscordEmbeds::image _image;
    DiscordEmbeds::thumbnail _thumbnail;
    DiscordEmbeds::video _video;
    DiscordEmbeds::provider _provider;
    DiscordEmbeds::author _author;
    QList<DiscordEmbeds::field> _fields;
    bool _hasEmbed = false;
};

Q_DECLARE_METATYPE(QDiscordEmbed)

#endif // QDISCORDEMBED_HPP
