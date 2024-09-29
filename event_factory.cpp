//
// Created by vincent on 13/02/24.
//


#include "event_factory.h"
#include "scene/main/viewport.h"

#include <core/input/input.h>

void EventFactory::instantiate_event(InputData &input_data, Viewport* viewport) {
	switch (input_data.event_type) {
		case EventType::ACTION_EVENT: {
			action_event(input_data, viewport);
		} break;
		case EventType::JOY_MOTION_EVENT: {
			joy_motion_event(input_data, viewport);
		} break;
		case EventType::JOY_BUTTON_EVENT: {
			joy_button_event(input_data, viewport);
		} break;
		case EventType::MOUSE_MOTION_EVENT: {
			mouse_motion_event(input_data, viewport);
		}
		default: {

		}break;
	}
}

void EventFactory::action_event(InputData &input_data, Viewport* viewport) {
	Ref<InputEventAction> refEventAction;
	refEventAction.instantiate();
	refEventAction->set_action(input_data.action_name);
	refEventAction->set_pressed(input_data.action == ActionType::DO);


	if (input_data.action == ActionType::DO) {
		Input::get_singleton()->action_press(input_data.action_name);
	} else {
		Input::get_singleton()->action_release(input_data.action_name);
	}

	viewport->push_input(refEventAction);
}


void EventFactory::joy_button_event(InputData &input_data, Viewport* viewport) {
	Ref<InputEventJoypadButton> refJoyButton;
	refJoyButton.instantiate();
	refJoyButton->set_button_index(input_data.button);
	refJoyButton->set_pressure(1.0);
	refJoyButton->set_device(0);
	refJoyButton->set_pressed(input_data.action == ActionType::DO);


	if (input_data.action == ActionType::DO) {
		Input::get_singleton()->joy_button(0, input_data.button, true);
	} else {
		Input::get_singleton()->joy_button(0, input_data.button, false);
	}

	viewport->push_input(refJoyButton);
}


void EventFactory::joy_motion_event(InputData &input_data, Viewport* viewport) {
	Ref<InputEventJoypadMotion> refJoyMotion;
	refJoyMotion.instantiate();
	refJoyMotion->set_device(0);
	refJoyMotion->set_axis(input_data.axis);

	if (input_data.action == ActionType::DO) {
		refJoyMotion->set_axis_value(input_data.axis_value);
		Input::get_singleton()->set_joy_axis(0, input_data.axis, input_data.axis_value);
	} else {
		Input::get_singleton()->set_joy_axis(0, input_data.axis, 0.0f);
		refJoyMotion->set_axis_value(0.0f);
	}

	viewport->push_input(refJoyMotion);
}

void EventFactory::mouse_motion_event(InputData &input_data, Viewport* viewport) {
	viewport->warp_mouse(input_data.position);
/*
	Ref<InputEventMouseMotion> refMouseMotion;
	refMouseMotion.instantiate();
	refMouseMotion->set_device(0);
	refMouseMotion->set_position(input_data.position);

	viewport->push_input(refMouseMotion);
*/
}


EventFactory* EventFactory::singleton = nullptr;

EventFactory *EventFactory::get_instance() {
	if (singleton == nullptr) {
		singleton = new EventFactory();
	}

	return singleton;

}

EventFactory::EventFactory() = default;