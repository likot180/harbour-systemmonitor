#ifndef DATASOURCECELL_H
#define DATASOURCECELL_H

#include <QObject>
#include <QVector>
#include <QString>
#include "datasource.h"
#include "systemsnapshot.h"

class DataSourceCell : public DataSource
{
    Q_OBJECT
public:
    explicit DataSourceCell(SystemSnapshot *parent = 0);

signals:

public slots:
    void processSystemSnapshot();

private:
    QVector<unsigned long long> m_sourcesRx;
    QVector<unsigned long long> m_sourcesTx;

    QDateTime m_prevTime;
    QVector<unsigned long long> m_prevBytesRx;
    QVector<unsigned long long> m_prevBytesTx;
};

#endif // DATASOURCECELL_H
