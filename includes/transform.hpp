#pragma once
#include <vector>
#include <string>
#include <memory>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetMapper.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkXMLUnstructuredGridWriter.h>

enum TransformType
{
  MergeTransform, TranslationTransform
};

struct Params
{
  virtual ~Params(void) = default;

  TransformType kind;
  // TODO
};

struct MergeParams : public Params
{
  std::vector<std::string> m_meshes;
  std::string              m_result_file_name;
  bool                     m_compute_quality;

  MergeParams(std::vector<std::string> const& meshes, std::string const& result_file_name, bool compute_quality) :
  m_meshes(meshes), m_result_file_name(result_file_name), m_compute_quality(compute_quality) {
    kind = MergeTransform;
  }

  virtual ~MergeParams() = default;
  // TODO
};

struct TranslationParams : public Params
{
  std::vector<double> m_coords;
  std::string         m_mesh, m_result_file_name;
  bool                m_compute_quality;

  TranslationParams(std::vector<double> const& coords, std::string const& mesh, std::string const& result_file_name, bool compute_quality) :
  m_coords(coords), m_mesh(mesh), m_result_file_name(result_file_name), m_compute_quality(compute_quality) {
    kind = TranslationTransform;
  }

  virtual ~TranslationParams() = default;
  // TODO
};

class Transform
{
  std::shared_ptr<Params> m_params;
public:
  Transform(std::shared_ptr<Params> const& params) : m_params(params) {}
  Transform(void) {}
  ~Transform(void) {}

  void operator()() {
    if (m_params -> kind == MergeTransform) {
      std::shared_ptr<MergeParams> merge_param(dynamic_cast<MergeParams*>(m_params.get()));
      
    } else if(m_params -> kind == TranslationTransform) {
      std::shared_ptr<TranslationParams> translation_param(dynamic_cast<TranslationParams*>(m_params.get()));
      std::string mesh(translation_param -> m_mesh);

      /* Matrix Transform */


      auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>(vtkXMLUnstructuredGridReader::New());
      reader -> SetFileName(mesh.c_str());
      reader -> Update();

      auto mesh_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      mesh_mapper -> SetInputConnection(reader -> GetOutputPort());

      auto actor = vtkSmartPointer<vtkActor>(vtkActor::New());
      actor -> SetMapper(mesh_mapper);

      auto transform = vtkSmartPointer<vtkTransform>::New();
      double *data = translation_param->m_coords.data();
      transform -> Translate(translation_param->m_coords.data());

      auto transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
      transformFilter -> SetInputConnection(mesh_mapper -> GetOutputPort());
      transformFilter -> SetTransform(transform);

      auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
      writer -> SetInputData(transformFilter -> GetOutput());
      writer -> SetFileName(translation_param -> m_result_file_name . c_str());
      writer -> Write();
    }
  }

  // TODO
};
