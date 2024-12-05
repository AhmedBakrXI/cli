#include "CommandRegistry.h"

void CommandRegistry::registerCommand(AbstractCommand &command) {
    QMutexLocker locker(&mutex);
    registry.insert(command.getName(), &command);
}

AbstractCommand* CommandRegistry::getCommand(const QString &commandName) {
    QMutexLocker locker(&mutex);
    if (registry.contains(commandName)) {
        auto it = registry.find(commandName);
        if (it != registry.end()) {
            return it.value(); // Return the pointer
        }
    }
    return nullptr;
}
