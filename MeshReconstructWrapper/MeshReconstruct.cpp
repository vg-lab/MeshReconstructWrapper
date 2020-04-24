//
// Created by ivan on 7/4/20.
//

#include <string>
#include <QDir>
#include <boost/process.hpp>
#include <QSettings>
#include <QCoreApplication>
#include "MeshReconstruct.h"
#include <boost/dll.hpp>
#include <iostream>

#ifdef _WIN32
#define INSTALL std::string("src/install.bat")
#define RUN "/src/run.bat"
#else
#define INSTALL std::string("src/install.sh")
#define RUN "/src/run.sh"
#endif

#define ENV "env"

namespace meshreconstruct
{
  MeshReconstruct* MeshReconstruct::_instance = nullptr;

  MeshReconstruct::MeshReconstruct( )
  {
#ifdef _WIN32
    QSettings settings(QSettings::IniFormat,QSettings::SystemScope,"MeshReconstruct","preferences");
#else
    QSettings settings( "MeshReconstruct", "preferences" );
#endif

    _configPath = QFileInfo( settings.fileName( ) ).absoluteDir( ).absolutePath( );
    QDir dir( _configPath );
    if( !dir.exists( ) )
    {
      dir.mkpath( _configPath );
    }
    _envPath = _configPath + "/" + ENV;

    _exePath = boost::dll::program_location( ).parent_path( ).string( );

    initPythonEnv( );
  }

  int MeshReconstruct::checkPython( )
  {
#ifdef _WIN32
    std::string pythonName = "py";
#else
    std::string pythonName = "python3";
#endif
    std::string version;
    std::string token;
    boost::process::ipstream inputStream;
    try
    {
      int result = boost::process::system( pythonName + " --version",
                                           boost::process::std_out >
                                           inputStream );
      if( result != 0 )
      {
        return 0;
      }
      while( inputStream >> token )
      {
        version += token;
      }
      if( version.empty( ) )
      {
        return 0;
      }
      version = version.substr( 6 );
      int versionMajor = version[ 0 ] - '0';
      return versionMajor;
    } catch( boost::process::process_error& er )
    {
      return 0;
    }
  }

  void MeshReconstruct::resetPythonEnv( )
  {
    QDir dir( _envPath );
    dir.removeRecursively( );

    initPythonEnv( );
  }

  void MeshReconstruct::initPythonEnv( )
  {
    _pythonVersion = checkPython( );

    if( _pythonVersion == 3 )
    {
      _init = true;
      if( !QFileInfo( _envPath ).exists( ) )
      {

        std::string command =
            "\"" + _exePath +
            "/" + INSTALL + "\" " + _envPath.toStdString( );
        boost::process::ipstream errStream;
        int result = boost::process::system( command,
                                             boost::process::std_out > stdout,
                                             boost::process::std_err >
                                             errStream,
                                             boost::process::std_in < stdin );

        std::string line;
        std::string error;
        while( errStream && std::getline( errStream, line ) && !line.empty( ) )
        {
          error += line;
        }

        if( result != 0 || error.find( "ERROR" ) != std::string::npos )
        {
          _init = false;
        }
      }
    }
  }


  int MeshReconstruct::repairFile( const QString& outputFile, const QString& inputFile,
                      const QString& saveFormat,
                      int precision, float reduction, bool includeSegments,
                      int kernelSize,
                      bool clean, const QString& exportPath )
  {
    if (!_init) {
      throw "It cannot be repaired because the system does not have python or the environment was not created correctly.";
    }
    QStringList arguments;

    arguments << "-a" << "\"" + outputFile + "\"" << "-v"
              << "\"" + inputFile + "\"" << "-s" << saveFormat << "-p"
              << QString::number( precision )
              << "-r" << QString::number( reduction ) << "-f"
              << QString::number( (int) includeSegments ) << "-k"
              << QString::number( kernelSize )
              << "-c" << QString::number( (int) clean );

    if( !exportPath.isEmpty( ) )
    {
      arguments << "-e" << "\"" + exportPath + "\"";
    }

    QString command =
        "\"" + QString::fromStdString(_exePath) + RUN + "\" " +
        _envPath + " " + arguments.join( " " );

#ifdef _WIN32
    command.insert(0,"\"");
    command.append("\"");
#endif

    return std::system( command.toStdString( ).c_str( ) );
  }

  int MeshReconstruct::repairDir(const QString &outputDir, const QString &inputDir, const QString &saveFormat,
                              int precision, float reduction, bool includeSegments, int kernelSize,
                              bool clean, const QString& exportPath) {
    if (!_init) {
      throw "It cannot be repaired because the system does not have python or the environment was not created correctly.";
    }

    QStringList arguments;

    arguments << "-o" << "\"" + outputDir + "\"" << "-w" << "\"" + inputDir + "\"" <<"-s" << saveFormat << "-p" << QString::number(precision)
              << "-r" << QString::number(reduction) << "-f" << QString::number( (int) includeSegments) << "-k" << QString::number(kernelSize)
              << "-c" << QString::number((int) clean);

    if (!exportPath.isEmpty()) {
      arguments << "-e" << "\"" + exportPath + "\"";
    }

    QString command = "\"" + QString::fromStdString(_exePath) + "/" + RUN + "\" " + _envPath + " " + arguments.join(" ");

#ifdef _WIN32
    command.insert(0,"\"");
    command.append("\"");
#endif

    return std::system(command.toStdString().c_str());

  }

  MeshReconstruct* MeshReconstruct::getInstance( )
  {
    if (_instance == nullptr) {
      _instance = new MeshReconstruct();
    }
    return _instance;
  }

  bool MeshReconstruct::isInit( ) const
  {
    return _init;
  }

}

