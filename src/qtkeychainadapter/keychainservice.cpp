#include "keychainservice.h"

#include "keychain.h"

#include <QDebug>

using namespace qtkeychainadapter;

KeyChainService::KeyChainService(const QString &name, QObject* parent)
    : QObject(parent)
    , m_name(name)
{
}

void KeyChainService::readKey(const QString &key)
{
    auto read_job = new QKeychain::ReadPasswordJob(m_name);
    read_job->setKey(key);

    connect(read_job, &QKeychain::ReadPasswordJob::finished, this, [=]() {
        if (read_job->error()) {
            emit error(tr("Read key failed: %1").arg(qPrintable(read_job->errorString())));
            return;
        }
        emit keyRestored(key, read_job->textData());
    });

    read_job->start();
}

void KeyChainService::writeKey(const QString &key, const QString &value)
{
    auto write_job = new QKeychain::WritePasswordJob(m_name);
    write_job->setKey(key);

    connect(write_job, &QKeychain::WritePasswordJob::finished, this, [=](){
        if (write_job->error()) {
            emit error(tr("Write key failed: %1").arg(qPrintable(write_job->errorString())));
            return;
        }
        qDebug().nospace() << this << "::writeKey: key " << key << " written";
        emit keyStored(key);
    });

    write_job->setTextData(value);
    write_job->start();
}

void KeyChainService::deleteKey(const QString &key)
{
    auto delete_job = new QKeychain::DeletePasswordJob(m_name);
    delete_job->setKey(key);

    connect(delete_job, &QKeychain::DeletePasswordJob::finished, this, [=]() {
        if (delete_job->error()) {
            emit error(tr("Delete key failed: %1").arg(qPrintable(delete_job->errorString())));
            return;
        }
        emit keyDeleted(key);
    });

    delete_job->start();
}
