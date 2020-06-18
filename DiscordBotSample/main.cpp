#include <QCoreApplication>
#include "discordbot.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DiscordBot * Bot = new DiscordBot();

    const QString botToken = "Insert Bot Token Here";

    Bot->login(botToken);

    return a.exec();
}
