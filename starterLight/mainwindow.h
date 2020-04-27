#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include <QVector3D>
#include <vector>
#include <QFile>

using namespace std;

namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

struct MyTraits : public OpenMesh::DefaultTraits
{
    // use vertex normals and vertex colors
    VertexAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    // store the previous halfedge
    HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
    // use face normals face colors
    FaceAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    EdgeAttributes( OpenMesh::Attributes::Color );
    // vertex thickness
    VertexTraits{float thickness; float value; Color faceShadingColor;};
    // edge thickness
    EdgeTraits{float thickness;};
};
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;


enum DisplayMode {Normal, TemperatureMap, ColorShading};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector3D faceNormal(MyMesh* mesh, int faceID0, int faceID1);

    void actualiserAffichageFaces(MyMesh* _mesh);

    void displayMesh(MyMesh *_mesh, DisplayMode mode = DisplayMode::Normal);
    void resetAllColorsAndThickness(MyMesh* _mesh);

private slots:

    void on_pushButton_launch_clicked();
    void on_pushButton_chargement_clicked();

    void on_pushButton_afficherSelection_clicked();

    void on_pushButton_enregistrerLABEL_clicked();
    void on_pushButton_enregistrerCSV_clicked();


private:

    //liste de l'attribution de parties a chaque face
    vector<QString> partAttribution;

    MyMesh::Color unknownColor = MyMesh::Color(175, 175, 175);
    MyMesh::Color pink = MyMesh::Color(255, 100, 200);
    MyMesh::Color blue = MyMesh::Color(100, 100, 255);
    MyMesh::Color red = MyMesh::Color(255, 100, 100);
    MyMesh::Color yellow = MyMesh::Color(255, 255, 100);
    MyMesh::Color brown = MyMesh::Color(150, 90, 60);


    MyMesh mesh;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
