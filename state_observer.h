//
// Created by vincent on 11/09/24.
//

#ifndef GODOT_OBSERVER_H
#define GODOT_OBSERVER_H

#include "scene/main/node.h"

class StateObserver : public Node {
	GDCLASS(StateObserver, Node);

public:
	void set_testing_state_string(const String &p_state);
	String get_testing_state_string() const;
	Vector<String> get_testing_state() const;
	void send_input(const Ref<InputEvent> &p_event);
	void _notification(int p_notification);

private:
	Vector<String> testing_state;
	String testing_state_string;

protected:
	static void _bind_methods();

};

#endif //GODOT_OBSERVER_H
