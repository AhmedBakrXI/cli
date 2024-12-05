#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H

#include <QString>
#include <QMap>
#include <QMutex>

#include "AbstractCommand.h"

class CommandRegistry {
public:
    // Static method to get the single instance of CommandRegistry
    static CommandRegistry& instance() {
        static CommandRegistry instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Prevent copy constructor and assignment operator
    CommandRegistry(const CommandRegistry&) = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;

    void registerCommand(AbstractCommand &command);
    AbstractCommand* getCommand(const QString& commandName);

private:
    CommandRegistry() = default; // Private constructor to prevent instantiation outside of the instance() method

    QMap<QString, AbstractCommand*> registry;
    QMutex mutex; // Mutex to ensure thread-safety
};

#endif // COMMANDREGISTRY_H
