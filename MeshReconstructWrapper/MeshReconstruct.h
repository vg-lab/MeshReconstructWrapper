//
// Created by ivan on 7/4/20.
//

#ifndef MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
#define MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H

#include <QString>
namespace meshreconstruct
{
  class MeshReconstruct
  {
    int _pythonVersion;
    QString _envPath;
    bool _init;
    std::string _exePath;

    public:
    static MeshReconstruct *getInstance();

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
    MeshReconstruct(MeshReconstruct const&);
    MeshReconstruct& operator=(MeshReconstruct const&);

    private:
    static MeshReconstruct* _instance;

    int checkPython( );

    void resetPythonEnv( );


  };

  MeshReconstruct* MeshReconstruct::_instance = nullptr;
}

#endif //MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
