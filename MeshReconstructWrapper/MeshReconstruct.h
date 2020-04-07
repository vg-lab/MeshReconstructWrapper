//
// Created by ivan on 7/4/20.
//

#ifndef MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
#define MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H

#include <meshreconstructwrapper/api.h>

#include <QString>
namespace meshreconstruct
{
  class MESHRECONSTRUCTWRAPPER_API MeshReconstruct
  {
    int _pythonVersion;
    QString _envPath;
    std::string _exePath;
    QString _configPath;
    bool _init;

    public:
    static MeshReconstruct *getInstance();
    MeshReconstruct(MeshReconstruct const&) = delete;
    MeshReconstruct& operator=(MeshReconstruct const&) = delete;

    void initPythonEnv( );

    int repairFile( const QString& outputFile, const QString& inputFile,
                    const QString& saveFormat, int precision, float reduction,
                    bool includeSegments, int kernelSize, bool clean,
                    const QString& exportPath );

    int repairDir( const QString& outputDir, const QString& inputDir,
                   const QString& saveFormat, int precision, float reduction,
                   bool includeSegments, int kernelSize, bool clean,
                   const QString& exportPath );


    protected:
    MeshReconstruct();

    private:
    static MeshReconstruct* _instance;

    int checkPython( );

    void resetPythonEnv( );


  };
}

#endif //MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
