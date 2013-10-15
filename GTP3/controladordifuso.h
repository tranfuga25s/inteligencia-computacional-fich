#ifndef CONTROLADORDIFUSO_H
#define CONTROLADORDIFUSO_H

#include <QObject>

class ControladorDifuso : public QObject
{
    Q_OBJECT
public:
    explicit ControladorDifuso(QObject *parent = 0);
    
private:
    
};

#endif // CONTROLADORDIFUSO_H
