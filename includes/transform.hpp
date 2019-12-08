#pragma once
#include <vector>
#include <string>
#include <memory>

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
  kind(MergeTransform), m_meshes(meshes), m_result_file_name(result_file_name), m_compute_quality(compute_quality) {}

  virtual ~MergeParams() = default;
  // TODO
};

struct TranslationParams : public Params
{
  std::vector<double> m_coords;
  std::string         m_mesh, m_result_file_name;
  bool                m_compute_quality;

  TranslationParams(std::vector<double> const& coords, std::string const& mesh, std::string const& result_file_name, bool compute_quality) :
  kind(TranslationTransform), m_coords(coords), m_mesh(mesh), m_result_file_name(result_file_name), m_compute_quality(compute_quality) {}

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
      std::shared_ptr<MergeTransform> merge_param(m_params);
      
    }
  }

  // TODO
};
