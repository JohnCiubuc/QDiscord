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

#ifndef QDISCORDRESTCOMPONENT_HPP
#define QDISCORDRESTCOMPONENT_HPP

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include "qdiscordmessage.hpp"
#include "qdiscordutilities.hpp"
#include "qdiscordchannel.hpp"
#include "qdiscorduser.hpp"

/*!
 * \brief The REST component of QDiscord.
 *
 * This class handles all REST operations to the Discord API.
 */
class QDiscordRestComponent : public QObject
{
    Q_OBJECT
public:
    explicit QDiscordRestComponent(QObject * parent = 0);
    ~QDiscordRestComponent();
    /*!
     * \brief Acquires a token for use in all other methods using a standard
     * Discord account.
     *
     * If logging in fails, emits QDiscordRestComponent::loginFailed
     * If logging in succeeds, emits QDiscordRestComponent::tokenVerified
     * \param email An e-mail to log in with.
     * \param password The password to the provided Discord account.
     * \deprecated This method has been deprecated for bot usage by Discord.\n
     * See https://discordapp.com/developers/docs/topics/oauth2#bot-vs-user-accounts\n
     * and https://github.com/hammerandchisel/discord-api-docs/issues/69
     */
    void login(const QString & email, const QString & password);
    /*!
     * \brief Sets the token for use in all other methods.
     *
     * If logging in fails, emits QDiscordRestComponent::loginFailed
     * If logging in succeeds, emits QDiscordRestComponent::tokenVerified
     * \param token The token to use.
     * \param tokenType Specifies the type of the provided token.
     */
    void login(const QString & token,
               QDiscordTokenType tokenType = QDiscordTokenType::Bot);
    /*!
     * \brief Sends a message to the specified channel.
     *
     * If not logged in or if the channel pointer is `null`, does nothing.
     * \param content The message's contents.
     * \param channel The channel to send the message in. This may be a private
     * or a guild channel.
     * \param tts Whether to use text to speech when sending the message.
     */
    void sendMessage(const QString & content,
                     QSharedPointer<QDiscordChannel> channel,
                     bool tts = false);
    /*!
     * \brief Sends a message to the specified channel ID.
     * \param content The message's contents.
     * \param channelId The channel to send the message in. This may be a
     * private or a guild channel.
     * \param tts Whether to use text to speech when sending the message.
     */
    void sendMessage(const QString & content,
                     const QString & channelId,
                     bool tts = false);
    void sendEmbedAndMessage(const QString & message,
                             const QJsonObject & embeds,
                             const QString & channelId);
    void sendEmbed(const QJsonObject & embeds,
                   const QString & channelId);
    ///\brief Deletes the specified message.
    void deleteMessage(QDiscordMessage message);
    ///\brief Deletes the specified message by ID and channel ID.
    void deleteMessage(const QString & channelId, const QString & messageId);
    ///\brief Edits the specified message to contain the specified content
    void editMessage(const QString & newContent, QDiscordMessage message);
    /*!
     * \brief Edits the message specified by channel ID and mesage ID to contain
     * the specified content.
     */
    void editMessage(const QString & newContent,
                     const QString & channelId,
                     const QString & messageId);
    ///\brief Logs out using the stored token.
    void logout();
    /*!
     * \brief Sends a request to receive an endpoint for connecting using a
     * WebSocket.
     */
    void getEndpoint();
    ///\brief Changes the name of the specified channel.
    void setChannelName(const QString & name,
                        QSharedPointer<QDiscordChannel> channel);
    ///\brief Changes the name of the channel with specified ID.
    void setChannelName(const QString & name, const QString & channelId);
    /*!
     * \brief Changes the position of the specified text channel on the channel
     * list.
     */
    void setChannelPosition(int position,
                            QSharedPointer<QDiscordChannel> channel);
    /*!
     * \brief Changes the position of the text channel with the specified ID on
     * the channel list.
     */
    void setChannelPosition(int position, const QString & channelId);
    ///\brief Changes the topic of the specified text channel.
    void setChannelTopic(const QString & topic,
                         QSharedPointer<QDiscordChannel> channel);
    ///\brief Changes the topic of the text channel with the specified ID.
    void setChannelTopic(const QString & topic, const QString & channelId);
    ///\brief Changes the bitrate of the specified voice channel.
    void setChannelBitrate(int bitrate,
                           QSharedPointer<QDiscordChannel> channel);
    ///\brief Changes the bitrate of the voice channel with the specified ID.
    void setChannelBitrate(int bitrate, const QString & channelId);
    ///\brief Changes the user limit on the specified voice channel.
    void setChannelUserLimit(int limit,
                             QSharedPointer<QDiscordChannel> channel);
    ///\brief Changes the user limit of the voice channel with the specified ID.
    void setChannelUserLimit(int limit, const QString & channelId);
    ///\brief Sets the user belonging to this client.
    void setSelf(QSharedPointer<QDiscordUser> self);

