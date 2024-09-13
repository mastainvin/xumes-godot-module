//
// Created by vincent on 11/09/24.
//

#include "state_observer.h"

#include <iostream>
#include <fstream>

#include "feature_node.h"


void StateObserver::_notification(int p_notification) {

	switch(p_notification) {
		case NOTIFICATION_READY: {
			// add observer in feature node (root)
			Node* p_root = get_tree()->get_current_scene();

			if (FeatureNode* p_feature_node = dynamic_cast<FeatureNode*>(p_root)) {
				p_feature_node->add_observer(this);
			}

		} break;
		case NOTIFICATION_PREDELETE: {
		} break;
	}
}


void StateObserver::set_testing_state_string(const String &p_state) {
	ERR_THREAD_GUARD
	if (testing_state_string == p_state) {
		return;
	}

	testing_state_string = p_state;

	testing_state = p_state.split(",");
	// we don't check here if the attribute exists because they are put at runtime.
}

String StateObserver::get_testing_state_string() const {
	return testing_state_string;
}

Vector<String> StateObserver::get_testing_state() const {
	return testing_state;
}

void StateObserver::send_input(const Ref<InputEvent> &p_event) {
	_call_input(p_event);
}

void StateObserver::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_testing_state", "state"), &StateObserver::set_testing_state_string);
	ClassDB::bind_method(D_METHOD("get_testing_state"), &StateObserver::get_testing_state_string);

	ADD_GROUP("Testing", "testing_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "testing_state", PROPERTY_HINT_MULTILINE_TEXT), "set_testing_state", "get_testing_state");
}