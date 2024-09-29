//
// Created by vincent on 14/02/24.
//

#include "input_handler.h"

void InputHandler::handle(Array &inputs, Viewport* viewport) {
	Dictionary input;
	std::unordered_set<InputData, InputData::HashFunction> input_set;
	InputData input_data;

	for (int i = 0; i < inputs.size() ; i++) {
		input = inputs[i];

		input_data = Translator::get_instance()->translate_input(input);
		input_set.insert(input_data);
		input_data.action = ActionType::DO;
		EventFactory::get_instance()->instantiate_event(input_data, viewport);
	}

	for (InputData input_data_pressed : pressed_inputs) {
		if (input_set.find(input_data_pressed) == input_set.end()) {
			input_data_pressed.action = ActionType::UNDO;
			EventFactory::get_instance()->instantiate_event(input_data_pressed, viewport);
		}
	}

	pressed_inputs = input_set;
}

void InputHandler::flush(Viewport* viewport) {
	for (InputData input_data_pressed : pressed_inputs) {
			input_data_pressed.action = ActionType::UNDO;
			EventFactory::get_instance()->instantiate_event(input_data_pressed, viewport);
	}
	pressed_inputs.clear();
}