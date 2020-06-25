//
// Created by ivan on 7/4/20.
//

#ifndef MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
#define MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H

#include <meshreconstructwrapper/api.h>

#include <QString>
namespace meshreconstruct
{
  /// Singleton class that allow to repair and extract metrics for the meshes in VRML format.
  /// Note that, this class uses Python 3.7 to perform the reconstruction, so it's necessary has python 3.7 installed in the system (all environment management is done automatically).
  class MESHRECONSTRUCTWRAPPER_API MeshReconstruct
  {
    int _pythonVersion;
    QString _envPath;
    std::string _exePath;
    QString _configPath;
    bool _init;

    public:
    /// get the singleton instance
    /// \return pointer to the singleton instance
    static MeshReconstruct *getInstance();

    MeshReconstruct(MeshReconstruct const&) = delete;
    MeshReconstruct& operator=(MeshReconstruct const&) = delete;

    /// Remove the entire Python environment and rebuild it.
    void resetPythonEnv( );

    /// check if it started successfully
    /// \return true if its ready to use, false otherwise
    bool isInit( ) const;

    /// Repair a single file and export both the original and the repaired meshes to
    /// the desired format
    /// \param outputFile path to the metrics file (csv format)
    /// \param inputFile path to input file (VRML format)
    /// \param saveFormat allows to select the format of exported meshes (original and repaired). Values allowed:
    /// "None", "Stl", "Vrml", "Obj"
    /// \param precision controls the quality of the reconstruction, a sutiable value for spines would be 100.
    /// Note that this parameter controls the number of voxels generate for the reconstruccion a too big value can
    /// exahust the memory of the system
    /// \param reduction controls the reduction percentage applied to the repaired meshes to export. Values mst be in 0-100 range
    /// \param includeSegments if true the method take into account dendritics segments, otherwise take into account only spines (only valid for Imaris Filament tracer files).
    /// \param kernelSize Controls the aggressiveness of the joining process and Gaussian smoothing
    /// \param clean if true, the input VRML file will be preprocessed and all unnecessary parts will be removed.
    /// \param exportPath path where the generated meshes will be exported
    /// \return
    int repairFile( const QString& outputFile, const QString& inputFile,
                    const QString& saveFormat, int precision, float reduction,
                    bool includeSegments, int kernelSize, bool clean,
                    const QString& exportPath );

    /// see repairFile()
    int repairDir( const QString& outputDir, const QString& inputDir,
                   const QString& saveFormat, int precision, float reduction,
                   bool includeSegments, int kernelSize, bool clean,
                   const QString& exportPath );


    protected:
    MeshReconstruct();

    private:
    static MeshReconstruct* _instance;

    void initPythonEnv( );

    int checkPython( );

  };
}

#endif //MESHRECONSTRUCTWRAPPER_MESHRECONSTRUCT_H
