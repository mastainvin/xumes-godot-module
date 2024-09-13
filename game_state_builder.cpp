//
// Created by vincent on 11/02/24.
//

#include "game_state_builder_interface.h"
#include "state_observer.h"

bool GameStateBuilderDefault::get_game_state(const Node *p_node, Dictionary *p_state) {
	bool has_properties = false;

	if (p_node->get_child_count() > 0) {
		Node* p_child = p_node->find_child("StateObserver", false);

		if (StateObserver* p_observer = dynamic_cast<StateObserver*>(p_child)) {
			Vector<String> testing_state = p_observer->get_testing_state();

			has_properties = testing_state.size() > 0;

			p_state->operator[]("__type__") = p_node->get_name();

			for(auto str : testing_state) {
				bool r_valid;
				Variant property = p_node->get(str, &r_valid);
				if (r_valid) {
					p_state->operator[](str) = property;
				}
			}
		}
	}

	bool child_has_properties = false;

	for (int i = 0; i < p_node->get_child_count(); i++){
		Node* child = p_node->get_child(i);
		Dictionary child_state;
		bool r = get_game_state(child, &child_state);
		if (r) {
			p_state->operator[](child->get_name()) = child_state;
			child_has_properties = true;
		}
	}

	return has_properties || child_has_properties;
}