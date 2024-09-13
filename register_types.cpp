//
// Created by vincent on 10/02/24.
//

#include "register_types.h"

#include "core/object/class_db.h"

#include "feature_node.h"
#include "state_observer.h"

#include "xumes_communication_thread.h"


void initialize_xumes_module(ModuleInitializationLevel p_level) {

	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<FeatureNode>();
		ClassDB::register_class<StateObserver>();
	}

	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		XumesCommunicationThread::get_singleton()->init();
	}

}

void uninitialize_xumes_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		XumesCommunicationThread::get_singleton()->finish();
	}
}
