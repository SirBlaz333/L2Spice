#ifndef APP_STATE_H
#define APP_STATE_H

#include <qstring.h>

/**
 * AppState is used to store the state of windowed application.
 */
class AppState
{
    bool empty;
    QString name;
    QString libreNetlist;
    QString spiceNetlist;
    QString libreSourceFile;
    QString spiceSourceFile;

public:
    /**
     * Creates an empty state.
     */
    AppState();
    /**
     * Creates the state with specified parameters.
     */
    AppState(const QString &name,
             const QString &libreNotation,
             const QString &spiceNotation,
             const QString &libreSourceFile = QString(),
             const QString &spiceSourceFile = QString());

    /**
     * @return the file where Spice netlist is stored. Can be empty if the netlist is not stored anywhere.
     */
    QString getSpiceSourceFile() const;

    /**
     * @return the file where LibrePCB circuit is stored. Can be empty if the circuit is not stored anywhere.
     */
    QString getLibreSourceFile() const;

    /**
     * @return the SPICE netlist.
     */
    QString getSpiceNetlist() const;

    /**
     * @return the LibrePCB circuit.
     */
    QString getLibreNetlist() const;

    /**
     * @return the name of the state.
     */
    QString getName() const;

    /**
     * @return whether the state is empty or not.
     */
    bool isEmpty() const;

    /**
     * Updates the file name where the LibrePCB circuit is stored.
     * @param newLibreSourceFile - new LibrePCB circuit file.
     */
    void setLibreSourceFile(const QString &newLibreSourceFile);

    /**
     * Updates the file name where the SPICE netlist is stored.
     * @param newLibreSourceFile - new SPICE netlist file.
     */
    void setSpiceSourceFile(const QString &newSpiceSourceFile);
};

#endif // APP_STATE_H
