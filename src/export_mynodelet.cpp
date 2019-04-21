#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <pipeline_nodelet/my_nodes.h>

PLUGINLIB_EXPORT_CLASS(pipeline_nodelet::Level1, nodelet::Nodelet);
