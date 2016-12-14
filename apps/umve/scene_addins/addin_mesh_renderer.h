/*
 * Copyright (C) 2015, Simon Fuhrmann
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#ifndef UMVE_ADDIN_MESHES_RENDERER_HEADER
#define UMVE_ADDIN_MESHES_RENDERER_HEADER

#include <string>

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QBoxLayout>

#include "mve/mesh.h"

#include "scene_addins/mesh_list.h"
#include "scene_addins/addin_base.h"

class AddinMeshesRenderer : public AddinBase
{
    Q_OBJECT

public:
    AddinMeshesRenderer (void);
    QWidget* get_sidebar_widget (void);

    void add_mesh (std::string const& name,
        mve::TriangleMesh::Ptr mesh,
        std::string const& filename = "",
        ogl::Texture::Ptr texture = nullptr);

    void load_mesh (std::string const& filename);
    virtual void set_state (AddinState* state);

protected:
    void paint_impl (void);

protected slots:
    void matcap_cb_changed (void);

private:
    QVBoxLayout* render_meshes_box;
    QCheckBox* render_lighting_cb;
    QCheckBox* render_wireframe_cb;
    QCheckBox* render_color_cb;
    QCheckBox* render_matcap_cb;
    QComboBox* render_matcap_selector;
    QMeshList* mesh_list;
};

#endif /* UMVE_ADDIN_MESHES_RENDERER_HEADER */