    void getGuildMember(const QString & guildID, const QString & memberID);
    void getGuild(const QString & guildID);

    void getGuildEmojis(const QString & guildID);
    void triggerTypingIndicator(QString channel_id);

    void patchGuildMember(const QString & guildID, const QString & memberID, const QJsonObject & object);
    void patchGuildMember(const QString & guildID, const QString & memberID, const QJsonArray & array);

    void getPinnedMessages(const QString channel_id);
    void addPinnedMessage(const QDiscordMessage message);

    void createReaction(const QDiscordMessage message, const QUrl emoji);
    void deleteReaction(const QDiscordMessage message, const QUrl emoji);
    void deleteUserReaction(const QDiscordMessage message, const QString userId, const QUrl emoji);
    void getReactions(const QDiscordMessage message, const QUrl emoji);
    void deleteAllReactions(const QDiscordMessage message);
    void deleteAllReactionsForEmoji(const QDiscordMessage message, const QUrl emoji);
signals:
    /*!
     * \brief Emitted when a WebSocket endpoint has successfully been acquired.
     * \param endpoint The URL to the acquired endpoint.
     */
    void endpointAcquired(const QString & endpoint);
    /*!
     * \brief Emitted when acquiring a WebSocket endpoint has failed.
     * \param error A QNetworkReply::NetworkError enum containing more
     * information about the reason why this request failed.\n
     * QDiscordUtilities::networkErrorToString will return an error string in
     * the context of the Discord API.
     */
    void endpointAcquireFailed(QNetworkReply::NetworkError error);
    ///\brief Emitted when a logout has successfully completed.
    void loggedOut();
    /*!
     * \brief Emitted when the token acquired when logging in has been verified
     * to be correct.
     */
    void tokenVerified(const QString & token, QDiscordTokenType tokenType);
    /*!
     * \brief Emitted when logging in has failed.
     *
     * The most common cause for this would be invalid authentication.
     * Double-check your login information.
     * \param error A QNetworkReply::NetworkError enum containing more
     * information about the reason why this request failed.\n
     * QDiscordUtilities::networkErrorToString will return an error string in
     * the context of the Discord API.
     */
    void loginFailed(QNetworkReply::NetworkError error);
    ///\brief Emitted when a message has been successfully sent.
    void messageSent(const QDiscordMessage & message);
    /*!
     * \brief Emitted when sending a message has failed.
     * \param error A QNetworkReply::NetworkError enum containing more
     * information about the reason why this request failed.\n
     * QDiscordUtilities::networkErrorToString will return an error string in
     * the context of the Discord API.
     */
    void messageSendFailed(QNetworkReply::NetworkError error);
    ///\brief Emitted when a message has been successfully deleted.
    void messageDeleted(const QString & messageId);

    void getGuildMemberAcquired(QByteArray reply);
    void getGuildAcquired(QByteArray reply);
    void getGuildMemberFailed(QNetworkReply::NetworkError error);
    void guildEmojis(QByteArray reply);
    void patchGuildMemberSuccess();
    void pinnedMessages(QJsonArray pinnedMessages);
    void reactions(QDiscordMessage message, QJsonArray users);
    /*!
     * \brief Emitted when deleting a message has failed.
     * \param error A QNetworkReply::NetworkError enum containing more
     * information about the reason why this request failed.\n
     * QDiscordUtilities::networkErrorToString will return an error string in
     * the context of the Discord API.
     */
    void messageDeleteFailed(QNetworkReply::NetworkError error);
    void messageEdited(const QDiscordMessage & message);
    void messageEditFailed(QNetworkReply::NetworkError error);
    /*!
     * \brief Emitted when a channel has been updated.
     * \param channel A reference to the channel that was updated.
     */
    void channelUpdated(const QDiscordChannel & channel);
    /*!
     * \brief Emitted when a channel update has failed.
     * \param error A QNetworkReply::NetworkError enum containing more
     * information about the reason why this request failed.\n
     * QDiscordUtilities::networkErrorToString will return an error string in
     * the context of the Discord API.
     */
    void channelUpdateFailed(QNetworkReply::NetworkError error);
private:
    template<class Functor>
    void deleteResource(const QUrl & url, Functor function);
    template<class Functor>
    void patch(const QJsonObject & object, const QUrl & url, Functor function);
    template<class Functor>
    void patch(const QJsonArray & array, const QUrl & url, Functor function);
    template<class Functor>
    void post(const QJsonObject & object, const QUrl & url, Functor function);
    template<class Functor>
    void post(const QJsonArray & array, const QUrl & url, Functor function);
    template<class Functor>
    void get(const QUrl & url, Functor function);
    template<class Functor>
    void put(const QJsonArray & array, const QUrl & url, Functor function);
    QSharedPointer<QDiscordUser> _self;
    QString _authentication;
    QNetworkAccessManager _manager;
    bool _loggedIn;
};

#endif // QDISCORDRESTCOMPONENT_HPP
