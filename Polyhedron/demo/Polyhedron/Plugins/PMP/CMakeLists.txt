include( polyhedron_demo_macros )
if(EIGEN3_FOUND)

  polyhedron_demo_plugin(jet_fitting_plugin Jet_fitting_plugin)
  target_link_libraries(jet_fitting_plugin PUBLIC scene_polyhedron_item  scene_surface_mesh_item scene_polylines_item)

else(EIGEN3_FOUND)
  message(STATUS "NOTICE: Eigen 3.1 (or greater) was not found. Jet fitting plugin will not be available.")
endif(EIGEN3_FOUND)

if(EIGEN3_FOUND)
  if("${EIGEN3_VERSION}" VERSION_GREATER "3.1.90")

    qt5_wrap_ui( hole_fillingUI_FILES Hole_filling_widget.ui)
    polyhedron_demo_plugin(hole_filling_plugin Hole_filling_plugin ${hole_fillingUI_FILES})
    target_link_libraries(hole_filling_plugin PUBLIC scene_polyhedron_item scene_polylines_item scene_polyhedron_selection_item)

    qt5_wrap_ui( hole_fillingUI_FILES Hole_filling_widget.ui)
    polyhedron_demo_plugin(hole_filling_sm_plugin Hole_filling_plugin ${hole_fillingUI_FILES})
    target_link_libraries(hole_filling_sm_plugin PUBLIC scene_surface_mesh_item scene_polylines_item scene_surface_mesh_selection_item)
    target_compile_definitions(hole_filling_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

    qt5_wrap_ui( fairingUI_FILES Fairing_widget.ui)
    polyhedron_demo_plugin(fairing_plugin Fairing_plugin ${fairingUI_FILES})
    target_link_libraries(fairing_plugin PUBLIC scene_polyhedron_selection_item)

    polyhedron_demo_plugin(fairing_sm_plugin Fairing_plugin ${fairingUI_FILES})
    target_link_libraries(fairing_sm_plugin PUBLIC scene_surface_mesh_selection_item)
    target_compile_definitions(fairing_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

    polyhedron_demo_plugin(hole_filling_polyline_plugin Hole_filling_polyline_plugin)
    target_link_libraries(hole_filling_polyline_plugin PUBLIC scene_surface_mesh_item scene_polyhedron_item scene_polylines_item)
    
    qt5_wrap_ui( Mean_curvature_flow_skeleton_pluginUI_FILES  Mean_curvature_flow_skeleton_plugin.ui)
    polyhedron_demo_plugin(mean_curvature_flow_skeleton_plugin Mean_curvature_flow_skeleton_plugin ${Mean_curvature_flow_skeleton_pluginUI_FILES})
    target_link_libraries(mean_curvature_flow_skeleton_plugin PUBLIC
        scene_polyhedron_item 
        scene_points_with_normal_item
        scene_polylines_item
        scene_mcf_poly_item
        demo_framework)
        
    qt5_wrap_ui( Mean_curvature_flow_skeleton_pluginUI_FILES  Mean_curvature_flow_skeleton_plugin.ui)
    polyhedron_demo_plugin(mean_curvature_flow_skeleton_sm_plugin Mean_curvature_flow_skeleton_plugin ${Mean_curvature_flow_skeleton_pluginUI_FILES})
    target_link_libraries(mean_curvature_flow_skeleton_sm_plugin
      PUBLIC
        scene_surface_mesh_item
        scene_points_with_normal_item
        scene_polylines_item
        scene_mcf_sm_item
        demo_framework)
    target_compile_definitions(mean_curvature_flow_skeleton_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )
  else()
    message(STATUS "NOTICE: The hole filling and fairing plugins require Eigen 3.2 (or higher) and will not be available.")
  endif()
else()
  message(STATUS "NOTICE: The hole filling and fairing plugins require Eigen 3.2 (or higher) and will not be available.")
endif()


polyhedron_demo_plugin(orient_soup_plugin Orient_soup_plugin)
target_link_libraries(orient_soup_plugin PUBLIC scene_polygon_soup_item scene_polyhedron_item scene_surface_mesh_item scene_polylines_item scene_points_with_normal_item)


polyhedron_demo_plugin(inside_out_plugin Inside_out_plugin)
target_link_libraries(inside_out_plugin PUBLIC scene_polyhedron_item scene_surface_mesh_item scene_polygon_soup_item)

polyhedron_demo_plugin(join_and_split_polyhedra_plugin Join_and_split_polyhedra_plugin)
target_link_libraries(join_and_split_polyhedra_plugin PUBLIC scene_polyhedron_item scene_polyhedron_selection_item)

polyhedron_demo_plugin(join_and_split_sm_plugin Join_and_split_polyhedra_plugin)
target_link_libraries(join_and_split_sm_plugin PUBLIC scene_surface_mesh_item scene_surface_mesh_selection_item)
target_compile_definitions(join_and_split_sm_plugin  PUBLIC "-DUSE_SURFACE_MESH")



qt5_wrap_ui( point_inside_polyhedronUI_FILES Point_inside_polyhedron_widget.ui)
polyhedron_demo_plugin(point_inside_polyhedron_plugin Point_inside_polyhedron_plugin ${point_inside_polyhedronUI_FILES})
target_link_libraries(point_inside_polyhedron_plugin PUBLIC scene_polyhedron_item scene_surface_mesh_item scene_points_with_normal_item)


qt5_wrap_ui( polyhedron_slicerUI_FILES Polyhedron_slicer_widget.ui)
polyhedron_demo_plugin(polyhedron_slicer_plugin Polyhedron_slicer_plugin ${polyhedron_slicerUI_FILES})
target_link_libraries(polyhedron_slicer_plugin PUBLIC scene_polyhedron_item scene_surface_mesh_item scene_basic_objects scene_polylines_item)

polyhedron_demo_plugin(polyhedron_stitching_plugin Polyhedron_stitching_plugin)
target_link_libraries(polyhedron_stitching_plugin PUBLIC scene_polyhedron_item scene_surface_mesh_item scene_polylines_item)

qt5_wrap_ui( selectionUI_FILES Selection_widget.ui)
add_library(selection_plugin SHARED Selection_plugin.cpp ${selectionUI_FILES})
#polyhedron_demo_plugin(selection_plugin Selection_plugin ${selectionUI_FILES})
target_link_libraries(selection_plugin PUBLIC scene_polyhedron_selection_item scene_points_with_normal_item scene_polylines_item)

qt5_wrap_ui( selectionUI_FILES Selection_widget.ui)
add_library(selection_sm_plugin SHARED Selection_plugin.cpp ${selectionUI_FILES})
#polyhedron_demo_plugin(selection_sm_plugin Selection_plugin ${selectionUI_FILES})
target_link_libraries(selection_sm_plugin PUBLIC scene_surface_mesh_selection_item scene_points_with_normal_item scene_polylines_item)
target_compile_definitions(selection_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

polyhedron_demo_plugin(self_intersection_plugin Self_intersection_plugin)
target_link_libraries(self_intersection_plugin PUBLIC scene_polyhedron_item scene_polyhedron_selection_item )

polyhedron_demo_plugin(self_intersection_sm_plugin Self_intersection_plugin)
target_link_libraries(self_intersection_sm_plugin PUBLIC scene_surface_mesh_selection_item scene_surface_mesh_item)
target_compile_definitions(self_intersection_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

polyhedron_demo_plugin(triangulate_facets_plugin Triangulate_facets_plugin)
target_link_libraries(triangulate_facets_plugin PUBLIC scene_polyhedron_item scene_surface_mesh_item)

polyhedron_demo_plugin(corefinement_plugin Corefinement_plugin)
target_link_libraries(corefinement_plugin PUBLIC scene_surface_mesh_item scene_polyhedron_item)

polyhedron_demo_plugin(surface_intersection_plugin Surface_intersection_plugin)
target_link_libraries(surface_intersection_plugin PUBLIC scene_polyhedron_item scene_polylines_item scene_points_with_normal_item)

polyhedron_demo_plugin(surface_intersection_sm_plugin Surface_intersection_plugin)
target_link_libraries(surface_intersection_sm_plugin PUBLIC scene_surface_mesh_item scene_polylines_item scene_points_with_normal_item)
target_compile_definitions(surface_intersection_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

polyhedron_demo_plugin(repair_polyhedron_plugin Repair_polyhedron_plugin)
target_link_libraries(repair_polyhedron_plugin PUBLIC scene_surface_mesh_item scene_polyhedron_item)

qt5_wrap_ui( isotropicRemeshingUI_FILES Isotropic_remeshing_dialog.ui)
polyhedron_demo_plugin(isotropic_remeshing_plugin Isotropic_remeshing_plugin  ${isotropicRemeshingUI_FILES})
target_link_libraries(isotropic_remeshing_plugin PUBLIC scene_polyhedron_item scene_polyhedron_selection_item)

polyhedron_demo_plugin(isotropic_remeshing_sm_plugin Isotropic_remeshing_plugin  ${isotropicRemeshingUI_FILES})
target_link_libraries(isotropic_remeshing_sm_plugin PUBLIC scene_surface_mesh_item scene_surface_mesh_selection_item)
target_compile_definitions(isotropic_remeshing_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

if(TBB_FOUND)
  CGAL_target_use_TBB(isotropic_remeshing_sm_plugin)
  CGAL_target_use_TBB(isotropic_remeshing_plugin)
endif()

polyhedron_demo_plugin(distance_plugin Distance_plugin)
target_link_libraries(distance_plugin PUBLIC scene_polyhedron_item scene_color_ramp)

if(TBB_FOUND)
  CGAL_target_use_TBB(distance_plugin)
endif()


polyhedron_demo_plugin(detect_sharp_edges_plugin Detect_sharp_edges_plugin)
target_link_libraries(detect_sharp_edges_plugin PUBLIC scene_polyhedron_item)

polyhedron_demo_plugin(detect_sharp_edges_sm_plugin Detect_sharp_edges_plugin)
target_link_libraries(detect_sharp_edges_sm_plugin PUBLIC scene_surface_mesh_item)
target_compile_definitions(detect_sharp_edges_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

polyhedron_demo_plugin(distance_sm_plugin Distance_plugin)
target_link_libraries(distance_sm_plugin PUBLIC scene_surface_mesh_item  scene_color_ramp)
target_compile_definitions(distance_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

qt5_wrap_ui( randomPerturbationUI_FILES Random_perturbation_dialog.ui)
polyhedron_demo_plugin(random_perturbation_plugin Random_perturbation_plugin ${randomPerturbationUI_FILES})
target_link_libraries(random_perturbation_plugin PUBLIC scene_polyhedron_item scene_polyhedron_selection_item)

polyhedron_demo_plugin(degenerated_faces_poly_plugin Degenerated_faces_plugin)
target_link_libraries(degenerated_faces_poly_plugin PUBLIC scene_polyhedron_item scene_polyhedron_selection_item)

polyhedron_demo_plugin(degenerated_faces_sm_plugin Degenerated_faces_plugin)
target_link_libraries(degenerated_faces_sm_plugin PUBLIC scene_surface_mesh_item scene_surface_mesh_selection_item)
target_compile_definitions(degenerated_faces_sm_plugin PUBLIC "-DUSE_SURFACE_MESH" )

