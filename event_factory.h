//
// Created by vincent on 13/02/24.
//

#ifndef GODOT_EVENT_FACTORY_INTERFACE_H
#define GODOT_EVENT_FACTORY_INTERFACE_H

#include "core/input/input_event.h"

#include "input_data.h"
#include "scene/main/viewport.h"

class EventFactory {

private:
	static EventFactory *singleton;

	void action_event(InputData &input_data, Viewport* viewport);
	void joy_button_event(InputData &input_data, Viewport* viewport);
	void joy_motion_event(InputData &input_data, Viewport* viewport);
	void mouse_motion_event(InputData &input_data, Viewport* viewport);

public:
	void instantiate_event(InputData &input_data, Viewport* viewport);


	static EventFactory *get_instance();
	EventFactory(EventFactory &other) = delete;
	void operator=(const EventFactory &) = delete;

	EventFactory();
};

#endif //GODOT_EVENT_FACTORY_INTERFACE_H
