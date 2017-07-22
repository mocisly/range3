/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   main_task.cpp                                            *
 *  GROUP:  RangeTestApp                                             *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   22-th July 2017                                          *
 *                                                                   *
 *  DESCRIPTION: Main task class definition                          *
 *********************************************************************/

#include <QCoreApplication>

#include <rblib.h>

#include "main_task.h"

MainTask::MainTask(QObject *parent) :
    QObject(parent)
{
}

void MainTask::perform(void) const
{
    RLogger::info("Range Test Application\n");
}

void MainTask::run(void)
{
    QCoreApplication *app = (QCoreApplication*)this->parent();

    try
    {
        // Process command line arguments.
        QStringList arguments = app->arguments();
        QList<QString> argumentList;
        foreach (const QString &str, arguments)
        {
            argumentList.append(str);
        }

        QList<RArgumentOption> validOptions;
//        validOptions.append(RArgumentOption("file",RArgumentOption::Path,QVariant(),"File name",false,false));

        RArgumentsParser argumentsParser(argumentList,validOptions);

        if (argumentsParser.isSet("help"))
        {
            argumentsParser.printHelp("Test Application");
            app->exit(0);
            return;
        }

        if (argumentsParser.isSet("version"))
        {
            argumentsParser.printVersion();
            app->exit(0);
            return;
        }

        this->perform();
    }
    catch (const RError &error)
    {
        RLogger::error("Failed to start test application. %s\n",error.getMessage().toUtf8().constData());
        app->exit(1);
    }

    app->exit(0);
}
