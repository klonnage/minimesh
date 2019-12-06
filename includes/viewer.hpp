#pragma once
#include <string>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetMapper.h>

class Viewer
{
  std::string m_filename;
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader;
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInterractor;

public:
  Viewer(void) {}
  Viewer(std::string const& filename) : m_filename(filename) {
    /* Instanciate viewer */
    reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>(vtkXMLUnstructuredGridReader::New());
    reader -> SetFileName(m_filename.c_str());
    reader -> Update();

    auto mapper = vtkSmartPointer<vtkDataSetMapper>(vtkDataSetMapper::New());
    mapper -> SetInputConnection(reader -> GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
    actor -> SetMapper(mapper);

    auto renderer = vtkSmartPointer<vtkRenderer>(vtkRenderer::New());
    renderer -> AddActor(actor);

    auto renderWindow = vtkSmartPointer<vtkRenderWindow>(vtkRenderWindow::New());
    renderWindow -> AddRenderer(renderer);

    renderWindowInterractor = vtkSmartPointer<vtkRenderWindowInteractor>(vtkRenderWindowInteractor::New());
    renderWindowInterractor -> SetRenderWindow(renderWindow);
  }

  void interract() {
    renderWindowInterractor -> Initialize();
    renderWindowInterractor -> Render();
    renderWindowInterractor -> Start();
  }

  ~Viewer(void) {}

  // TODO
};
