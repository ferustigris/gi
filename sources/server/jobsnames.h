#ifndef JOBSNAME_H
#define JOBSNAME_H
namespace jobsnames {
    const QString JOB_BASEMANAGER = "baseManager";
    const QString JOB_CALCULATOR = "calculator";
}
namespace commandsnames {
    const quint16 JOB_UNIQUEID = 1;//команда получить уникальный ИД для запускаемой задачи
    const quint16 JOB_CALCSUB = 4;
    const quint16 JOB_CALCMULT = 3;
    const quint16 JOB_CALCPLUS = 1;
    const quint16 JOB_CALCMINUS = 2;
    const quint16 JOB_ANSWER = 7;
}
namespace pathnames {
    const QString PATH_PLUGINS = "plugins";
}
#endif // JOBSNAME_H
